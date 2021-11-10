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
#define template_unbind_rate 1
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
    int number_of_types = 2;
    vector<vector<int>> monomers;
    vector<int> typeOne;
    vector<int> typeTwo;
    typeOne.push_back(100);
    typeOne.push_back(100);
    typeTwo.push_back(100);
    typeTwo.push_back(100);

    monomers.push_back(typeOne);
    monomers.push_back(typeTwo);

    Polymer * init_temp= new Polymer(0, {0,1,0,1,0,1});

    //Need an initial template sequence here going into system
    System * system = new System(number_of_families, number_of_types, monomers, init_temp);

    while(current_time<end_time){
        //system->print();

        //We calculate all rates in conglomerates and externally
        system->updateRates();

        //We get the total rate of all transitions
        total_rate = system->getTotalRate();

        //We generate a random number from the exponential distribution
        random_device rd;
        mt19937 gen(rd());
        exponential_distribution<double> exp_distribution(1/total_rate);
        double random_time = exp_distribution(gen);

        //Update time
        current_time += random_time;
        //cout << current_time << endl;

        //Get specific external and conglomerate transition rates
        //rates[rates.size()-1] will be external rate (last one in vector)
        vector<double> rates = system->getSpecificRates();

        //Generate a random number for ratio
        double rand = gen();
        double rando = gen.max();
        //Loop rates and find the first that is larger than the random number
        double current_number = 0;
        int chosen_conglomerate = -1;
        for(int i=0; i<rates.size(); i++){
            current_number += rates[i];
            if(rand/rando <= current_number/total_rate){
                chosen_conglomerate = i;
                break;
            }
        }

        //Check that something has been chosen
        if(chosen_conglomerate==-1){
            cout << "random numbers gone wild 1" << endl;
            return 0;
        }
        //If the chosen conglomerate is actually external transitions then find the right external transition
        if(chosen_conglomerate == rates.size()-1){
            system->chooseExternalTransition();
        } else { //If not find the transition in the chosen conglomerate
            system->chooseInternalTransition(chosen_conglomerate);
        }
        //system->print();
    }

    delete system;
    return 0;

}
