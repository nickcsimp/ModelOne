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
    cout << "Test Polymer Initialisation" << endl;
    if(!testPolymerInitialisation()){
        cout << "Failed: testPolymerInitialisation()";
        return false;
    }

    cout << "Test Add Polymer" << endl;
    if(!testAddPolymer()){
        cout << "Failed: testAddPolymer()";
        return false;
    }

    cout << "Test Polymer Equals" << endl;
    if(!testPolymerEquals()){
        cout << "Failed: testPolymerEquals()";
        return false;
    }

    cout << "Test CutPolymer" << endl;
    if(!testCutPolymer()){
        cout << "Failed: testCutPolymer()";
        return false;
    }

    cout << "Test PolymerAddConnection" << endl;
    if(!testPolymerAddConnection()){
        cout << "Failed: testPolymerAddConnection()";
        return false;
    }

    cout << "Test PolymerRemoveConnection" << endl;
    if(!testPolymerRemoveConnection()){
        cout << "Failed: testPolymerRemoveConnection()";
        return false;
    }

    cout << "Test ConnectionInitialisation" << endl;
    if(!testConnectionInitialisation()){
        cout << "Failed: testConnectionInitialisation()";
        return false;
    }

    cout << "Test ConnectionEquals" << endl;
    if(!testConnectionEquals()){
        cout << "Failed: testConnectionEquals()";
        return false;
    }

    cout << "Test EditConnection" << endl;
    if(!testEditConnection()){
        cout << "Failed: testEditConnection()";
        return false;
    }

    cout << "Test ConnectedNeighboursInitialisation" << endl;
    if(!testConnectedNeighboursInitialisation()){
        cout << "Failed: testConnectedNeighboursInitialisation()";
        return false;
    }

    cout << "Test ConnectedNeighbours Equals" << endl;
    if(!testConnectedNeighboursEquals()){
        cout << "Failed: testConnectedNeighboursEquals()";
        return false;
    }

    cout << "Test UnconnectedNeighboursInitialisation" << endl;
    if(!testUnconnectedNeighboursInitialisation()){
        cout << "Failed: testUnconnectedNeighboursInitialisation()";
        return false;
    }

    cout << "Test UnconnectedNeighbours Equals" << endl;
    if(!testUnconnectedNeighboursEquals()){
        cout << "Failed: testUnconnectedNeighboursEquals()";
        return false;
    }
    cout << "Test DimerInitialisation" << endl;
    if(!testDimerInitialisation()){
        cout << "Failed: testDimerInitialisation()";
        return false;
    }

    cout << "Test Dimer Equals" << endl;
    if(!testDimerEquals()){
        cout << "Failed: testDimerEquals()";
        return false;
    }

    cout << "Test UpdatePolymersInConglomerate" << endl;
    if(!testUpdatePolymersInConglomerate()){
        cout << "Failed: testUpdatePolymersInConglomerate()";
        return false;
    }

    cout << "Test UpdatePolymerConnections" << endl;
    if(!testUpdatePolymerConnections()){
        cout << "Failed: testUpdatePolymerConnections()";
        return false;
    }

    cout << "Test UpdateAvailableTemplateBonds" << endl;
    if(!testUpdateAvailableTemplateBonds()){
        cout << "Failed: testUpdateAvailableTemplateBonds()";
        return false;
    }

    cout << "Test GetPossibleSites" << endl;
    if(!testGetPossibleSites()){
        cout << "Failed: testGetPossibleSites()";
        return false;
    }

    cout << "Test UpdateTailUnbindingSites" << endl;
    if(!testUpdateTailUnbindingSites()){
        cout << "Failed: testUpdateTailUnbindingSites()";
        return false;
    }

    cout << "Test UpdateTailBindingSites" << endl;
    if(!testUpdateTailBindingSites()){
        cout << "Failed: testUpdateTailBindingSites()";
        return false;
    }

    cout << "Test ConnectionOptions" << endl;
    if(!testConnectionOptions()){
        cout << "Failed:testConnectionOptions()";
        return false;
    }

    cout << "Test UpdateValidNeighboursBinding" << endl;
    if(!testUpdateValidNeighboursBinding()){
        cout << "Failed:testUpdateValidNeighboursBinding()";
        return false;
    }

    cout << "Test UpdateValidNeighboursUnbinding" << endl;
    if(!testUpdateValidNeighboursUnbinding()){
        cout << "Failed:testUpdateValidNeighboursUnbinding()";
        return false;
    }

    cout << "Test ConglomerateEquals" << endl;
    if(!testConglomerateEquals()){
        cout << "Failed:testConglomerateEquals()";
        return false;
    }

    cout << "Test JoinPolymer" << endl;
    if(!testJoinPolymer()){
        cout << "Failed:testJoinPolymer()";
        return false;
    }

    cout << "Test SeparatePolymers" << endl;
    if(!testSeparatePolymer()){
        cout << "Failed:testSeparatePolymer()";
        return false;
    }

    cout << "Test GetTree" << endl;
    if(!testGetTree()){
        cout << "Failed:testGetTree()";
        return false;
    }
    cout << "Test UpdateConnectivity" << endl;
    if(!testUpdateConnectivity()){
        cout << "Failed:testUpdateConnectivity()";
        return false;
    }
    cout << "Test RemoveConnection" << endl;
    if(!testRemoveConnection()){
        cout << "Failed:testRemoveConnection()";
        return false;
    }

    cout << "Test Monomer Rebind" << endl;
    if(!testMonomerRebind()){
        cout << "Failed:testMonomerRebind()";
        return false;
    }

    cout << "Test System Ability" << endl;
    if(!testSystemAbility()){
        cout << "Failed:testSystemAbility()";
        return false;
    }

    cout << "Test Perform Functions" << endl;
    if(!testPerformFunctions()){
        cout << "Failed:testPerformFunctions()";
        return false;
    }


    cout << "Tests passed" << endl;
    return true;
}

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

    int head_sites = con->getHeadUnbindingSites();
    vector<Connection *> head_connections = con->getHeadUnbindingConnections();

    if(sites!=1 || connections.size() != 1){
        return false;
    }

    if(head_sites!=2 || head_connections.size() != 2){
        return false;
    }

    bool uno = false;
    bool dos = false;
    bool tres = false;

    for(auto & con : head_connections){
        if(*con==*conOne){
            uno = true;
        }

        if(*con==*conFour){
            tres = true;
        }
    }

    for(auto & con : connections){
        if(*con==*conThree){
            dos = true;
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

    int head_sites = con->getHeadBindingSites();
    vector<Connection *> head_connections = con->getHeadBindingConnections();

    if(head_sites !=0 || head_connections.size()!=0){
        return false;
    }

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

bool Tests::testGetTree(){
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

    Conglomerate * co = new Conglomerate({conOn, conTw, conThre, conFou}, 2, 2);

    co->updatePolymersInConglomerate();
    co->updatePolymerConnections();

    vector<Polymer *> p = co->getTree(pOn, {pOn});

    if(p.size()!=3){
        return false;
    }

    bool uno = false;
    bool dos = false;
    bool tres = false;

    for(auto & poly : p){
        if(*poly==*pOn){
            uno = true;
        }

        if(*poly==*pTw){
            dos = true;
        }

        if(*poly==*pThre){
            tres = true;
        }
    }

    if(!uno || !dos || !tres){
        return false;
    }


    vector<Polymer *> pol = co->getTree(pTw, {pTw});

    if(pol.size()!=3){
        return false;
    }

    uno = false;
    dos = false;
    tres = false;

    for(auto & poly : pol){
        if(*poly==*pOn){
            uno = true;
        }

        if(*poly==*pTw){
            dos = true;
        }

        if(*poly==*pThre){
            tres = true;
        }
    }

    if(!uno || !dos || !tres){
        return false;
    }

    Polymer * pOne = new Polymer(0, {1,0,1,0,1});
    pOne->setIndex(0);

    Polymer * pTwo = new Polymer(1, {1,0,1,0,1});
    pTwo->setIndex(1);

    Polymer * pThree = new Polymer(0, {1,0,1,0,1});
    pThree->setIndex(2);

    tuple<Polymer *, int> tOne = make_tuple(pOne, 2);
    tuple<Polymer *, int> tTwo = make_tuple(pOne, 3);
    tuple<Polymer *, int> tThree = make_tuple(pOne, 4);

    tuple<Polymer *, int> tFour = make_tuple(pTwo, 0);
    tuple<Polymer *, int> tNine = make_tuple(pTwo, 1);
    tuple<Polymer *, int> tFive = make_tuple(pTwo, 2);
    tuple<Polymer *, int> tSix = make_tuple(pTwo, 3);
    tuple<Polymer *, int> tSeven = make_tuple(pTwo, 4);

    tuple<Polymer *, int> tEight = make_tuple(pThree, 0);
    tuple<Polymer *, int> tTen = make_tuple(pThree, 1);

    Connection * conOne = new Connection(tOne, tSeven);
    Connection * conTwo = new Connection(tTwo, tSix);
    Connection * conThree = new Connection(tThree, tFive);
    Connection * conFour = new Connection(tNine, tEight);
    Connection * conFive = new Connection(tFour, tTen);

    Conglomerate * con = new Conglomerate({conOne, conTwo, conThree}, 2, 2);

    con->updatePolymersInConglomerate();
    con->updatePolymerConnections();

    vector<Polymer *> po = con->getTree(pOne, {pOne});

    if(po.size()!=2){
        return false;
    }

    uno = false;
    dos = false;

    for(auto & poly : po){
        if(*poly==*pOne){
            uno = true;
        }

        if(*poly==*pTwo){
            dos = true;
        }
    }

    if(!uno || !dos){
        return false;
    }

    return true;


}

bool Tests::testUpdateConnectivity(){
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

    Conglomerate * co = new Conglomerate({conOn, conTw, conThre, conFou}, 2, 2);

    co->updatePolymersInConglomerate();
    co->updatePolymerConnections();

    vector<vector<Connection *>> output = co->updateConnectivity();

    if(output.size()!=1){
        return false;
    }
    if(output[0].size()!=4){
        return false;
    }

    bool uno = false;
    bool dos = false;
    bool tres = false;
    bool cuatro = false;

    for(auto & con : output[0]){
        if(*con == *conOn){
            uno = true;
        }

        if(*con == *conTw){
            dos = true;
        }

        if(*con == *conThre){
            tres = true;
        }

        if(*con == *conFou){
            cuatro = true;
        }
    }

    if(!uno || !dos || !tres || !cuatro){
        return false;
    }


    Polymer * pOne = new Polymer(0, {1,0,1,0,1});
    pOne->setIndex(0);

    Polymer * pTwo = new Polymer(1, {1,0,1,0,1});
    pTwo->setIndex(1);

    Polymer * pThree = new Polymer(0, {1,0,1,0,1});
    pThree->setIndex(2);

    Polymer * pFour = new Polymer(0, {1,0,1,0,1});
    pFour->setIndex(3);

    tuple<Polymer *, int> tOne = make_tuple(pOne, 2);
    tuple<Polymer *, int> tTwo = make_tuple(pOne, 3);
    tuple<Polymer *, int> tThree = make_tuple(pOne, 4);

    tuple<Polymer *, int> tFour = make_tuple(pTwo, 0);
    tuple<Polymer *, int> tNine = make_tuple(pTwo, 1);
    tuple<Polymer *, int> tFive = make_tuple(pTwo, 2);
    tuple<Polymer *, int> tSix = make_tuple(pTwo, 3);
    tuple<Polymer *, int> tSeven = make_tuple(pTwo, 4);

    tuple<Polymer *, int> tEight = make_tuple(pThree, 0);
    tuple<Polymer *, int> tTen = make_tuple(pThree, 1);

    tuple<Polymer *, int> tEleven = make_tuple(pFour, 4);
    tuple<Polymer *, int> tTwelve = make_tuple(pFour, 3);

    Connection * conOne = new Connection(tOne, tSeven);
    Connection * conTwo = new Connection(tTwo, tSix);
    Connection * conThree = new Connection(tThree, tFive);
    Connection * conFour = new Connection(tEleven, tEight);
    Connection * conFive = new Connection(tTwelve, tTen);

    Conglomerate * con = new Conglomerate({conOne, conTwo, conThree, conFour, conFive}, 2, 2);

    con->updatePolymersInConglomerate();
    con->updatePolymerConnections();

    vector<vector<Connection *>> out = con->updateConnectivity();

    if(out.size()!=2){
        return false;
    }

    if(out[0].size()!=3){
        return false;
    }

    if(out[1].size()!=2){
        return false;
    }

    uno = false;
    dos = false;
    tres = false;
    cuatro = false;
    bool cinco = false;

    for(auto & connect : out[0]){
        if(*connect==*conOne){
            uno = true;
        }

        if(*connect==*conTwo){
            dos = true;
        }

        if(*connect==*conThree){
            tres = true;
        }
    }

    if(!uno || !dos || !tres){
        return false;
    }

    for(auto & connect : out[1]){
        if(*connect==*conFour){
            cuatro = true;
        }

        if(*connect==*conFive){
            cinco = true;
        }
    }

    if(!cuatro || !cinco){
        return false;
    }

    return true;
}

bool Tests::testRemoveConnection(){
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

    Conglomerate * co = new Conglomerate({conOn, conTw, conThre, conFou}, 2, 2);

    co->updatePolymersInConglomerate();
    co->updatePolymerConnections();

    vector<Conglomerate *> output = co->removeConnection(conFou);

    if(output.size()!=1){
        return false;
    }

    output[0]->setIndex(1);

    Conglomerate * new_con = new Conglomerate(pThre, 2, 2);

    new_con->setIndex(1);

    if(!(*new_con==*output[0])){

        return false;
    }

    Polymer * pMon = new Polymer(0, {0});
    Polymer * pTue = new Polymer(1, {0});

    tuple<Polymer *, int> tWed = make_tuple(pMon, 0);
    tuple<Polymer *, int> tThu = make_tuple(pTue, 0);

    Connection * cFri = new Connection(tWed, tThu);

    Conglomerate * cSat = new Conglomerate({cFri}, 2, 1);
    cSat->updatePolymersInConglomerate();
    cSat->updatePolymerConnections();
    vector<Conglomerate *> vSun = cSat->removeConnection(cFri);

    if(vSun.size()!=1){
        return false;
    }
    Conglomerate * correct = new Conglomerate(pTue, 2, 1);
    if(!(*vSun[0]==*correct)){
        return false;
    }


    return true;
}

bool Tests::testMonomerRebind(){

    vector<Conglomerate *> conglomerates;
    int index = 0;
    Polymer * monomer = new Polymer(1, {0});
    monomer->setIndex(++index);
    Conglomerate * moncong = new Conglomerate(monomer, 2, 1);
    moncong->setIndex(++index);
    Polymer * polymer = new Polymer(0, {0,0,0,0,0});
    polymer->setIndex(++index);
    Conglomerate * polcong = new Conglomerate(polymer, 2, 1);
    polcong->setIndex(++index);

    conglomerates.push_back(moncong);
    conglomerates.push_back(polcong);

    tuple<Polymer *, int> tup = make_tuple(monomer, 0);
    tuple<Polymer *, int> tups = make_tuple(polymer, 2);

    Connection * connie = new Connection(tup, tups);
    polcong->addConnection(connie);

    polcong->updatePolymersInConglomerate();
    polcong->updatePolymerConnections();
    polcong->updateAvailableTemplateBonds();
    polcong->updateTailUnbindingSites();
    polcong->updateTailBindingSites();
    polcong->updateValidNeighboursBinding();
    polcong->updateValidNeighboursUnbinding();
    int cong_to_be_removed = -1;
    for(int i=0; i<conglomerates.size(); i++){
        if(*conglomerates[i]==*moncong){
            cong_to_be_removed=i;
        }
    }
    conglomerates.erase(conglomerates.begin()+cong_to_be_removed);

    Conglomerate * moncongtwo = polcong->removeConnection(connie)[0];
    moncongtwo->setIndex(++index);
    conglomerates.push_back(moncongtwo);

    polcong->addConnection(connie);
    polcong->updatePolymersInConglomerate();
    polcong->updatePolymerConnections();
    polcong->updateAvailableTemplateBonds();
    polcong->updateTailUnbindingSites();
    polcong->updateTailBindingSites();
    polcong->updateValidNeighboursBinding();
    polcong->updateValidNeighboursUnbinding();
    cong_to_be_removed = -1;
    for(int i=0; i<conglomerates.size(); i++){
        if(*conglomerates[i]==*moncongtwo){
            cong_to_be_removed=i;
        }
    }
    conglomerates.erase(conglomerates.begin()+cong_to_be_removed);

    polcong->updateConglomerate();
    return true;
}

bool Tests::testSystemAbility(){

    //Testing system initialisation
    int family_count = 2;
    int monomer_type_count = 1;
    vector<vector<int>> number_of_monomers;
    Polymer * initial_template;

    vector<int> type_one;
    type_one.push_back(10);
    type_one.push_back(10);
    number_of_monomers.push_back(type_one);

    initial_template = new Polymer(0, {0,0,0,0,0,0});

    System * system = new System(family_count, monomer_type_count, number_of_monomers, initial_template);

    system->getEverything();
    vector<vector<Connection *>> head_binding = system->getHeadBinding();
    vector<vector<Connection *>> tail_binding = system->getTailBinding();
    vector<vector<Connection *>> head_unbinding = system->getHeadUnbinding();
    vector<vector<Connection *>> tail_unbinding = system->getTailUnbinding();
    vector<vector<ConnectedNeighbours *>> connected_neighbours = system->getConnectedNeighbours();
    vector<vector<UnconnectedNeighbours *>> unconnected_neighbours = system->getUnconnectedNeighbours();
    vector<vector<PotentialSite *>> available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    vector<vector<ExternalConnection *>> potential_head_connection = system->getPotentialHeadConnection();
    vector<vector<ExternalConnection *>> potential_tail_connection = system->getPotentialTailConnection();

    if(head_binding.size()!=21){
        return false;
    }
    for(auto & elem : head_binding){
        if(elem.size()!=0){
            return false;
        }
    }

    if(tail_binding.size()!=21){
        return false;
    }
    for(auto & elem : tail_binding){
        if(elem.size()!=0){
            return false;
        }
    }

    if(head_unbinding.size()!=21){
        return false;
    }
    for(auto & elem : head_unbinding){
        if(elem.size()!=0){
            return false;
        }
    }

    if(tail_unbinding.size()!=21){
        return false;
    }
    for(auto & elem : tail_unbinding){
        if(elem.size()!=0){
            return false;
        }
    }

    if(connected_neighbours.size()!=21){
        return false;
    }
    for(auto & elem : connected_neighbours){
        if(elem.size()!=0){
            return false;
        }
    }

    if(unconnected_neighbours.size()!=21){
        return false;
    }
    for(auto & elem : unconnected_neighbours){
        if(elem.size()!=0){
            return false;
        }
    }

    if(available_head_tail_sites.size()!=21){
        return false;
    }
    for(int elem=0; elem<available_head_tail_sites.size(); elem++){
        if(elem == 0){
            if(available_head_tail_sites[elem].size()!=6){
                return false;
            }
        } else if(available_head_tail_sites[elem].size()!=1){
            return false;
        }
    }

    if(potential_head_connection.size()!=21){
        return false;
    }
    for(int elem=0; elem<potential_head_connection.size(); elem++){
        if(elem==0){
            if(potential_head_connection[elem].size()!=60){
                return false;
            }
        } else if(elem<11){
            if(potential_head_connection[elem].size()!=10) {
                return false;
            }
        } else if(potential_head_connection[elem].size()!=0) {
            return false;
        }

    }

    if(potential_tail_connection.size()!=21){
        return false;
    }
    for(int elem=0; elem<potential_tail_connection.size(); elem++){
        if(potential_tail_connection[elem].size()!=0){
            return false;
        }
    }

    //Testing first monomer-conglomerate bond
    vector<Conglomerate *> conglomerates = system->getConglomerates();
    vector<Polymer *> polymers = system->getPolymers();

    tuple<Polymer *, int> tOne = make_tuple(polymers[0] ,1);
    tuple<Polymer *, int> tTwo = make_tuple(polymers[20] ,0);
    Connection * conOne = new Connection(tOne, tTwo);
    conglomerates[0]->addConnection(conOne);

    system->eraseConglomerate(20);

    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();


    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if(head_binding.size()!=20){
        return false;
    }
    for(auto & elem : head_binding){
        if(elem.size()!=0){
            return false;
        }
    }

    if(tail_binding.size()!=20){
        return false;
    }
    for(auto & elem : tail_binding){
        if(elem.size()!=0){
            return false;
        }
    }

    if(head_unbinding.size()!=20){
        return false;
    }
    for(int elem=0; elem<head_unbinding.size(); elem++){
        if(elem==0){
            if(head_unbinding[elem].size()!=1){
                return false;
            }
        } else if(head_unbinding[elem].size()!=0){
            return false;
        }
    }

    if(tail_unbinding.size()!=20){
        return false;
    }
    for(auto & elem : tail_unbinding){
        if(elem.size()!=0){
            return false;
        }
    }

    if(connected_neighbours.size()!=20){
        return false;
    }
    for(auto & elem : connected_neighbours){
        if(elem.size()!=0){
            return false;
        }
    }

    if(unconnected_neighbours.size()!=20){
        return false;
    }
    for(auto & elem : unconnected_neighbours){
        if(elem.size()!=0){
            return false;
        }
    }

    if(available_head_tail_sites.size()!=20){
        return false;
    }
    for(int elem=0; elem<available_head_tail_sites.size(); elem++){
        if(elem == 0){
            if(available_head_tail_sites[elem].size()!=5){
                return false;
            }
        } else if(available_head_tail_sites[elem].size()!=1){
            return false;
        }
    }

    if(potential_head_connection.size()!=20){
        return false;
    }
    for(int elem=0; elem<potential_head_connection.size(); elem++){
        if(elem==0){
            if(potential_head_connection[elem].size()!=45){
                return false;
            }
        } else if(elem<11){
            if(potential_head_connection[elem].size()!=9) {
                return false;
            }
        } else if(potential_head_connection[elem].size()!=0) {
            return false;
        }

    }

    if(potential_tail_connection.size()!=20){
        return false;
    }
    for(int elem=0; elem<potential_tail_connection.size(); elem++){
        if(potential_tail_connection[elem].size()!=0){
            return false;
        }
    }

    //Testing second monomer-conglomerate bond
    tOne = make_tuple(polymers[0] ,0);
    tTwo = make_tuple(polymers[19] ,0);
    conOne = new Connection(tOne, tTwo);
    conglomerates[0]->addConnection(conOne);

    system->eraseConglomerate(19);

    system->getEverything();

    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if(head_binding.size()!=19){
        
        return false;
    }
    for(auto & elem : head_binding){
        if(elem.size()!=0){
            
            return false;
        }
    }

    if(tail_binding.size()!=19){
        
        return false;
    }
    for(auto & elem : tail_binding){
        if(elem.size()!=0){
            
            return false;
        }
    }

    if(head_unbinding.size()!=19){
        
        return false;
    }
    for(int elem=0; elem<head_unbinding.size(); elem++){
        if(elem==0){
            if(head_unbinding[elem].size()!=2){
                
                return false;
            }
        } else if(head_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(tail_unbinding.size()!=19){
        
        return false;
    }
    for(auto & elem : tail_unbinding){
        if(elem.size()!=0){
            
            return false;
        }
    }

    if(connected_neighbours.size()!=19){
        
        return false;
    }
    for(auto & elem : connected_neighbours){
        if(elem.size()!=0){
            
            return false;
        }
    }

    if(unconnected_neighbours.size()!=19){
        
        return false;
    }
    for(int elem=0; elem<unconnected_neighbours.size(); elem++){
        if(elem==0){
            if(unconnected_neighbours[elem].size()!=1){
                
                return false;
            }
        } else if(unconnected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(available_head_tail_sites.size()!=19){
        
        return false;
    }
    for(int elem=0; elem<available_head_tail_sites.size(); elem++){
        if(elem == 0){
            if(available_head_tail_sites[elem].size()!=4){
                
                return false;
            }
        } else if(available_head_tail_sites[elem].size()!=1){
            
            return false;
        }
    }

    if(potential_head_connection.size()!=19){
        
        return false;
    }
    for(int elem=0; elem<potential_head_connection.size(); elem++){
        if(elem==0){
            if(potential_head_connection[elem].size()!=32){
                
                return false;
            }
        } else if(elem<11){
            if(potential_head_connection[elem].size()!=8) {
                
                return false;
            }
        } else if(potential_head_connection[elem].size()!=0) {
            
            return false;
        }

    }

    if(potential_tail_connection.size()!=19){
        
        return false;
    }
    for(int elem=0; elem<potential_tail_connection.size(); elem++){
        if(potential_tail_connection[elem].size()!=0){
            
            return false;
        }
    }

    //Testing third monomer-conglomerate bond
    
    tOne = make_tuple(polymers[0] ,3);
    tTwo = make_tuple(polymers[18] ,0);
    conOne = new Connection(tOne, tTwo);
    conglomerates[0]->addConnection(conOne);

    system->eraseConglomerate(18);

    system->getEverything();

    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if(head_binding.size()!=18){
        
        return false;
    }
    for(auto & elem : head_binding){
        if(elem.size()!=0){
            
            return false;
        }
    }

    if(tail_binding.size()!=18){
        
        return false;
    }
    for(auto & elem : tail_binding){
        if(elem.size()!=0){
            
            return false;
        }
    }

    if(head_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<head_unbinding.size(); elem++){
        if(elem==0){
            if(head_unbinding[elem].size()!=3){
                
                return false;
            }
        } else if(head_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(tail_unbinding.size()!=18){
        
        return false;
    }
    for(auto & elem : tail_unbinding){
        if(elem.size()!=0){
            
            return false;
        }
    }

    if(connected_neighbours.size()!=18){
        
        return false;
    }
    for(auto & elem : connected_neighbours){
        if(elem.size()!=0){
            
            return false;
        }
    }

    if(unconnected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<unconnected_neighbours.size(); elem++){
        if(elem==0){
            if(unconnected_neighbours[elem].size()!=1){
                
                return false;
            }
        } else if(unconnected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(available_head_tail_sites.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<available_head_tail_sites.size(); elem++){
        if(elem == 0){
            if(available_head_tail_sites[elem].size()!=3){
                
                return false;
            }
        } else if(available_head_tail_sites[elem].size()!=1){
            
            return false;
        }
    }

    if(potential_head_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_head_connection.size(); elem++){
        if(elem==0){
            if(potential_head_connection[elem].size()!=21){
                
                return false;
            }
        } else if(elem<11){
            if(potential_head_connection[elem].size()!=7) {
                
                return false;
            }
        } else if(potential_head_connection[elem].size()!=0) {
            
            return false;
        }

    }

    if(potential_tail_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_tail_connection.size(); elem++){
        if(potential_tail_connection[elem].size()!=0){
            
            return false;
        }
    }

    //Testing backbone bonding
    
    UnconnectedNeighbours * conTwo = new UnconnectedNeighbours(polymers[20], polymers[19]);

    conglomerates[0]->joinPolymers(conTwo);
    system->erasePolymer(19);
    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if(head_binding.size()!=18){
        
        return false;
    }
    for(auto & elem : head_binding){
        if(elem.size()!=0){
            
            return false;
        }
    }

    if(tail_binding.size()!=18){
        
        return false;
    }
    for(auto & elem : tail_binding){
        if(elem.size()!=0){
            
            return false;
        }
    }

    if(head_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<head_unbinding.size(); elem++){
        if(elem==0){
            if(head_unbinding[elem].size()!=2){
                
                return false;
            }
        } else if(head_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(tail_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<tail_unbinding.size(); elem++){
        if(elem==0){
            if(tail_unbinding[elem].size()!=1){
                
                return false;
            }
        } else if(tail_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(connected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<connected_neighbours.size(); elem++){
        if(elem==0){
            if(connected_neighbours[elem].size()!=2){
                
                
                return false;
            }
        } else if(connected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(unconnected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<unconnected_neighbours.size(); elem++){
        if(elem==0){
            if(unconnected_neighbours[elem].size()!=0){
                
                return false;
            }
        } else if(unconnected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(available_head_tail_sites.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<available_head_tail_sites.size(); elem++){
        if(elem == 0){
            if(available_head_tail_sites[elem].size()!=3){
                
                return false;
            }
        } else if(available_head_tail_sites[elem].size()!=1){
            
            return false;
        }
    }

    if(potential_head_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_head_connection.size(); elem++){
        if(elem==0){
            if(potential_head_connection[elem].size()!=21){
                
                return false;
            }
        } else if(elem<11){
            if(potential_head_connection[elem].size()!=7) {
                
                return false;
            }
        } else if(potential_head_connection[elem].size()!=0) {
            
            return false;
        }

    }

    if(potential_tail_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_tail_connection.size(); elem++){
        if(potential_tail_connection[elem].size()!=0){
            
            return false;
        }
    }

    //Testing tail unbind
    
    tOne = make_tuple(polymers[0] ,1);
    tTwo = make_tuple(polymers[19] ,0);
    conOne = new Connection(tOne, tTwo);

    conglomerates[0]->removeConnection(conOne);

    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if(head_binding.size()!=18){
        
        return false;
    }
    for(auto & elem : head_binding){
        if(elem.size()!=0){
            
            return false;
        }
    }

    if(tail_binding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<tail_binding.size(); elem++){
        if(elem==0){
            if(tail_binding[elem].size()!=1){
                
                return false;
            }
        } else if(tail_binding[elem].size()!=0){
            
            return false;
        }
    }

    if(head_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<head_unbinding.size(); elem++){
        if(elem==0){
            if(head_unbinding[elem].size()!=2){
                
                return false;
            }
        } else if(head_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(tail_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<tail_unbinding.size(); elem++){
        if(elem==0){
            if(tail_unbinding[elem].size()!=0){
                
                return false;
            }
        } else if(tail_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(connected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<connected_neighbours.size(); elem++){
        if(elem==0){
            if(connected_neighbours[elem].size()!=0){
                
                
                return false;
            }
        } else if(connected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(unconnected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<unconnected_neighbours.size(); elem++){
        if(elem==0){
            if(unconnected_neighbours[elem].size()!=0){
                
                return false;
            }
        } else if(unconnected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(available_head_tail_sites.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<available_head_tail_sites.size(); elem++){
        if(elem == 0){
            if(available_head_tail_sites[elem].size()!=5){
                
                return false;
            }
        } else if(available_head_tail_sites[elem].size()!=1){
            return false;
        }
    }

    if(potential_head_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_head_connection.size(); elem++){
        if(elem==0){
            if(potential_head_connection[elem].size()!=38){
                return false;
            }
        } else if(elem<11){
            if(potential_head_connection[elem].size()!=7) {
                return false;
            }
        } else if(potential_head_connection[elem].size()!=0) {
            return false;
        }
    }

    if(potential_tail_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_tail_connection.size(); elem++){
        if(potential_tail_connection[elem].size()!=0){
            
            return false;
        }
    }

    //Testing tail bind
    
    tOne = make_tuple(polymers[0] ,1);
    tTwo = make_tuple(polymers[19] ,0);
    conOne = new Connection(tOne, tTwo);
    conglomerates[0]->addConnection(conOne);
    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if(head_binding.size()!=18){
        
        return false;
    }
    for(auto & elem : head_binding){
        if(elem.size()!=0){
            
            return false;
        }
    }

    if(tail_binding.size()!=18){
        
        return false;
    }
    for(auto & elem : tail_binding){
        if(elem.size()!=0){
            
            return false;
        }
    }

    if(head_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<head_unbinding.size(); elem++){
        if(elem==0){
            if(head_unbinding[elem].size()!=2){
                
                return false;
            }
        } else if(head_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(tail_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<tail_unbinding.size(); elem++){
        if(elem==0){
            if(tail_unbinding[elem].size()!=1){
                
                return false;
            }
        } else if(tail_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(connected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<connected_neighbours.size(); elem++){
        if(elem==0){
            if(connected_neighbours[elem].size()!=2){
                
                
                return false;
            }
        } else if(connected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(unconnected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<unconnected_neighbours.size(); elem++){
        if(elem==0){
            if(unconnected_neighbours[elem].size()!=0){
                
                return false;
            }
        } else if(unconnected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(available_head_tail_sites.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<available_head_tail_sites.size(); elem++){
        if(elem == 0){
            if(available_head_tail_sites[elem].size()!=3){
                
                return false;
            }
        } else if(available_head_tail_sites[elem].size()!=1){
            return false;
        }
    }

    if(potential_head_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_head_connection.size(); elem++){
        if(elem==0){
            if(potential_head_connection[elem].size()!=21){
                return false;
            }
        } else if(elem<11){
            if(potential_head_connection[elem].size()!=7) {
                return false;
            }
        } else if(potential_head_connection[elem].size()!=0) {
            return false;
        }

    }

    if(potential_tail_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_tail_connection.size(); elem++){
        if(potential_tail_connection[elem].size()!=0){
            
            return false;
        }
    }

    //Testing head unbind
    
    tOne = make_tuple(polymers[0] ,0);
    tTwo = make_tuple(polymers[19] ,1);
    conOne = new Connection(tOne, tTwo);
    conglomerates[0]->removeConnection(conOne);
    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if(head_binding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<head_binding.size(); elem++){
        if(elem==0){
            if(head_binding[elem].size()!=1){
                
                return false;
            }
        } else if(head_binding[elem].size()!=0){
            
            return false;
        }

    }

    if(tail_binding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<tail_binding.size(); elem++){
        if(elem==0){
            if(tail_binding[elem].size()!=0){
                
                return false;
            }
        } else if(tail_binding[elem].size()!=0){
            
            return false;
        }
    }

    if(head_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<head_unbinding.size(); elem++){
        if(elem==0){
            if(head_unbinding[elem].size()!=1){
                
                return false;
            }
        } else if(head_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(tail_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<tail_unbinding.size(); elem++){
        if(elem==0){
            if(tail_unbinding[elem].size()!=1){
                
                return false;
            }
        } else if(tail_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(connected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<connected_neighbours.size(); elem++){
        if(elem==0){
            if(connected_neighbours[elem].size()!=0){
                
                
                return false;
            }
        } else if(connected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(unconnected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<unconnected_neighbours.size(); elem++){
        if(elem==0){
            if(unconnected_neighbours[elem].size()!=0){
                
                return false;
            }
        } else if(unconnected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(available_head_tail_sites.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<available_head_tail_sites.size(); elem++){
        if(elem == 0){
            if(available_head_tail_sites[elem].size()!=5){
                
                return false;
            }
        } else if(available_head_tail_sites[elem].size()!=1){
            return false;
        }
    }

    if(potential_head_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_head_connection.size(); elem++){
        if(elem==0){
            if(potential_head_connection[elem].size()!=38){
                return false;
            }
        } else if(elem<11){
            if(potential_head_connection[elem].size()!=7) {
                return false;
            }
        } else if(potential_head_connection[elem].size()!=0) {
            return false;
        }
    }

    if(potential_tail_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_tail_connection.size(); elem++){
        if(potential_tail_connection[elem].size()!=0){
            
            return false;
        }
    }

    //Testing tail unbind - and conglomerate split
    
    tOne = make_tuple(polymers[0] ,1);
    tTwo = make_tuple(polymers[19] ,0);
    conOne = new Connection(tOne, tTwo);
    Conglomerate * new_cong = conglomerates[0]->removeConnection(conOne)[0];
    system->addConglomerate(new_cong);
    conglomerates.push_back(new_cong);


    system->getEverything();

    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if(head_binding.size()!=19){
        
        return false;
    }
    for(int elem=0; elem<head_binding.size(); elem++){
        if(elem==0){
            if(head_binding[elem].size()!=0){
                
                return false;
            }
        } else if(head_binding[elem].size()!=0){
            
            return false;
        }

    }

    if(tail_binding.size()!=19){
        
        return false;
    }
    for(int elem=0; elem<tail_binding.size(); elem++){
        if(elem==0){
            if(tail_binding[elem].size()!=0){
                
                return false;
            }
        } else if(tail_binding[elem].size()!=0){
            
            return false;
        }
    }

    if(head_unbinding.size()!=19){
        
        return false;
    }
    for(int elem=0; elem<head_unbinding.size(); elem++){
        if(elem==0){
            if(head_unbinding[elem].size()!=1){
                
                return false;
            }
        } else if(head_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(tail_unbinding.size()!=19){
        
        return false;
    }
    for(int elem=0; elem<tail_unbinding.size(); elem++){
        if(elem==0){
            if(tail_unbinding[elem].size()!=0){
                
                return false;
            }
        } else if(tail_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(connected_neighbours.size()!=19){
        
        return false;
    }
    for(int elem=0; elem<connected_neighbours.size(); elem++){
        if(elem==0){
            if(connected_neighbours[elem].size()!=0){
                
                
                return false;
            }
        } else if(connected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(unconnected_neighbours.size()!=19){
        
        return false;
    }
    for(int elem=0; elem<unconnected_neighbours.size(); elem++){
        if(elem==0){
            if(unconnected_neighbours[elem].size()!=0){
                
                return false;
            }
        } else if(unconnected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(available_head_tail_sites.size()!=19){
        
        return false;
    }
    for(int elem=0; elem<available_head_tail_sites.size(); elem++){
        if(elem == 0){
            if(available_head_tail_sites[elem].size()!=5){
                
                return false;
            }
        } else if(elem == available_head_tail_sites.size()-1) {
            if(available_head_tail_sites[elem].size()!=2){
                
                return false;
            }
        } else {
            if(available_head_tail_sites[elem].size()!=1){
                return false;
            }
        }
    }

    if(potential_head_connection.size()!=19){
        
        return false;
    }
    for(int elem=0; elem<potential_head_connection.size(); elem++){
        if(elem==0){
            if(potential_head_connection[elem].size()!=41){
                return false;
            }
        } else if(elem<11){
            if(potential_head_connection[elem].size()!=9) {
                return false;
            }
        } else if(potential_head_connection[elem].size()!=0) {
            return false;
        }
    }

    if(potential_tail_connection.size()!=19){
        
        return false;
    }
    for(int elem=0; elem<potential_tail_connection.size(); elem++){
        if(elem==0){
            if(potential_tail_connection[elem].size()!=4){
                
                return false;
            }
        } else {
            if (potential_tail_connection[elem].size() != 0) {
                
                return false;
            }
        }
    }

    //Testing head bind of two separate conglomerates
    
    tOne = make_tuple(polymers[0] ,1);
    tTwo = make_tuple(polymers[19] ,0);
    conOne = new Connection(tOne, tTwo);
    conglomerates[0]->addConnection(conOne);
    system->eraseConglomerate(system->getConglomerates().size()-1);
    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();
    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if(head_binding.size()!=18){
        
        return false;
    }

    for(int elem=0; elem<head_binding.size(); elem++){
        if(elem==0){
            if(head_binding[elem].size()!=1){
                
                return false;
            }
        } else if(head_binding[elem].size()!=0){
            
            return false;
        }

    }

    if(tail_binding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<tail_binding.size(); elem++){
        if(elem==0){
            if(tail_binding[elem].size()!=0){
                
                return false;
            }
        } else if(tail_binding[elem].size()!=0){
            
            return false;
        }
    }

    if(head_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<head_unbinding.size(); elem++){
        if(elem==0){
            if(head_unbinding[elem].size()!=1){
                
                return false;
            }
        } else if(head_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(tail_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<tail_unbinding.size(); elem++){
        if(elem==0){
            if(tail_unbinding[elem].size()!=1){
                
                return false;
            }
        } else if(tail_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(connected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<connected_neighbours.size(); elem++){
        if(elem==0){
            if(connected_neighbours[elem].size()!=0){
                
                
                return false;
            }
        } else if(connected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(unconnected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<unconnected_neighbours.size(); elem++){
        if(elem==0){
            if(unconnected_neighbours[elem].size()!=0){
                
                return false;
            }
        } else if(unconnected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(available_head_tail_sites.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<available_head_tail_sites.size(); elem++){
        if(elem == 0){
            if(available_head_tail_sites[elem].size()!=5){
                
                return false;
            }
        } else if(available_head_tail_sites[elem].size()!=1){
            return false;
        }
    }

    if(potential_head_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_head_connection.size(); elem++){
        if(elem==0){
            if(potential_head_connection[elem].size()!=38){
                return false;
            }
        } else if(elem<11){
            if(potential_head_connection[elem].size()!=7) {
                return false;
            }
        } else if(potential_head_connection[elem].size()!=0) {
            return false;
        }
    }

    if(potential_tail_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_tail_connection.size(); elem++){
        if(potential_tail_connection[elem].size()!=0){
            
            return false;
        }
    }

    //Testing tail rebind
    
    tOne = make_tuple(polymers[0] ,0);
    tTwo = make_tuple(polymers[19] ,1);
    conOne = new Connection(tOne, tTwo);
    conglomerates[0]->addConnection(conOne);
    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if(head_binding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<head_binding.size(); elem++){
        if(elem==0){
            if(head_binding[elem].size()!=0){
                
                return false;
            }
        } else if(head_binding[elem].size()!=0){
            
            return false;
        }

    }

    if(tail_binding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<tail_binding.size(); elem++){
        if(elem==0){
            if(tail_binding[elem].size()!=0){
                
                return false;
            }
        } else if(tail_binding[elem].size()!=0){
            
            return false;
        }
    }

    if(head_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<head_unbinding.size(); elem++){
        if(elem==0){
            if(head_unbinding[elem].size()!=2){
                
                return false;
            }
        } else if(head_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(tail_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<tail_unbinding.size(); elem++){
        if(elem==0){
            if(tail_unbinding[elem].size()!=1){
                
                return false;
            }
        } else if(tail_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(connected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<connected_neighbours.size(); elem++){
        if(elem==0){
            if(connected_neighbours[elem].size()!=2){
                
                
                return false;
            }
        } else if(connected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(unconnected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<unconnected_neighbours.size(); elem++){
        if(elem==0){
            if(unconnected_neighbours[elem].size()!=0){
                
                return false;
            }
        } else if(unconnected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(available_head_tail_sites.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<available_head_tail_sites.size(); elem++){
        if(elem == 0){
            if(available_head_tail_sites[elem].size()!=3){
                
                return false;
            }
        } else {
            if(available_head_tail_sites[elem].size()!=1){
                
                
                return false;
            }
        }
    }

    if(potential_head_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_head_connection.size(); elem++){
        if(elem==0){
            if(potential_head_connection[elem].size()!=21){
                
                
                return false;
            }
        } else if(elem<11){
            if(potential_head_connection[elem].size()!=7) {
                
                
                return false;
            }
        } else if(potential_head_connection[elem].size()!=0) {
            
            
            return false;
        }
    }

    if(potential_tail_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_tail_connection.size(); elem++){
        if(elem==0){
            if(potential_tail_connection[elem].size()!=0){
                
                return false;
            }
        } else {
            if (potential_tail_connection[elem].size() != 0) {
                
                return false;
            }
        }
    }

    //Testing backbone break
    

    ConnectedNeighbours * conThree = new ConnectedNeighbours(polymers[19], 0, 1);

    Polymer * new_poly = conglomerates[0]->separatePolymers(conThree);
    system->addPolymer(new_poly);
    polymers.push_back(new_poly);

    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if(head_binding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<head_binding.size(); elem++){
        if(elem==0){
            if(head_binding[elem].size()!=0){
                
                return false;
            }
        } else if(head_binding[elem].size()!=0){
            
            return false;
        }

    }

    if(tail_binding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<tail_binding.size(); elem++){
        if(elem==0){
            if(tail_binding[elem].size()!=0){
                
                return false;
            }
        } else if(tail_binding[elem].size()!=0){
            
            return false;
        }
    }

    if(head_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<head_unbinding.size(); elem++){
        if(elem==0){
            if(head_unbinding[elem].size()!=3){
                
                return false;
            }
        } else if(head_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(tail_unbinding.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<tail_unbinding.size(); elem++){
        if(elem==0){
            if(tail_unbinding[elem].size()!=0){
                
                return false;
            }
        } else if(tail_unbinding[elem].size()!=0){
            
            return false;
        }
    }

    if(connected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<connected_neighbours.size(); elem++){
        if(elem==0){
            if(connected_neighbours[elem].size()!=0){
                
                
                return false;
            }
        } else if(connected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(unconnected_neighbours.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<unconnected_neighbours.size(); elem++){
        if(elem==0){
            if(unconnected_neighbours[elem].size()!=1){
                
                return false;
            }
        } else if(unconnected_neighbours[elem].size()!=0){
            
            return false;
        }
    }

    if(available_head_tail_sites.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<available_head_tail_sites.size(); elem++){
        if(elem == 0){
            if(available_head_tail_sites[elem].size()!=3){
                
                return false;
            }
        } else {
            if(available_head_tail_sites[elem].size()!=1){
                
                
                return false;
            }
        }
    }

    if(potential_head_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_head_connection.size(); elem++){
        if(elem==0){
            if(potential_head_connection[elem].size()!=21){
                
                
                return false;
            }
        } else if(elem<11){
            if(potential_head_connection[elem].size()!=7) {
                
                
                return false;
            }
        } else if(potential_head_connection[elem].size()!=0) {
            
            
            return false;
        }
    }

    if(potential_tail_connection.size()!=18){
        
        return false;
    }
    for(int elem=0; elem<potential_tail_connection.size(); elem++){
        if(elem==0){
            if(potential_tail_connection[elem].size()!=0){
                
                return false;
            }
        } else {
            if (potential_tail_connection[elem].size() != 0) {
                
                return false;
            }
        }
    }


    return true;
}

bool Tests::testPerformFunctions() {

    //Testing system initialisation
    int family_count = 2;
    int monomer_type_count = 1;
    vector<vector<int>> number_of_monomers;
    Polymer *initial_template;

    vector<int> type_one;
    type_one.push_back(10);
    type_one.push_back(10);
    number_of_monomers.push_back(type_one);

    initial_template = new Polymer(0, {0, 0, 0, 0, 0, 0});

    System *system = new System(family_count, monomer_type_count, number_of_monomers, initial_template);

    system->getEverything();
    vector<vector<Connection *>> head_binding = system->getHeadBinding();
    vector<vector<Connection *>> tail_binding = system->getTailBinding();
    vector<vector<Connection *>> head_unbinding = system->getHeadUnbinding();
    vector<vector<Connection *>> tail_unbinding = system->getTailUnbinding();
    vector<vector<ConnectedNeighbours *>> connected_neighbours = system->getConnectedNeighbours();
    vector<vector<UnconnectedNeighbours *>> unconnected_neighbours = system->getUnconnectedNeighbours();
    vector<vector<PotentialSite *>> available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    vector<vector<ExternalConnection *>> potential_head_connection = system->getPotentialHeadConnection();
    vector<vector<ExternalConnection *>> potential_tail_connection = system->getPotentialTailConnection();

    if (head_binding.size() != 21) {
        
        return false;
    }
    for (auto &elem: head_binding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (tail_binding.size() != 21) {
        
        return false;
    }
    for (auto &elem: tail_binding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (head_unbinding.size() != 21) {
        
        return false;
    }
    for (auto &elem: head_unbinding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (tail_unbinding.size() != 21) {
        
        return false;
    }
    for (auto &elem: tail_unbinding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (connected_neighbours.size() != 21) {
        
        return false;
    }
    for (auto &elem: connected_neighbours) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (unconnected_neighbours.size() != 21) {
        
        return false;
    }
    for (auto &elem: unconnected_neighbours) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (available_head_tail_sites.size() != 21) {
        
        return false;
    }
    for (int elem = 0; elem < available_head_tail_sites.size(); elem++) {
        if (elem == 0) {
            if (available_head_tail_sites[elem].size() != 6) {
                
                return false;
            }
        } else if (available_head_tail_sites[elem].size() != 1) {
            
            
            return false;
        }
    }

    if (potential_head_connection.size() != 21) {
        
        return false;
    }
    for (int elem = 0; elem < potential_head_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_head_connection[elem].size() != 60) {
                
                
                return false;
            }
        } else if (elem < 11) {
            if (potential_head_connection[elem].size() != 10) {
                
                
                return false;
            }
        } else if (potential_head_connection[elem].size() != 0) {
            
            
            return false;
        }

    }

    if (potential_tail_connection.size() != 21) {
        
        return false;
    }
    for (int elem = 0; elem < potential_tail_connection.size(); elem++) {
        if (potential_tail_connection[elem].size() != 0) {
            
            return false;
        }
    }

    //Testing first monomer-conglomerate bond
    
    vector<Conglomerate *> conglomerates = system->getConglomerates();
    vector<Polymer *> polymers = system->getPolymers();

    tuple<Polymer *, int> tOne = make_tuple(polymers[0], 1);
    tuple<Polymer *, int> tTwo = make_tuple(polymers[20], 0);
    Connection *conOne = new Connection(tOne, tTwo);

    ExternalConnection * conFour = new ExternalConnection(tOne, tTwo, conglomerates[0], conglomerates[20]);

    system->performHeadConnection(conFour);

    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();


    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if (head_binding.size() != 20) {
        
        return false;
    }
    for (auto &elem: head_binding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (tail_binding.size() != 20) {
        
        return false;
    }
    for (auto &elem: tail_binding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (head_unbinding.size() != 20) {
        
        return false;
    }
    for (int elem = 0; elem < head_unbinding.size(); elem++) {
        if (elem == 0) {
            if (head_unbinding[elem].size() != 1) {
                
                return false;
            }
        } else if (head_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (tail_unbinding.size() != 20) {
        
        return false;
    }
    for (auto &elem: tail_unbinding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (connected_neighbours.size() != 20) {
        
        return false;
    }
    for (auto &elem: connected_neighbours) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (unconnected_neighbours.size() != 20) {
        
        return false;
    }
    for (auto &elem: unconnected_neighbours) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (available_head_tail_sites.size() != 20) {
        
        return false;
    }
    for (int elem = 0; elem < available_head_tail_sites.size(); elem++) {
        if (elem == 0) {
            if (available_head_tail_sites[elem].size() != 5) {
                
                return false;
            }
        } else if (available_head_tail_sites[elem].size() != 1) {
            
            
            return false;
        }
    }

    if (potential_head_connection.size() != 20) {
        
        return false;
    }
    for (int elem = 0; elem < potential_head_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_head_connection[elem].size() != 45) {
                
                
                return false;
            }
        } else if (elem < 11) {
            if (potential_head_connection[elem].size() != 9) {
                
                
                return false;
            }
        } else if (potential_head_connection[elem].size() != 0) {
            
            
            return false;
        }

    }

    if (potential_tail_connection.size() != 20) {
        
        return false;
    }
    for (int elem = 0; elem < potential_tail_connection.size(); elem++) {
        if (potential_tail_connection[elem].size() != 0) {
            
            return false;
        }
    }

    //Testing second monomer-conglomerate bond
    tOne = make_tuple(polymers[0], 0);
    tTwo = make_tuple(polymers[19], 0);

    conFour = new ExternalConnection(tOne, tTwo, conglomerates[0], conglomerates[19]);

    system->performHeadConnection(conFour);

    system->getEverything();

    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if (head_binding.size() != 19) {
        
        return false;
    }
    for (auto &elem: head_binding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (tail_binding.size() != 19) {
        
        return false;
    }
    for (auto &elem: tail_binding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (head_unbinding.size() != 19) {
        
        return false;
    }
    for (int elem = 0; elem < head_unbinding.size(); elem++) {
        if (elem == 0) {
            if (head_unbinding[elem].size() != 2) {
                
                return false;
            }
        } else if (head_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (tail_unbinding.size() != 19) {
        
        return false;
    }
    for (auto &elem: tail_unbinding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (connected_neighbours.size() != 19) {
        
        return false;
    }
    for (auto &elem: connected_neighbours) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (unconnected_neighbours.size() != 19) {
        
        return false;
    }
    for (int elem = 0; elem < unconnected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (unconnected_neighbours[elem].size() != 1) {
                
                return false;
            }
        } else if (unconnected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (available_head_tail_sites.size() != 19) {
        
        return false;
    }
    for (int elem = 0; elem < available_head_tail_sites.size(); elem++) {
        if (elem == 0) {
            if (available_head_tail_sites[elem].size() != 4) {
                
                return false;
            }
        } else if (available_head_tail_sites[elem].size() != 1) {
            
            
            return false;
        }
    }

    if (potential_head_connection.size() != 19) {
        
        return false;
    }
    for (int elem = 0; elem < potential_head_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_head_connection[elem].size() != 32) {
                
                
                return false;
            }
        } else if (elem < 11) {
            if (potential_head_connection[elem].size() != 8) {
                
                
                return false;
            }
        } else if (potential_head_connection[elem].size() != 0) {
            
            
            return false;
        }

    }

    if (potential_tail_connection.size() != 19) {
        
        return false;
    }
    for (int elem = 0; elem < potential_tail_connection.size(); elem++) {
        if (potential_tail_connection[elem].size() != 0) {
            
            return false;
        }
    }

    //Testing third monomer-conglomerate bond
    
    tOne = make_tuple(polymers[0], 3);
    tTwo = make_tuple(polymers[18], 0);

    conFour = new ExternalConnection(tOne, tTwo, conglomerates[0], conglomerates[18]);

    system->performHeadConnection(conFour);

    system->getEverything();

    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if (head_binding.size() != 18) {
        
        return false;
    }
    for (auto &elem: head_binding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (tail_binding.size() != 18) {
        
        return false;
    }
    for (auto &elem: tail_binding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (head_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < head_unbinding.size(); elem++) {
        if (elem == 0) {
            if (head_unbinding[elem].size() != 3) {
                
                return false;
            }
        } else if (head_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (tail_unbinding.size() != 18) {
        
        return false;
    }
    for (auto &elem: tail_unbinding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (connected_neighbours.size() != 18) {
        
        return false;
    }
    for (auto &elem: connected_neighbours) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (unconnected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < unconnected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (unconnected_neighbours[elem].size() != 1) {
                
                return false;
            }
        } else if (unconnected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (available_head_tail_sites.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < available_head_tail_sites.size(); elem++) {
        if (elem == 0) {
            if (available_head_tail_sites[elem].size() != 3) {
                
                return false;
            }
        } else if (available_head_tail_sites[elem].size() != 1) {
            
            
            return false;
        }
    }

    if (potential_head_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_head_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_head_connection[elem].size() != 21) {
                
                
                return false;
            }
        } else if (elem < 11) {
            if (potential_head_connection[elem].size() != 7) {
                
                
                return false;
            }
        } else if (potential_head_connection[elem].size() != 0) {
            
            
            return false;
        }

    }

    if (potential_tail_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_tail_connection.size(); elem++) {
        if (potential_tail_connection[elem].size() != 0) {
            
            return false;
        }
    }

    //Testing backbone bonding
    
    UnconnectedNeighbours *conTwo = new UnconnectedNeighbours(polymers[20], polymers[19]);

    system->performNeighboursBind(conglomerates[0], conTwo);

    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if (head_binding.size() != 18) {
        
        return false;
    }
    for (auto &elem: head_binding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (tail_binding.size() != 18) {
        
        return false;
    }
    for (auto &elem: tail_binding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (head_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < head_unbinding.size(); elem++) {
        if (elem == 0) {
            if (head_unbinding[elem].size() != 2) {
                
                return false;
            }
        } else if (head_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (tail_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < tail_unbinding.size(); elem++) {
        if (elem == 0) {
            if (tail_unbinding[elem].size() != 1) {
                
                return false;
            }
        } else if (tail_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (connected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < connected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (connected_neighbours[elem].size() != 2) {
                
                
                return false;
            }
        } else if (connected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (unconnected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < unconnected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (unconnected_neighbours[elem].size() != 0) {
                
                return false;
            }
        } else if (unconnected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (available_head_tail_sites.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < available_head_tail_sites.size(); elem++) {
        if (elem == 0) {
            if (available_head_tail_sites[elem].size() != 3) {
                
                return false;
            }
        } else if (available_head_tail_sites[elem].size() != 1) {
            
            
            return false;
        }
    }

    if (potential_head_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_head_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_head_connection[elem].size() != 21) {
                
                
                return false;
            }
        } else if (elem < 11) {
            if (potential_head_connection[elem].size() != 7) {
                
                
                return false;
            }
        } else if (potential_head_connection[elem].size() != 0) {
            
            
            return false;
        }

    }

    if (potential_tail_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_tail_connection.size(); elem++) {
        if (potential_tail_connection[elem].size() != 0) {
            
            return false;
        }
    }

    //Testing tail unbind
    
    tOne = make_tuple(polymers[0], 1);
    tTwo = make_tuple(polymers[19], 0);
    conOne = new Connection(tOne, tTwo);

    system->performTailUnbinding(conglomerates[0], conOne);
    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if (head_binding.size() != 18) {
        return false;
    }
    for (auto &elem: head_binding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (tail_binding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < tail_binding.size(); elem++) {
        if (elem == 0) {
            if (tail_binding[elem].size() != 1) {
                
                return false;
            }
        } else if (tail_binding[elem].size() != 0) {
            
            return false;
        }
    }

    if (head_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < head_unbinding.size(); elem++) {
        if (elem == 0) {
            if (head_unbinding[elem].size() != 2) {
                
                return false;
            }
        } else if (head_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (tail_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < tail_unbinding.size(); elem++) {
        if (elem == 0) {
            if (tail_unbinding[elem].size() != 0) {
                
                return false;
            }
        } else if (tail_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (connected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < connected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (connected_neighbours[elem].size() != 0) {
                
                
                return false;
            }
        } else if (connected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (unconnected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < unconnected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (unconnected_neighbours[elem].size() != 0) {
                
                return false;
            }
        } else if (unconnected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (available_head_tail_sites.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < available_head_tail_sites.size(); elem++) {
        if (elem == 0) {
            if (available_head_tail_sites[elem].size() != 5) {
                
                return false;
            }
        } else if (available_head_tail_sites[elem].size() != 1) {
            
            
            return false;
        }
    }

    if (potential_head_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_head_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_head_connection[elem].size() != 38) {
                
                
                return false;
            }
        } else if (elem < 11) {
            if (potential_head_connection[elem].size() != 7) {
                
                
                return false;
            }
        } else if (potential_head_connection[elem].size() != 0) {
            
            
            return false;
        }
    }

    if (potential_tail_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_tail_connection.size(); elem++) {
        if (potential_tail_connection[elem].size() != 0) {
            
            return false;
        }
    }

    //Testing tail bind
    
    tOne = make_tuple(polymers[0], 1);
    tTwo = make_tuple(polymers[19], 0);
    conOne = new Connection(tOne, tTwo);

    system->performTailBinding(conglomerates[0], conOne);

    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if (head_binding.size() != 18) {
        
        return false;
    }
    for (auto &elem: head_binding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (tail_binding.size() != 18) {
        
        return false;
    }
    for (auto &elem: tail_binding) {
        if (elem.size() != 0) {
            
            return false;
        }
    }

    if (head_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < head_unbinding.size(); elem++) {
        if (elem == 0) {
            if (head_unbinding[elem].size() != 2) {
                
                return false;
            }
        } else if (head_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (tail_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < tail_unbinding.size(); elem++) {
        if (elem == 0) {
            if (tail_unbinding[elem].size() != 1) {
                
                return false;
            }
        } else if (tail_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (connected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < connected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (connected_neighbours[elem].size() != 2) {
                
                
                return false;
            }
        } else if (connected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (unconnected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < unconnected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (unconnected_neighbours[elem].size() != 0) {
                
                return false;
            }
        } else if (unconnected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (available_head_tail_sites.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < available_head_tail_sites.size(); elem++) {
        if (elem == 0) {
            if (available_head_tail_sites[elem].size() != 3) {
                
                return false;
            }
        } else if (available_head_tail_sites[elem].size() != 1) {
            
            
            return false;
        }
    }

    if (potential_head_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_head_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_head_connection[elem].size() != 21) {
                
                
                return false;
            }
        } else if (elem < 11) {
            if (potential_head_connection[elem].size() != 7) {
                
                
                return false;
            }
        } else if (potential_head_connection[elem].size() != 0) {
            
            
            return false;
        }

    }

    if (potential_tail_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_tail_connection.size(); elem++) {
        if (potential_tail_connection[elem].size() != 0) {
            
            return false;
        }
    }

    //Testing head unbind
    
    tOne = make_tuple(polymers[0], 0);
    tTwo = make_tuple(polymers[19], 1);
    conOne = new Connection(tOne, tTwo);

    system->performHeadUnbinding(conglomerates[0], conOne);

    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if (head_binding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < head_binding.size(); elem++) {
        if (elem == 0) {
            if (head_binding[elem].size() != 1) {
                
                return false;
            }
        } else if (head_binding[elem].size() != 0) {
            
            return false;
        }

    }

    if (tail_binding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < tail_binding.size(); elem++) {
        if (elem == 0) {
            if (tail_binding[elem].size() != 0) {
                
                return false;
            }
        } else if (tail_binding[elem].size() != 0) {
            
            return false;
        }
    }

    if (head_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < head_unbinding.size(); elem++) {
        if (elem == 0) {
            if (head_unbinding[elem].size() != 1) {
                
                return false;
            }
        } else if (head_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (tail_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < tail_unbinding.size(); elem++) {
        if (elem == 0) {
            if (tail_unbinding[elem].size() != 1) {
                
                return false;
            }
        } else if (tail_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (connected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < connected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (connected_neighbours[elem].size() != 0) {
                
                
                return false;
            }
        } else if (connected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (unconnected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < unconnected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (unconnected_neighbours[elem].size() != 0) {
                
                return false;
            }
        } else if (unconnected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (available_head_tail_sites.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < available_head_tail_sites.size(); elem++) {
        if (elem == 0) {
            if (available_head_tail_sites[elem].size() != 5) {
                
                return false;
            }
        } else if (available_head_tail_sites[elem].size() != 1) {
            
            
            return false;
        }
    }

    if (potential_head_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_head_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_head_connection[elem].size() != 38) {
                
                
                return false;
            }
        } else if (elem < 11) {
            if (potential_head_connection[elem].size() != 7) {
                
                
                return false;
            }
        } else if (potential_head_connection[elem].size() != 0) {
            
            
            return false;
        }
    }

    if (potential_tail_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_tail_connection.size(); elem++) {
        if (potential_tail_connection[elem].size() != 0) {
            
            return false;
        }
    }

    //Testing tail unbind - and conglomerate split
    
    tOne = make_tuple(polymers[0], 1);
    tTwo = make_tuple(polymers[19], 0);
    conOne = new Connection(tOne, tTwo);

    system->performTailUnbinding(conglomerates[0], conOne);

    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if (head_binding.size() != 19) {
        
        return false;
    }
    for (int elem = 0; elem < head_binding.size(); elem++) {
        if (elem == 0) {
            if (head_binding[elem].size() != 0) {
                
                return false;
            }
        } else if (head_binding[elem].size() != 0) {
            
            return false;
        }

    }

    if (tail_binding.size() != 19) {
        
        return false;
    }
    for (int elem = 0; elem < tail_binding.size(); elem++) {
        if (elem == 0) {
            if (tail_binding[elem].size() != 0) {
                
                return false;
            }
        } else if (tail_binding[elem].size() != 0) {
            
            return false;
        }
    }

    if (head_unbinding.size() != 19) {
        
        return false;
    }
    for (int elem = 0; elem < head_unbinding.size(); elem++) {
        if (elem == 0) {
            if (head_unbinding[elem].size() != 1) {
                
                return false;
            }
        } else if (head_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (tail_unbinding.size() != 19) {
        
        return false;
    }
    for (int elem = 0; elem < tail_unbinding.size(); elem++) {
        if (elem == 0) {
            if (tail_unbinding[elem].size() != 0) {
                
                return false;
            }
        } else if (tail_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (connected_neighbours.size() != 19) {
        
        return false;
    }
    for (int elem = 0; elem < connected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (connected_neighbours[elem].size() != 0) {
                
                
                return false;
            }
        } else if (connected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (unconnected_neighbours.size() != 19) {
        
        return false;
    }
    for (int elem = 0; elem < unconnected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (unconnected_neighbours[elem].size() != 0) {
                
                return false;
            }
        } else if (unconnected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (available_head_tail_sites.size() != 19) {
        
        return false;
    }
    for (int elem = 0; elem < available_head_tail_sites.size(); elem++) {
        if (elem == 0) {
            if (available_head_tail_sites[elem].size() != 5) {
                
                return false;
            }
        } else if (elem == available_head_tail_sites.size() - 1) {
            if (available_head_tail_sites[elem].size() != 2) {
                
                return false;
            }
        } else {
            if (available_head_tail_sites[elem].size() != 1) {
                
                
                return false;
            }
        }
    }

    if (potential_head_connection.size() != 19) {
        
        return false;
    }
    for (int elem = 0; elem < potential_head_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_head_connection[elem].size() != 41) {
                
                
                return false;
            }
        } else if (elem < 11) {
            if (potential_head_connection[elem].size() != 9) {
                
                
                return false;
            }
        } else if (potential_head_connection[elem].size() != 0) {
            
            
            return false;
        }
    }

    if (potential_tail_connection.size() != 19) {
        
        return false;
    }
    for (int elem = 0; elem < potential_tail_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_tail_connection[elem].size() != 4) {
                
                return false;
            }
        } else {
            if (potential_tail_connection[elem].size() != 0) {
                
                return false;
            }
        }
    }

    //Testing tail bind of two separate conglomerates
    
    tOne = make_tuple(polymers[0], 1);
    tTwo = make_tuple(polymers[19], 0);

    conFour = new ExternalConnection(tOne, tTwo, conglomerates[0], conglomerates[conglomerates.size()-1]);
    system->performTailConnection(conFour);

    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if (head_binding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < head_binding.size(); elem++) {
        if (elem == 0) {
            if (head_binding[elem].size() != 1) {
                return false;
            }
        } else if (head_binding[elem].size() != 0) {
            
            return false;
        }

    }

    if (tail_binding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < tail_binding.size(); elem++) {
        if (elem == 0) {
            if (tail_binding[elem].size() != 0) {
                
                return false;
            }
        } else if (tail_binding[elem].size() != 0) {
            
            return false;
        }
    }

    if (head_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < head_unbinding.size(); elem++) {
        if (elem == 0) {
            if (head_unbinding[elem].size() != 1) {
                
                return false;
            }
        } else if (head_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (tail_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < tail_unbinding.size(); elem++) {
        if (elem == 0) {
            if (tail_unbinding[elem].size() != 1) {
                
                return false;
            }
        } else if (tail_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (connected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < connected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (connected_neighbours[elem].size() != 0) {
                
                
                return false;
            }
        } else if (connected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (unconnected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < unconnected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (unconnected_neighbours[elem].size() != 0) {
                
                return false;
            }
        } else if (unconnected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (available_head_tail_sites.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < available_head_tail_sites.size(); elem++) {
        if (elem == 0) {
            if (available_head_tail_sites[elem].size() != 5) {
                
                return false;
            }
        } else if (available_head_tail_sites[elem].size() != 1) {
            
            
            return false;
        }
    }

    if (potential_head_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_head_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_head_connection[elem].size() != 38) {
                
                
                return false;
            }
        } else if (elem < 11) {
            if (potential_head_connection[elem].size() != 7) {
                
                
                return false;
            }
        } else if (potential_head_connection[elem].size() != 0) {
            
            
            return false;
        }
    }

    if (potential_tail_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_tail_connection.size(); elem++) {
        if (potential_tail_connection[elem].size() != 0) {
            
            return false;
        }
    }

    //Testing head rebind
    
    tOne = make_tuple(polymers[0], 0);
    tTwo = make_tuple(polymers[19], 1);
    conOne = new Connection(tOne, tTwo);

    system->performHeadBinding(conglomerates[0], conOne);

    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if (head_binding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < head_binding.size(); elem++) {
        if (elem == 0) {
            if (head_binding[elem].size() != 0) {
                
                return false;
            }
        } else if (head_binding[elem].size() != 0) {
            
            return false;
        }

    }

    if (tail_binding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < tail_binding.size(); elem++) {
        if (elem == 0) {
            if (tail_binding[elem].size() != 0) {
                
                return false;
            }
        } else if (tail_binding[elem].size() != 0) {
            
            return false;
        }
    }

    if (head_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < head_unbinding.size(); elem++) {
        if (elem == 0) {
            if (head_unbinding[elem].size() != 2) {
                
                return false;
            }
        } else if (head_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (tail_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < tail_unbinding.size(); elem++) {
        if (elem == 0) {
            if (tail_unbinding[elem].size() != 1) {
                
                return false;
            }
        } else if (tail_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (connected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < connected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (connected_neighbours[elem].size() != 2) {
                
                
                return false;
            }
        } else if (connected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (unconnected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < unconnected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (unconnected_neighbours[elem].size() != 0) {
                
                return false;
            }
        } else if (unconnected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (available_head_tail_sites.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < available_head_tail_sites.size(); elem++) {
        if (elem == 0) {
            if (available_head_tail_sites[elem].size() != 3) {
                
                return false;
            }
        } else {
            if (available_head_tail_sites[elem].size() != 1) {
                
                
                return false;
            }
        }
    }

    if (potential_head_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_head_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_head_connection[elem].size() != 21) {
                
                
                return false;
            }
        } else if (elem < 11) {
            if (potential_head_connection[elem].size() != 7) {
                
                
                return false;
            }
        } else if (potential_head_connection[elem].size() != 0) {
            
            
            return false;
        }
    }

    if (potential_tail_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_tail_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_tail_connection[elem].size() != 0) {
                
                return false;
            }
        } else {
            if (potential_tail_connection[elem].size() != 0) {
                
                return false;
            }
        }
    }

    //Testing backbone break
    

    ConnectedNeighbours *conThree = new ConnectedNeighbours(polymers[19], 0, 1);

    system->performNeighboursUnbind(conglomerates[0], conThree);

    system->getEverything();
    conglomerates = system->getConglomerates();
    polymers = system->getPolymers();

    head_binding = system->getHeadBinding();
    tail_binding = system->getTailBinding();
    head_unbinding = system->getHeadUnbinding();
    tail_unbinding = system->getTailUnbinding();
    connected_neighbours = system->getConnectedNeighbours();
    unconnected_neighbours = system->getUnconnectedNeighbours();
    available_head_tail_sites = system->getAvailableHeadTailSites();
    system->updatePotentialHeadTailSites();
    potential_head_connection = system->getPotentialHeadConnection();
    potential_tail_connection = system->getPotentialTailConnection();

    if (head_binding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < head_binding.size(); elem++) {
        if (elem == 0) {
            if (head_binding[elem].size() != 0) {
                
                return false;
            }
        } else if (head_binding[elem].size() != 0) {
            
            return false;
        }

    }

    if (tail_binding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < tail_binding.size(); elem++) {
        if (elem == 0) {
            if (tail_binding[elem].size() != 0) {
                
                return false;
            }
        } else if (tail_binding[elem].size() != 0) {
            
            return false;
        }
    }

    if (head_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < head_unbinding.size(); elem++) {
        if (elem == 0) {
            if (head_unbinding[elem].size() != 3) {
                
                return false;
            }
        } else if (head_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (tail_unbinding.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < tail_unbinding.size(); elem++) {
        if (elem == 0) {
            if (tail_unbinding[elem].size() != 0) {
                
                return false;
            }
        } else if (tail_unbinding[elem].size() != 0) {
            
            return false;
        }
    }

    if (connected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < connected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (connected_neighbours[elem].size() != 0) {
                
                
                return false;
            }
        } else if (connected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (unconnected_neighbours.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < unconnected_neighbours.size(); elem++) {
        if (elem == 0) {
            if (unconnected_neighbours[elem].size() != 1) {
                
                return false;
            }
        } else if (unconnected_neighbours[elem].size() != 0) {
            
            return false;
        }
    }

    if (available_head_tail_sites.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < available_head_tail_sites.size(); elem++) {
        if (elem == 0) {
            if (available_head_tail_sites[elem].size() != 3) {
                
                return false;
            }
        } else {
            if (available_head_tail_sites[elem].size() != 1) {
                
                
                return false;
            }
        }
    }

    if (potential_head_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_head_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_head_connection[elem].size() != 21) {
                
                
                return false;
            }
        } else if (elem < 11) {
            if (potential_head_connection[elem].size() != 7) {
                
                
                return false;
            }
        } else if (potential_head_connection[elem].size() != 0) {
            
            
            return false;
        }
    }

    if (potential_tail_connection.size() != 18) {
        
        return false;
    }
    for (int elem = 0; elem < potential_tail_connection.size(); elem++) {
        if (elem == 0) {
            if (potential_tail_connection[elem].size() != 0) {
                
                return false;
            }
        } else {
            if (potential_tail_connection[elem].size() != 0) {
                
                return false;
            }
        }
    }




    return true;
}

