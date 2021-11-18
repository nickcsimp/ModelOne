//
// Created by Nicholas Simpson on 20/10/2021.
//
#include <iostream>
#include <vector>
#include "Polymer.h"

using namespace std;
#ifndef TESTTWO_CONNECTION_H
#define TESTTWO_CONNECTION_H


class Connection{
private:
    tuple<Polymer *, int> one;
    tuple<Polymer *, int> two;
public:
    Connection(tuple<Polymer *, int> one, tuple<Polymer *, int> two) : one(one), two(two) {

    }

    vector<Polymer *> getPolymers();

    vector<int> getIndexes();

    void setIndex(int which_polymer, int new_index);

    void changePolymer(int which_polymer, Polymer * new_polymer);

    bool operator==(Connection c);
};

#endif //TESTTWO_CONNECTION_H
