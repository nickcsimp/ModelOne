//
// Created by Nicholas Simpson on 20/10/2021.
//

#include "System.h"
using namespace std;

System::System(int family_count, int monomer_type_count, vector<vector<int>> monomer_count, Polymer * initial_template){
    polymer_index=0;
    conglomerate_index=0;

    number_of_families = family_count;
    number_of_monomer_types = monomer_type_count;
    number_of_monomers = monomer_count;

    initial_template->setIndex(++polymer_index);
    polymers.push_back(initial_template);
    Conglomerate * c = new Conglomerate(initial_template, number_of_families, number_of_monomer_types);
    c->setIndex(++conglomerate_index);
    conglomerates.push_back(c);
}

vector<vector<int>> System::getMonomers(){
    return number_of_monomers;
}

vector<Dimer *> System::getDimers(){
    return dimers;
}

void System::changeMonomerCount(int family, int type, int increase){
    if(number_of_monomers[family][type]+increase>=0) {
        number_of_monomers[family][type] = number_of_monomers[family][type] + increase;
    } else {
        throw invalid_argument("Monomer count can't be below 0.");
    }
}


void System::addDimer(int family, int familyTwo, int type){
    Dimer * d = new Dimer(type, family, familyTwo);
    dimers.push_back(d);
    number_of_monomers[type][family]--;
    number_of_monomers[type][familyTwo]--;
}

void System:: removeDimer(int index){
    int type_of_monomer = dimers[index]->getType();
    vector<int> families = dimers[index]->getFamilies();
    for(auto & family : families){
        number_of_monomers[type_of_monomer][family]++;
    }
    dimers.erase(dimers.begin()+index);
}


vector<Polymer *> System::getPolymers(){
    return polymers;
}

vector<Conglomerate *> System::getConglomerates(){
    return conglomerates;
}

void System::addPolymer(int family, int type){
    vector<int> seq;
    seq.push_back(type);
    Polymer * p = new Polymer(family, seq);
    p->setIndex(++polymer_index);
    polymers.push_back(p);
    changeMonomerCount(family, type, -1);
}

void System::removePolymer(Polymer * p){ //TODO test
    int number = -1;
    for(int i=0; i<polymers.size(); i++){
        if(*p==*polymers[i]){
            number = i;
        }
    }
    if(number != -1){
        polymers.erase(polymers.begin()+number);
    }
}

void System::removeConglomerate(Conglomerate * c){ //TODO test
    int number = -1;
    for(int i=0; i<conglomerates.size(); i++){
        if(*c==*conglomerates[i]){
            number = i;
        }
    }
    if(number != -1){

        conglomerates.erase(conglomerates.begin()+number);
    }
}

void System::addConglomerate(Conglomerate * c){
    c->setIndex(++conglomerate_index);
    conglomerates.push_back(c);
}

void System::joinPolymers(Polymer *pOne, Polymer * pTwo){ //TODO test
    pOne->addPolymer(pTwo, five_prime);
    removePolymer(pTwo);
}



