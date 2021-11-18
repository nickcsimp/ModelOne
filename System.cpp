//
// Created by Nicholas Simpson on 20/10/2021.
//

#include "System.h"
using namespace std;

System::System(int family_count, int monomer_type_count, vector<vector<int>> monomer_count, Polymer * initial_template){
    polymer_index=0;
    conglomerate_index=0;
    polymers.clear();
    conglomerates.clear();

    number_of_families = family_count;
    number_of_monomer_types = monomer_type_count;
    number_of_monomers = monomer_count;

    initial_template->setIndex(++polymer_index);
    polymers.push_back(initial_template);
    Conglomerate * c = new Conglomerate(initial_template, number_of_families, number_of_monomer_types);
    c->setIndex(++conglomerate_index);
    conglomerates.push_back(c);

    for(int i=0; i<number_of_monomer_types; i++){
        for(int j=0; j<number_of_families; j++){
            for(int k=0; k<number_of_monomers[i][j]; k++){
                Polymer * p = new Polymer(j, {i});
                p->setIndex(++polymer_index);
                Conglomerate * c = new Conglomerate(p, number_of_families, number_of_monomer_types);
                c->setIndex(++conglomerate_index);
                polymers.push_back(p);
                conglomerates.push_back(c);
            }
        }
    }

}


void System::chooseBond(int transition){
    if(transition==0){
        chooseHeadBinding();
    } else if(transition==1){
        chooseTailBinding();
    } else if(transition==2){
        chooseHeadUnbinding();
    } else if(transition==3){
        chooseTailUnbinding();
    } else if(transition==4){
        chooseNeighboursUnbind();
    } else if(transition==5){
        chooseNeighboursBind();
    } else if(transition==6){
        chooseHeadConnection();
    } else if(transition==7){
        chooseTailConnection();
    }
}

vector<int> System::getRates(){
    vector<int> rates;
    rates.push_back(number_head_binding*template_head_bind_rate);
    rates.push_back(number_tail_binding*template_tail_bind_rate);
    rates.push_back(number_head_unbinding*template_head_unbind_rate);
    rates.push_back(number_tail_unbinding*template_tail_unbind_rate);
    rates.push_back(number_connected_neighbours*backbone_unbind_rate);
    rates.push_back(number_unconnected_neighbours*backbone_bind_rate);
    rates.push_back(number_potential_head_connections*template_head_bind_rate);
    rates.push_back(number_potential_tail_connections*template_tail_bind_rate);

    /*cout << "Head Binding: " << number_head_binding << endl;
    cout << "Tail Binding: " << number_tail_binding << endl;
    cout << "Head Unbinding: " << number_head_unbinding << endl;
    cout << "Tail Unbinding: " << number_tail_unbinding << endl;
    cout << "Connected Neighbours: " << number_connected_neighbours << endl;
    cout << "Unconnected Neighbours: " << number_unconnected_neighbours << endl;*/
    //cout << "Head Connections: " << number_potential_head_connections << endl;
    //cout << "Tail Connections: " << number_potential_tail_connections << endl;
    return rates;
}



void System::getEverything(){
    for(auto & cong : conglomerates){
        cong->updateConglomerate();
    }
    head_binding = getHeadBinding();
    tail_binding = getTailBinding();

    head_unbinding = getHeadUnbinding();
    tail_unbinding = getTailUnbinding();

    connected_neighbours = getConnectedNeighbours();
    unconnected_neighbours = getUnconnectedNeighbours();

    available_head_tail_sites = getAvailableHeadTailSites();

    updatePotentialHeadTailSites();
}


vector<vector<Connection *>> System::getHeadBinding(){
    number_head_binding=0;
    vector<vector<Connection *>> output;
    for(auto & cong : conglomerates){
        vector<Connection *> c;
        for(auto & con : cong->getHeadBindingConnections()){
            c.push_back(con);
            number_head_binding++;
        }
        output.push_back(c);
    }
    return output;
}

