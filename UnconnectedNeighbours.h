//
// Created by Nicholas Simpson on 03/11/2021.
//

#ifndef TESTTWO_UNCONNECTEDNEIGHBOURS_H
#define TESTTWO_UNCONNECTEDNEIGHBOURS_H


#include "Polymer.h"

class UnconnectedNeighbours {
private:
    Polymer * polymerOne;
    Polymer * polymerTwo;
public:
    UnconnectedNeighbours(Polymer* polyOne, Polymer* polyTwo);

    vector<Polymer*> getPolymers();
};


#endif //TESTTWO_UNCONNECTEDNEIGHBOURS_H
