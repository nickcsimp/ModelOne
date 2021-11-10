//
// Created by Nicholas Simpson on 20/10/2021.
//

#include "Conglomerate.h"
using namespace std;

Conglomerate::Conglomerate(vector<Connection *> con, int family_count, int monomer_type_count){
    connections = con;
    for(auto & c : con){
        c->getPolymers()[0]->addConnection(c->getPolymers()[1]);
        c->getPolymers()[1]->addConnection(c->getPolymers()[0]);
    }
    number_of_families = family_count;
    number_of_monomer_types = monomer_type_count;
    //update();
}

Conglomerate::Conglomerate(Polymer * polymer, int family_count, int monomer_type_count){
    connections.clear();
    polymers_in_conglomerate.push_back(polymer);
    number_of_families = family_count;
    number_of_monomer_types = monomer_type_count;
    //update();
}

void Conglomerate::update(){
    updatePolymersInConglomerate();
    updatePolymerConnections();
    updateAvailableTemplateBonds();
    updateTailUnbindingSites();
    updateTailBindingSites();
    updateValidNeighboursBinding();
    updateValidNeighboursUnbinding();
}

int Conglomerate::getIndex(){
    return index;
}

void Conglomerate::setIndex(int ind) {
    index=ind;
}
vector<Polymer*> Conglomerate::getPolymersInConglomerate(){
    return polymers_in_conglomerate;
}

void Conglomerate::addConnection(Connection* con){
    connections.push_back(con);
    con->getPolymers()[0]->addConnection(con->getPolymers()[1]);
    con->getPolymers()[1]->addConnection(con->getPolymers()[0]);
    updatePolymersInConglomerate();
}

void Conglomerate::addConnections(vector<Connection*> cons){
    for(auto & con : cons){
        connections.push_back(con);
        con->getPolymers()[0]->addConnection(con->getPolymers()[1]);
        con->getPolymers()[1]->addConnection(con->getPolymers()[0]);
    }

    updatePolymersInConglomerate();
}


vector<Conglomerate *> Conglomerate::removeConnection(Connection* con){
    vector<Conglomerate *> new_conglomerates;
    vector<vector<Connection *>> connectivity;
    for(int i=0; i<connections.size(); i++){
        if(*con == *connections[i]){
            connections.erase(connections.begin()+i);
            if(con->getPolymers()[0]->removeConnection(con->getPolymers()[1]) || con->getPolymers()[1]->removeConnection(con->getPolymers()[0])){
                connectivity = updateConnectivity();
            }
        }
    }
    if(connectivity.size()!=1){
        connections = connectivity[0];
        for(int j=1; j<connectivity.size(); j++){
            new_conglomerates.push_back(new Conglomerate(connectivity[j], number_of_families, number_of_monomer_types));
        }
    }
    return new_conglomerates;
}

vector<Polymer *> Conglomerate::getTree(Polymer * p, vector<Polymer *> connected_polymers){

    vector<tuple<Polymer *, int>> cons = p->getConnections();
    for(auto & con : cons){ //Loop all connections
        Polymer * c = get<0>(con); //Get one of the polymers in the connection
        bool in_vector = false;
        for(auto & elem : connected_polymers){
            if(*elem == *c){
                in_vector = true;
            }
        }
        if(!in_vector){
            connected_polymers.push_back(c); //add this polymer to the vector
            vector<Polymer *> connected_connected_polymers = getTree(c, connected_polymers);
            connected_polymers.insert(connected_polymers.end(), connected_connected_polymers.begin(), connected_connected_polymers.end());
        }
    }
    return connected_polymers;
}

vector<vector<Connection *>> Conglomerate::updateConnectivity(){ //TODO test
    updatePolymersInConglomerate();
    updatePolymerConnections();

    vector<vector<Connection *>> output;
    vector<vector<Polymer *>> p_con;

    for(auto & polymer : polymers_in_conglomerate){ //Loop polymers in conglomerate
        bool in_list = false;
        for(auto & list : p_con){
            for(auto & p : list){
                if(*polymer==*p){
                    in_list=true; //If the polymer is already in p_con then it's connection is found
                }
            }
        }
        if(!in_list){
            vector<Polymer *> p;
            p.push_back(polymer);
            p_con.push_back(getTree(polymer, p));
        }
    }

    for(auto & list : p_con){
        vector<Connection *> vec;
        output.push_back(vec);
    }

    //loop all connections
    //find the place

    for(auto & connection : connections){
        for(int i=0; i<p_con.size(); i++){
            for(int j=0; j<p_con[i].size(); j++){
                if(*connection->getPolymers()[0]==*p_con[i][j]){
                    output[i].push_back(connection);
                }
            }
        }
    }

    return output;
}

