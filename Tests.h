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

    bool testPolymerInitialisation();
    bool testAddPolymer();
    bool testPolymerEquals();
    bool testCutPolymer();

    bool testConnectionInitialisation();
    bool testConnectionEquals();
    bool testEditConnection();

    bool testConnectedNeighboursInitialisation();
    bool testConnectedNeighboursEquals();

    bool testUnconnectedNeighboursInitialisation();
    bool testUnconnectedNeighboursEquals();

    bool testUpdatePolymersInConglomerate();
    bool testUpdatePolymerConnections();
    bool testUpdateAvailableTemplateBonds();
    bool testGetPossibleSites();
    bool testUpdateTailUnbindingSites();
    bool testUpdateTailBindingSites();
    bool testConnectionOptions();
    bool testUpdateValidNeighboursBinding();
    bool testUpdateValidNeighboursUnbinding();
    bool testConglomerateEquals();
    bool testJoinPolymer();
    bool testSeparatePolymer();
    bool testGetTree();
    bool testUpdateConnectivity();
    bool testRemoveConnection();
    bool testMonomerRebind();

    bool testPerformFunctions();
    bool testSystemAbility();

};


#endif //TESTTWO_TESTS_H