vector<vector<Connection *>> System::getTailBinding(){
    number_tail_binding=0;
    vector<vector<Connection *>> output;
    for(auto & cong : conglomerates){
        vector<Connection *> c;
        for(auto & con : cong->getTailBindingConnections()){
            c.push_back(con);
            number_tail_binding++;
        }
        output.push_back(c);
    }
    return output;
}

vector<vector<Connection *>> System::getHeadUnbinding(){
    number_head_unbinding = 0;
    vector<vector<Connection *>> output;
    for(auto & cong : conglomerates){
        vector<Connection *> c;
        for(auto & con : cong->getHeadUnbindingConnections()){
            c.push_back(con);
            number_head_unbinding++;
        }
        output.push_back(c);
    }
    return output;
}

vector<vector<Connection *>> System::getTailUnbinding(){
    vector<vector<Connection *>> output;
    number_tail_unbinding=0;
    for(auto & cong : conglomerates){
        vector<Connection *> c;
        for(auto & con : cong->getTailUnbindingConnections()){
            c.push_back(con);
            number_tail_unbinding++;
        }
        output.push_back(c);
    }
    return output;
}

vector<vector<ConnectedNeighbours *>> System::getConnectedNeighbours(){
    vector<vector<ConnectedNeighbours *>>  output;
    number_connected_neighbours=0;
    for(auto & cong : conglomerates){
        vector<ConnectedNeighbours *> c;
        for(auto & con : cong->getValidConnectedNeighbours()){
            c.push_back(con);
            number_connected_neighbours++;
        }
        output.push_back(c);
    }
    return output;
}

vector<vector<UnconnectedNeighbours *>> System::getUnconnectedNeighbours(){
    vector<vector<UnconnectedNeighbours *>> output;
    number_unconnected_neighbours=0;
    for(auto & cong : conglomerates){
        vector<UnconnectedNeighbours *> c;
        for(auto & con : cong->getValidUnconnectedNeighbours()){
            c.push_back(con);
            number_unconnected_neighbours++;
        }
        output.push_back(c);
    }
    return output;
}

vector<vector<PotentialSite *>> System::getAvailableHeadTailSites(){
    vector<vector<PotentialSite *>> output;
    for(auto & cong : conglomerates){
        vector<PotentialSite *> c;
        for(auto & con : cong->getHeadTailSites()){
            PotentialSite * ps = new PotentialSite(get<0>(con), get<1>(con), cong);
            c.push_back(ps);
        }
        output.push_back(c);
    }
    return output;
}

void System::updatePotentialHeadTailSites(){
    potential_head_connections.clear();
    potential_tail_connections.clear();
    number_potential_head_connections=0;
    number_potential_tail_connections=0;

    for(auto & cong : conglomerates){
        vector<ExternalConnection *> v;
        potential_head_connections.push_back(v);
        vector<ExternalConnection *> c;
        potential_tail_connections.push_back(c);
    }
    int can_connect_number =0;

    for(int cong = 0; cong<available_head_tail_sites.size()-1; cong++){
        for(int i = 0; i<available_head_tail_sites[cong].size(); i++){
            for(int congo = cong+1; congo<available_head_tail_sites.size(); congo++){
                for(int j = 0; j<available_head_tail_sites[congo].size(); j++){
                    bool can_connect = true;
                    if(*available_head_tail_sites[cong][i]->getConglomerate()==*available_head_tail_sites[congo][j]->getConglomerate()){
                        //no connection
                        can_connect=false;
                    } else if(*available_head_tail_sites[cong][i]->getPolymer()==*available_head_tail_sites[congo][j]->getPolymer()){
                        //No connection
                        can_connect=false;
                    } else if(available_head_tail_sites[cong][i]->getFamily()==available_head_tail_sites[congo][j]->getFamily()){
                        //No connection
                        can_connect=false;
                    } else if(available_head_tail_sites[cong][i]->getType()!=available_head_tail_sites[congo][j]->getType()){
                        //No connection
                        can_connect=false;
                    }
                    if(can_connect){
                        can_connect_number++;
                        tuple<Polymer *, int> tup = make_tuple(available_head_tail_sites[cong][i]->getPolymer(), available_head_tail_sites[cong][i]->getIndex());
                        tuple<Polymer *, int> tups = make_tuple(available_head_tail_sites[congo][j]->getPolymer(), available_head_tail_sites[congo][j]->getIndex());
                        if(available_head_tail_sites[cong][i]->getHead() || available_head_tail_sites[congo][j]->getHead()){
                            number_potential_head_connections++;
                            potential_head_connections[cong].push_back(new ExternalConnection(tup, tups, conglomerates[cong], conglomerates[congo]));
                        } else {
                            number_potential_tail_connections++;
                            potential_tail_connections[cong].push_back(new ExternalConnection(tup, tups, conglomerates[cong], conglomerates[congo]));
                        }
                    }
                }
            }
        }
    }
}

