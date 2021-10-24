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
};


#endif //TESTTWO_TESTS_H
