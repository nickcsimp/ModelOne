//
// Created by Nicholas Simpson on 24/10/2021.
//

#include <iostream>
#include <vector>
#include "Polymer.h"
#include "Conglomerate.h"
#include "Connection.h"
#include "System.h"

using namespace std;

#ifndef TESTTWO_TESTS_H
#define TESTTWO_TESTS_H


class Tests {
private:

public:
    Tests();
    bool runTests();
    bool testSystemInitialisation();
    bool testChangeMonomerCount();
    bool testChangeDimerCount();
    bool testPolymerInitialisation();
    bool testPolymerParameters();
    bool testPolymerEquals();
    bool testAddPolymer();
    bool testCutPolymer();
    bool testRemovePolymer();
    bool testConnectionInitialisation();
    bool testConnectionEquals();
    bool testConnectionRemove();
    bool testConglomerateInitialisation();
    bool testConglomerateGetters();
    bool testUpdatePolymersInConglomerate();
    bool testUpdateTemplateBond();
    bool testUpdateBackboneBond();
    bool testUpdatePolymerConnections();
    bool testUpdateTailUnbindingSites();
    bool testUpdateTailBindingSites();
    bool testTailConnectionOptions();
    bool testUpdateValidNeighbour();
    bool testValidNeighbourOptions();
    bool testSystemGetters();
};


#endif //TESTTWO_TESTS_H
