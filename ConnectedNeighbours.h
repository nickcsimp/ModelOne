//
// Created by Nicholas Simpson on 03/11/2021.
//

#ifndef TESTTWO_CONNECTEDNEIGHBOURS_H
#define TESTTWO_CONNECTEDNEIGHBOURS_H


#include "Polymer.h"

class ConnectedNeighbours {
private:
    Polymer * polymer;
    int indexOne;
    int indexTwo;

public:
    ConnectedNeighbours(Polymer * poly, int indOne, int indTwo);
    Polymer * getPolymer();
    vector<int> getIndexes();
};


#endif //TESTTWO_CONNECTEDNEIGHBOURS_H
