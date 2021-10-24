//
// Created by Nicholas Simpson on 20/10/2021.
//

#include "Conglomerate.h"
using namespace std;

Conglomerate::Conglomerate(vector<Connection *> con){
    connections = con;
}

Conglomerate::Conglomerate(Polymer *p, int index, int monomer_type){
    vector<int> s = {monomer_type};
    Polymer *polymer = new Polymer(s);
    tuple<Polymer *, int> t_one = make_tuple(p, index);
    tuple<Polymer *, int> t_two = make_tuple(polymer, 0);
    Connection *c = new Connection(t_one, t_two);
    connections.push_back(c);
}

Conglomerate::Conglomerate(Polymer * p_one, int index_one, Polymer * p_two, int index_two){
    tuple<Polymer *, int> t_one = make_tuple(p_one, index_one);
    tuple<Polymer *, int> t_two = make_tuple(p_two, index_two);
    Connection *c = new Connection(t_one, t_two);
    connections.push_back(c);
}

int Conglomerate::getIndex(){
    return index;
}

void Conglomerate::setIndex(int ind) {
    index=ind;
}

void Conglomerate::addConnection(Connection* con){
    connections.push_back(con);
    updatePolymersInConglomerate();
}

void Conglomerate::removeConnection(Connection* con){
    for(int i=0; i<connections.size(); i++){
        if(con == connections[i]){
            connections.erase(connections.begin()+i);
        }
    }
    if(connections.size()==0){
        remove();
    }
    updatePolymersInConglomerate();
}

vector<Connection *> Conglomerate::getConnections(){
    return connections;
}

void Conglomerate::updatePolymersInConglomerate() {
    for(auto & elem : connections){
        vector<Polymer *> v= elem->getPolymers();
        for(auto & eleme : v){
            bool in_vector = false;
            for(auto & elemen : polymers_in_conglomerate){
                if(eleme==elemen){
                    in_vector = true;
                }
            }
            if(!in_vector){
                polymers_in_conglomerate.push_back(eleme);
            }
        }
    }
}

void Conglomerate::updateTemplateBond(){
    template_bonds = 0;
    for(auto & elem : polymers_in_conglomerate){
        template_bonds=template_bonds+elem->getLength();
    }
    template_bonds=template_bonds-(2*connections.size());
}

void Conglomerate::updateBackboneBonds(){
    backbone_bonds=0;
    for(auto & elem : polymers_in_conglomerate){
        backbone_bonds=backbone_bonds+elem->getLength()-1;
    }
}

