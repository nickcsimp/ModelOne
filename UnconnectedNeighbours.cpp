//
// Created by Nicholas Simpson on 03/11/2021.
//

#include "UnconnectedNeighbours.h"

//TODO order?
UnconnectedNeighbours::UnconnectedNeighbours(Polymer* polyOne, Polymer* polyTwo){
    polymerOne = polyOne;
    polymerTwo = polyTwo;
    if(polyOne==polyTwo){
        cout << "ERROR: the same polymer cannot be an unconnected neighbour" << endl;
        //Todo: make this delete the connection
    }
}

vector<Polymer*> UnconnectedNeighbours::getPolymers(){
    vector<Polymer *> output;
    output.push_back(polymerOne);
    output.push_back(polymerTwo);
    return output;
}

bool UnconnectedNeighbours::operator==(UnconnectedNeighbours neighbour){
    if(*neighbour.getPolymers()[0]==*polymerOne && *neighbour.getPolymers()[1]==*polymerTwo){
        return true;
    }

    if(*neighbour.getPolymers()[1]==*polymerOne && *neighbour.getPolymers()[0]==*polymerTwo){
        return true;
    }

    return false;
}