vector<Connection *> Conglomerate::getConnections(){
    return connections;
}

void Conglomerate::updatePolymersInConglomerate() {
    if (connections.size() > 0) { //If a lone polymer then leave this
        polymers_in_conglomerate.clear();
        for (auto &elem: connections) { //Loop all connections in conglomerate
            vector<Polymer *> v = elem->getPolymers(); //Find the polymers involved in the connection
            for (auto &eleme: v) { //Loop the two polymers in each connection
                bool in_vector = false; //Initialise a boolean to determine whether the polymer is already in the list
                for (auto &elemen: polymers_in_conglomerate) { //Loop all polymers already in the list
                    if (*eleme ==
                        *elemen) { //If any polymers in the list match the polymer we are looking at the bool becomes true
                        in_vector = true;
                    }
                }
                if (!in_vector) {
                    polymers_in_conglomerate.push_back(eleme);
                }
            }
        }
        for (int j = 0; j < polymers_in_conglomerate.size(); j++) {
            for (int i = 1; i < polymers_in_conglomerate.size(); i++) {
                if (polymers_in_conglomerate[i - 1]->getIndex() > polymers_in_conglomerate[i]->getIndex()) {
                    Polymer *temp = polymers_in_conglomerate[i - 1];
                    polymers_in_conglomerate[i - 1] = polymers_in_conglomerate[i];
                    polymers_in_conglomerate[i] = temp;
                }
            }
        }
    }
}

/*void Conglomerate::updateTemplateBond(){
    updatePolymersInConglomerate(); // Probs shouldn't have to rerun every time
    template_bonds = 0;
    for(auto & elem : polymers_in_conglomerate){
        template_bonds=template_bonds+elem->getLength();
    }
    template_bonds=template_bonds-(2*connections.size());
}*/

void Conglomerate::updateAvailableTemplateBonds(){
    updatePolymersInConglomerate(); // Probs shouldn't have to rerun every time
    updatePolymerConnections();
    available_template_bonds.clear();
    for(int i=0; i<number_of_monomer_types; i++){
        vector<int> family;
        for(int j=0; j<number_of_families; j++){
            family.push_back(0);
        }
        available_template_bonds.push_back(family);
    }

    for(int i=0; i<polymers_in_conglomerate.size(); i++){
        int family = polymers_in_conglomerate[i]->getFamily();
        vector<int> seq = polymers_in_conglomerate[i]->getSequence();
        for(int k=0; k<seq.size(); k++){
            bool there_is_a_connection = false;
            for(int j=0; j<polymer_connection_indexes[i].size(); j++){
                if(polymer_connection_indexes[i][j]==k){
                    there_is_a_connection = true;
                }
            }
            if(!there_is_a_connection){
                available_template_bonds[seq[k]][family]++;
            }
        }
    }
}

vector<tuple<Polymer *, int>> Conglomerate::getPossibleSites(int type, int family){
    vector<tuple<Polymer *, int>> output;
    for(int i=0; i<polymers_in_conglomerate.size(); i++){
        if(family == polymers_in_conglomerate[i]->getFamily()) {
            vector<int> seq = polymers_in_conglomerate[i]->getSequence();
            for (int k = 0; k < seq.size(); k++) {
                bool there_is_a_connection = false;
                for (int j = 0; j < polymer_connection_indexes[i].size(); j++) {
                    if (polymer_connection_indexes[i][j] == k) {
                        there_is_a_connection = true;
                    }
                }
                if (!there_is_a_connection) {
                    if(seq[k]==type){
                        tuple<Polymer *, int> site = make_tuple(polymers_in_conglomerate[i], k);
                        output.push_back(site);
                    }
                }
            }
        }
    }
    return output;
}

