//
// Created by Nicholas Simpson on 03/11/2021.
//

#include "ConnectedNeighbours.h"

ConnectedNeighbours::ConnectedNeighbours(Polymer * poly, int indOne, int indTwo){
    polymer = poly;
    indexOne = indOne;
    indexTwo = indTwo;
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