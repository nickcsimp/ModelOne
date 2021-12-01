//
// Created by Nicholas Simpson on 26/11/2021.
//

#include "Simulation.h"

Simulation::Simulation(double G_gen, double G_spec, double G_bb, double k_nought, double k_poly, double endtime) {
    Ggen = G_gen;
    Gspec = G_spec;
    Gbb = G_bb;
    end_time = endtime;
    k_zero = k_nought;
    k_pol = k_poly;

    effective_conc = 100;

}

void Simulation::run() {
    double current_time = 0;

    double total_rate;

    int number_of_families = 2;
    int number_of_types = 1;
    vector <vector<int>> monomers;
    vector<int> typeOne;
    typeOne.push_back(100);
    typeOne.push_back(100);

    monomers.push_back(typeOne);

    Polymer *init_temp = new Polymer(0, {0, 0, 0, 0, 0, 0});

    double energy[3] = {Ggen, Gspec, Gbb};
    double baserates[2] = {k_zero, k_pol};
    //Need an initial template sequence here going into system
    System *system = new System(number_of_families, number_of_types, monomers, init_temp, energy, baserates, effective_conc);
    int count = 0;
    system->print();
    while (current_time < end_time) {
        //cout << endl << "------------------" << endl;
        //We calculate all rates in conglomerates and externally
        system->getEverything();

        //system->print();

        //Get rates
        vector<int> rates = system->getRates();
        double total_rate = 0;
        for (auto &elem: rates) {
            total_rate += elem;
        }
        //We generate a random number from the exponential distribution
        random_device rd;
        mt19937 gen(rd());

        double rand = gen();
        double rando = gen.max();

        double random_time = -1 * log(rand / rando) / total_rate;

        //Update time
        current_time += random_time;
        //cout << current_time << endl;

        //Generate a random number for ratio
        rand = gen();
        rando = gen.max();
        //Loop rates and find the first that is larger than the random number
        double current_number = 0;
        int chosen_transition = -1;
        for (int i = 0; i < rates.size(); i++) {
            current_number += rates[i];
            if (rand / rando <= current_number / total_rate) {
                chosen_transition = i;
                break;
            }
        }

        //Check that something has been chosen
        if (chosen_transition == -1) {
            cout << "random numbers gone wild 1" << endl;
            return;
        }
        bool successful = system->chooseBond(chosen_transition);

        if (!successful) {
            system->print();
            cout << "Failed choosing bond: " << chosen_transition << endl;

            cout << "Head Binding: " << rates[0] << endl;
            cout << "Tail Binding: " << rates[1] << endl;
            cout << "Head Unbinding: " << rates[2] << endl;
            cout << "Tail Unbinding: " << rates[3] << endl;
            cout << "Connected Neighbours: " << rates[4] << endl;
            cout << "Unconnected Neighbours: " << rates[5] << endl;
            cout << "Head Connections: " << rates[6] << endl;
            cout << "Tail Connections: " << rates[7] << endl;
            return;
        }
        count++;
        cout << "Transition count = " << count << endl;
    }

    system->getEverything();

    system->print();

    delete system;
}
