//
// Created by Nicholas Simpson on 24/10/2021.
//

#include "Tests.h"

Tests::Tests(){

}

bool Tests::runTests() {
    if(!testSystemInitialisation()){
        cout << "Failed: testSystemInitialisation";
        return false;
    }

    cout << "Tests passed" << endl;
    return true;
}

bool Tests::testSystemInitialisation(){
    int monomer_test_number=100;
    System * system = new System(monomer_test_number);
    return system->getMonomers()==monomer_test_number;
}