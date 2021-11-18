//
// Created by Nicholas Simpson on 20/10/2021.
//

#define three_prime 0
#define five_prime 1

#include "Polymer.h"
using namespace std;

Polymer::Polymer(int fam, vector<int> s) {
    family=fam;
    sequence = s;
    length = s.size();
}

int Polymer::getIndex(){
    return index;
}

int Polymer::getFamily(){
    return family;
}

void Polymer::setIndex(int ind) {
    index=ind;
}

vector<int> Polymer::getSequence(){
    return sequence;
}

int Polymer::getLength(){
    return length;
}

void Polymer::addPolymer(Polymer * poly, int pos){
    vector<int> seq = poly->getSequence();
    if(pos==three_prime){
        sequence.insert(sequence.begin(), seq.begin(), seq.end());
    }
    else {
        sequence.insert(sequence.end(), seq.begin(), seq.end());
    }
    length = length + seq.size();
}

Polymer * Polymer::cutPolymer(int index){
    vector<int> new_seq;
    for(int i=index; i<length; i++){
        new_seq.push_back(sequence[i]);
    }
    sequence.erase(sequence.begin()+index, sequence.end());
    length = index;

    return new Polymer(family, new_seq);
}

vector<tuple<Polymer *, int>> Polymer::getConnections(){
    return connections;
}

void Polymer::clearConnections(){
    connections.clear();
}

void Polymer::addConnection(Polymer * p){
    //connections holds the polymer that is connected, and the number of connections between the two polymers

    if(*this == *p){
        cout << "ERROR: Polymers cannot self connect" << endl;
        return;
    }
    int connection_count = 0;
    for(auto & pol : connections){
        connection_count+=get<1>(pol);
    }

    if(connection_count==length){
        cout << "This polymer: " << index << " Other polymer: " <<  p->getIndex() << endl;
        cout << "Length: " << length << endl;
        for(auto & elem : connections){
            cout << "Polymer: " << get<0>(elem)->getIndex() << " Number: " << get<1>(elem) << endl;
        }
        cout << "ERROR: Cannot add connection to this polymer" << endl;
        return;
    }
    bool not_connected = true;
    for(int i=0; i<connections.size(); i++){ //Loop connections on polymer
        if(*p==*get<0>(connections[i])){ // If this polymer is already connected
            int count = get<1>(connections[i]); //find number of connections between polymers
            connections[i] = make_tuple(p, count+1); //Add another connection
            not_connected = false;
        }
    }
    if(not_connected){
        connections.push_back(make_tuple(p, 1)); //If they aren't already connected, we make a new element with new polymer and 1 connection
    }
}

bool Polymer::removeConnection(Polymer * p){ //Returns true if no connections remain
    for(int i=0; i<connections.size(); i++){
        if(*get<0>(connections[i])==*p){
            int count = get<1>(connections[i]);
            if(count==1) {
                connections.erase(connections.begin() + i);
                return true;
            } else {
                connections[i] = make_tuple(p, count-1);
                return false;
            }
        }
    }
    cout << "ERROR: No connection to be removed" << endl;
    return false;
}

bool Polymer::operator==(Polymer p) {
    if (p.getLength() == length) {
        vector<int> seq = p.getSequence();
        for (int i = 0; i < length; i++) {
            if(sequence[i]!=seq[i]){
                return false;
            }
        }
        if(family!=p.getFamily()){
            return false;
        }
        if(p.getIndex()==index) { //This is probs all thats needed
            return true;
        }
    }
    return false;
}