void Conglomerate::updatePolymerConnections(){//TODO check this

    for(int j=0; j<polymers_in_conglomerate.size(); j++){
        vector<Connection *> v;
        vector<int> indexs;
        for(auto & elem : connections) {
            for (int i=0; i<2; i++) {
                Polymer *p = elem->getPolymers()[i];
                if (p == polymers_in_conglomerate[j]) {
                    v.push_back(elem);
                    indexs.push_back(elem->getIndexes()[i]);
                }
            }
        }
        polymer_connections.push_back(v);
        polymer_connection_indexes.push_back(indexs);
    }

    // Go through all polymers
    for(int i=0; i<polymers_in_conglomerate.size(); i++) {
        int longness = polymer_connections[i].size();
        // sort into order
        for (int k = 0; k < longness; k++) {
            for (int j = 0; j < longness; j++) {
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

void Conglomerate::updateTailUnbindingSites(){ //TODO check this
    tail_unbinding_sites=0;
    tail_unbinding_connections.clear();

    // Go through all polymers
    for(int i=0; i<polymers_in_conglomerate.size(); i++) {
        int longness = polymer_connections[i].size();
        for(auto & elem : polymer_connections[i]){
            tail_unbinding_connections.push_back(elem);
        }
        // If there are 0, 1, or 2 connections on one polymer then all connections must be unbindable
        if (polymer_connections[i].size() < 3) {
            tail_unbinding_sites = tail_unbinding_sites + polymer_connections[i].size();
        } else { // If there are more than two connections
            // We check to see how many are surrounded by template bonds
            int middle_connections=0;
            for (int k = 2; k < longness; k++) {
                if (polymer_connection_indexes[i][k-2] == polymer_connection_indexes[i][k]) {
                    middle_connections++;
                    tail_unbinding_connections.erase(tail_unbinding_connections.begin()+k-1);
                }
            }
            tail_unbinding_sites=tail_unbinding_sites+polymer_connections[i].size()-middle_connections;
        }
    }
}

void Conglomerate::updateTailBindingSites(){//TODO this
    //Tail unbinding sites that are next to a free binding site
    //Need to also check neighbouring polymers - dont double count
    //Make a list of all connections rather than counting?

    // Loop through polymer connections
    // If there is a free polymer in tail and there is a free binding site next to it
    // Or if there is a free tail next to it - separate count and half end result

    tail_binding_sites = 0;
    tail_unbinding_connections.clear();

    //ind!=0
    //ind-1!=ind[-1]
    // if j=0 and  ind!=0 then there will be a tail before

    for(int i=0; i<polymers_in_conglomerate.size(); i++) { //Loop through polymers in conglomerate
        int longness = polymer_connections[i].size(); // Find the number or connections on this polymer
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

            if(j==longness && ind!=polymers_in_conglomerate[i]->getLength()) {//TODO: check get length checks could be getlength-1
                //tail site ind+1; direction -1
                tuple<Polymer *, int> possible_binding_site = make_tuple(polymers_in_conglomerate[i], ind + 1);
                if (tailConnectionOptions(polymer_connections[i][j], polymers_in_conglomerate[i], -1,
                                          possible_binding_site)) {
                    tail_binding_sites++;
                }
            } else if(j<longness){
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
    //tail_binding_connections will have duplicates, remove these

}

bool Conglomerate::tailConnectionOptions(Connection *con, Polymer * p, int direction, tuple<Polymer *, int > original_site){

    vector<Polymer *> poly = con->getPolymers(); // get polymers in connection
    vector<int> ind = con->getIndexes(); // get indexes in connection
    Polymer * connected_polymer;
    int connected_index;

    for(int ite=0; ite<2; ite++){
        if(poly[ite]!=p){
            connected_polymer=poly[ite]; //This is the polymer connected to p
            connected_index=ind[ite]; //This is the index on polymer which is connected to p
        }
    }

    if(direction == 1){
        if(connected_index == connected_polymer->getLength()){
            return false;
        }
    } else {
        if(connected_index == 0){
            return false;
        }
    }

    for(auto & elem : connections){ //Search all connections for one on the neighbouring position
        for(int ite=0; ite<2; ite++){
            if(elem->getPolymers()[ite]==connected_polymer && elem->getIndexes()[ite]==connected_index+direction){
                // If a connection exists,then we check the connection to see if there is a free site on that
                // This has to loop as a junction with any number of polymers can exist
                return tailConnectionOptions( elem, elem->getPolymers()[ite], -direction, original_site);
            }
        }
    }

    //If there is no connection then a new one can be made
    tuple<Polymer *, int > two = make_tuple(connected_polymer, connected_index+direction);
    tail_binding_connections.push_back(new Connection(original_site, two));
    return true;
}


void Conglomerate::updateValidNeighbours() {
    //Go through connections
    //Find connections at the end or beginning of a polymer
    //Check the neighbour - other polymers?
    //Divide number by two
    valid_neighbours=0;

    for(auto & elem : connections){
        for(int i=0; i<2; i++){
            if(elem->getIndexes()[i]==0){
                //At beginning of a polymer
                validNeighbourOptions(elem, elem->getPolymers()[i], 1);
            }
            if(elem->getIndexes()[i]==elem->getPolymers()[i]->getLength()){
                //At end of polymer
                validNeighbourOptions(elem, elem->getPolymers()[i], -1);
            }
        }
    }
    valid_neighbours = valid_neighbours/2;
}

bool Conglomerate::validNeighbourOptions(Connection * con, Polymer * p, int direction) {
    vector<Polymer *> poly = con->getPolymers(); // get polymers in connection //TODO 10 repeated lines
    vector<int> ind = con->getIndexes(); // get indexes in connection
    Polymer * connected_polymer;
    int connected_index;

    for(int ite=0; ite<2; ite++){
        if(poly[ite]!=p){
            connected_polymer=poly[ite]; //This is the polymer connected to p
            connected_index=ind[ite]; //This is the index on polymer which is connected to p
        }
    }

    int polymer_number;
    for(int i=0; i<polymers_in_conglomerate.size(); i++){//Loop polymers
        if(polymers_in_conglomerate[i]==connected_polymer){//Find polymer we care about
            polymer_number=i;
            break;
        }
    }
    for(int j=0; j<polymer_connections[polymer_number].size(); j++){//Loop connections in polymer
        if(polymer_connection_indexes[polymer_number][j]==connected_index+direction){ //Find if there is a connection on neighbour
            //Find new polymer
            for(int k=0; k<2; k++) {
                if(polymer_connections[polymer_number][j]->getPolymers()[k]!=p){
                    if(direction==1) {
                        if(polymer_connections[polymer_number][j]->getIndexes()[k]==polymer_connections[polymer_number][j]->getPolymers()[k]->getLength()){
                            //Valid neighbour
                            valid_neighbours++;
                            return true;
                        }
                    } else {
                        if(polymer_connections[polymer_number][j]->getIndexes()[k]==0){
                            //Valid neighbour
                            valid_neighbours++;
                            return true;
                        }
                    }
                    return validNeighbourOptions(polymer_connections[polymer_number][j], polymer_connections[polymer_number][j]->getPolymers()[k], -direction);
                }
            }
        }
    }
    //No connection at any point then there can be no valid neighbour
    return false;

}

void Conglomerate::remove(){
    //TODO this
}