int Conglomerate::getTemplateBonds(){
    return template_bonds;
}

vector<vector<int>> Conglomerate::getAvailableTemplateBonds(){
    return available_template_bonds;
}

void Conglomerate::updateBackboneBonds(){
    updatePolymersInConglomerate(); // Probs shouldn't have to rerun every time
    backbone_bonds=0;
    for(auto & elem : polymers_in_conglomerate){
        backbone_bonds=backbone_bonds+elem->getLength()-1;
    }
}

int Conglomerate::getBackboneBonds(){
    return backbone_bonds;
}

void Conglomerate::updatePolymerConnections(){
    updatePolymersInConglomerate(); // Probs shouldn't have to rerun every time

    polymer_connection_indexes.clear();
    polymer_connections.clear();
    for(auto & j : polymers_in_conglomerate){ //Loop all polymers
        vector<Connection *> v;
        vector<int> indexs;
        for(auto & elem : connections) { //Loop all connections
            for (int i=0; i<2; i++) { //Loop the two polymers in each connection
                Polymer *p = elem->getPolymers()[i]; //Find the polymer
                if (*p == *j) { //If our polymer is *the* polymer
                    v.push_back(elem); //We add the connection to our vector of connections for this polymer
                    indexs.push_back(elem->getIndexes()[i]); //We add the index to the index vector for this polymer
                }
            }
        }
        polymer_connections.push_back(v); //Once looped all connections, we add this polymers connections to the conglomerate vector
        polymer_connection_indexes.push_back(indexs); //And the indexes
    }

    for(int i=0; i<polymer_connections.size(); i++) { //Then loop the polymers again
        for (int k = 0; k < polymer_connections[i].size(); k++) { // sort into order
            for (int j = 0; j < polymer_connections[i].size()-1; j++) {
                if (polymer_connection_indexes[i][j] > polymer_connection_indexes[i][j + 1]) {
                    int temp = polymer_connection_indexes[i][j];
                    Connection * temporary = polymer_connections[i][j];
                    polymer_connection_indexes[i][j]=polymer_connection_indexes[i][j+1];
                    polymer_connections[i][j] = polymer_connections[i][j + 1];
                    polymer_connection_indexes[i][j+1]=temp;
                    polymer_connections[i][j + 1] = temporary;
                }
            }
        }
    }
}

vector<vector<Connection * >> Conglomerate::getPolymerConnections(){
    return polymer_connections;
}

vector<vector<int>> Conglomerate::getPolymerConnectionIndexes(){
    return polymer_connection_indexes;
}

void Conglomerate::updateTailUnbindingSites(){
    tail_unbinding_sites=0;
    tail_unbinding_connections.clear();
    updatePolymersInConglomerate(); //This bloody guy again
    updatePolymerConnections();

    // Go through all polymers

    for(int i=0; i<polymer_connections.size(); i++) {

        vector<Connection *> cons = polymer_connections[i];

        // If there are 0, 1, or 2 connections on one polymer then all connections must be unbindable
        if (polymer_connections[i].size() < 3) {
            tail_unbinding_sites = tail_unbinding_sites + polymer_connections[i].size();
        } else { // If there are more than two connections
            // We check to see how many are surrounded by template bonds
            int middle_connections=0;
            for (int k = 2; k < polymer_connections[i].size(); k++) {
                if (polymer_connection_indexes[i][k-2] == polymer_connection_indexes[i][k]-2) {
                    middle_connections++;
                    cons.erase(cons.begin()+k-1);
                }
            }
            tail_unbinding_sites=tail_unbinding_sites+polymer_connections[i].size()-middle_connections;
        }

        for(auto & elem : cons){
            bool in_vector = false;
            for(auto & elemen : tail_unbinding_connections){
                if(*elem==*elemen){
                    in_vector=true;
                }
            }
            if(!in_vector) {
                tail_unbinding_connections.push_back(elem);
            }
        }
    }
    tail_unbinding_sites=tail_unbinding_sites/2;
}

int Conglomerate::getTailUnbindingSites(){
    return tail_unbinding_sites;
}

