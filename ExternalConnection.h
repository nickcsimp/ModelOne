//
// Created by Nicholas Simpson on 15/11/2021.
//
#include <iostream>
#include <vector>
#include "Polymer.h"
#include "Conglomerate.h"

using namespace std;
#ifndef TESTTWO_EXTERNALCONNECTION_H
#define TESTTWO_EXTERNALCONNECTION_H


class ExternalConnection {
private:
    tuple<Polymer *, int> one;
    tuple<Polymer *, int> two;
    Conglomerate * cong_one;
    Conglomerate * cong_two;
public:
    ExternalConnection(tuple<Polymer *, int> tone, tuple<Polymer *, int> ttwo, Conglomerate * cone, Conglomerate * ctwo);

    vector<Polymer *> getPolymers();
    vector<int> getIndexes();
    vector<Conglomerate *> getConglomerates();
};


#endif //TESTTWO_EXTERNALCONNECTION_H
