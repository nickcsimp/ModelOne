//
// Created by Nicholas Simpson on 20/10/2021.
//

#define three_prime 0
#define five_prime 1

#include "Polymer.h"
using namespace std;

Polymer::Polymer(vector<int> s) {
    sequence = s;
    length = s.size();
}

int Polymer::getIndex(){
    return index;
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
    //polymer sorting out
}

Polymer * Polymer::cutPolymer(int index){
    vector<int> new_seq;
    for(int i=index; i<length; i++){
        new_seq.push_back(sequence[i]);
    }
    sequence.erase(sequence.begin()+index, sequence.end());
    length = index;

    return new Polymer(new_seq);
}

bool Polymer::operator==(Polymer p) {
    if (p.getLength() == length) {
        vector<int> seq = p.getSequence();
        for (int i = 0; i < length; i++) {
            if(sequence[i]!=seq[i]){
                return false;
            }
        }
        if(p.getIndex()==index) { //This is probs all thats needed
            return true;
        }
    }
    return false;
}

void Polymer::remove(){
    //TODO this
}