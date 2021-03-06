//
// Created by Nicholas Simpson on 20/10/2021.
//

#include <iostream>
#include <vector>

#define three_prime 0
#define five_prime 1
using namespace std;

#ifndef TESTTWO_POLYMER_H
#define TESTTWO_POLYMER_H


class Polymer {
private:
    int index ;
    vector<int> sequence;
    int length;
    int family;

public:
    explicit Polymer(int fam, vector<int> s);

    int getIndex();

    int getFamily();

    void setIndex(int ind);

    vector<int> getSequence();

    int getLength();

    void addPolymer(Polymer * poly, int pos);

    Polymer * cutPolymer(int index);

    bool operator==(Polymer p);
};

#endif //TESTTWO_POLYMER_H
