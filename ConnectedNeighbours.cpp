//
// Created by Nicholas Simpson on 03/11/2021.
//

#include "ConnectedNeighbours.h"

ConnectedNeighbours::ConnectedNeighbours(Polymer * poly, int indOne, int indTwo){
    polymer = poly;
    indexOne = indOne;
    indexTwo = indTwo;
    if(indOne!=indTwo+1 && indTwo!=indOne+1){
        cout << "ERROR: Neighbours must be adjacent" << endl;
        //Todo: Somehow sort this
    }
}
Polymer * ConnectedNeighbours::getPolymer(){
    return polymer;
}
vector<int> ConnectedNeighbours::getIndexes(){
    vector<int> output;
    output.push_back(indexOne);
    output.push_back(indexTwo);
    return output;
}

bool ConnectedNeighbours::operator==(ConnectedNeighbours neighbours){
    if(!(*neighbours.getPolymer()==*polymer)){
        return false;
    }

    if(neighbours.getIndexes()[0] == indexOne && neighbours.getIndexes()[1] == indexTwo){
        return true;
    }

    if(neighbours.getIndexes()[1] == indexOne && neighbours.getIndexes()[0] == indexTwo){
        return true;
    }

    return false;
}