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

    /*bool testSystemInitialisation();
    bool testChangeMonomerCount();
    bool testChangeDimerCount();
    bool testPolymerParameters();

    bool testUpdateTailBindingSites();
    bool testTailConnectionOptions();
    bool testUpdateValidNeighbour();
    bool testValidNeighbourOptions();
    bool testSystemGetters();*/

    bool testPolymerInitialisation();
    bool testAddPolymer();
    bool testPolymerEquals();
    bool testCutPolymer();
    bool testPolymerAddConnection();
    bool testPolymerRemoveConnection();

    bool testConnectionInitialisation();
    bool testConnectionEquals();
    bool testEditConnection();

    bool testConnectedNeighboursInitialisation();
    bool testConnectedNeighboursEquals();

    bool testUnconnectedNeighboursInitialisation();
    bool testUnconnectedNeighboursEquals();

    bool testDimerInitialisation();
    bool testDimerEquals();

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

    bool testChooseBond();
    bool testGetRates();
    bool testGetEverything();
    bool testGetHeadBinding();
    bool testGetTailBinding();
    bool testGetHeadUnbinding();
    bool testGetTailUnbinding();
    bool testGetConnectedNeighbours();
    bool testGetUnconnectedNeighbours();
    bool testGetAvailableHeadTailSites();

    bool testChooseHeadBinding();
    bool testChooseTailBinding();
    bool testChooseHeadUnbinding();
    bool testChooseTailUnbinding();
    bool testChooseNeighboursUnbind();
    bool testChooseNeighboursBind();
    bool testChooseHeadConnection();
    bool testChooseTailConnection();


    //bool testConglomerateInitialisation();
    bool testUpdateRates();
};


#endif //TESTTWO_TESTS_H
