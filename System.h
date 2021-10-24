//
// Created by Nicholas Simpson on 20/10/2021.
//

#include <iostream>
#include <vector>
#include "Polymer.h"
#include "Conglomerate.h"
using namespace std;

#ifndef TESTTWO_SYSTEM_H
#define TESTTWO_SYSTEM_H

class System {
private:
    int monomers;
    int dimers;
    vector<Polymer *> polymers;
    vector<Conglomerate *> conglomerates;
public:

    System(int monomerCount);

    int getMonomers();

    int getDimers();

    void changeMonomerCount(int increase);

    void changeDimerCount(int increase);

    vector<Polymer *> getPolymers();

    vector<Conglomerate *> getConglomerates();

    void addPolymer(Polymer *p);

    void addConglomerate(Conglomerate *c);

    void popPolymer();

    void joinPolymers(int ind_one, int ind_two);

    void print();
};


#endif //TESTTWO_SYSTEM_H
