//
// Created by Nicholas Simpson on 03/11/2021.
//

#include <vector>
#include <iostream>

using namespace std;

#ifndef TESTTWO_DIMER_H
#define TESTTWO_DIMER_H


class Dimer {
private:
    int type;
    int familyOne;
    int familyTwo;

public:
    Dimer(int monomer_type, int famOne, int famTwo);
    int getType();
    vector<int> getFamilies();
    bool operator==(Dimer d);
};


#endif //TESTTWO_DIMER_H
