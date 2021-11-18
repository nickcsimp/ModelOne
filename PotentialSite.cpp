//
// Created by Nicholas Simpson on 15/11/2021.
//

#include "PotentialSite.h"

PotentialSite::PotentialSite(Polymer *p, int ind, Conglomerate *con) {
    polymer = p;
    index = ind;
    conglomerate = con;

    family = polymer->getFamily();
    type = polymer->getSequence()[index];

    if(index+1 == polymer->getLength()){
        head = true;
    } else {
        head = false;
    }
}

Polymer * PotentialSite::getPolymer(){
    return polymer;
}
int PotentialSite::getIndex(){
    return index;
}
Conglomerate * PotentialSite::getConglomerate(){
    return conglomerate;
}
int PotentialSite::getFamily(){
    return family;
}
int PotentialSite::getType(){
    return type;
}
bool PotentialSite::getHead(){
    return head;
}