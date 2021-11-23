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
    int end_time = 1000;
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
    int count = 0;

    while(current_time<end_time){
        //cout << endl << "------------------" << endl;
        //We calculate all rates in conglomerates and externally
        system->getEverything();

        //system->print();

        //Get rates
        vector<int> rates = system->getRates();
        double total_rate = 0;
        for(auto & elem : rates){
            total_rate+=elem;
        }
        //We generate a random number from the exponential distribution
        random_device rd;
        mt19937 gen(rd());

        double rand = gen();
        double rando = gen.max();

        double random_time = -1*log(rand/rando)/total_rate;

        //Update time
        current_time += random_time;
        //cout << current_time << endl;

        //Generate a random number for ratio
        rand = gen();
        rando = gen.max();
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
            return 0;
        }
        count++;
        cout << "Transition count = " << count << endl;
    }

    /*system->getEverything();

    //system->print();

    //Get rates
    vector<int> rates = system->getRates();



    system->print();

    cout << "Head Binding: " << rates[0] << endl;
    cout << "Tail Binding: " << rates[1] << endl;
    cout << "Head Unbinding: " << rates[2] << endl;
    cout << "Tail Unbinding: " << rates[3] << endl;
    cout << "Connected Neighbours: " << rates[4] << endl;
    cout << "Unconnected Neighbours: " << rates[5] << endl;
    cout << "Head Connections: " << rates[6] << endl;
    cout << "Tail Connections: " << rates[7] << endl;*/

    cout << "Transition count = " << count << endl;
    delete system;
    return 0;
}

