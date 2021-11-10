//
// Created by Nicholas Simpson on 24/10/2021.
//

#include "Tests.h"
#include <stdlib.h>
#include <ctime>

Tests::Tests(){
    srand(time(NULL));
}

bool Tests::runTests() {
    if(!testUpdateRates()){
        cout << "Failed: testUpdateRates";
    }
    if(!testPolymerInitialisation()){
        cout << "Failed: testPolymerInitialisation()";
        return false;
    }

    if(!testAddPolymer()){
        cout << "Failed: testAddPolymer()";
        return false;
    }

    if(!testPolymerEquals()){
        cout << "Failed: testPolymerEquals()";
        return false;
    }

    if(!testCutPolymer()){
        cout << "Failed: testCutPolymer()";
        return false;
    }

    if(!testPolymerAddConnection()){
        cout << "Failed: testPolymerAddConnection()";
        return false;
    }

    if(!testPolymerRemoveConnection()){
        cout << "Failed: testPolymerRemoveConnection()";
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

    if(!testEditConnection()){
        cout << "Failed: testEditConnection()";
        return false;
    }

    if(!testConnectedNeighboursInitialisation()){
        cout << "Failed: testConnectedNeighboursInitialisation()";
        return false;
    }

    if(!testConnectedNeighboursEquals()){
        cout << "Failed: testConnectedNeighboursEquals()";
        return false;
    }

    if(!testUnconnectedNeighboursInitialisation()){
        cout << "Failed: testUnconnectedNeighboursInitialisation()";
        return false;
    }

    if(!testUnconnectedNeighboursEquals()){
        cout << "Failed: testUnconnectedNeighboursEquals()";
        return false;
    }
    if(!testDimerInitialisation()){
        cout << "Failed: testDimerInitialisation()";
        return false;
    }
    if(!testDimerEquals()){
        cout << "Failed: testDimerEquals()";
        return false;
    }

    if(!testUpdatePolymersInConglomerate()){
        cout << "Failed: testUpdatePolymersInConglomerate()";
        return false;
    }

    if(!testUpdatePolymerConnections()){
        cout << "Failed: testUpdatePolymerConnections()";
        return false;
    }

    if(!testUpdateAvailableTemplateBonds()){
        cout << "Failed: testUpdateAvailableTemplateBonds()";
        return false;
    }

    if(!testGetPossibleSites()){
        cout << "Failed: testGetPossibleSites()";
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

    if(!testConnectionOptions()){
        cout << "Failed:testConnectionOptions()";
        return false;
    }

    if(!testUpdateValidNeighboursBinding()){
        cout << "Failed:testUpdateValidNeighboursBinding()";
        return false;
    }

    if(!testUpdateValidNeighboursUnbinding()){
        cout << "Failed:testUpdateValidNeighboursUnbinding()";
        return false;
    }

    if(!testConglomerateEquals()){
        cout << "Failed:testConglomerateEquals()";
        return false;
    }

    if(!testJoinPolymer()){
        cout << "Failed:testJoinPolymer()";
        return false;
    }

    if(!testSeparatePolymer()){
        cout << "Failed:testSeparatePolymer()";
        return false;
    }
/*

    if(!testConglomerateInitialisation()){
        cout << "Failed: testConglomerateInitialisation()";
        return false;
    }

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

    if(!testPolymerParameters()){
        cout << "Failed: testPolymerParameters()";
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
    */
    cout << "Tests passed" << endl;
    return true;
}

/*
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


bool Tests::testUpdateTemplateBond(){
    vector<Polymer*> polymers;
    vector<Connection*> connections;
    vector<tuple<Polymer *, int>> sites;
    for(int i=0; i< 10; i++) {
        vector<int> s;
        for (int j = 0; j < 10; j++) {
            s.push_back(rand() % 10);
        }
        Polymer *p = new Polymer(s);
        p->setIndex(i);
        polymers.push_back(p);
        s.clear();
        if (i == 0){
            for(int j=0; j<10; j++){
                sites.push_back(make_tuple(p, j));
            }
        } else {
            sites.push_back(make_tuple(p, 0));
        }
    }

    for(int i=0; i<9; i++){
        connections.push_back(new Connection(sites[i], sites[i+10]));
    }
    Conglomerate * conglomerate = new Conglomerate(connections);
    conglomerate->setIndex(10);
    conglomerate->updateTemplateBond();
    int available_template_bonds = conglomerate->getTemplateBonds();

    if(available_template_bonds!=82){
        return false;
    }
    return true;
}

bool Tests::testUpdateBackboneBond(){
    vector<Polymer*> polymers;
    vector<Connection*> connections;
    vector<tuple<Polymer *, int>> sites;
    for(int i=0; i< 10; i++) {
        vector<int> s;
        for (int j = 0; j < 10; j++) {
            s.push_back(rand() % 10);
        }
        Polymer *p = new Polymer(s);
        p->setIndex(i);
        polymers.push_back(p);
        s.clear();
        if (i == 0){
            for(int j=0; j<10; j++){
                sites.push_back(make_tuple(p, j));
            }
        } else {
            sites.push_back(make_tuple(p, 0));
        }
    }

    for(int i=0; i<9; i++){
        connections.push_back(new Connection(sites[i], sites[i+10]));
    }
    Conglomerate * conglomerate = new Conglomerate(connections);
    conglomerate->setIndex(10);
    conglomerate->updateBackboneBonds();
    int backbone_bonds = conglomerate->getBackboneBonds();

    if(backbone_bonds!=90){
        return false;
    }
    return true;
}

bool Tests::testUpdatePolymerConnections() {
    vector<Polymer *> polymers;
    vector<Connection *> connections;
    vector<tuple<Polymer *, int>> sites;
    for (int i = 0; i < 10; i++) {
        vector<int> s;
        for (int j = 0; j < 10; j++) {
            s.push_back(rand() % 10);
        }
        Polymer *p = new Polymer(s);
        p->setIndex(i);
        polymers.push_back(p);
        s.clear();
        if (i == 0) {
            for (int j = 0; j < 10; j++) {
                sites.push_back(make_tuple(p, j));
            }
        } else {
            sites.push_back(make_tuple(p, 0));
        }
    }

    for (int i = 0; i < 9; i++) {
        connections.push_back(new Connection(sites[i], sites[i + 10]));
    }
    Conglomerate *conglomerate = new Conglomerate(connections);
    conglomerate->setIndex(10);
    conglomerate->updatePolymerConnections();
    vector<vector<Connection * >> cons = conglomerate->getPolymerConnections();
    vector<vector<int>> inds = conglomerate->getPolymerConnectionIndexes();

    vector<int> nought = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> rest = {0};

    vector<vector<Connection * >> correctConnections;
    vector<vector<int>> correctIndexes;
    correctIndexes.push_back(nought);
    correctConnections.push_back(connections);

    for (int i = 1; i < 10; i++) {
        correctIndexes.push_back(rest);
        vector<Connection *> v = {connections[i - 1]};
        correctConnections.push_back(v);
    }

    if(cons.size()!=correctConnections.size() || inds.size()!=correctIndexes.size()){
        return false;
    }

    for (int i = 0; i < cons.size(); i++) { //Loop polymers in cons
        for (int j = 0; j < cons[i].size(); j++) { //Loop connections in polymer
            if (!(*cons[i][j] == *correctConnections[i][j])) { //If they're not as theyre supposed to be
                return false; //It fails
            }
            if(inds[i][j]!=correctIndexes[i][j]){
                return false;
            }
        }
    }

    return true;
}


bool Tests::testTailConnectionOptions(){
    vector<int> seq = {0,1,2,3,4};
    Polymer * pOne = new Polymer(seq);
    pOne->setIndex(0);

    Polymer * pTwo = new Polymer(seq);
    pTwo->setIndex(1);

    Polymer * pThree = new Polymer(seq);
    pTwo->setIndex(2);

    tuple<Polymer *, int> oneNought = make_tuple(pOne, 0);
    tuple<Polymer *, int> oneOne = make_tuple(pOne, 1);

    tuple<Polymer *, int> twoFour = make_tuple(pTwo, 4);
    tuple<Polymer *, int> twoThree = make_tuple(pTwo, 3);
    tuple<Polymer *, int> twoTwo = make_tuple(pTwo, 2);
    tuple<Polymer *, int> twoOne = make_tuple(pTwo, 1);

    tuple<Polymer *, int> threeFour = make_tuple(pThree, 4);
    tuple<Polymer *, int> threeThree = make_tuple(pThree, 3);

    tuple<Polymer *, int> threeOne = make_tuple(pThree, 1);
    tuple<Polymer *, int> threeNought = make_tuple(pThree, 0);

    vector<Connection *> connections;
    connections.push_back(new Connection(oneNought, twoFour));
    connections.push_back(new Connection(oneOne, twoThree));

    Conglomerate * conglomerate = new Conglomerate(connections);

    if(!(conglomerate->tailConnectionOptions(connections[1], pOne, -1, oneOne))){
        return false;
    }

    Connection * connection_to_be_removed = new Connection(twoTwo, threeThree);
    Connection * connection_two_be_removed = new Connection(twoOne, threeFour);

    conglomerate->addConnection(connection_to_be_removed);
    conglomerate->addConnection(connection_two_be_removed);

    if(!(conglomerate->tailConnectionOptions(connections[1], pOne, -1, oneOne))){
        return false;
    }

    conglomerate->removeConnection(connection_to_be_removed);
    conglomerate->removeConnection(connection_two_be_removed);

    Connection * connection_to_be_added = new Connection(twoTwo, threeNought);
    Connection * connection_two_be_added = new Connection(twoOne, threeOne);

    conglomerate->addConnection(connection_to_be_added);
    conglomerate->addConnection(connection_two_be_added);

    if(conglomerate->tailConnectionOptions(connections[1], pOne, -1, oneOne)){
        return false;
    }

    return true;
}

bool Tests::testUpdateValidNeighbour(){
    vector<int> seq = {0,1,2,3,4,5};
    Polymer * pOne = new Polymer(seq);
    pOne->setIndex(0);

    tuple<Polymer *, int> oneNought = make_tuple(pOne, 0);
    tuple<Polymer *, int> oneOne = make_tuple(pOne, 1);
    tuple<Polymer *, int> oneTwo = make_tuple(pOne, 2);
    tuple<Polymer *, int> oneThree = make_tuple(pOne, 3);
    tuple<Polymer *, int> oneFour = make_tuple(pOne, 4);
    tuple<Polymer *, int> oneFive = make_tuple(pOne, 5);

    seq = {0,1,2};
    Polymer * pTwo = new Polymer(seq);
    pTwo->setIndex(1);

    tuple<Polymer *, int> twoTwo = make_tuple(pTwo, 2);
    tuple<Polymer *, int> twoOne = make_tuple(pTwo, 1);
    tuple<Polymer *, int> twoNought = make_tuple(pTwo, 0);

    Polymer * pThree = new Polymer(seq);
    pThree->setIndex(2);

    tuple<Polymer *, int> threeTwo = make_tuple(pThree, 2);
    tuple<Polymer *, int> threeOne = make_tuple(pThree, 1);
    tuple<Polymer *, int> threeNought = make_tuple(pThree, 0);

    seq = {0,1,2,3,4};
    Polymer * pFour = new Polymer(seq);
    pFour->setIndex(3);


    tuple<Polymer *, int> fourFour = make_tuple(pFour, 4);
    tuple<Polymer *, int> fourThree = make_tuple(pFour, 3);
    tuple<Polymer *, int> fourTwo = make_tuple(pFour, 2);
    tuple<Polymer *, int> fourOne = make_tuple(pFour, 1);
    tuple<Polymer *, int> fourNought = make_tuple(pFour, 0);

    Connection * important_connection = new Connection(oneThree, twoTwo);
    vector<Connection *> connections;
    connections.push_back(important_connection);
    connections.push_back(new Connection(oneNought, threeTwo));
    connections.push_back(new Connection(oneOne, threeOne));
    connections.push_back(new Connection(oneTwo, threeNought));
    connections.push_back(new Connection(oneFour, twoOne));
    connections.push_back(new Connection(oneFive, twoNought));
    Conglomerate * conglomerate = new Conglomerate(connections);

    conglomerate->updatePolymersInConglomerate();
    conglomerate->updatePolymerConnections();

    conglomerate->updateValidNeighbours();

    int valid_neighbours = conglomerate->getValidNeighbours();

    if(valid_neighbours!=1){
        return false;
    }

    connections.clear();
    connections.push_back(important_connection);
    connections.push_back(new Connection(oneFour, twoOne));
    connections.push_back(new Connection(oneFive, twoNought));
    connections.push_back(new Connection(oneNought, fourFour));
    connections.push_back(new Connection(oneOne, fourThree));
    connections.push_back(new Connection(oneTwo, fourTwo));
    conglomerate = new Conglomerate(connections);

    conglomerate->updatePolymersInConglomerate();
    conglomerate->updatePolymerConnections();

    conglomerate->updateValidNeighbours();

    valid_neighbours = conglomerate->getValidNeighbours();

    if(valid_neighbours!=0){
        return false;
    }

    conglomerate->addConnection(new Connection(threeNought, fourOne));
    conglomerate->addConnection(new Connection(threeOne, fourNought));

    conglomerate->updatePolymersInConglomerate();
    conglomerate->updatePolymerConnections();

    conglomerate->updateValidNeighbours();

    valid_neighbours = conglomerate->getValidNeighbours();

    if(valid_neighbours!=1){
        return false;
    }
    return true;
}

bool Tests::testValidNeighbourOptions(){
    vector<int> seq = {0,1,2,3,4,5};
    Polymer * pOne = new Polymer(seq);
    pOne->setIndex(0);

    tuple<Polymer *, int> oneNought = make_tuple(pOne, 0);
    tuple<Polymer *, int> oneOne = make_tuple(pOne, 1);
    tuple<Polymer *, int> oneTwo = make_tuple(pOne, 2);
    tuple<Polymer *, int> oneThree = make_tuple(pOne, 3);
    tuple<Polymer *, int> oneFour = make_tuple(pOne, 4);
    tuple<Polymer *, int> oneFive = make_tuple(pOne, 5);

    seq = {0,1,2};
    Polymer * pTwo = new Polymer(seq);
    pTwo->setIndex(1);

    tuple<Polymer *, int> twoTwo = make_tuple(pTwo, 2);
    tuple<Polymer *, int> twoOne = make_tuple(pTwo, 1);
    tuple<Polymer *, int> twoNought = make_tuple(pTwo, 0);

    Polymer * pThree = new Polymer(seq);
    pThree->setIndex(2);

    tuple<Polymer *, int> threeTwo = make_tuple(pThree, 2);
    tuple<Polymer *, int> threeOne = make_tuple(pThree, 1);
    tuple<Polymer *, int> threeNought = make_tuple(pThree, 0);

    seq = {0,1,2,3,4};
    Polymer * pFour = new Polymer(seq);
    pFour->setIndex(3);


    tuple<Polymer *, int> fourFour = make_tuple(pFour, 4);
    tuple<Polymer *, int> fourThree = make_tuple(pFour, 3);
    tuple<Polymer *, int> fourTwo = make_tuple(pFour, 2);
    tuple<Polymer *, int> fourOne = make_tuple(pFour, 1);
    tuple<Polymer *, int> fourNought = make_tuple(pFour, 0);

    Connection * important_connection = new Connection(oneThree, twoTwo);
    vector<Connection *> connections;
    connections.push_back(important_connection);
    connections.push_back(new Connection(oneNought, threeTwo));
    connections.push_back(new Connection(oneOne, threeOne));
    connections.push_back(new Connection(oneTwo, threeNought));
    connections.push_back(new Connection(oneFour, twoOne));
    connections.push_back(new Connection(oneFive, twoNought));
    Conglomerate * conglomerate = new Conglomerate(connections);

    conglomerate->updatePolymersInConglomerate();
    conglomerate->updatePolymerConnections();

    if(!conglomerate->validNeighbourOptions(important_connection, pTwo, -1, pTwo)){
        return false;
    }

    connections.clear();
    connections.push_back(important_connection);
    connections.push_back(new Connection(oneFour, twoOne));
    connections.push_back(new Connection(oneFive, twoNought));
    connections.push_back(new Connection(oneNought, fourFour));
    connections.push_back(new Connection(oneOne, fourThree));
    connections.push_back(new Connection(oneTwo, fourTwo));
    conglomerate = new Conglomerate(connections);

    conglomerate->updatePolymersInConglomerate();
    conglomerate->updatePolymerConnections();

    if(conglomerate->validNeighbourOptions(important_connection, pTwo, -1, pTwo)){
        return false;
    }

    conglomerate->addConnection(new Connection(threeNought, fourOne));
    conglomerate->addConnection(new Connection(threeOne, fourNought));

    conglomerate->updatePolymersInConglomerate();
    conglomerate->updatePolymerConnections();

    if(!conglomerate->validNeighbourOptions(important_connection, pTwo, -1, pTwo)){
        return false;
    }

    return true;
}

bool Tests::testSystemGetters(){
    vector<Polymer *> polymers;
    for(int i=0; i<10; i++){
        vector<int> seq;
        for(int j=0; j<10; j++){
            seq.push_back(rand()%10);
        }
        Polymer * p = new Polymer(seq);
        p->setIndex(i);
        polymers.push_back(p);
    }
    tuple<Polymer *, int> noughtNought = make_tuple(polymers[0], 0);
    tuple<Polymer *, int> noughtOne = make_tuple(polymers[0], 1);
    tuple<Polymer *, int> noughtSeven= make_tuple(polymers[0], 7);
    tuple<Polymer *, int> noughtEight = make_tuple(polymers[0], 8);

    tuple<Polymer *, int> oneThree = make_tuple(polymers[1], 3);

    tuple<Polymer *, int> twoFive = make_tuple(polymers[2], 5);
    tuple<Polymer *, int> twoFour = make_tuple(polymers[2], 4);

    tuple<Polymer *, int> threeThree = make_tuple(polymers[3], 3);
    tuple<Polymer *, int> threeFour = make_tuple(polymers[3], 3);
    tuple<Polymer *, int> threeNine = make_tuple(polymers[3], 9);

    vector<Connection *> conOne;
    conOne.push_back(new Connection(noughtNought, threeThree));
    conOne.push_back(new Connection(noughtOne, threeFour));
    conOne.push_back(new Connection(noughtSeven, twoFive));
    conOne.push_back(new Connection(noughtEight, twoFour));
    conOne.push_back(new Connection(oneThree, threeNine));
    Conglomerate * conglomerateOne = new Conglomerate(conOne);
    conglomerateOne->setIndex(1);

    tuple<Polymer *, int> sixThree = make_tuple(polymers[6], 3);
    tuple<Polymer *, int> sixFour = make_tuple(polymers[6], 4);

    tuple<Polymer *, int> fiveNought = make_tuple(polymers[5], 0);
    tuple<Polymer *, int> fiveEight = make_tuple(polymers[5], 8);
    tuple<Polymer *, int> fiveNine = make_tuple(polymers[5], 9);


    tuple<Polymer *, int> fourSix = make_tuple(polymers[4], 6);

    vector<Connection *> conTwo;
    conTwo.push_back(new Connection(fourSix, fiveNought));
    conTwo.push_back(new Connection(fiveEight, sixFour));
    conTwo.push_back(new Connection(fiveNine, sixThree));
    Conglomerate * conglomerateTwo = new Conglomerate(conTwo);
    conglomerateTwo->setIndex(2);

    System * system = new System(100);
    for(int i=0; i<10; i++){
        system->addPolymer(polymers[i]);
    }

    system->addConglomerate(conglomerateOne);
    system->addConglomerate(conglomerateTwo);

    vector<Polymer *> poly = system->getPolymers();
    vector<Conglomerate *> conglomy = system->getConglomerates();

    if(poly.size()!=10 || conglomy.size()!=2){
        return false; //Better test probs needed
    }
    return true;
}*/

bool Tests::testPolymerInitialisation(){
    vector<int> s = {1, 2, 1, 3, 1, 2, 1};
    int family = 2;
    Polymer * p = new Polymer(family, s);
    p->setIndex(4);
    if(p->getFamily()==family && p->getLength()==7 && p->getSequence()==s && p->getIndex()==4){
        return true;
    }
    return false;
}

bool Tests::testAddPolymer(){
    vector<int> s = {1, 2};
    int family = 2;
    Polymer * p = new Polymer(family, s);
    int index=5;
    p->setIndex(index);

    s = {3, 4};
    Polymer * pCopy = new Polymer(family, s);
    index=6;
    pCopy->setIndex(index);

    p->addPolymer(pCopy, five_prime);

    index=5;
    Polymer * result = new Polymer(family, {1, 2, 3, 4});
    result->setIndex(index);

    if(*p == *result){
        return true;
    }
    return false;
}

bool Tests::testPolymerEquals(){
    int family = 2;
    vector<int> s = {1, 2, 1, 3, 1, 2, 1};
    Polymer * p = new Polymer(family, s);
    int index=5;
    p->setIndex(index);

    Polymer * pCopy = new Polymer(family, s);
    pCopy->setIndex(index);

    Polymer * diffIndex = new Polymer(family, s);
    diffIndex->setIndex(4);

    Polymer * diffSeq = new Polymer(family, {1, 2, 3});
    diffSeq->setIndex(index);

    Polymer * diffFam = new Polymer(family-1, s);
    diffSeq->setIndex(index);

    if(!(*p==*pCopy)){
        return false;
    }

    if(*p==*diffIndex){
        return false;
    }

    if(*p==*diffSeq){
        return false;
    }

    if(*p==*diffFam){
        return false;
    }

    return true;
}

bool Tests::testCutPolymer(){
    int family = 0;
    Polymer * firstPolymer = new Polymer(family, {1,2,3,4});
    firstPolymer->setIndex(1);
    Polymer * secondPolymer = firstPolymer->cutPolymer(2);
    secondPolymer->setIndex(2);

    Polymer * firstResult = new Polymer(family, {1,2});
    firstResult->setIndex(1);

    Polymer * secondResult = new Polymer(family, {3,4});
    secondResult->setIndex(2);

    if(!(*firstPolymer==*firstResult) || !(*secondPolymer==*secondResult)){
        return false;
    }

    return true;

}

bool Tests::testPolymerAddConnection() {
    vector<int> seq = {1,2,3,4,5};
    int fam = 0;
    Polymer *p = new Polymer(fam, seq);
    p->setIndex(0);

    p->addConnection(p);
    cout << "Error expected" << endl;

    if(p->getConnections().size()!=0){
        return false;
    }

    Polymer *q = new Polymer(fam+1, seq);
    q->setIndex(1);

    for(int i=0; i<5; i++){
        p->addConnection(q);
        q->addConnection(p);
        vector<tuple<Polymer *, int>> pCon = p->getConnections();
        vector<tuple<Polymer *, int>> qCon = q->getConnections();
        if(!(*get<0>(pCon[0])==*q) || !(*get<0>(qCon[0])==*p)){
            return false;
        }
        if(get<1>(pCon[0])!=i+1 || get<1>(qCon[0])!=i+1){
            return false;
        }
    }
    p->addConnection(q);
    cout << "Error expected" << endl;
    q->addConnection(p);
    cout << "Error expected" << endl;
    if(get<1>(p->getConnections()[0])!=5 || get<1>(q->getConnections()[0])!=5){
        return false;
    }


    return true;
}

bool Tests::testPolymerRemoveConnection() {
    vector<int> seq = {1,2,3,4,5};
    int fam = 0;
    Polymer *p = new Polymer(fam, seq);
    p->setIndex(0);

    Polymer *q = new Polymer(fam+1, seq);
    q->setIndex(1);

    for(int i=0; i<5; i++){
        p->addConnection(q);
        q->addConnection(p);
    }

    for(int i=4; i>0; i--){
        p->removeConnection(q);
        q->removeConnection(p);
        vector<tuple<Polymer *, int>> pCon = p->getConnections();
        vector<tuple<Polymer *, int>> qCon = q->getConnections();

        if(!(*get<0>(pCon[0])==*q) || !(*get<0>(qCon[0])==*p)){
            return false;
        }
        if(get<1>(pCon[0])!=i || get<1>(qCon[0])!=i){
            return false;
        }
    }

    if(!(p->removeConnection(q))){
        return false;
    }

    if(!(q->removeConnection(p))){
        return false;
    }

    p->removeConnection(q);
    cout << "Error expected" << endl;
    q->removeConnection(p);
    cout << "Error expected" << endl;
    if(p->getConnections().size()!=0 || q->getConnections().size()!=0){
        return false;
    }
    return true;
}


bool Tests::testConnectionInitialisation(){
    int family = 0;
    vector<int> s = {1,2,1,1,2};
    Polymer * pOne = new Polymer(family, s);
    pOne->setIndex(1);
    int indOne = 2;

    vector<int> seq = {2,1,1,1,1,2};
    Polymer * pTwo = new Polymer(family +1, seq);
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
    int family = 0;
    vector<int> s = {1,2,1,1,2};
    Polymer * pOne = new Polymer(family, s);
    pOne->setIndex(1);
    int indOne = 2;

    vector<int> seq = {2,1,1,1,1,2};
    Polymer * pTwo = new Polymer(family, seq);
    pOne->setIndex(2);
    int indTwo = 5;

    vector<int> seque = {2,1,1,1,1,2};
    Polymer * pThree = new Polymer(family, seq);
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

bool Tests::testEditConnection() {
    int family = 0;
    vector<int> s = {1,2,1,1,2};
    Polymer * pOne = new Polymer(family, s);
    pOne->setIndex(1);
    int indOne = 2;

    vector<int> seq = {2,1,1,1,1,2};
    Polymer * pTwo = new Polymer(family +1, seq);
    pOne->setIndex(2);
    int indTwo = 5;

    tuple<Polymer *, int> one = make_tuple(pOne, indOne);
    tuple<Polymer *, int> two = make_tuple(pTwo, indTwo);
    Connection * con = new Connection(one, two);

    vector<int> sequence = {2,1,1,1,1,2};
    Polymer * pThree = new Polymer(family +1, seq);
    pOne->setIndex(1);

    con->changePolymer(1, pThree);

    if(!(*con->getPolymers()[1]==*pThree)){
        return false;
    }

    con->setIndex(1, 4);

    if(con->getIndexes()[1]!=4){
        return false;
    }

    con->changePolymer(1, pOne);
    cout << "Error expected" << endl;

    if(!(*con->getPolymers()[1]==*pThree)){
        return false;
    }

    con->setIndex(1, 10);
    cout << "Error expected" << endl;

    if(con->getIndexes()[1]!=4){
        return false;
    }

    con->setIndex(1, -5);
    cout << "Error expected" << endl;

    if(con->getIndexes()[1]!=4){
        return false;
    }

    return true;
}

bool Tests::testConnectedNeighboursInitialisation(){
    int family = 0;
    vector<int> seq = {1,2,1,1,2,1};
    Polymer *p = new Polymer (family, seq);
    p->setIndex(0);

    ConnectedNeighbours * con = new ConnectedNeighbours(p, 0, 1);

    if(!(*con->getPolymer()==*p)){
        return false;
    }

    if(con->getIndexes()[0]!=0 || con->getIndexes()[1]!=1){
        return false;
    }

    ConnectedNeighbours * conNeigh = new ConnectedNeighbours(p, 0, 0);
    cout << "Error expected" << endl;

    return true;
}

bool Tests::testConnectedNeighboursEquals(){
    int family = 0;
    vector<int> seq = {1,2,1,1,2,1};
    Polymer *p = new Polymer (family, seq);
    p->setIndex(0);

    int fam = 1;
    vector<int> sequence = {2,1,1,2,1};
    Polymer *q = new Polymer (fam, sequence);
    q->setIndex(0);

    ConnectedNeighbours * con = new ConnectedNeighbours(p, 0, 1);
    ConnectedNeighbours * copy = new ConnectedNeighbours(p, 0, 1);
    ConnectedNeighbours * diffPoly = new ConnectedNeighbours(q, 0, 1);
    ConnectedNeighbours * diffInd = new ConnectedNeighbours(p, 1, 2);

    if(!(*con==*copy)){
        return false;
    }
    if(*con==*diffPoly){
        return false;
    }
    if(*con==*diffInd){
        return false;
    }

    return true;
}

bool Tests::testUnconnectedNeighboursInitialisation(){
    int family = 0;
    vector<int> seq = {1,2,1,1,2,1};
    Polymer *p = new Polymer (family, seq);
    p->setIndex(0);

    int fam = 1;
    vector<int> sequence = {2,1,1,2,1};
    Polymer *q = new Polymer (fam, sequence);
    q->setIndex(1);

    UnconnectedNeighbours * uncon = new UnconnectedNeighbours(p, q);

    if(!(*uncon->getPolymers()[0]==*p)){
        return false;
    }

    if(!(*uncon->getPolymers()[1]==*q)){
        return false;
    }

    UnconnectedNeighbours * ncon = new UnconnectedNeighbours(p, p);
    cout << "Error expected" << endl;

    return true;

}

bool Tests::testUnconnectedNeighboursEquals(){
    int family = 0;
    vector<int> seq = {1,2,1,1,2,1};
    Polymer *p = new Polymer (family, seq);
    p->setIndex(0);

    int fam = 1;
    vector<int> sequence = {2,1,1,2,1};
    Polymer *q = new Polymer (fam, sequence);
    q->setIndex(1);

    int f = 2;
    vector<int> s = {2,1,2,1};
    Polymer *r = new Polymer (f, s);
    q->setIndex(2);

    UnconnectedNeighbours * uncon = new UnconnectedNeighbours(p, q);
    UnconnectedNeighbours * copy= new UnconnectedNeighbours(p, q);
    UnconnectedNeighbours * sqitch = new UnconnectedNeighbours(q, p);
    UnconnectedNeighbours * diffPolymer = new UnconnectedNeighbours(p, r);

    if(!(*uncon==*copy)){
        return false;
    }

    if(!(*uncon==*sqitch)){
        return false;
    }

    if(*uncon==*diffPolymer){
        return false;
    }

    return true;
}

bool Tests::testDimerInitialisation(){
    Dimer * d = new Dimer(0, 1, 2);

    if(d->getType()!=0){
        return false;
    }

    if(d->getFamilies()[0]!=1 || d->getFamilies()[1]!=2){
        return false;
    }

    Dimer * e = new Dimer(0, 1, 1);
    cout << "Error expected" << endl;

    return true;
}

bool Tests::testDimerEquals(){
    Dimer * d = new Dimer(0, 1, 2);
    Dimer * copy = new Dimer(0, 1, 2);
    Dimer * diffType = new Dimer(1, 1, 2);
    Dimer * diffFam = new Dimer(0, 1, 3);
    Dimer * diffFamily = new Dimer(0, 0, 2);

    if(!(*d==*copy)){
        return false;
    }

    if(*d==*diffType){
        return false;
    }

    if(*d==*diffFam){
        return false;
    }

    if(*d==*diffFamily){
        return false;
    }
    return true;
}

bool Tests::testUpdatePolymersInConglomerate(){


    Polymer * pOne = new Polymer(0, {1,0,1,0,1});
    pOne->setIndex(0);

    Polymer * pTwo = new Polymer(1, {1,0,1,0,1});
    pTwo->setIndex(1);

    Polymer * pThree = new Polymer(0, {1,0,1,0,1});
    pThree->setIndex(2);

    tuple<Polymer *, int> tOne = make_tuple(pOne, 0);
    tuple<Polymer *, int> tTwo = make_tuple(pOne, 1);
    tuple<Polymer *, int> tThree = make_tuple(pOne, 2);

    tuple<Polymer *, int> tFour = make_tuple(pTwo, 0);
    tuple<Polymer *, int> tFive = make_tuple(pTwo, 2);
    tuple<Polymer *, int> tSix = make_tuple(pTwo, 3);
    tuple<Polymer *, int> tSeven = make_tuple(pTwo, 4);

    tuple<Polymer *, int> tEight = make_tuple(pThree, 4);

    Connection * conOne = new Connection(tOne, tSeven);
    Connection * conTwo = new Connection(tTwo, tSix);
    Connection * conThree = new Connection(tThree, tFive);
    Connection * conFour = new Connection(tFour, tEight);

    Conglomerate * con = new Conglomerate({conOne, conTwo, conThree, conFour}, 2, 2);

    con->updatePolymersInConglomerate();

    if(con->getPolymersInConglomerate().size()!=3){
        return false;
    }
    bool uno = false;
    bool dos = false;
    bool tres = false;
    for(auto & elem : con->getPolymersInConglomerate()){
        if(*elem==*pOne){
            uno = true;
        }
        if(*elem==*pTwo){
            dos = true;
        }
        if(*elem==*pThree){
            tres = true;
        }
    }

    if(!uno || !dos || !tres){
        return false;
    }

    return true;
}

bool Tests::testUpdatePolymerConnections(){
    Polymer * pOne = new Polymer(0, {1,0,1,0,1});
    pOne->setIndex(0);

    Polymer * pTwo = new Polymer(1, {1,0,1,0,1});
    pTwo->setIndex(1);

    Polymer * pThree = new Polymer(0, {1,0,1,0,1});
    pThree->setIndex(2);

    tuple<Polymer *, int> tOne = make_tuple(pOne, 0);
    tuple<Polymer *, int> tTwo = make_tuple(pOne, 1);
    tuple<Polymer *, int> tThree = make_tuple(pOne, 2);

    tuple<Polymer *, int> tFour = make_tuple(pTwo, 0);
    tuple<Polymer *, int> tFive = make_tuple(pTwo, 2);
    tuple<Polymer *, int> tSix = make_tuple(pTwo, 3);
    tuple<Polymer *, int> tSeven = make_tuple(pTwo, 4);

    tuple<Polymer *, int> tEight = make_tuple(pThree, 4);

    Connection * conOne = new Connection(tOne, tSeven);
    Connection * conTwo = new Connection(tTwo, tSix);
    Connection * conThree = new Connection(tThree, tFive);
    Connection * conFour = new Connection(tFour, tEight);

    Conglomerate * con = new Conglomerate({conOne, conTwo, conThree, conFour}, 2, 2);

    con->updatePolymersInConglomerate();
    con->updatePolymerConnections();

    vector<vector<Connection *>> connections = con->getPolymerConnections();
    vector<vector<int>> indexes = con->getPolymerConnectionIndexes();

    if(connections.size()!= 3 || indexes.size()!=3){
        return false;
    }

    if(!(*connections[0][0] == *conOne) || indexes[0][0] != 0){
        return false;
    }

    if(!(*connections[0][1] == *conTwo || indexes[0][1] != 1)){
        return false;
    }

    if(!(*connections[0][2] == *conThree || indexes[0][2] != 2)){
        return false;
    }

    if(!(*connections[1][0] == *conFour || indexes[1][0] != 0)){
        return false;
    }

    if(!(*connections[1][1] == *conThree) || indexes[1][1] != 2){
        return false;
    }

    if(!(*connections[1][2] == *conTwo) || indexes[1][2] != 3){
        return false;
    }

    if(!(*connections[1][3] == *conOne) || indexes[1][3] != 4){
        return false;
    }

    if(!(*connections[2][0] == *conFour) || indexes[2][0] != 4){
        return false;
    }

    return true;
}

bool Tests::testUpdateAvailableTemplateBonds(){
    Polymer * pOne = new Polymer(0, {1,0,1,0,1});
    pOne->setIndex(0);

    Polymer * pTwo = new Polymer(1, {1,0,1,0,1});
    pTwo->setIndex(1);

    Polymer * pThree = new Polymer(0, {1,0,1,0,1});
    pThree->setIndex(2);

    tuple<Polymer *, int> tOne = make_tuple(pOne, 0);
    tuple<Polymer *, int> tTwo = make_tuple(pOne, 1);
    tuple<Polymer *, int> tThree = make_tuple(pOne, 2);

    tuple<Polymer *, int> tFour = make_tuple(pTwo, 0);
    tuple<Polymer *, int> tFive = make_tuple(pTwo, 2);
    tuple<Polymer *, int> tSix = make_tuple(pTwo, 3);
    tuple<Polymer *, int> tSeven = make_tuple(pTwo, 4);

    tuple<Polymer *, int> tEight = make_tuple(pThree, 4);

    Connection * conOne = new Connection(tOne, tSeven);
    Connection * conTwo = new Connection(tTwo, tSix);
    Connection * conThree = new Connection(tThree, tFive);
    Connection * conFour = new Connection(tFour, tEight);

    Conglomerate * con = new Conglomerate({conOne, conTwo, conThree, conFour}, 2, 2);

    con->updateAvailableTemplateBonds();

    vector<vector<int>> tempBonds = con->getAvailableTemplateBonds();

    if(tempBonds.size()!=2){
        return false;
    }

    if(tempBonds[0].size()!=2){
        return false;
    }

    if(tempBonds[1].size()!=2){
        return false;
    }

    if(tempBonds[0][0]!=3 || tempBonds[0][1]!=1){
        return false;
    }

    if(tempBonds[1][0]!=3 || tempBonds[1][1]!=0){
        return false;
    }

    return true;
}

bool Tests::testGetPossibleSites(){
    Polymer * pOne = new Polymer(0, {1,0,1,0,1});
    pOne->setIndex(0);

    Polymer * pTwo = new Polymer(1, {1,0,1,0,1});
    pTwo->setIndex(1);

    Polymer * pThree = new Polymer(0, {1,0,1,0,1});
    pThree->setIndex(2);

    tuple<Polymer *, int> tOne = make_tuple(pOne, 0);
    tuple<Polymer *, int> tTwo = make_tuple(pOne, 1);
    tuple<Polymer *, int> tThree = make_tuple(pOne, 2);

    tuple<Polymer *, int> tFour = make_tuple(pTwo, 0);
    tuple<Polymer *, int> tFive = make_tuple(pTwo, 2);
    tuple<Polymer *, int> tSix = make_tuple(pTwo, 3);
    tuple<Polymer *, int> tSeven = make_tuple(pTwo, 4);

    tuple<Polymer *, int> tEight = make_tuple(pThree, 4);

    Connection * conOne = new Connection(tOne, tSeven);
    Connection * conTwo = new Connection(tTwo, tSix);
    Connection * conThree = new Connection(tThree, tFive);
    Connection * conFour = new Connection(tFour, tEight);

    Conglomerate * con = new Conglomerate({conOne, conTwo, conThree, conFour}, 2, 2);

    con->updatePolymersInConglomerate();
    con->updatePolymerConnections();
    vector<tuple<Polymer *, int>> sites = con->getPossibleSites(0,0);

    if(sites.size()!=3){
        return false;
    }

    bool uno = false;
    bool dos = false;
    bool tres = false;
    for(auto & elem : sites){
        if(elem == make_tuple(pOne, 3)){
            uno = true;
        }
        if(elem == make_tuple(pThree, 1)){
            dos = true;
        }
        if(elem == make_tuple(pThree, 3)){
            tres = true;
        }
    }

    if(!uno || !dos || !tres){
        return false;
    }

    sites = con->getPossibleSites(0,1);

    if(sites.size()!=1){
        return false;
    }

    uno = false;
    dos = false;
    tres = false;
    for(auto & elem : sites){
        if(elem == make_tuple(pTwo, 1)){
            uno = true;
        }
    }

    if(!uno){
        return false;
    }

    sites = con->getPossibleSites(1,0);

    if(sites.size()!=3){
        return false;
    }

    uno = false;
    dos = false;
    tres = false;
    for(auto & elem : sites){
        if(elem == make_tuple(pOne, 4)){
            uno = true;
        }
        if(elem == make_tuple(pThree, 0)){
            dos = true;
        }
        if(elem == make_tuple(pThree, 2)){
            tres = true;
        }
    }

    if(!uno || !dos || !tres){
        return false;
    }

    sites = con->getPossibleSites(1,1);

    if(sites.size()!=0){
        return false;
    }


    return true;
}

bool Tests::testUpdateTailUnbindingSites(){
    Polymer * pOne = new Polymer(0, {1,0,1,0,1});
    pOne->setIndex(0);

    Polymer * pTwo = new Polymer(1, {1,0,1,0,1});
    pTwo->setIndex(1);

    Polymer * pThree = new Polymer(0, {1,0,1,0,1});
    pThree->setIndex(2);

    tuple<Polymer *, int> tOne = make_tuple(pOne, 0);
    tuple<Polymer *, int> tTwo = make_tuple(pOne, 1);
    tuple<Polymer *, int> tThree = make_tuple(pOne, 2);

    tuple<Polymer *, int> tFour = make_tuple(pTwo, 0);
    tuple<Polymer *, int> tFive = make_tuple(pTwo, 2);
    tuple<Polymer *, int> tSix = make_tuple(pTwo, 3);
    tuple<Polymer *, int> tSeven = make_tuple(pTwo, 4);

    tuple<Polymer *, int> tEight = make_tuple(pThree, 4);

    Connection * conOne = new Connection(tOne, tSeven);
    Connection * conTwo = new Connection(tTwo, tSix);
    Connection * conThree = new Connection(tThree, tFive);
    Connection * conFour = new Connection(tFour, tEight);

    Conglomerate * con = new Conglomerate({conOne, conTwo, conThree, conFour}, 2, 2);

    con->updatePolymersInConglomerate();
    con->updatePolymerConnections();

    con->updateTailUnbindingSites();

    int sites = con->getTailUnbindingSites();
    vector<Connection *> connections = con->getTailUnbindingConnections();

    if(sites!=3 || connections.size() != 3){
        return false;
    }

    bool uno = false;
    bool dos = false;
    bool tres = false;

    for(auto & con : connections){
        if(*con==*conOne){
            uno = true;
        }
        if(*con==*conThree){
            dos = true;
        }
        if(*con==*conFour){
            tres = true;
        }
    }
    if(!uno || !dos || !tres){
        return false;
    }
    return true;
}

bool Tests::testUpdateTailBindingSites(){
    Polymer * pOne = new Polymer(0, {1,0,1,0,1});
    pOne->setIndex(0);

    Polymer * pTwo = new Polymer(1, {1,0,1,0,1});
    pTwo->setIndex(1);

    Polymer * pThree = new Polymer(0, {1,0,1,0,1});
    pThree->setIndex(2);

    tuple<Polymer *, int> tOne = make_tuple(pOne, 0);
    tuple<Polymer *, int> tTwo = make_tuple(pOne, 1);
    tuple<Polymer *, int> tThree = make_tuple(pOne, 2);

    tuple<Polymer *, int> tFour = make_tuple(pTwo, 0);
    tuple<Polymer *, int> tFive = make_tuple(pTwo, 2);
    tuple<Polymer *, int> tSix = make_tuple(pTwo, 3);
    tuple<Polymer *, int> tSeven = make_tuple(pTwo, 4);

    tuple<Polymer *, int> tEight = make_tuple(pThree, 4);

    Connection * conOne = new Connection(tOne, tSeven);
    Connection * conTwo = new Connection(tTwo, tSix);
    Connection * conThree = new Connection(tThree, tFive);
    Connection * conFour = new Connection(tFour, tEight);

    Conglomerate * con = new Conglomerate({conOne, conTwo, conThree, conFour}, 2, 2);

    con->updatePolymersInConglomerate();
    con->updatePolymerConnections();

    con->updateTailBindingSites();

    int sites = con->getTailBindingSites();
    vector<Connection *> connections = con->getTailBindingConnections();

    if(sites!=2 || connections.size() != 2){
        return false;
    }

    bool uno = false;
    bool dos = false;

    tuple<Polymer *, int> site_on_two = make_tuple(pTwo, 1);
    tuple<Polymer *, int> site_on_one = make_tuple(pOne, 3);
    tuple<Polymer *, int> site_on_three = make_tuple(pThree, 3);

    Connection * poss_con_one = new Connection(site_on_two, site_on_one);
    Connection * poss_con_two = new Connection(site_on_two, site_on_three);

    for(auto & con : connections){
        if(*con==*poss_con_one){
            uno = true;
        }
        if(*con==*poss_con_one){
            dos = true;
        }
    }
    if(!uno || !dos){
        return false;
    }
    return true;
}

bool Tests::testConnectionOptions(){
    Polymer * pOne = new Polymer(0, {1,0,1,0,1});
    pOne->setIndex(0);

    Polymer * pTwo = new Polymer(1, {1,0,1,0,1});
    pTwo->setIndex(1);

    Polymer * pThree = new Polymer(0, {1,1,1,1,1});
    pThree->setIndex(2);

    tuple<Polymer *, int> tOne = make_tuple(pOne, 0);
    tuple<Polymer *, int> tTwo = make_tuple(pOne, 1);
    tuple<Polymer *, int> tThree = make_tuple(pOne, 2);

    tuple<Polymer *, int> tFour = make_tuple(pTwo, 0);
    tuple<Polymer *, int> tFive = make_tuple(pTwo, 2);
    tuple<Polymer *, int> tSix = make_tuple(pTwo, 3);
    tuple<Polymer *, int> tSeven = make_tuple(pTwo, 4);

    tuple<Polymer *, int> tEight = make_tuple(pThree, 4);

    Connection * conOne = new Connection(tOne, tSeven);
    Connection * conTwo = new Connection(tTwo, tSix);
    Connection * conThree = new Connection(tThree, tFive);
    Connection * conFour = new Connection(tFour, tEight);

    Conglomerate * con = new Conglomerate({conOne, conTwo, conThree, conFour}, 2, 2);

    con->updatePolymersInConglomerate();
    con->updatePolymerConnections();

    con->updateTailBindingSites();

    int sites = con->getTailBindingSites();
    vector<Connection *> connections = con->getTailBindingConnections();

    if(sites!=1 || connections.size() != 1){
        return false;
    }

    bool uno = false;

    tuple<Polymer *, int> site_on_two = make_tuple(pTwo, 1);
    tuple<Polymer *, int> site_on_one = make_tuple(pOne, 3);

    Connection * poss_con_one = new Connection(site_on_two, site_on_one);

    for(auto & con : connections){
        if(*con==*poss_con_one){
            uno = true;
        }
    }
    if(!uno){
        return false;
    }
    return true;
}

bool Tests::testUpdateValidNeighboursBinding(){
    Polymer * pOne = new Polymer(0, {1,0,1,0,1});
    pOne->setIndex(0);

    Polymer * pTwo = new Polymer(1, {1,0,1,0,1});
    pTwo->setIndex(1);

    Polymer * pThree = new Polymer(0, {1,1,1,1,1});
    pThree->setIndex(2);

    tuple<Polymer *, int> tOne = make_tuple(pOne, 0);
    tuple<Polymer *, int> tTwo = make_tuple(pOne, 1);
    tuple<Polymer *, int> tThree = make_tuple(pOne, 2);

    tuple<Polymer *, int> tFour = make_tuple(pTwo, 0);
    tuple<Polymer *, int> tFive = make_tuple(pTwo, 2);
    tuple<Polymer *, int> tSix = make_tuple(pTwo, 3);
    tuple<Polymer *, int> tSeven = make_tuple(pTwo, 4);

    tuple<Polymer *, int> tEight = make_tuple(pThree, 4);

    Connection * conOne = new Connection(tOne, tSeven);
    Connection * conTwo = new Connection(tTwo, tSix);
    Connection * conThree = new Connection(tThree, tFive);
    Connection * conFour = new Connection(tFour, tEight);

    Conglomerate * con = new Conglomerate({conOne, conTwo, conThree, conFour}, 2, 2);

    con->updatePolymersInConglomerate();
    con->updatePolymerConnections();

    con->updateValidNeighboursBinding();

    if(con->getValidNeighboursBinding()!=0){
        return false;
    }

    Polymer * pOn = new Polymer(0, {1,0,1,0,1});
    pOn->setIndex(0);

    Polymer * pTw = new Polymer(1, {1,0,1,0,1});
    pTw->setIndex(1);

    Polymer * pThre = new Polymer(0, {1,0,1,0,1});
    pThre->setIndex(2);

    tuple<Polymer *, int> tOn = make_tuple(pOn, 2);
    tuple<Polymer *, int> tTw = make_tuple(pOn, 3);
    tuple<Polymer *, int> tThre = make_tuple(pOn, 4);

    tuple<Polymer *, int> tFou = make_tuple(pTw, 0);
    tuple<Polymer *, int> tNin = make_tuple(pTw, 1);
    tuple<Polymer *, int> tFiv = make_tuple(pTw, 2);
    tuple<Polymer *, int> tSi = make_tuple(pTw, 3);
    tuple<Polymer *, int> tSeve = make_tuple(pTw, 4);

    tuple<Polymer *, int> tEigh = make_tuple(pThre, 0);
    tuple<Polymer *, int> tTe = make_tuple(pThre, 1);

    Connection * conOn = new Connection(tOn, tSeve);
    Connection * conTw = new Connection(tTw, tSi);
    Connection * conThre = new Connection(tThre, tFiv);
    Connection * conFou = new Connection(tNin, tEigh);
    Connection * conFiv = new Connection(tFou, tTe);

    Conglomerate * co = new Conglomerate({conOn, conTw, conThre, conFou, conFiv}, 2, 2);

    co->updatePolymersInConglomerate();
    co->updatePolymerConnections();

    co->updateValidNeighboursBinding();

    if(co->getValidNeighboursBinding()!=1 || co->getValidUnconnectedNeighbours().size()!=1){
        return false;
    }

    UnconnectedNeighbours * steve = new UnconnectedNeighbours(pOn, pThre);

    if(!(*steve == *co->getValidUnconnectedNeighbours()[0])){
        return false;
    }

    return true;

}

bool Tests::testUpdateValidNeighboursUnbinding(){
    Polymer * pOne = new Polymer(0, {1,0,1,0,1});
    pOne->setIndex(0);

    Polymer * pTwo = new Polymer(1, {1,0,1,0,1});
    pTwo->setIndex(1);

    Polymer * pThree = new Polymer(0, {1,1,1,1,1});
    pThree->setIndex(2);

    tuple<Polymer *, int> tOne = make_tuple(pOne, 0);
    tuple<Polymer *, int> tTwo = make_tuple(pOne, 1);
    tuple<Polymer *, int> tThree = make_tuple(pOne, 2);

    tuple<Polymer *, int> tFour = make_tuple(pTwo, 0);
    tuple<Polymer *, int> tFive = make_tuple(pTwo, 2);
    tuple<Polymer *, int> tSix = make_tuple(pTwo, 3);
    tuple<Polymer *, int> tSeven = make_tuple(pTwo, 4);

    tuple<Polymer *, int> tEight = make_tuple(pThree, 4);

    Connection * conOne = new Connection(tOne, tSeven);
    Connection * conTwo = new Connection(tTwo, tSix);
    Connection * conThree = new Connection(tThree, tFive);
    Connection * conFour = new Connection(tFour, tEight);

    Conglomerate * con = new Conglomerate({conOne, conTwo, conThree, conFour}, 2, 2);

    con->updatePolymersInConglomerate();
    con->updatePolymerConnections();

    con->updateValidNeighboursUnbinding();

    if(con->getValidNeighboursUnbinding()!=4){
        return false;
    }

    ConnectedNeighbours * neighOne = new ConnectedNeighbours(pOne, 0, 1);
    ConnectedNeighbours * neighTwo = new ConnectedNeighbours(pOne, 1, 2);
    ConnectedNeighbours * neighThree = new ConnectedNeighbours(pTwo, 2, 3);
    ConnectedNeighbours * neighFour = new ConnectedNeighbours(pTwo, 3, 4);

    bool uno = false;
    bool dos = false;
    bool tres = false;
    bool cuatro = false;

    for(auto & connect : con->getValidConnectedNeighbours()){

        if(*connect==*neighOne){
            uno = true;
        }

        if(*connect==*neighTwo){
            dos = true;
        }

        if(*connect==*neighThree){
            tres = true;
        }

        if(*connect==*neighFour){
            cuatro = true;
        }

    }

    if(!uno || !dos || !tres || !cuatro){
        return false;
    }

    Polymer * pOn = new Polymer(0, {1,0,1,0,1});
    pOn->setIndex(0);

    Polymer * pTw = new Polymer(1, {1,0,1,0,1});
    pTw->setIndex(1);

    Polymer * pThre = new Polymer(0, {1,0,1,0,1});
    pThre->setIndex(2);

    tuple<Polymer *, int> tOn = make_tuple(pOn, 2);
    tuple<Polymer *, int> tTw = make_tuple(pOn, 3);
    tuple<Polymer *, int> tThre = make_tuple(pOn, 4);

    tuple<Polymer *, int> tFou = make_tuple(pTw, 0);
    tuple<Polymer *, int> tNin = make_tuple(pTw, 1);
    tuple<Polymer *, int> tFiv = make_tuple(pTw, 2);
    tuple<Polymer *, int> tSi = make_tuple(pTw, 3);
    tuple<Polymer *, int> tSeve = make_tuple(pTw, 4);

    tuple<Polymer *, int> tEigh = make_tuple(pThre, 0);
    tuple<Polymer *, int> tTe = make_tuple(pThre, 1);

    Connection * conOn = new Connection(tOn, tSeve);
    Connection * conTw = new Connection(tTw, tSi);
    Connection * conThre = new Connection(tThre, tFiv);
    Connection * conFou = new Connection(tNin, tEigh);
    Connection * conFiv = new Connection(tFou, tTe);

    Conglomerate * co = new Conglomerate({conOn, conTw, conThre, conFou, conFiv}, 2, 2);

    co->updatePolymersInConglomerate();
    co->updatePolymerConnections();

    co->updateValidNeighboursUnbinding();

    if(co->getValidNeighboursUnbinding()!=6 || co->getValidConnectedNeighbours().size()!=6){
        return false;
    }


    ConnectedNeighbours * steve = new ConnectedNeighbours(pOn, 2, 3);
    ConnectedNeighbours * stephen = new ConnectedNeighbours(pOn, 3, 4);
    ConnectedNeighbours * stephe = new ConnectedNeighbours(pTw, 0, 1);
    ConnectedNeighbours * steven = new ConnectedNeighbours(pTw, 2, 3);
    ConnectedNeighbours * stephanie = new ConnectedNeighbours(pTw, 3, 4);
    ConnectedNeighbours * stephany = new ConnectedNeighbours(pThre, 0, 1);

    uno = false;
    dos = false;
    tres = false;
    cuatro = false;
    bool cinco = false;
    bool seis = false;

    for(auto & connect : co->getValidConnectedNeighbours()){

        if(*connect==*steve){
            uno = true;
        }

        if(*connect==*steven){
            dos = true;
        }

        if(*connect==*stephe){
            tres = true;
        }

        if(*connect==*stephen){
            cuatro = true;
        }

        if(*connect==*stephanie){
            cinco = true;
        }

        if(*connect==*stephany){
            seis = true;
        }

    }

    if(!uno || !dos || !tres || !cuatro || !cinco || !seis){
        return false;
    }

    return true;
}

bool Tests::testConglomerateEquals(){
    return true;
}

bool Tests::testJoinPolymer(){
    Polymer * pOn = new Polymer(0, {1,0,1,0,1});
    pOn->setIndex(0);

    Polymer * pTw = new Polymer(1, {1,0,1,0,1});
    pTw->setIndex(1);

    Polymer * pThre = new Polymer(0, {1,0,1,0,1});
    pThre->setIndex(2);

    tuple<Polymer *, int> tOn = make_tuple(pOn, 2);
    tuple<Polymer *, int> tTw = make_tuple(pOn, 3);
    tuple<Polymer *, int> tThre = make_tuple(pOn, 4);

    tuple<Polymer *, int> tFou = make_tuple(pTw, 0);
    tuple<Polymer *, int> tNin = make_tuple(pTw, 1);
    tuple<Polymer *, int> tFiv = make_tuple(pTw, 2);
    tuple<Polymer *, int> tSi = make_tuple(pTw, 3);
    tuple<Polymer *, int> tSeve = make_tuple(pTw, 4);

    tuple<Polymer *, int> tEigh = make_tuple(pThre, 0);
    tuple<Polymer *, int> tTe = make_tuple(pThre, 1);

    Connection * conOn = new Connection(tOn, tSeve);
    Connection * conTw = new Connection(tTw, tSi);
    Connection * conThre = new Connection(tThre, tFiv);
    Connection * conFou = new Connection(tNin, tEigh);
    Connection * conFiv = new Connection(tFou, tTe);

    Conglomerate * co = new Conglomerate({conOn, conTw, conThre, conFou, conFiv}, 2, 2);

    co->updatePolymersInConglomerate();
    co->updatePolymerConnections();
    co->updateValidNeighboursUnbinding();
    co->updateValidNeighboursBinding();

    if(co->getValidUnconnectedNeighbours().size()!=1){
        return false;
    }

    co->joinPolymers(co->getValidUnconnectedNeighbours()[0]);

    co->updatePolymersInConglomerate();
    co->updatePolymerConnections();

    co->updateValidNeighboursBinding();



    if(co->getValidUnconnectedNeighbours().size()!=0){
        return false;
    }

    if(co->getPolymersInConglomerate().size()!=2){
        return false;
    }
    if(co->getValidNeighboursBinding()!=0){
        return false;
    }
    if(co->getValidNeighboursUnbinding()!=8){
        return false;
    }

    return true;

}

bool Tests::testSeparatePolymer(){
    Polymer * pOn = new Polymer(0, {1,0,1,0,1});
    pOn->setIndex(0);

    Polymer * pTw = new Polymer(1, {1,0,1,0,1});
    pTw->setIndex(1);

    Polymer * pThre = new Polymer(0, {1,0,1,0,1});
    pThre->setIndex(2);

    tuple<Polymer *, int> tOn = make_tuple(pOn, 2);
    tuple<Polymer *, int> tTw = make_tuple(pOn, 3);
    tuple<Polymer *, int> tThre = make_tuple(pOn, 4);

    tuple<Polymer *, int> tFou = make_tuple(pTw, 0);
    tuple<Polymer *, int> tNin = make_tuple(pTw, 1);
    tuple<Polymer *, int> tFiv = make_tuple(pTw, 2);
    tuple<Polymer *, int> tSi = make_tuple(pTw, 3);
    tuple<Polymer *, int> tSeve = make_tuple(pTw, 4);

    tuple<Polymer *, int> tEigh = make_tuple(pThre, 0);
    tuple<Polymer *, int> tTe = make_tuple(pThre, 1);

    Connection * conOn = new Connection(tOn, tSeve);
    Connection * conTw = new Connection(tTw, tSi);
    Connection * conThre = new Connection(tThre, tFiv);
    Connection * conFou = new Connection(tNin, tEigh);
    Connection * conFiv = new Connection(tFou, tTe);

    Conglomerate * co = new Conglomerate({conOn, conTw, conThre, conFou, conFiv}, 2, 2);

    co->updatePolymersInConglomerate();
    co->updatePolymerConnections();
    co->updateValidNeighboursUnbinding();
    co->updateValidNeighboursBinding();

    vector<ConnectedNeighbours *> neighbours = co->getValidConnectedNeighbours();

    if(neighbours.size()==0){
        return false;
    }

    Polymer * p = co->separatePolymers(neighbours[0]);
    p->setIndex(3);
    co->updatePolymersInConglomerate();
    co->updatePolymerConnections();
    co->updateValidNeighboursUnbinding();

    neighbours = co->getValidConnectedNeighbours();

    if(neighbours.size()!=4){
        return false;
    }
    tuple<Polymer *, int> tupperware = make_tuple(p, 0);
    Connection * c = new Connection(tupperware, tSi);

    tuple<Polymer *, int> tupperwhere = make_tuple(p, 1);
    Connection * cc = new Connection(tupperwhere, tFiv);

    bool uno = false;
    bool dos = false;
    bool tres = false;
    bool cuatro = false;
    bool cinco = false;

    if(co->getConnections().size()!=5){
        return false;
    }

    for(auto & connection : co->getConnections()){
        if(*connection == *c){
            uno = true;
        }
        if(*connection == *conOn){
            dos = true;
        }
        if(*connection == *cc){
            tres = true;
        }
        if(*connection == *conFou){
            cuatro = true;
        }
        if(*connection == *conFiv){
            cinco = true;
        }
    }

    if(!uno || !dos || !tres || !cuatro || !cinco){
        return false;
    }

    return true;
}

/*bool Tests::testConglomerateInitialisation(){

    Polymer * polymer = new Polymer(0, {1,1,1,1,1,1});
    polymer->setIndex(0);
    Conglomerate * c = new Conglomerate(polymer, 2, 2);

    if(c->getConnections().size()!=0){
        return false;
    }

    if(c->getPolymersInConglomerate().size()!=1){
        return false;
    }

    if(!(*c->getPolymersInConglomerate()[0]==*polymer)){
        return false;
    }

    if(c->getAvailableTemplateBonds().size()!=2){
        return false;
    }

    if(c->getAvailableTemplateBonds()[0].size()!=2 || c->getAvailableTemplateBonds()[1].size()!=2){
        return false;
    }

    if(c->getAvailableTemplateBonds()[0][0]!=0 || c->getAvailableTemplateBonds()[0][1]!=0){
        return false;
    }

    if(c->getAvailableTemplateBonds()[1][0]!=6 || c->getAvailableTemplateBonds()[1][1]!=0){
        return false;
    }

    if(c->getValidNeighboursBinding()!=0){
        return false;
    }

    if(c->getValidNeighboursUnbinding()!=0){
        return false;
    }

    if(c->getTailUnbindingSites()!=0){
        return false;
    }

    if(c->getTailBindingSites()!=0){
        return false;
    }

    if(c->getPolymerConnections().size()!=1){
        return false;
    }

    if(c->getPolymerConnections()[0].size()!=0){
        return false;
    }


    Polymer * pOne = new Polymer(0, {1,0,1,0,1});
    pOne->setIndex(0);

    Polymer * pTwo = new Polymer(1, {1,0,1,0,1});
    pOne->setIndex(1);

    Polymer * pThree = new Polymer(0, {1,0,1,0,1});
    pOne->setIndex(2);

    tuple<Polymer *, int> tOne = make_tuple(pOne, 0);
    tuple<Polymer *, int> tTwo = make_tuple(pOne, 1);
    tuple<Polymer *, int> tThree = make_tuple(pOne, 2);

    tuple<Polymer *, int> tFour = make_tuple(pTwo, 0);
    tuple<Polymer *, int> tFive = make_tuple(pTwo, 2);
    tuple<Polymer *, int> tSix = make_tuple(pTwo, 3);
    tuple<Polymer *, int> tSeven = make_tuple(pTwo, 4);

    tuple<Polymer *, int> tEight = make_tuple(pThree, 4);

    Connection * conOne = new Connection(tOne, tSeven);
    Connection * conTwo = new Connection(tTwo, tSix);
    Connection * conThree = new Connection(tThree, tFive);
    Connection * conFour = new Connection(tFour, tEight);

    Conglomerate * con = new Conglomerate({conOne, conTwo, conThree, conFour}, 2, 2);

    if(con->getConnections().size()!=4){
        cout << 1 << endl;
        return false;
    }

    if(con->getPolymersInConglomerate().size()!=3){
        cout << 2 << endl;
        cout << con->getPolymersInConglomerate().size() << endl;
        return false;
    }

    if(con->getAvailableTemplateBonds().size()!=2){
        cout << 3 << endl;
        return false;
    }

    if(con->getAvailableTemplateBonds()[0].size()!=2 || c->getAvailableTemplateBonds()[1].size()!=2){
        cout << 4 << endl;
        return false;
    }

    if(con->getAvailableTemplateBonds()[0][0]!=3 || c->getAvailableTemplateBonds()[0][1]!=1){
        cout << 5 << endl;
        return false;
    }

    if(con->getAvailableTemplateBonds()[1][0]!=3 || c->getAvailableTemplateBonds()[1][1]!=0){
        cout << 6 << endl;
        return false;
    }

    if(con->getValidNeighboursBinding()!=0){
        cout << 7 << endl;
        return false;
    }

    if(con->getValidNeighboursUnbinding()!=2){
        cout << 8 << endl;
        return false;
    }

    if(con->getTailUnbindingSites()!=2){
        cout << 9 << endl;
        return false;
    }

    if(con->getTailBindingSites()!=0){
        cout << 10 << endl;
        return false;
    }

    if(con->getPolymerConnections().size()!=3){
        cout << 11 << endl;
        return false;
    }


    return true;

}*/

bool Tests::testUpdateRates() {

    return true;
}