void System::chooseHeadBinding(){
    cout << "Head Binding" << endl;
    random_device rd;
    mt19937 gen(rd());
    double rand = gen();
    double rando = gen.max();
    double current_number = 0;
    double total = 0;
    for(int j=0; j<head_binding.size(); j++){
        total+=head_binding[j].size();
    }
    int chosen_conglomerate = -1;
    for(int i=0; i<head_binding.size(); i++){
        current_number+=head_binding[i].size();
        if(rand/rando <= current_number/total){
            chosen_conglomerate = i;
            break;
        }
    }
    current_number = 0;
    int chosen_bond = -1;
    for(int i=0; i<head_binding[chosen_conglomerate].size(); i++){
        current_number++;
        if(rand/rando <= current_number/head_binding[chosen_conglomerate].size()){
            chosen_bond = i;
            break;
        }
    }

    conglomerates[chosen_conglomerate]->addConnection(head_binding[chosen_conglomerate][chosen_bond]);

}

void System::chooseTailBinding(){
    cout << "Tail Binding" << endl;
    random_device rd;
    mt19937 gen(rd());
    double rand = gen();
    double rando = gen.max();
    double current_number = 0;
    double total = 0;
    for(int j=0; j<tail_binding.size(); j++){
        total+=tail_binding[j].size();
    }
    int chosen_conglomerate = -1;
    for(int i=0; i<tail_binding.size(); i++){
        current_number+=tail_binding[i].size();
        if(rand/rando <= current_number/total){
            chosen_conglomerate = i;
            break;
        }
    }
    current_number = 0;
    int chosen_bond = -1;
    for(int i=0; i<tail_binding[chosen_conglomerate].size(); i++){
        current_number++;
        if(rand/rando <= current_number/tail_binding[chosen_conglomerate].size()){
            chosen_bond = i;
            break;
        }
    }

    conglomerates[chosen_conglomerate]->addConnection(tail_binding[chosen_conglomerate][chosen_bond]);
}
void System::chooseHeadUnbinding(){
    cout << "Head Unbinding" << endl;
    random_device rd;
    mt19937 gen(rd());
    double rand = gen();
    double rando = gen.max();
    double current_number = 0;
    double total = 0;
    for(int j=0; j<head_unbinding.size(); j++){
        total+=head_unbinding[j].size();
    }
    int chosen_conglomerate = -1;
    for(int i=0; i<head_unbinding.size(); i++){
        current_number+=head_unbinding[i].size();
        if(rand/rando <= current_number/total){
            chosen_conglomerate = i;
            break;
        }
    }
    current_number = 0;
    int chosen_bond = -1;
    for(int i=0; i<head_unbinding[chosen_conglomerate].size(); i++){
        current_number++;
        if(rand/rando <= current_number/head_unbinding[chosen_conglomerate].size()){
            chosen_bond = i;
            break;
        }
    }

    cout << "Polymers being unbound: " << head_unbinding[chosen_conglomerate][chosen_bond]->getPolymers()[0]->getIndex() << ' ' <<  head_unbinding[chosen_conglomerate][chosen_bond]->getPolymers()[1]->getIndex() << endl;

    Conglomerate * new_cong = conglomerates[chosen_conglomerate]->removeConnection(head_unbinding[chosen_conglomerate][chosen_bond])[0];
    new_cong->setIndex(++conglomerate_index);

    for(auto & elem : head_unbinding[chosen_conglomerate][chosen_bond]->getPolymers()[0]->getConnections()){
        cout << get<0>(elem)->getIndex() << ' ' << get<1>(elem) << '|';
    }
    cout << endl;
    for(auto & elem : head_unbinding[chosen_conglomerate][chosen_bond]->getPolymers()[1]->getConnections()){
        cout << get<0>(elem)->getIndex() << ' ' << get<1>(elem);
    }
    conglomerates.push_back(new_cong);
}
void System::chooseTailUnbinding(){
    cout << "Tail Unbinding" << endl;
    random_device rd;
    mt19937 gen(rd());
    double rand = gen();
    double rando = gen.max();
    double current_number = 0;
    double total = 0;
    for(int j=0; j<tail_unbinding.size(); j++){
        total+=tail_unbinding[j].size();
    }
    int chosen_conglomerate = -1;
    for(int i=0; i<tail_unbinding.size(); i++){
        current_number+=tail_unbinding[i].size();
        if(rand/rando <= current_number/total){
            chosen_conglomerate = i;
            break;
        }
    }
    current_number = 0;
    int chosen_bond = -1;
    for(int i=0; i<tail_unbinding[chosen_conglomerate].size(); i++){
        current_number++;
        if(rand/rando <= current_number/tail_unbinding[chosen_conglomerate].size()){
            chosen_bond = i;
            break;
        }
    }

    conglomerates[chosen_conglomerate]->removeConnection(tail_unbinding[chosen_conglomerate][chosen_bond]);
}
void System::chooseNeighboursUnbind(){
    cout << "Neighbours Unbinding" << endl;
    random_device rd;
    mt19937 gen(rd());
    double rand = gen();
    double rando = gen.max();
    double current_number = 0;
    double total = 0;
    for(int j=0; j<connected_neighbours.size(); j++){
        total+=connected_neighbours[j].size();
    }
    int chosen_conglomerate = -1;
    for(int i=0; i<connected_neighbours.size(); i++){
        current_number+=connected_neighbours[i].size();
        if(rand/rando <= current_number/total){
            chosen_conglomerate = i;
            break;
        }
    }
    current_number = 0;
    int chosen_bond = -1;
    for(int i=0; i<connected_neighbours[chosen_conglomerate].size(); i++){
        current_number++;
        if(rand/rando <= current_number/connected_neighbours[chosen_conglomerate].size()){
            chosen_bond = i;
            break;
        }
    }

    cout << "Polymer: " << connected_neighbours[chosen_conglomerate][chosen_bond]->getPolymer()->getIndex() << '.' << connected_neighbours[chosen_conglomerate][chosen_bond]->getIndexes()[0] << '.' << connected_neighbours[chosen_conglomerate][chosen_bond]->getIndexes()[1] << endl;

    Polymer * new_poly = conglomerates[chosen_conglomerate]->separatePolymers(connected_neighbours[chosen_conglomerate][chosen_bond]);
    new_poly->setIndex(++polymer_index);
    polymers.push_back(new_poly);

}
void System::chooseNeighboursBind(){
    cout << "Neighbours Binding" << endl;
    /*for(int cong = 0; cong<unconnected_neighbours.size(); cong++){
        for(auto & e : unconnected_neighbours[cong]){
            cout << "Polymers: " << e->getPolymers()[0]->getIndex() << ' ' << e->getPolymers()[1]->getIndex() << endl;
            vector<Connection *> cons = conglomerates[cong]->getConnections();
            for(auto & con : cons){
                if(*con->getPolymers()[0]==*e->getPolymers()[0]){
                    cout << "Polymer: " << e->getPolymers()[0]->getIndex() << " Connected to: " << con->getPolymers()[1]->getIndex() << endl;
                }
                if(*con->getPolymers()[1]==*e->getPolymers()[0]){
                    cout << "Polymer: " << e->getPolymers()[0]->getIndex() << " Connected to: " << con->getPolymers()[0]->getIndex() << endl;
                }
                if(*con->getPolymers()[0]==*e->getPolymers()[1]){
                    cout << "Polymer: " << e->getPolymers()[1]->getIndex() << " Connected to: " << con->getPolymers()[1]->getIndex() << endl;
                }
                if(*con->getPolymers()[1]==*e->getPolymers()[1]){
                    cout << "Polymer: " << e->getPolymers()[1]->getIndex() << " Connected to: " << con->getPolymers()[0]->getIndex() << endl;
                }

            }
        }
    }*/

    random_device rd;
    mt19937 gen(rd());
    double rand = gen();
    double rando = gen.max();
    double current_number = 0;
    double total = 0;
    for(int j=0; j<unconnected_neighbours.size(); j++){
        total+=unconnected_neighbours[j].size();
    }
    int chosen_conglomerate = -1;
    for(int i=0; i<unconnected_neighbours.size(); i++){
        current_number+=unconnected_neighbours[i].size();
        if(rand/rando <= current_number/total){
            chosen_conglomerate = i;
            break;
        }
    }
    current_number = 0;
    int chosen_bond = -1;
    for(int i=0; i<unconnected_neighbours[chosen_conglomerate].size(); i++){
        current_number++;
        if(rand/rando <= current_number/unconnected_neighbours[chosen_conglomerate].size()){
            chosen_bond = i;
            break;
        }
    }

    conglomerates[chosen_conglomerate]->joinPolymers(unconnected_neighbours[chosen_conglomerate][chosen_bond]);
}
void System::chooseHeadConnection(){
    cout << "Head Connection" << endl;
    random_device rd;
    mt19937 gen(rd());
    double rand = gen();
    double rando = gen.max();
    double current_number = 0;
    double total = 0;
    for(int j=0; j<potential_head_connections.size(); j++){
        total+=potential_head_connections[j].size();
    }
    int chosen_conglomerate = -1;
    for(int i=0; i<potential_head_connections.size(); i++){
        current_number+=potential_head_connections[i].size();
        if(rand/rando <= current_number/total){
            chosen_conglomerate = i;
            break;
        }
    }
    current_number = 0;
    int chosen_bond = -1;
    for(int i=0; i<potential_head_connections[chosen_conglomerate].size(); i++){
        current_number++;
        if(rand/rando <= current_number/potential_head_connections[chosen_conglomerate].size()){
            chosen_bond = i;
            break;
        }
    }
    vector<Conglomerate *> congs = potential_head_connections[chosen_conglomerate][chosen_bond]->getConglomerates();
    vector<Polymer *> polys = potential_head_connections[chosen_conglomerate][chosen_bond]->getPolymers();
    vector<int> inds = potential_head_connections[chosen_conglomerate][chosen_bond]->getIndexes();

    cout << "Polymers being connected: " << polys[0]->getIndex() << '.' << inds[0] << ' ' << polys[1]->getIndex() << '.' << inds[1] << endl;
    vector<Connection *> cons = congs[1]->getConnections();
    congs[0]->addConnections(cons);

    tuple<Polymer *, int> tup = make_tuple(polys[0], inds[0]);
    tuple<Polymer *, int> tups = make_tuple(polys[1], inds[1]);

    cout << "adding connection" << endl;
    congs[0]->addConnection(new Connection(tup, tups));
    cout << "Conglomerate index: ";
    cout << congs[0]->getIndex() << endl;
    cout << "updating conglomerate" << endl;
    cout << 1;
    congs[0]->updatePolymersInConglomerate();
    cout << 2;
    congs[0]->updatePolymerConnections();
    cout << 3;
    congs[0]->updateAvailableTemplateBonds();
    cout << 4;
    congs[0]->updateTailUnbindingSites();
    cout << 5;
    congs[0]->updateTailBindingSites();
    cout << 6;
    congs[0]->updateValidNeighboursBinding();
    cout << 7;
    congs[0]->updateValidNeighboursUnbinding();
    cout << endl;
    cout << "removing conglomerate" << endl;
    int cong_to_be_removed = -1;
    for(int i=0; i<conglomerates.size(); i++){
        if(*conglomerates[i]==*congs[1]){
            cong_to_be_removed=i;
        }
    }
    conglomerates.erase(conglomerates.begin()+cong_to_be_removed);
}

