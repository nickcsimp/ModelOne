//
// Created by Nicholas Simpson on 24/10/2021.
//

#include "Tests.h"
#include <stdlib.h>
#include <ctime>

Tests::Tests(){
    srand(time(NULL));
}

/*bool Tests::runTests() {
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

    if(!testConnectionInitialisation()){
        cout << "Failed: testConnectionInitialisation()";
        return false;
    }

    if(!testConnectionEquals()){
        cout << "Failed: testConnectionEquals()";
        return false;
    }


    if(!testConglomerateInitialisation()){
        cout << "Failed: testConglomerateInitialisation()";
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
}*/

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

bool Tests::testConglomerateInitialisation(){
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
    for(int i=0; i<10; i++){
        connections.push_back(new Connection(sites[i], sites[i+10]));
    }
    Conglomerate * conglomerate = new Conglomerate(connections);
    conglomerate->setIndex(10);

    if(connections!=conglomerate->getConnections() || conglomerate->getIndex()!=10){
        return false;
    }

    return true;
}

bool Tests::testUpdatePolymersInConglomerate(){
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
    conglomerate->updatePolymersInConglomerate();
    vector<Polymer *> polymers_in_conglomerate = conglomerate->getPolymersInConglomerate();
    vector<int> pic_indexes;

    for(auto & i : polymers_in_conglomerate){
        pic_indexes.push_back(i->getIndex());
    }

    for(int i=0; i<pic_indexes.size(); i++){
        for(int j=1; j<pic_indexes.size(); j++){
            if(pic_indexes[j-1]>pic_indexes[j]){
                int temp = pic_indexes[j-1];
                pic_indexes[j-1] = pic_indexes[j];
                pic_indexes[j] = temp;
            }
        }
    }

    for(int i=0; i<pic_indexes.size(); i++){
        if(pic_indexes[i]!=i){
            return false;
        }
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

bool Tests::testUpdateTailUnbindingSites(){
    vector<Polymer *> polymers;
    vector<Connection *> connections;
    vector<tuple<Polymer *, int>> sites;
    for (int i = 0; i < 6; i++) {
        vector<int> s;
        for (int j = 0; j < 10; j++) {
            s.push_back(rand() % 10);
        }
        Polymer *p = new Polymer(s);
        p->setIndex(i);
        polymers.push_back(p);
        s.clear();
        if (i == 0) {
            for (int j = 0; j < 5; j++) {
                sites.push_back(make_tuple(p, 2*j));
            }
        } else {
            sites.push_back(make_tuple(p, 0));
        }
    }

    for (int i = 0; i < 5; i++) {
        connections.push_back(new Connection(sites[i], sites[i + 5]));
    }

    Conglomerate *conglomerate = new Conglomerate(connections);
    conglomerate->setIndex(10);

    conglomerate->updateTailUnbindingSites();
    int unbinding_sites = conglomerate->getTailUnbindingSites();
    vector<Connection *> unbinding_connections = conglomerate->getTailUnbindingConnections();

    int correct_unbinding_sites = 5;
    vector<Connection *> correct_unbinding_connections = connections;

    if(unbinding_sites!=correct_unbinding_sites){
        return false;
    }

    int count = 0;
    for(auto & elem : correct_unbinding_connections){
        for(auto & element : unbinding_connections){
            if(*elem==*element){
                count++;
            }
        }
    }

    if(count!=correct_unbinding_connections.size()){
        return false;
    }

    return true;
}

bool Tests::testUpdateTailBindingSites(){
    vector<Polymer *> polymers;
    vector<Connection *> connections;
    vector<tuple<Polymer *, int>> sites;
    for (int i = 0; i < 6; i++) {
        vector<int> s;
        for (int j = 0; j < 10; j++) {
            s.push_back(rand() % 10);
        }
        Polymer *p = new Polymer(s);
        p->setIndex(i);
        polymers.push_back(p);
        s.clear();
        if (i == 0) {
            for (int j = 0; j < 5; j++) {
                sites.push_back(make_tuple(p, 2*j));
            }
        } else {
            sites.push_back(make_tuple(p, 0));
        }
    }

    for (int i = 0; i < 5; i++) {
        connections.push_back(new Connection(sites[i], sites[i + 5]));
    }

    Conglomerate *conglomerate = new Conglomerate(connections);
    conglomerate->setIndex(10);

    conglomerate->updateTailBindingSites();
    int binding_sites = conglomerate->getTailBindingSites();
    vector<Connection *> binding_connections = conglomerate->getTailBindingConnections();

    int correct_binding_sites = 4;
    vector<Connection *> correct_binding_connections;

    for(int i=0; i<4; i++){
        tuple<Polymer *, int> one = make_tuple(polymers[0], (2*i)+1);
        tuple<Polymer *, int> two = make_tuple(polymers[i+2], 1);
        correct_binding_connections.push_back(new Connection(one, two));
    }

    if(binding_sites!=correct_binding_sites){
        return false;
    }

    int count = 0;
    for(auto & elem : correct_binding_connections){
        for(auto & element : binding_connections){
            if(*elem==*element){
                count++;
            }
        }
    }

    if(count!=correct_binding_connections.size()){
        return false;
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