int Conglomerate::getTailBindingSites(){
    return tail_binding_sites;
}

vector<Connection *> Conglomerate::getTailUnbindingConnections(){
    return tail_unbinding_connections;
}

vector<Connection *> Conglomerate::getTailBindingConnections(){
    return tail_binding_connections;
}

void Conglomerate::updateTailBindingSites(){
    //Tail unbinding sites that are next to a free binding site
    //Need to also check neighbouring polymers - dont double count
    //Make a list of all connections rather than counting?

    // Loop through polymer connections
    // If there is a free polymer in tail and there is a free binding site next to it
    // Or if there is a free tail next to it - separate count and half end result

    tail_binding_sites = 0;
    tail_binding_connections.clear();

    updatePolymersInConglomerate(); //This bloody guy again
    updatePolymerConnections();

    //ind!=0
    //ind-1!=ind[-1]
    // if j=0 and  ind!=0 then there will be a tail before

    for(int i=0; i<polymers_in_conglomerate.size(); i++) { //Loop through polymers in conglomerate
        int longness = polymer_connections[i].size(); // Find the number of connections on this polymer
        for(int j=0; j<longness; j++){ // Loop through the connections
            int ind = polymer_connection_indexes[i][j]; // This is the connection index
            if(j==0 && ind!=0){
                //tail site ind-1; direction +1
                tuple<Polymer *, int> possible_binding_site = make_tuple(polymers_in_conglomerate[i], ind-1);
                if(tailConnectionOptions(polymer_connections[i][j], polymers_in_conglomerate[i], 1, possible_binding_site)){
                    tail_binding_sites++;
                }
            } else if(j>0){
                if(polymer_connection_indexes[i][j-1]!=ind-1){ // If the neighbour is also connected then there is no tail before
                    //tail site ind-1; direction +1
                    tuple<Polymer *, int> possible_binding_site = make_tuple(polymers_in_conglomerate[i], ind-1);
                    if(tailConnectionOptions(polymer_connections[i][j], polymers_in_conglomerate[i], 1, possible_binding_site)){
                        tail_binding_sites++;
                    }
                }
            }

            if(j==longness-1 && ind!=polymers_in_conglomerate[i]->getLength()-1) {
                //tail site ind+1; direction -1
                tuple<Polymer *, int> possible_binding_site = make_tuple(polymers_in_conglomerate[i], ind + 1);
                if (tailConnectionOptions(polymer_connections[i][j], polymers_in_conglomerate[i], -1,
                                          possible_binding_site)) {
                    tail_binding_sites++;
                }
            } else if(j<longness-1){
                if(polymer_connection_indexes[i][j+1]!=ind+1){
                    //tail site ind+1; direction -1
                    tuple<Polymer *, int> possible_binding_site = make_tuple(polymers_in_conglomerate[i], ind+1);
                    if(tailConnectionOptions(polymer_connections[i][j], polymers_in_conglomerate[i], -1, possible_binding_site)){
                        tail_binding_sites++;
                    }
                }
            }
        }

    }
    tail_binding_sites = tail_binding_sites/2;
    vector<int> repeats;
    for(int j=0; j<tail_binding_connections.size(); j++){
        for(int i=j+1; i<tail_binding_connections.size(); i++){
            if(*tail_binding_connections[j]==*tail_binding_connections[i]){
                repeats.push_back(i);
            }
        }
    }
    for(int i=repeats.size(); i>0; i--) {
        tail_binding_connections.erase(tail_binding_connections.begin() + i);
    }
}

