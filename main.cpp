#include <iostream>
#include <vector>

#include "Polymer.h"
#include "Connection.h"
#include "Conglomerate.h"
#include "System.h"
#include "Tests.h"

using namespace std;
#define three_prime 0
#define five_prime 1

int main() {
    /*auto *system = new System(100);

    vector<int> v(10, 1);
    system->addPolymer(new Polymer(v));

    vector<int> ve(10, 3);
    system->addPolymer(new Polymer(ve));

    system->joinPolymers(0, 1);

    system->addPolymer(system->getPolymers()[0]->cutPolymer(5));

    system->addConglomerate(new Conglomerate(system->getPolymers()[0], 4, 4));

    system->print();

    Connection *con = system->getConglomerates()[0]->getConnections()[0];
    system->getConglomerates()[0]->removeConnection(con);

    system->print();

*/
    Tests *tests = new Tests();
    tests->runTests();
    return 0;
}
