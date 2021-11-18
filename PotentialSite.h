//
// Created by Nicholas Simpson on 15/11/2021.
//

#ifndef TESTTWO_POTENTIALSITE_H
#define TESTTWO_POTENTIALSITE_H

using namespace std;

#include "Polymer.h"
#include "Conglomerate.h"


class PotentialSite {
private:
    Polymer * polymer;
    int index;
    Conglomerate * conglomerate;
    int family;
    int type;
    bool head;

public:
    PotentialSite(Polymer * p, int ind, Conglomerate * con);
    Polymer * getPolymer();
    int getIndex();
    Conglomerate * getConglomerate();
    int getFamily();
    int getType();
    bool getHead();
};


#endif //TESTTWO_POTENTIALSITE_H
