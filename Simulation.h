//
// Created by Nicholas Simpson on 26/11/2021.
//

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

#include "Polymer.h"
#include "Connection.h"
#include "Conglomerate.h"
#include "System.h"

using namespace std;

#ifndef TESTTWO_SIMULATION_H
#define TESTTWO_SIMULATION_H

class Simulation {
private:
    double Ggen;
    double Gspec;
    double Gbb;
    double k_zero;
    double k_pol;
    double effective_conc;
    double end_time;
public:
    Simulation(double Ggen, double Gspec, double Gbb, double k_nought, double k_poly, double end_time);

    void run();


};


#endif //TESTTWO_SIMULATION_H
