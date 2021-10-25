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

    if(!testChangeMonomerCount()){
        cout << "Failed: testChangeMonomerCount";
        return false;
    }

    if(!testChangeDimerCount()){
        cout << "Failed: testChangeDimerCount";
        return false;
    }

    if(!testPolymerInitialisation()){
        cout << "Failed: testPolymerInitialisation()";
        return false;
    }

    if(!testPolymerParameters()){
        cout << "Failed: testPolymerParameters()";
        return false;
    }

    if(!testPolymerEquals()){
        cout << "Failed: testPolymerEquals()";
        return false;
    }

    if(!testAddPolymer()){
        cout << "Failed: testAddPolymer()";
        return false;
    }

    if(!testCutPolymer()){
        cout << "Failed: testCutPolymer()";
        return false;
    }

    if(!testRemovePolymer()){
        cout << "Failed: testRemovePolymer()";
        return false;
    }

    if(!testConnectionInitialisation()){
        cout << "Failed: testConnectionInitialisation()";
        return false;
    }

    if(!testConnectionEquals()){
        cout << "Failed: testConnectionEquals()";
        return false;
    }

    if(!testConnectionRemove()){
        cout << "Failed: testConnectionRemove()";
        return false;
    }

    if(!testConglomerateInitialisation()){
        cout << "Failed: testConglomerateInitialisation()";
        return false;
    }

    if(!testConglomerateGetters()){
        cout << "Failed: testConglomerateGetters()";
        return false;
    }

    if(!testUpdatePolymersInConglomerate()){
        cout << "Failed: testUpdatePolymersInConglomerate()";
        return false;
    }

    if(!testUpdateTemplateBond()){
        cout << "Failed: testUpdateTemplateBond()";
        return false;
    }

    if(!testUpdateBackboneBond()){
        cout << "Failed: testUpdateBackboneBond()";
        return false;
    }

    if(!testUpdatePolymerConnections()){
        cout << "Failed: testUpdatePolymerConnections()";
        return false;
    }

    if(!testUpdateTailUnbindingSites()){
        cout << "Failed: testUpdateTailUnbindingSites()";
        return false;
    }

    if(!testUpdateTailBindingSites()){
        cout << "Failed: testUpdateTailBindingSites()";
        return false;
    }

    if(!testTailConnectionOptions()){
        cout << "Failed: testTailConnectionOptions()";
        return false;
    }

    if(!testUpdateValidNeighbour()){
        cout << "Failed: testUpdateValidNeighbour()";
        return false;
    }

    if(!testValidNeighbourOptions()){
        cout << "Failed: testValidNeighbourOptions()";
        return false;
    }

    if(!testSystemGetters()){
        cout << "Failed: testSystemGetters()";
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


bool Tests::testChangeMonomerCount(){
    int monomer_test_number=100;
    int increase=20;
    int decrease=-50;
    System * system = new System(monomer_test_number);
    system->changeMonomerCount(increase);
    if(system->getMonomers()!=monomer_test_number+increase){
        return false;
    }
    system->changeMonomerCount(decrease);
    if(system->getMonomers()!=monomer_test_number+increase+decrease){
        return false;
    }
    return true;
}

bool Tests::testChangeDimerCount(){
    int monomer_test_number=100;
    int increase=50;
    int decrease=-20;
    System * system = new System(monomer_test_number);
    system->changeDimerCount(increase);
    if(system->getDimers()!=increase){
        return false;
    }
    system->changeDimerCount(decrease);
    if(system->getDimers()!=increase+decrease){
        return false;
    }
    return true;
}

bool Tests::testPolymerInitialisation(){
    vector<int> s = {1, 2, 1, 3, 1, 2, 1};
    Polymer * p = new Polymer(s);
    return p->getSequence()==s;
}

bool Tests::testPolymerParameters(){
    vector<int> s = {1, 2, 1, 3, 1, 2, 1};
    Polymer * p = new Polymer(s);
    int length = s.size();
    int index=5;
    p->setIndex(index);
    if(p->getIndex()!=index){
        return false;
    }

    if(p->getLength()!=length){
        return false;
    }

    return true;
}

bool Tests::testPolymerEquals(){
    vector<int> s = {1, 2, 1, 3, 1, 2, 1};
    Polymer * p = new Polymer(s);
    int index=5;
    p->setIndex(index);

    Polymer * pCopy = new Polymer(s);
    pCopy->setIndex(index);

    Polymer * diffIndex = new Polymer(s);
    diffIndex->setIndex(4);

    Polymer * diffSeq = new Polymer({1, 2, 3});
    diffSeq->setIndex(5);

    if(!(*p==*pCopy)){
        return false;
    }

    if(*p==*diffIndex){
        return false;
    }

    if(*p==*diffSeq){
        return false;
    }

    return true;
}


bool Tests::testAddPolymer(){
    vector<int> s = {1, 2};
    Polymer * p = new Polymer(s);
    int index=5;
    p->setIndex(index);

    s = {3, 4};
    Polymer * pCopy = new Polymer(s);
    index=6;
    pCopy->setIndex(index);

    p->addPolymer(pCopy, five_prime);

    index=5;
    Polymer * result = new Polymer({1, 2, 3, 4});
    result->setIndex(index);

    if(*p == *result){
        return true;
    }
    return false;
}

bool Tests::testCutPolymer(){
    Polymer * firstPolymer = new Polymer({1,2,3,4});
    firstPolymer->setIndex(1);
    Polymer * secondPolymer = firstPolymer->cutPolymer(2);
    secondPolymer->setIndex(2);

    Polymer * firstResult = new Polymer({1,2});
    firstResult->setIndex(1);

    Polymer * secondResult = new Polymer({3,4});
    secondResult->setIndex(2);

    if(!(*firstPolymer==*firstResult) || !(*secondPolymer==*secondResult)){
        return false;
    }

    return true;

}

bool Tests::testRemovePolymer(){
    //Todo this
    return true;
}

bool Tests::testConnectionInitialisation(){
    vector<int> s = {1,2,1,1,2};
    Polymer * pOne = new Polymer(s);
    pOne->setIndex(1);
    int indOne = 2;

    vector<int> seq = {2,1,1,1,1,2};
    Polymer * pTwo = new Polymer(seq);
    pOne->setIndex(2);
    int indTwo = 5;

    tuple<Polymer *, int> one = make_tuple(pOne, indOne);
    tuple<Polymer *, int> two = make_tuple(pTwo, indTwo);
    Connection * con = new Connection(one, two);

    vector<Polymer *> polymers = con->getPolymers();

    vector<int> indexes = con->getIndexes();

    if(!(*polymers[0]==*pOne)){
        return false;
    }

    if(!(*polymers[1]==*pTwo)){
        return false;
    }

    if(indexes[0] != indOne){
        return false;
    }

    if(indexes[1] != indTwo){
        return false;
    }

    return true;
}

bool Tests::testConnectionEquals(){
    vector<int> s = {1,2,1,1,2};
    Polymer * pOne = new Polymer(s);
    pOne->setIndex(1);
    int indOne = 2;

    vector<int> seq = {2,1,1,1,1,2};
    Polymer * pTwo = new Polymer(seq);
    pOne->setIndex(2);
    int indTwo = 5;

    vector<int> seque = {2,1,1,1,1,2};
    Polymer * pThree = new Polymer(seq);
    pOne->setIndex(3);
    int indThree = 3;

    tuple<Polymer *, int> one = make_tuple(pOne, indOne);
    tuple<Polymer *, int> two = make_tuple(pTwo, indTwo);
    tuple<Polymer *, int> three = make_tuple(pThree, indTwo);
    tuple<Polymer *, int> four = make_tuple(pTwo, indThree);

    Connection * con = new Connection(one, two);

    Connection * conCopy = new Connection(one, two);

    Connection * conReversed = new Connection(two, one);

    Connection * diffPolymer = new Connection(one, three);

    Connection * diffIndex = new Connection(one, four);

    if(!(*con==*conCopy)){
        return false;
    }

    if(!(*con==*conReversed)){
        return false;
    }

    if((*con==*diffPolymer)){
        return false;
    }

    if((*con==*diffIndex)){
        return false;
    }

    return true;
}

bool Tests::testConnectionRemove(){
    //Todo this
    return true;
}

bool Tests::testConglomerateInitialisation(){
    //Todo this
    return true;
}

bool Tests::testConglomerateGetters(){
    //Todo this
    return true;
}

bool Tests::testUpdatePolymersInConglomerate(){
    //Todo this
    return true;
}

bool Tests::testUpdateTemplateBond(){
    //Todo this
    return true;
}

bool Tests::testUpdateBackboneBond(){
    //Todo this
    return true;
}

bool Tests::testUpdatePolymerConnections(){
    //Todo this
    return true;
}

bool Tests::testUpdateTailUnbindingSites(){
    //Todo this
    return true;
}

bool Tests::testUpdateTailBindingSites(){
    //Todo this
    return true;
}

bool Tests::testTailConnectionOptions(){
    //Todo this
    return true;
}

bool Tests::testUpdateValidNeighbour(){
    //Todo this
    return true;
}

bool Tests::testValidNeighbourOptions(){
    //Todo this
    return true;
}

bool Tests::testSystemGetters(){
    //Todo this
    return true;
}

