#include <iostream>
#include <vector>
#include <random>

#include "Polymer.h"
#include "Connection.h"
#include "Conglomerate.h"
#include "System.h"
#include "Tests.h"

using namespace std;
#define three_prime 0
#define five_prime 1

#define template_tail_unbind_rate 1
#define template_head_unbind_rate 1
#define template_bind_rate 1
#define backbone_bind_rate 1
#define backbone_unbind_rate 1



int main() {
    Tests *tests = new Tests();
    tests->runTests();

    double current_time = 0;
    int end_time = 100000000;
    double total_rate;

    int number_of_families = 2;
    int number_of_types = 1;
    vector<vector<int>> monomers;
    vector<int> typeOne;
    typeOne.push_back(100);
    typeOne.push_back(100);

    monomers.push_back(typeOne);

    Polymer * init_temp= new Polymer(0, {0,0,0,0,0,0});

    //Need an initial template sequence here going into system
    System * system = new System(number_of_families, number_of_types, monomers, init_temp);

    while(current_time<end_time){
        cout << endl << "------------------" << endl;
        //We calculate all rates in conglomerates and externally
        system->getEverything();

        //Get rates
        vector<int> rates = system->getRates();
        double total_rate = 0;
        for(auto & elem : rates){
            total_rate+=elem;
        }
        //We generate a random number from the exponential distribution
        random_device rd;
        mt19937 gen(rd());
        exponential_distribution<double> exp_distribution(1/total_rate);
        double random_time = exp_distribution(gen);

        //Update time
        current_time += random_time;
        //cout << current_time << endl;

        //Generate a random number for ratio
        double rand = gen();
        double rando = gen.max();
        //Loop rates and find the first that is larger than the random number
        double current_number = 0;
        int chosen_transition = -1;
        for(int i=0; i<rates.size(); i++){
            current_number += rates[i];
            if(rand/rando <= current_number/total_rate){
                chosen_transition = i;
                break;
            }
        }

        //Check that something has been chosen
        if(chosen_transition==-1){
            cout << "random numbers gone wild 1" << endl;
            return 0;
        }
        bool successful = system->chooseBond(chosen_transition);

        if(!successful){
            return 0;
        }
    }

    delete system;
    return 0;

    //Todo: Tests now have a fit at my checking system - see whats wrong
    //Todo: Keep writing error checks until one makes sense
}

