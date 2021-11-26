#include <iostream>
#include <vector>
#include <random>

#include "Polymer.h"
#include "Connection.h"
#include "Conglomerate.h"
#include "System.h"
#include "Tests.h"
#include "Simulation.h"

using namespace std;
#define three_prime 0
#define five_prime 1

#define template_tail_unbind_rate 1
#define template_head_unbind_rate 1
#define template_bind_rate 1
#define backbone_bind_rate 1
#define backbone_unbind_rate 0



int main() {
    Tests *tests = new Tests();
    tests->runTests();

    double g_gen[] = {-15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1};
    double g_bb[] = {-15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1};
    double g_spec[] = {-4, 2, 8};

    double k0 = 1;
    double k = 2;
    for(auto & gen : g_gen){
        for(auto & bb : g_bb){
            for(auto & spec : g_spec){
                Simulation * sim = new Simulation(gen, spec, bb, k0, k, 10);
            }
        }
    }
    return 0;
}

/*TODO:
 * change tests to work
 * make new tests for simulation
 * get a good output
 */