void System::updateRates() { //TODO test
    specific_rates.clear();
    total_rate = 0;
    number_of_available_sites.clear();
    for (auto &elem: conglomerates) {
        double rate = 0;
        elem->update();

        rate = elem->getTailUnbindingSites() * template_unbind_rate;
        rate = elem->getHeadUnbindingSites() * template_unbind_rate;
        rate = rate + elem->getTailBindingSites() * template_bind_rate;
        rate = rate + elem->getHeadBindingSites() * template_bind_rate;
        rate = rate + elem->getValidNeighboursBinding() * backbone_bind_rate;
        rate = rate + elem->getValidNeighboursUnbinding() * backbone_unbind_rate;

        total_rate = total_rate + rate;
        specific_rates.push_back(rate);

        vector<vector<int>> bonds = elem->getAvailableTemplateBonds();
        number_of_available_sites.push_back(bonds);
    }
    number_of_available_sites.push_back(number_of_monomers);

    double rate = 0;
    number_of_connections.clear();

    for (int i = 0; i < number_of_monomer_types; i++) {
        vector<int> family;
        for (int j = 0; j < number_of_families; j++) {
            family.push_back(0);
        }
        number_of_connections.push_back(family);
    }


    for (int i = 0; i < number_of_available_sites.size() - 1; i++) {
        for (int j = i + 1; j < number_of_available_sites.size(); j++) {
            for (int k = 0; k < number_of_monomer_types; k++) {
                for (int l = 0; l < number_of_families; l++) {
                    for (int m = 0; m < number_of_families; m++) {
                        if(m!=l){
                            number_of_connections[k][l] = number_of_connections[k][l] +
                                                          number_of_available_sites[i][k][l] * number_of_available_sites[j][k][m];
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < number_of_monomer_types; i++) {
        for (int j = 0; j < number_of_families; j++) {
            for(int k=0; k<number_of_families; k++){
                if(j!=k) {
                    number_of_connections[i][j] =
                            number_of_connections[i][j] + (number_of_monomers[i][j]) * number_of_monomers[i][k];
                }
            }
        }
    }



    for (int i = 0; i < number_of_monomer_types; i++) {
        for (int j = 0; j < number_of_families; j++) {
            rate = rate + number_of_connections[i][j]*template_bind_rate/2; //We double count every connection
        }
    }

    rate = rate + dimers.size() * template_unbind_rate;

    total_rate = total_rate + rate;
    specific_rates.push_back(rate);
}

double System::getTotalRate(){
    return total_rate;
}

vector<double> System::getSpecificRates(){
    return specific_rates;
}

tuple<vector<tuple<Polymer *, int>>, vector<tuple<Polymer *, int>>> System::headOrTail(vector<tuple<Polymer *, int>> input){
    tuple<vector<tuple<Polymer *, int>>, vector<tuple<Polymer *, int>>> output;
    vector<tuple<Polymer *, int>> heads;
    vector<tuple<Polymer *, int>> tails;
    for(int i=0; i< input.size(); i++){
        if(get<0>(input[i])->getLength() == get<1>(input[i])+1){
            heads.push_back(input[i]);
        } else {
            tails.push_back(input[i]);
        }
    }
    output = make_tuple(heads, tails);
    return output;
}

bool System::chooseExternalTransition() { //Todo test

    vector<vector<vector<tuple<vector<tuple<Polymer *, int>>, vector<tuple<Polymer *, int>>>>>> all_sites;
    //This is conglomerate->type->family-><head sites><non-head sites>

    cout << "Number of conglomerates:" << endl;
    cout << conglomerates.size() << endl << endl;
    //loop through conglomerates
    for(auto & cong : conglomerates){
        vector<vector<tuple<vector<tuple<Polymer *, int>>, vector<tuple<Polymer *, int>>>>> cong_sites;
        vector<tuple<vector<tuple<Polymer *, int>>, vector<tuple<Polymer *, int>>>> type_sites;
        //Loop through types
        for(int type = 0; type<number_of_monomer_types; type++){
            //loop through families
            for(int fam = 0; fam<number_of_families; fam++){
                //Get all possible sites on this conglomerate with this type and family
                vector<tuple<Polymer *, int>> tup = cong->getPossibleSites(type, fam);
                tuple<vector<tuple<Polymer *, int>>, vector<tuple<Polymer *, int>>> tups = headOrTail(tup);
                type_sites.push_back(tups);
            }
            //Add the types to the cong list
            cong_sites.push_back(type_sites);
        }
        //add the congs to the site list
        all_sites.push_back(cong_sites);
    }
    cout << "All sites heads:" << endl;
    for(auto & cong :all_sites){
        for(auto & type : cong){
            for(int i=0; i< type.size(); i++){
                cout << get<0>(type[i]).size() << ' ';
            }
            cout << endl;
        }
    }
    cout << endl;
    cout << "All sites tails:" << endl;
    for(auto & cong :all_sites){
        for(auto & type : cong){
            for(int i=0; i< type.size(); i++){
                cout << get<1>(type[i]).size() << ' ';
            }
            cout << endl;
        }
    }
    //We now have a 4 dimensional array with all possible binding sites on all conglomerates

    //We want to find which monomers can be chosen to bind
    vector<vector<bool>> site_exists;
    for(int type = 0; type<number_of_monomer_types; type++){
        vector<bool> type_exists;
        for(int fam = 0; fam<number_of_families; fam++){
            //initialise a boolean array with falses
            type_exists.push_back(false);
        }
        site_exists.push_back(type_exists);
    }

    //Loop through each dimension of the site lists
    for(int cong = 0; cong< all_sites.size(); cong++){
        for(int type =0; type< all_sites[cong].size(); type++){
            for(int fam = 0; fam<all_sites[cong][type].size(); fam++){
                if(get<0>(all_sites[cong][type][fam]).size()>0 || get<1>(all_sites[cong][type][fam]).size()>0){
                    //if a site is in the list then this type and family of monomer can be chosen
                    site_exists[type][fam] = true;
                }
            }
        }
    }


    //Also loop monomers to see if they are available

    for(int type =0; type< number_of_monomer_types; type++){
        for(int fam = 0; fam<number_of_families; fam++){
            if(number_of_monomers[type][fam]!=0){
                //if a monomer of this type and family is free then the site can be bound
                site_exists[type][fam] = true;
            }
        }
    }

    cout << "Site exists: " << endl;
    for(auto & type : site_exists){
        for(bool fam : type){
            cout << fam << ' ';
        }
        cout << endl;
    }
    cout << endl;

    //We then need to check that two of the same type are available on different families
    vector<bool> type_transition_possible;

    for(int type =0; type< number_of_monomer_types; type++){
        type_transition_possible.push_back(false);
    }

    for(int type =0; type< number_of_monomer_types; type++){
        for(int fam = 0; fam<number_of_families-1; fam++){
            if(site_exists[type][fam]){
                //This family and type exists, check other families
                for(int family = fam +1; family<number_of_families; family++){
                    if(site_exists[type][family]) {
                        type_transition_possible[type] = true;
                    }
                }
            }
        }
    }

    cout << "Type transition possible:" << endl;
    for(bool fam : type_transition_possible){
        cout << fam << ' ';
    }
    cout << endl;


    //Check that a transition is possible
    bool there_is_a_possible_transition = false;

    for(int type = 0; type<number_of_monomer_types; type++){
        if(type_transition_possible[type]){
            there_is_a_possible_transition = true;
        }
    }


    if(!there_is_a_possible_transition){
        cout << "No possible external transition" << endl;
    }



    vector<tuple<int, int>> number_of_type_sites;

    for(int i=0; i<number_of_monomer_types; i++){
        if(type_transition_possible[i]){
            int head = 0;
            int tail = 0;
            for(int j=0; j<number_of_families; j++){
                head += number_of_monomers[i][j];
                for(int k=0; k<conglomerates.size(); k++){
                    head += get<0>(all_sites[k][i][j]).size();
                    tail += get<1>(all_sites[k][i][j]).size();
                }
            }
            number_of_type_sites.push_back(make_tuple(head, tail));
        } else {
            number_of_type_sites.push_back(make_tuple(0, 0));
        }
    }

    cout << "Number of type sites heads" << endl;
    for(auto & number : number_of_type_sites){
        cout << get<0>(number) << ' ';
    }
    cout << endl;

    cout << "Number of type sites tails" << endl;
    for(auto & number : number_of_type_sites){
        cout << get<1>(number) << ' ';
    }
    cout << endl;

    vector<int> type_rates;
    for(auto & type : number_of_type_sites){
        int rate = (get<0>(type)*template_head_bind_rate) + (get<1>(type)*template_tail_bind_rate);
    }


    random_device rd;
    mt19937 gen(rd());

    int current_number = 0;
    double rand = gen();
    double rando = gen.max();

    double total = 0;
    int chosen_type = -1;
    for(int i=0; i<number_of_type_sites.size(); i++){
        total += number_of_type_sites[i];
    }

    cout << "Total: " << total << endl;

    for(int i=0; i<number_of_type_sites.size(); i++){
        if(rand/rando <= number_of_type_sites[current_number]/total){
            chosen_type = i;
            break;
        }
        current_number ++;
    }

    cout << "Chosen type: "<< chosen_type << endl << endl;


    int chosen_family_one = -1;
    int chosen_family_two = -1;

    //Now need to choose families
    if(number_of_families==2){
        if(site_exists[chosen_type][0] && site_exists[chosen_type][1]) {
            chosen_family_one = 0;
            chosen_family_two = 1;
        }
        cout << "Chosen family one: "<< chosen_family_one << endl << endl;
        cout << "Chosen family two: "<< chosen_family_two << endl << endl;
    } else {
        vector<int> number_of_fam_sites;

        for(int i=0; i<number_of_families; i++){
            if(site_exists[chosen_type][i]){
                int count = 0;
                count += number_of_monomers[chosen_type][i];
                for(int k=0; k<conglomerates.size(); k++){
                    count += all_sites[k][chosen_type][i].size();
                }
                number_of_fam_sites.push_back(count);
            } else {
                number_of_fam_sites.push_back(0);
            }
        }
        cout << 9 << endl;
        current_number = 0;
        rand = gen();
        rando = gen.max();

        total = 0;

        for(int i=0; i<number_of_fam_sites.size(); i++){
            total += number_of_fam_sites[i];
        }

        for(int i=0; i<number_of_fam_sites.size(); i++){
            if(rand/rando <= number_of_fam_sites[current_number]/total){
                chosen_family_one = i;
                break;
            }
            current_number ++;
        }
        cout << 10 << endl;

        current_number = 0;
        rand = gen();
        rando = gen.max();

        total = 0;

        for(int i=0; i<number_of_fam_sites.size(); i++){
            if(i!=chosen_family_one){
                total += number_of_fam_sites[i];
            }
        }

        for(int i=0; i<number_of_fam_sites.size(); i++) {
            if (i != chosen_family_one) {
                if (rand / rando <= number_of_fam_sites[current_number] / total) {
                    chosen_family_two = i;
                    break;
                }
            }
            current_number++;
        }
        cout << 11 << endl;

    }

    int chosen_conglomerate_one = -1;
    int chosen_conglomerate_two = -1;

    bool first_is_pool = false;
    bool second_is_pool = false;

    current_number = 0;
    rand = gen();
    rando = gen.max();

    total = 0;

    vector<int> number_of_cong_sites;

    for(int i=0; i<conglomerates.size(); i++){
        number_of_cong_sites.push_back(all_sites[i][chosen_type][chosen_family_one].size());
    }

    number_of_cong_sites.push_back(number_of_monomers[chosen_type][chosen_family_one]);

    cout << "Number of cong sites one" << endl;
    for(auto & cong : number_of_cong_sites){
        cout << cong << ' ';
    }
    cout << endl;

    for(int i=0; i<number_of_cong_sites.size(); i++){
        total += number_of_cong_sites[i];
    }


    for(int i=0; i<number_of_cong_sites.size(); i++) {
        current_number+=number_of_cong_sites[i];
        if (rand / rando <= current_number / total) {
            chosen_conglomerate_one = i;
            break;
        }
    }
    cout << "Chosen conglomerate one: " << chosen_conglomerate_one  << endl << endl;



    if(chosen_conglomerate_one == number_of_cong_sites.size()-1){
        first_is_pool=true;
    }

    current_number = 0;
    rand = gen();
    rando = gen.max();

    total = 0;
    number_of_cong_sites.clear();
    if(first_is_pool){
        for(int i=0; i<conglomerates.size(); i++){
            number_of_cong_sites.push_back(all_sites[i][chosen_type][chosen_family_two].size());
        }

        number_of_cong_sites.push_back(number_of_monomers[chosen_type][chosen_family_two]);
    } else {
        for(int i=0; i<conglomerates.size(); i++){
            if(i==chosen_conglomerate_one){
                number_of_cong_sites.push_back(0);
            } else {
                number_of_cong_sites.push_back(all_sites[i][chosen_type][chosen_family_two].size());
            }
        }

        number_of_cong_sites.push_back(number_of_monomers[chosen_type][chosen_family_two]);
    }

    cout << "Number of cong sites two" << endl;
    for(auto & cong : number_of_cong_sites){
        cout << cong << ' ';
    }
    cout << endl;

    for(int i=0; i<number_of_cong_sites.size(); i++){
        total += number_of_cong_sites[i];
    }

    for(int i=0; i<number_of_cong_sites.size(); i++) {
        if (rand / rando <= number_of_cong_sites[current_number] / total) {
            chosen_conglomerate_two = i;
            break;
        }
        current_number++;
    }

    if(chosen_conglomerate_two==number_of_cong_sites.size()-1){
        second_is_pool = true;
    }

    cout << "Chosen conglomerate two: " << chosen_conglomerate_two  << endl << endl;

    tuple<Polymer *, int> chosen_tuple_one;
    tuple<Polymer *, int> chosen_tuple_two;

    if(first_is_pool && second_is_pool){
        //Form dimer
        addDimer(chosen_family_one, chosen_family_two, chosen_type);
        return true;
    }
    cout << 16 << endl;
    if(first_is_pool){
        cout << 16.1 << endl;
        //Make a polymer with first monomer
        Polymer * p = new Polymer(chosen_family_one, {chosen_type});
        chosen_tuple_one = make_tuple(p, 0);
        p->setIndex(++polymer_index);
        polymers.push_back(p);
        cout << 17 << endl;
    } else {
        cout << 16.2 << endl;
        current_number = 0;
        rand = gen();
        rando = gen.max();

        total = 0;

        vector<tuple<Polymer *, int>> number_of_tuples = all_sites[chosen_conglomerate_one][chosen_type][chosen_family_one];

        total = number_of_tuples.size();

        for(int i=0; i<number_of_tuples.size(); i++) {
            current_number++;
            if (rand / rando <= current_number / total) {
                chosen_tuple_one = number_of_tuples[i];
                break;
            }
        }
        cout << 18 << endl;
    }

    if(second_is_pool){
        //Make a polymer with second monomer
        Polymer * p = new Polymer(chosen_family_two, {chosen_type});
        chosen_tuple_two = make_tuple(p, 0);
        p->setIndex(++polymer_index);
        polymers.push_back(p);
        cout << 19 << endl;
    } else {

        current_number = 0;
        rand = gen();
        rando = gen.max();

        total = 0;

        vector<tuple<Polymer *, int>> number_of_tuples = all_sites[chosen_conglomerate_two][chosen_type][chosen_family_two];

        total = number_of_tuples.size();

        for(int i=0; i<number_of_tuples.size(); i++) {
            current_number++;
            if (rand / rando <= current_number / total) {
                chosen_tuple_two = number_of_tuples[i];
                break;
            }
        }
        cout << 20 << endl;
    }

    if(first_is_pool){
        conglomerates[chosen_conglomerate_two]->addConnection(new Connection(chosen_tuple_one, chosen_tuple_two));
        number_of_monomers[chosen_type][chosen_family_one]--;
    } else if(second_is_pool){
        conglomerates[chosen_conglomerate_one]->addConnection(new Connection(chosen_tuple_one, chosen_tuple_two));
        number_of_monomers[chosen_type][chosen_family_two]--;
    } else {
        conglomerates[chosen_conglomerate_one]->addConnection(new Connection(chosen_tuple_one, chosen_tuple_two));
        conglomerates.erase(conglomerates.begin()+chosen_conglomerate_two);
    }













/*
    //Ignore these
        //unconnected neighbours vector<UnconnectedNeighbours *>
        //connected neighbours vector<ConnectedNeighbours *>
        //Leading edges vector<Connection *>
        //Lagging edges vector<>

    cout << "External transition chosen." << endl;
    int total = 0;

    random_device rd;
    mt19937 gen(rd());

    double current_number = 0;
    double rand = gen();
    double rando = gen.max();
    int chosen_monomer[2] = {-1, -1};
    bool is_broken = false;

    vector<vector<int>> total_number_of_sites;
    for(int i=0; i<number_of_monomer_types; i++) {
        vector<int> type;
        for (int j = 0; j < number_of_families; j++) {
            type.push_back(0);
        }
        total_number_of_sites.push_back(type);
    }


    for(auto & cong : number_of_available_sites){
        for(int i=0; i<number_of_monomer_types; i++) {
            for (int j = 0; j < number_of_families; j++) {
                total_number_of_sites[i][j] += cong[i][j];
                total += cong[i][j];
            }
        }
    }

    //Choose dimer break or template bond form
    int dimers_and_sites = total+dimers.size();
    if(rand/rando <= dimers.size()/dimers_and_sites){
        cout << "Dimer break chosen." << endl;
        //choose a dimer to break
        rand = gen();
        rando = gen.max();

        for(int i=0; i<dimers.size(); i++){
            current_number ++;
            if(rand/rando <= i/dimers.size()){
                removeDimer(i);
            }
        }
        return true;
    }

    cout << "Template bond chosen." << endl;

    current_number = 0;
    rand = gen();
    rando = gen.max();

    for(int i=0; i<number_of_monomer_types; i++){
        for(int j=0; j<number_of_families; j++){
            current_number += total_number_of_sites[i][j];
            if(rand/rando <= current_number/total){
                chosen_monomer[0] = i;
                chosen_monomer[1] = j;
                is_broken = true;
                break;
            }
        }
        if(is_broken){
            break;
        }
    }


    if(chosen_monomer[0]<0 || chosen_monomer[1]<0){
        cout << "random numbers gone wild 2" << endl;
        return false;
    }

    int second_chosen_monomer[2] = {-1, -1};

    total = 0;
    current_number = 0;
    rand = gen();
    rando = gen.max();

    for(int i=0; i<number_of_families; i++) {
        if (i != chosen_monomer[1]) {
              total = total + total_number_of_sites[chosen_monomer[0]][i];
        }
    }

    for(int i=0; i<number_of_families; i++) {
        if (i != chosen_monomer[1] ) {
            current_number += total_number_of_sites[chosen_monomer[0]][i];
            if (rand/rando <= current_number / total) {
                second_chosen_monomer[0] = chosen_monomer[0];
                second_chosen_monomer[1] = i;
                break;
            }
        }
    }


    if(second_chosen_monomer[0]<0 || second_chosen_monomer[1]<0){
        cout << "random numbers gone wild 3" << endl;
        return false;
    }

    current_number = 0;
    rand = gen();
    rando = gen.max();

    total = 0;

    for(auto & cong : number_of_available_sites){
        total = total + cong[chosen_monomer[0]][chosen_monomer[1]];
    }

    int chosen_conglomerate = -1;
    for(int i=0; i<number_of_available_sites.size(); i++){
        current_number += number_of_available_sites[i][chosen_monomer[0]][chosen_monomer[1]];
        if(rand/rando<=current_number/total){
            chosen_conglomerate = i;
            break;
        }
    }

    if(chosen_conglomerate<0){
        cout << "random numbers gone wild 4" << endl;
        return false;
    }

    bool first_is_pool = false;

    if(chosen_conglomerate==number_of_available_sites.size()-1){
        first_is_pool = true;
    }

    vector<tuple<Polymer*, int>> possible_sites_one;
    vector<tuple<Polymer*, int>> possible_sites_two;
    current_number = 0;

    rand = gen();
    rando = gen.max();

    total = 0;

    int second_chosen_conglomerate = -1;

    if(first_is_pool){
        for(int i=0; i<number_of_available_sites.size(); i++){
            total = total + number_of_available_sites[i][second_chosen_monomer[0]][second_chosen_monomer[1]];
        }


        for (int i = 0; i < number_of_available_sites.size(); i++) {
            current_number += number_of_available_sites[i][second_chosen_monomer[0]][second_chosen_monomer[1]];
            if (rand / rando <= current_number / total) {
                second_chosen_conglomerate = i;
                break;
            }
        }

    } else {
        for(int i=0; i<number_of_available_sites.size(); i++){
            if (i != chosen_conglomerate) {
                total = total + number_of_available_sites[i][second_chosen_monomer[0]][second_chosen_monomer[1]];
            }
        }

        for (int i = 0; i < number_of_available_sites.size(); i++) {
            if (i != chosen_conglomerate) {
                current_number += number_of_available_sites[i][second_chosen_monomer[0]][second_chosen_monomer[1]];
                if (rand / rando <= current_number / total) {
                    second_chosen_conglomerate = i;
                    break;
                }
            }
        }
    }

    if(second_chosen_conglomerate<0){
        cout << "random numbers gone wild 5" << endl;

        return false;
    }

    bool second_is_pool = false;
    if(second_chosen_conglomerate==number_of_available_sites.size()-1){
        second_is_pool = true;
    }

    if(first_is_pool && second_is_pool){
        //Create a dimer
        addDimer(chosen_monomer[1], second_chosen_monomer[1], chosen_monomer[0]);
        return true;
    }

    if(first_is_pool){
        Polymer *p = new Polymer(chosen_monomer[1], {chosen_monomer[0]});
        p->setIndex(++polymer_index);
        polymers.push_back(p);
        number_of_monomers[chosen_monomer[0]][chosen_monomer[1]]--;
        tuple<Polymer *, int> site = make_tuple(p, 0);
        possible_sites_one.push_back(site);
    } else {
        possible_sites_one = conglomerates[chosen_conglomerate]->getPossibleSites(chosen_monomer[0], chosen_monomer[1]);
    }
    if(second_is_pool){
        Polymer *p = new Polymer(second_chosen_monomer[1], {second_chosen_monomer[0]});
        p->setIndex(++polymer_index);
        polymers.push_back(p);
        number_of_monomers[second_chosen_monomer[0]][second_chosen_monomer[1]]--;
        tuple<Polymer *, int> site = make_tuple(p, 0);
        possible_sites_two.push_back(site);
    } else {
        possible_sites_two = conglomerates[second_chosen_conglomerate]->getPossibleSites(second_chosen_monomer[0], second_chosen_monomer[1]);
    }

    current_number = 0;
    rand = gen();
    rando = gen.max();

    int chosen_tuple = -1;

    for (int i = 0; i < possible_sites_one.size(); i++) {
        current_number ++;
        if (rand / rando <= current_number / possible_sites_one.size()) {
            chosen_tuple = i;
            break;
        }
    }

    if (chosen_tuple < 0) {
        cout << "random numbers gone wild 7" << endl;
        return false;
    }

    current_number = 0;

    rand = gen();
    rando = gen.max();

    int second_chosen_tuple = -1;

    for (int i = 0; i < possible_sites_two.size(); i++) {
        current_number ++;
        if (rand / rando <= current_number / possible_sites_two.size()) {
            second_chosen_tuple = i;
            break;
        }
    }

    if (second_chosen_tuple < 0) {
        cout << "random numbers gone wild 8" << endl;
        //Todo this is broken
        return false;
    }

    Connection *new_connection = new Connection(possible_sites_one[chosen_tuple],
                                                possible_sites_two[second_chosen_tuple]);

    if (chosen_conglomerate == number_of_available_sites.size() - 1) { //If first is monomer pool
        conglomerates[second_chosen_conglomerate]->addConnection(new_connection);

    } else if (second_chosen_conglomerate == number_of_available_sites.size() - 1) { // If second is monomer pool
        conglomerates[chosen_conglomerate]->addConnection(new_connection);

    } else { // neither are monomer pool
        vector<Connection *> connections;
        connections.push_back(new_connection);
        for (auto &con: conglomerates[second_chosen_conglomerate]->getConnections()) {
            connections.push_back(con);
        }
        conglomerates[chosen_conglomerate]->addConnections(connections);
        conglomerates.erase(conglomerates.begin() + second_chosen_conglomerate);
    }*/
    return true;
}

void System::chooseInternalTransition(int chosen_conglomerate) { //Todo test
    cout << "Internal transition chosen." << endl;
    vector<double> rates;
    double total_int_rate = specific_rates[chosen_conglomerate];
    Conglomerate * conglomerate = conglomerates[chosen_conglomerate];

    conglomerate->update();

    rates.push_back(conglomerate->getTailBindingSites() * template_bind_rate);

    rates.push_back(conglomerate->getHeadBindingSites() * template_bind_rate);

    rates.push_back(conglomerate->getTailUnbindingSites() * template_unbind_rate);

    rates.push_back(conglomerate->getHeadUnbindingSites() * template_unbind_rate);

    rates.push_back(conglomerate->getValidNeighboursBinding() * backbone_bind_rate);

    rates.push_back(conglomerate->getValidNeighboursUnbinding() * backbone_unbind_rate);

    random_device rd;
    mt19937 gen(rd());
    double current_number = 0;
    double rand = gen();
    double rando = gen.max();

    int chosen_transition = -1;
    for(int i=0; i<rates.size(); i++){
        current_number += rates[i];
        if(rand/rando <= current_number/total_int_rate){
            chosen_transition = i;
            break;
        }
    }

    if(chosen_transition<0 || chosen_transition>5){
        cout << "random numbers gone wild 9" << endl;
        return;
    }

    cout << "   Specific transition chosen: ";
    if(chosen_transition==0){ //Find tail to bind
        cout << "Tail binding." << endl;
        vector<Connection *> connections = conglomerate->getTailBindingConnections();

        current_number = 0;
        rand = gen();
        rando = gen.max();

        int chosen_connection = -1;
        for(int i=0; i<connections.size(); i++){
            current_number += i;
            if(rand/rando <= current_number/connections.size()){
                chosen_connection = i;
                break;
            }
        }

        conglomerate->addConnection(connections[chosen_connection]);
        //Check number of tail binding sites
        //Tail unbinding should remain the same
        //Check number of available sites (likely to drop by 2)
        //Valid neighbours for unbinding should have increased
        //Valid neighbours for binding may have increased
    }

    if(chosen_transition==1){ //Find head to bind
        cout << "Head binding." << endl;
        vector<Connection *> connections = conglomerate->getHeadBindingConnections();

        current_number = 0;
        rand = gen();
        rando = gen.max();

        int chosen_connection = -1;
        for(int i=0; i<connections.size(); i++){
            current_number += i;
            if(rand/rando <= current_number/connections.size()){
                chosen_connection = i;
                break;
            }
        }

        conglomerate->addConnection(connections[chosen_connection]);

        //Check number of tail binding sites
        //Tail unbinding should remain the same
        //Check number of available sites (likely to drop by 2)
        //Valid neighbours for unbinding should have increased
        //Valid neighbours for binding may have increased
    }

    if(chosen_transition==2){ //Find tail to unbind
        cout << "Tail unbinding." << endl;
        vector<Connection *> connections = conglomerate->getTailUnbindingConnections();
        current_number = 0;
        rand = gen();
        rando = gen.max();
        int chosen_connection = -1;
        for(int i=0; i<connections.size(); i++){
            current_number++;
            if(rand/rando <= current_number/connections.size()){
                chosen_connection = i;
                break;
            }
        }

        vector<Conglomerate *> new_conglomerates = conglomerate->removeConnection(connections[chosen_connection]);
        for(auto & cong : new_conglomerates){
            conglomerates.push_back(cong);
        }


        //tail binding sites may increase with lost connection
        //Tail unbinding should remain the same unless polymer disconnects
        //Check number of available sites (likely to increase by 2)
        //Valid neighbours for unbinding should have decreased
        //Valid neighbours for binding may have decreased
    }

    if(chosen_transition==3){ //Find head to unbind
        cout << "Head unbinding." << endl;
        vector<Connection *> connections = conglomerate->getHeadUnbindingConnections();
        current_number = 0;
        rand = gen();
        rando = gen.max();
        int chosen_connection = -1;
        for(int i=0; i<connections.size(); i++){
            current_number++;
            if(rand/rando <= current_number/connections.size()){
                chosen_connection = i;
                break;
            }
        }

        vector<Conglomerate *> new_conglomerates = conglomerate->removeConnection(connections[chosen_connection]);
        for(auto & cong : new_conglomerates){
            conglomerates.push_back(cong);
        }

        //tail binding sites may increase with lost connection
        //Tail unbinding should remain the same unless polymer disconnects
        //Check number of available sites (likely to increase by 2)
        //Valid neighbours for unbinding should have decreased
        //Valid neighbours for binding may have decreased
    }

    if(chosen_transition==4){ //Find neighbours to bind
        cout << "Neighbours binding." << endl;
        vector<UnconnectedNeighbours *> connections = conglomerate->getValidUnconnectedNeighbours();
        cout << connections.size() << endl;
        current_number = 0;
        rand = gen();
        rando = gen.max();


        int chosen_connection = -1;
        for(int i=0; i<connections.size(); i++){
            current_number += i;
            if(rand/rando <= current_number/connections.size()){
                chosen_connection = i;
                break;
            }
        }

        Polymer * polymer_to_be_removed = conglomerate->joinPolymers(connections[chosen_connection]);
        cout << "polymer_to_be_removed: " << polymer_to_be_removed->getIndex() << endl;
        //Find polymer in list //TODO broken
        for(int i=0; i<polymers.size(); i++){
            if(*polymer_to_be_removed == *polymers[i]){
                polymers.erase(polymers.begin() + i);
                //remove polymer from list
                break;
            }
        }

        //Tail unbinding decreased by 2
        //Valid unconnected drops by one
        //Valid connected increases by one
        // rest should be the same

    }
    if(chosen_transition==5){ //Find neighbours to unbind
        cout << "Neighbours unbinding." << endl;
        vector<ConnectedNeighbours *> connections = conglomerate->getValidConnectedNeighbours();

        current_number = 0;
        rand = gen();
        rando = gen.max();

        int chosen_connection = -1;
        for(int i=0; i<connections.size(); i++){
            current_number += i;
            if(rand/rando <= current_number/connections.size()){
                chosen_connection = i;
                break;
            }
        }

        Polymer * polymer_to_be_added = conglomerate->separatePolymers(connections[chosen_connection]);
        polymer_to_be_added->setIndex(++polymer_index);
        polymers.push_back(polymer_to_be_added);
    }

}

void System::print(){
    for(auto & elem : conglomerates){
        elem->update();
        cout << "Conglomerate " << elem->getIndex() << ':' << endl;
        for(int i=0; i<elem->getPolymersInConglomerate().size(); i++){
            cout << "Polymer: " << elem->getPolymersInConglomerate()[i]->getIndex() << endl;
            cout << "Connection Indexes" << endl;
            for(int j=0; j<elem->getPolymerConnectionIndexes()[i].size(); j++){
                cout << elem->getPolymerConnectionIndexes()[i][j];
            }
            cout << endl;
        }
    }
    cout << "Polymer Count: " << polymers.size() << endl;
    cout << "Dimer Count: " << dimers.size() << endl << endl;
}