void System::chooseTailConnection(){
     cout << "Tail Connection" << endl;
    random_device rd;
    mt19937 gen(rd());
    double rand = gen();
    double rando = gen.max();
    double current_number = 0;
    double total = 0;
    for(int j=0; j<potential_tail_connections.size(); j++){
        total+=potential_tail_connections[j].size();
    }
    int chosen_conglomerate = -1;
    for(int i=0; i<potential_tail_connections.size(); i++){
        current_number+=potential_tail_connections[i].size();
        if(rand/rando <= current_number/total){
            chosen_conglomerate = i;
            break;
        }
    }
    current_number = 0;
    int chosen_bond = -1;
    for(int i=0; i<potential_tail_connections[chosen_conglomerate].size(); i++){
        current_number++;
        if(rand/rando <= current_number/potential_tail_connections[chosen_conglomerate].size()){
            chosen_bond = i;
            break;
        }
    }
    vector<Conglomerate *> congs = potential_tail_connections[chosen_conglomerate][chosen_bond]->getConglomerates();
    vector<Polymer *> polys = potential_tail_connections[chosen_conglomerate][chosen_bond]->getPolymers();
    vector<int> inds = potential_tail_connections[chosen_conglomerate][chosen_bond]->getIndexes();

    vector<Connection *> cons = congs[1]->getConnections();
    congs[0]->addConnections(cons);

    tuple<Polymer *, int> tup = make_tuple(polys[0], inds[0]);
    tuple<Polymer *, int> tups = make_tuple(polys[1], inds[1]);

    congs[0]->addConnection(new Connection(tup, tups));
    congs[0]->updateConglomerate();

    int cong_to_be_removed = -1;
    for(int i=0; i<conglomerates.size(); i++){
        if(*conglomerates[i]==*congs[1]){
            cong_to_be_removed=i;
        }
    }
    conglomerates.erase(conglomerates.begin()+cong_to_be_removed);
}



void System::print(){
    cout << "Conglomerate Count: " << conglomerates.size() << endl;
    cout << "Polymer Count: " << polymers.size() << endl;
    vector<tuple<int, int>> hist;
    for(auto & cong : conglomerates){
        int count = 0;
        for(int tup=0; tup<hist.size(); tup++){
            if(get<0>(hist[tup]) == cong->getPolymersInConglomerate().size()){
                int one = get<0>(hist[tup]);
                int two = get<1>(hist[tup]);
                hist[tup] = make_tuple(one, two+1);
            } else {
                count ++;
            }
        }
        if(count == hist.size()){
            hist.push_back(make_tuple(cong->getPolymersInConglomerate().size(), 1));
        }
    }
    cout << "Polymers in Conglomerate     |   Number of Conglomerates" << endl;
    for(auto & tup : hist){
        cout << "   " << get<0>(tup) << "   |     "  << get<1>(tup) << endl;
    }
}

