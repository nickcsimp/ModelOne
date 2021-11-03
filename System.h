//
// Created by Nicholas Simpson on 20/10/2021.
//

#include <iostream>
#include <vector>
#include <random>

#include "Polymer.h"
#include "Conglomerate.h"
#include "Dimer.h"
using namespace std;

#define template_unbind_rate 1
#define template_bind_rate 1
#define backbone_bind_rate 1
#define backbone_unbind_rate 1

#ifndef TESTTWO_SYSTEM_H
#define TESTTWO_SYSTEM_H

class System {
private:
    int polymer_index;
    int conglomerate_index;

    vector<Dimer *> dimers;
    int number_of_families;
    int number_of_monomer_types;
    vector<vector<int>> number_of_monomers;

    vector<Polymer *> polymers;
    vector<Conglomerate *> conglomerates;

    vector<vector<vector<int>>> number_of_available_sites; //Conglom, type, family

    vector<vector<int>> number_of_connections;

    double total_rate;
    vector<double> specific_rates;
public:

    System(int family_count, int monomer_type_count, vector<vector<int>> number_of_monomers, Polymer * initial_template);

    vector<vector<int>> getMonomers();

    vector<Dimer *>getDimers();

    void changeMonomerCount(int family, int type, int increase);

    void addDimer(int family, int familyTwo, int type);

    void removeDimer(int index);

    vector<Polymer *> getPolymers();

    vector<Conglomerate *> getConglomerates();

    void addPolymer(int family, int type);

    void addConglomerate(Conglomerate *c);

    void removePolymer(Polymer * p);

    void removeConglomerate(Conglomerate * c);

    void joinPolymers(Polymer *pOne, Polymer * pTwo);

    void updateRates();

    double getTotalRate();

    vector<double> getSpecificRates();

    bool chooseExternalTransition();

    void chooseInternalTransition(int chosen_conglomerate);

    void print();
};


#endif //TESTTWO_SYSTEM_H