bool Conglomerate::tailConnectionOptions(Connection *con, Polymer * p, int direction, tuple<Polymer *, int > original_site){

    vector<Polymer *> poly = con->getPolymers(); // get polymers in connection
    vector<int> ind = con->getIndexes(); // get indexes in connection
    Polymer * connected_polymer;
    int connected_index;
    int this_index;

    for(int ite=0; ite<2; ite++){
        if(*poly[ite]==*p){
            this_index=ind[ite]; //This is the index on polymer which is connected to p
        } else {
            connected_polymer=poly[ite]; //This is the polymer connected to p
            connected_index=ind[ite]; //This is the index on polymer which is connected to p
        }
    }

    if(direction == 1){ //If we are at the end of the polymer then we cant bind
        if(connected_index == connected_polymer->getLength()-1){
            return false;
        }
    } else { //If we are at the end of the polymer then we cant bind
        if(connected_index == 0){
            return false;
        }
    }

    int connected_polymer_number; //Find the polymer we are trying to bind to
    for(int i=0; i<polymers_in_conglomerate.size(); i++){
        if(*polymers_in_conglomerate[i]==*connected_polymer){
            connected_polymer_number = i;
            break;
        }
    }

    for(int i=0; i<polymer_connection_indexes[connected_polymer_number].size(); i++){
        if(polymer_connection_indexes[connected_polymer_number][i]==connected_index+direction){
            //a connection exists on the desired monomer and so no tail can bind
            return false;
        }
    }

    if(connected_polymer->getSequence()[connected_index+direction]!=p->getSequence()[this_index-direction]){
        //If the types are not the same then they cannot bind
        return false;
    }

    /*
     * This is for looping
    for(auto & elem : connections){ //Search all connections for one on the neighbouring position
        for(int ite=0; ite<2; ite++){
            if(elem->getPolymers()[ite]==connected_polymer && elem->getIndexes()[ite]==connected_index+direction){


                //This has to loop as a junction with any number of polymers can exist
                return tailConnectionOptions( elem, elem->getPolymers()[ite], direction, original_site);
            }
        }
    }
    */



    //If there is no connection then a new one can be made
    tuple<Polymer *, int > two = make_tuple(connected_polymer, connected_index+direction);
    tail_binding_connections.push_back(new Connection(original_site, two));
    return true;
}


void Conglomerate::updateValidNeighboursBinding() {
    //Go through connections
    //Find connections at the end or beginning of a polymer
    //Check the neighbour - other polymers?
    //Divide number by two
    valid_neighbours_binding=0;
    valid_unconnected_neighbours.clear();

    for(auto & elem : connections){
        for(int i=0; i<2; i++){
            if(elem->getIndexes()[i]==0){
                //At beginning of a polymer
                if(validNeighbourBindingOptions(elem, elem->getPolymers()[i], 1, elem->getPolymers()[i])){
                    valid_neighbours_binding++;
                }
            }
            if(elem->getIndexes()[i]==elem->getPolymers()[i]->getLength()-1){
                //At end of polymer
                if(validNeighbourBindingOptions(elem, elem->getPolymers()[i], -1, elem->getPolymers()[i])){
                    valid_neighbours_binding++;
                }
            }
        }
    }
    valid_neighbours_binding = valid_neighbours_binding/2;

    vector<int> repeats;
    for(int j=0; j<valid_unconnected_neighbours.size(); j++){
        for(int i=j+1; i<valid_unconnected_neighbours.size(); i++){
            if(*valid_unconnected_neighbours[j]==*valid_unconnected_neighbours[i]){
                repeats.push_back(i);
            }
        }
    }
    for(int i=repeats.size(); i>0; i--) {
        valid_unconnected_neighbours.erase(valid_unconnected_neighbours.begin() + i);
    }

}

int Conglomerate::getValidNeighboursBinding(){
    return valid_neighbours_binding;
}

