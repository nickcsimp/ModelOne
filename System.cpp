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

    polymers.push_back(initial_template);
    Conglomerate * c = new Conglomerate(initial_template, number_of_families, number_of_monomer_types);
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
        //Update conglomerate first

        rate = elem->getTailUnbindingSites() * template_unbind_rate;
        rate = rate + elem->getTailBindingSites() * template_bind_rate;
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

bool System::chooseExternalTransition() { //Todo test
    int total = 0;
    for(auto & type : number_of_connections){
        for(auto & family : type){
            total = total + family;
        }
    }

    random_device rd;
    mt19937 gen(rd());

    double current_number = 0;
    double random_ratio = gen()/gen.max();
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
                total = total + cong[i][j];
            }
        }
    }

    for(int i=0; i<number_of_monomer_types; i++){
        for(int j=0; j<number_of_families; j++){
            current_number += total_number_of_sites[i][j];
            if(random_ratio <= current_number/total){
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
        cout << "random numbers gone wild" << endl;
        return false;
    }

    int second_chosen_monomer[2] = {-1, -1};

    total = 0;
    current_number = 0;
    random_ratio = gen()/gen.max();

    for(int i=0; i<number_of_families; i++) {
        if (i != chosen_monomer[1]) {
              total = total + total_number_of_sites[chosen_monomer[0]][i];
        }
    }

    for(int i=0; i<number_of_families; i++) {
        if (i != chosen_monomer[1]) {
            current_number += total_number_of_sites[chosen_monomer[0]][i];
            if (random_ratio <= current_number / total) {
                second_chosen_monomer[0] = chosen_monomer[0];
                chosen_monomer[1] = i;
                break;
            }
        }
    }


    if(second_chosen_monomer[0]<0 || second_chosen_monomer[1]<0){
        cout << "random numbers gone wild" << endl;
        return false;
    }

    current_number = 0;
    random_ratio = gen()/gen.max();

    total = 0;

    for(auto & cong : number_of_available_sites){
        total = total + cong[chosen_monomer[0]][chosen_monomer[1]];
    }

    int chosen_conglomerate = -1;
    for(int i=0; i<number_of_available_sites.size(); i++){
        current_number += number_of_available_sites[i][chosen_monomer[0]][chosen_monomer[1]];
        if(random_ratio<current_number/total){
            chosen_conglomerate = i;
            break;
        }
    }

    if(chosen_conglomerate<0){
        cout << "random numbers gone wild" << endl;
        return false;
    }

    vector<tuple<Polymer*, int>> possible_sites_one;
    current_number = 0;
    random_ratio = gen()/gen.max();

    total = 0;

    for(auto & cong : number_of_available_sites){
        total = total + cong[second_chosen_monomer[0]][second_chosen_monomer[1]];
    }
    int second_chosen_conglomerate = -1;

    if(chosen_conglomerate==number_of_available_sites.size()-1){
        //Second conglomerate can be any option including the monomer pool again
        for(int i=0; i<number_of_available_sites.size(); i++) {
            current_number += number_of_available_sites[i][chosen_monomer[0]][chosen_monomer[1]];
            if (random_ratio < current_number / total) {
                second_chosen_conglomerate = i;
                break;
            }
        }
        if(second_chosen_conglomerate<0){
            cout << "random numbers gone wild" << endl;
            return false;
        }

        if(second_chosen_conglomerate==number_of_available_sites.size()-1) {
            //Both are monomer pool, make a dimer
            Dimer * d = new Dimer(chosen_monomer[0], chosen_monomer[1], second_chosen_monomer[1]);
            dimers.push_back(d);
            return true;
        } else {
            //We are choosing monomers and so we just create a new polymer and conglomerate to add to something else
            Polymer *p = new Polymer(chosen_monomer[1], {chosen_monomer[0]});
            polymers.push_back(p);
            number_of_monomers[chosen_monomer[0]][chosen_monomer[1]]--;
            tuple<Polymer *, int> site = make_tuple(p, 0);
            possible_sites_one.push_back(site);
        }


    } else {
        //We are in a conglomerate, need to create a list of possible sites
        possible_sites_one = conglomerates[chosen_conglomerate]->getPossibleSites(chosen_monomer[0], chosen_monomer[1]);

        //Second conglomerate can't be the same as first chosen
        for(int i=0; i<number_of_available_sites.size(); i++) {
            if (i != chosen_conglomerate) {
                current_number += number_of_available_sites[i][chosen_monomer[0]][chosen_monomer[1]];
                if (random_ratio < current_number / total) {
                    second_chosen_conglomerate = i;
                    break;
                }
            }
        }

        if(second_chosen_conglomerate<0){
            cout << "random numbers gone wild" << endl;
            return false;
        }
    }

    vector<tuple<Polymer*, int>> possible_sites_two;

    if(second_chosen_conglomerate==number_of_available_sites.size()-1){
        //We are choosing monomers and so we just create a new polymer and conglomerate to add to something else
        Polymer * p = new Polymer(chosen_monomer[1], {chosen_monomer[0]});
        polymers.push_back(p);
        number_of_monomers[chosen_monomer[0]][chosen_monomer[1]]--;
        tuple<Polymer*, int> site = make_tuple(p, 0);
        possible_sites_two.push_back(site);
    } else {
        //We are in a conglomerate, need to create a list of possible sites
        possible_sites_two = conglomerates[second_chosen_conglomerate]->getPossibleSites(second_chosen_monomer[0], second_chosen_monomer[1]);
    }

    current_number = 0;
    random_ratio = gen()/gen.max();

    int chosen_tuple = -1;

    for(int i=0; i<possible_sites_one.size(); i++) {
        current_number += i+1;
        if (random_ratio < current_number / i<possible_sites_one.size()) {
            chosen_tuple = i;
            break;
        }
    }

    if(chosen_tuple<0){
        cout << "random numbers gone wild" << endl;
        return false;
    }

    current_number = 0;
    random_ratio = gen()/gen.max();

    int second_chosen_tuple = -1;

    for(int i=0; i<possible_sites_two.size(); i++) {
        current_number += i+1;
        if (random_ratio < current_number / i<possible_sites_two.size()) {
            second_chosen_tuple = i;
            break;
        }
    }

    if(second_chosen_tuple<0){
        cout << "random numbers gone wild" << endl;
        return false;
    }

    Connection * new_connection = new Connection(possible_sites_one[chosen_tuple], possible_sites_two[second_chosen_tuple]);
    if(chosen_conglomerate==number_of_available_sites.size()-1){ //If first is monomer pool
        conglomerates[second_chosen_conglomerate]->addConnection(new_connection);
    } else if (second_chosen_conglomerate==number_of_available_sites.size()-1){ // If second is monomer pool
        conglomerates[chosen_conglomerate]->addConnection(new_connection);
    } else { // neither are monomer pool
        vector<Connection *> connections;
        connections.push_back(new_connection);
        for(auto & con : conglomerates[second_chosen_conglomerate]->getConnections()){
            connections.push_back(con);
        }
        conglomerates[chosen_conglomerate]->addConnections(connections);
        conglomerates.erase(conglomerates.begin()+second_chosen_conglomerate);
    }
    return true;
}

void System::chooseInternalTransition(int chosen_conglomerate) { //Todo test
    vector<double> rates;
    double total_int_rate = specific_rates[chosen_conglomerate];
    Conglomerate * conglomerate = conglomerates[chosen_conglomerate];

    rates.push_back(conglomerate->getTailBindingSites() * template_bind_rate);
    rates.push_back(conglomerate->getTailUnbindingSites() * template_unbind_rate);
    rates.push_back(conglomerate->getValidNeighboursBinding() * backbone_bind_rate);
    rates.push_back(conglomerate->getValidNeighboursUnbinding() * backbone_unbind_rate);

    random_device rd;
    mt19937 gen(rd());

    double current_number = 0;
    double random_ratio = gen()/gen.max();
    int chosen_transition = -1;
    for(int i=0; i<rates.size(); i++){
        current_number += rates[i];
        if(random_ratio <= current_number/total_int_rate){
            chosen_transition = i;
            break;
        }
    }

    if(chosen_transition<0 || chosen_transition>3){
        cout << "random numbers gone wild" << endl;
        return;
    }

    if(chosen_transition==0){ //Find tail to bind

        vector<Connection *> connections = conglomerate->getTailBindingConnections();

        current_number = 0;
        random_ratio = gen()/gen.max();
        int chosen_connection = -1;
        for(int i=0; i<connections.size(); i++){
            current_number += i;
            if(random_ratio <= current_number/connections.size()){
                chosen_connection = i;
                break;
            }
        }

        conglomerate->addConnection(connections[chosen_connection]);
    }

    if(chosen_transition==1){ //Find tail to unbind
        vector<Connection *> connections = conglomerate->getTailUnbindingConnections();

        current_number = 0;
        random_ratio = gen()/gen.max();
        int chosen_connection = -1;
        for(int i=0; i<connections.size(); i++){
            current_number += i;
            if(random_ratio <= current_number/connections.size()){
                chosen_connection = i;
                break;
            }
        }

        if(conglomerate->removeConnection(connections[chosen_connection])){
            //If returns true then the conglomerate has no connections
        }
    }

    if(chosen_transition==2){ //Find neighbours to bind
        vector<UnconnectedNeighbours *> connections = conglomerate->getValidUnconnectedNeighbours();

        current_number = 0;
        random_ratio = gen()/gen.max();

        int chosen_connection = -1;
        for(int i=0; i<connections.size(); i++){
            current_number += i;
            if(random_ratio <= current_number/connections.size()){
                chosen_connection = i;
                break;
            }
        }

        // TODO way to join polymers in conglomerate and change polymers in system
        // conglomerate->joinPolymers(connections[i]);
    }

    if(chosen_transition==3){ //Find neighbours to unbind
        vector<ConnectedNeighbours *> connections = conglomerate->getValidConnectedNeighbours();

        current_number = 0;
        random_ratio = gen()/gen.max();

        int chosen_connection = -1;
        for(int i=0; i<connections.size(); i++){
            current_number += i;
            if(random_ratio <= current_number/connections.size()){
                chosen_connection = i;
                break;
            }
        }

        // TODO way to break polymers in conglomerate and change polymers in system
        // conglomerate->separatePolymers(connections[i]);
    }

}

void System::print(){
    for(auto & elem : conglomerates){
        cout << "Conglomerate " << elem->getIndex() << ':' << endl;
        for(auto & eleme : elem->getConnections()){
            cout << "   Polymer one: " << eleme->getPolymers()[0]->getIndex() << endl;
            cout << "   Index one: " << eleme->getIndexes()[0]<< endl;
            cout << "   Polymer two: " << eleme->getPolymers()[1]->getIndex() << endl;
            cout << "   Index two: " << eleme->getIndexes()[1]<< endl;
        }
    }
    for(auto & elem : polymers){
        cout << "Polymer " << elem->getIndex() << ':' << endl;
        cout << "   Sequence: ";
        for(auto & eleme : elem->getSequence()){
            cout << eleme;
        }
        cout << endl;
    }
}

