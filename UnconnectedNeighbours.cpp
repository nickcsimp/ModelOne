//
// Created by Nicholas Simpson on 03/11/2021.
//

#include "UnconnectedNeighbours.h"

UnconnectedNeighbours::UnconnectedNeighbours(Polymer* polyOne, Polymer* polyTwo){
    polymerOne = polyOne;
    polymerTwo = polyTwo;
}

vector<Polymer*> UnconnectedNeighbours::getPolymers(){
    vector<Polymer *> output;
    output.push_back(polymerOne);
    output.push_back(polymerTwo);
    return output;
}