bool Conglomerate::validNeighbourBindingOptions(Connection * con, Polymer * p, int direction, Polymer * original_polymer) {
    vector<Polymer *> poly = con->getPolymers(); // get polymers in connection
    vector<int> ind = con->getIndexes(); // get indexes in connection
    Polymer * connected_polymer;
    int connected_index;

    for(int ite=0; ite<2; ite++){
        if(!(*poly[ite]==*p)){
            connected_polymer=poly[ite]; //This is the polymer connected to p
            connected_index=ind[ite]; //This is the index on polymer which is connected to p
        }
    }

    for(auto & elem : connections){ //Search all connections for one on the neighbouring position
        for(int ite=0; ite<2; ite++){
            if(elem->getPolymers()[ite]==connected_polymer && elem->getIndexes()[ite]==connected_index+direction){
                // If a connection exists,then we check the connection to see if it's at the end of the polymer

                /*
                 * Checks for looping
                 * if(ite==0){
                    if(*elem->getPolymers()[1]==*original_polymer){
                        return false;
                    }
                } else {
                    if(*elem->getPolymers()[0]==*original_polymer){
                        return false;
                    }
                }*/


                if(direction==1){
                    if(ite==0){
                        if(elem->getIndexes()[1]==elem->getPolymers()[1]->getLength()-1){
                            UnconnectedNeighbours * neighbours = new UnconnectedNeighbours(elem->getPolymers()[1], p);
                            valid_unconnected_neighbours.push_back(neighbours);
                            return true;
                        }
                    } else {
                        if(elem->getIndexes()[0]==elem->getPolymers()[0]->getLength()-1){
                            UnconnectedNeighbours * neighbours = new UnconnectedNeighbours(elem->getPolymers()[0], p);
                            valid_unconnected_neighbours.push_back(neighbours);
                            return true;
                        }
                    }
                } else {
                    if(ite==0){
                        if(elem->getIndexes()[1]==0){
                            UnconnectedNeighbours * neighbours = new UnconnectedNeighbours(p, elem->getPolymers()[1]);
                            valid_unconnected_neighbours.push_back(neighbours);
                            return true;
                        }
                    } else {
                        if(elem->getIndexes()[0]==0){
                            UnconnectedNeighbours * neighbours = new UnconnectedNeighbours(p, elem->getPolymers()[0]);
                            valid_unconnected_neighbours.push_back(neighbours);
                            return true;
                        }
                    }
                }

                //If a connection exists but it's not the end of the polymer, we check on the connection
                // This is for looping
                //return validNeighbourBindingOptions(elem, elem->getPolymers()[ite], direction, original_polymer);

            }
        }
    }

    //If no connection exists then there is no valid neighbour
    return false;
}

void Conglomerate::updateValidNeighboursUnbinding(){
    updatePolymersInConglomerate();
    updatePolymerConnections();
    valid_neighbours_unbinding=0;
    valid_connected_neighbours.clear();

    for(int j=0; j<polymer_connection_indexes.size(); j++){
        int longness = polymer_connection_indexes[j].size();
        for(int i=0; i<longness-1; i++){
            if(polymer_connection_indexes[j][i]+1==polymer_connection_indexes[j][i+1]){
                vector<Polymer *> po_pol_one = polymer_connections[j][i]->getPolymers();
                vector<Polymer *> po_pol_two = polymer_connections[j][i+1]->getPolymers();
                if(*po_pol_one[0]==*po_pol_two[0] && *po_pol_one[1]==*po_pol_two[1]){
                    valid_neighbours_unbinding++;
                    ConnectedNeighbours * neighbours = new ConnectedNeighbours(polymers_in_conglomerate[j], polymer_connection_indexes[j][i], polymer_connection_indexes[j][i+1]);
                    valid_connected_neighbours.push_back(neighbours);
                } else if (*po_pol_one[0]==*po_pol_two[1] && *po_pol_one[1]==*po_pol_two[0]){
                    valid_neighbours_unbinding++;
                    ConnectedNeighbours * neighbours = new ConnectedNeighbours(polymers_in_conglomerate[j], polymer_connection_indexes[j][i], polymer_connection_indexes[j][i+1]);
                    valid_connected_neighbours.push_back(neighbours);
                }
            }
        }
    }
}

int Conglomerate::getValidNeighboursUnbinding(){
    return valid_neighbours_unbinding;
}

vector<ConnectedNeighbours *> Conglomerate::getValidConnectedNeighbours(){
    return valid_connected_neighbours;
}

vector<UnconnectedNeighbours *> Conglomerate::getValidUnconnectedNeighbours(){
    return valid_unconnected_neighbours;
}

bool Conglomerate::operator==(Conglomerate c){
    if(index==c.getIndex()){
        vector<Connection *> cons = c.getConnections();
        if(connections.size()==cons.size()) {
            for (int i = 0; i < connections.size(); i++) {
                if(!(*connections[i]==*cons[i])){
                    return false;
                }
            }
        } else {
            return false;
        }
    }
    return false;
}

Polymer * Conglomerate::joinPolymers(UnconnectedNeighbours * neighbours){
    Polymer * pOne = neighbours->getPolymers()[0];
    int p_one_orig_length = pOne->getLength();
    Polymer * pTwo = neighbours->getPolymers()[1];
    pOne->addPolymer(pTwo, three_prime); //increase length of pOne and add sequence
    int p_two_length = pTwo->getLength(); //Retain length of pTwo as all connections on pOne will be shifted by this length

    for(auto & connection : connections){ //Loop all connections on conglomerate
        vector<Polymer *> connected_polymers = connection->getPolymers();
        vector<int> polymers_indexes = connection->getIndexes();
        for(int i=0; i<2; i++){
            if(*connected_polymers[i]==*pTwo){//Find all connections using pTwo
                //We need to change the polymer of the connections as this polymer is being removed
                connection->changePolymer(i, pOne);
                connection->setIndex(i, polymers_indexes[i]+p_two_length);

                if(i==0) {
                    pOne->addConnection(connected_polymers[1]);
                }
                if(i==1) {
                    pOne->addConnection(connected_polymers[0]);
                }
            }
        }
    }

    //Find polymer in list
    int polymer_to_be_removed = -1;
    for(int i=0; i<polymers_in_conglomerate.size(); i++){
        if(*pTwo == *polymers_in_conglomerate[i]){
            polymer_to_be_removed = i;
            break;
        }
    }
    //remove polymer from list
    if(polymer_to_be_removed>0){
        polymers_in_conglomerate.erase(polymers_in_conglomerate.begin() + polymer_to_be_removed);
    }

    //Find connection in list
    int neighbours_to_be_removed = -1;
    for(int i=0; i<valid_unconnected_neighbours.size(); i++){
        if(*neighbours == *valid_unconnected_neighbours[i]){
            neighbours_to_be_removed = i;
            break;
        }
    }
    //remove connection from list
    if(neighbours_to_be_removed>0){
        valid_unconnected_neighbours.erase(valid_unconnected_neighbours.begin() + neighbours_to_be_removed);
    }
    ConnectedNeighbours * new_neighbour = new ConnectedNeighbours(pOne, p_one_orig_length, p_one_orig_length+1);
    valid_connected_neighbours.push_back(new_neighbour);

    valid_neighbours_binding--;
    valid_neighbours_unbinding+=2;
    backbone_bonds++;

    return pTwo;
}

Polymer * Conglomerate::separatePolymers(ConnectedNeighbours * neighbours){
    Polymer * pOne = neighbours->getPolymer();
    Polymer * pTwo = pOne->cutPolymer(neighbours->getIndexes()[1]);

    int p_one_length = pOne->getLength();

    for(auto & connection : connections){
        vector<Polymer *> connected_polymers = connection->getPolymers();
        vector<int> polymers_indexes = connection->getIndexes();
        for(int i=0; i<2; i++){
            if(*connected_polymers[i]==*pOne && polymers_indexes[i]>neighbours->getIndexes()[0]){
                //Find all connections using pOne after separation index
                //change polymer to new polymer
                connection->changePolymer(i, pTwo);
                //change index to remove length of first polymer
                connection->setIndex(i, polymers_indexes[i]-p_one_length);

                //Change polymer connection list
                if(i==0) {
                    pTwo->addConnection(connected_polymers[1]);
                    if(pOne->removeConnection(connected_polymers[1])){
                        updateConnectivity();
                    }
                }
                if(i==1) {
                    pTwo->addConnection(connected_polymers[0]);
                    if(pOne->removeConnection(connected_polymers[0])){
                        updateConnectivity();
                    }
                }
            }
        }
    }

    polymers_in_conglomerate.push_back(pTwo);

    //Find connection in list
    for(int i=0; i<valid_connected_neighbours.size(); i++){
        if(*neighbours == *valid_connected_neighbours[i]){
            valid_connected_neighbours.erase(valid_connected_neighbours.begin() + i);
            //remove connection from list
            break;
        }
    }

    UnconnectedNeighbours * new_neighbours = new UnconnectedNeighbours(pOne, pTwo);
    valid_unconnected_neighbours.push_back(new_neighbours);

    valid_neighbours_binding++;
    valid_neighbours_unbinding--;
    backbone_bonds--;

    return pTwo;
}