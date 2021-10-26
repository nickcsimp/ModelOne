//
// Created by Nicholas Simpson on 20/10/2021.
//

#include "System.h"
using namespace std;

System::System(int monomerCount){
    monomers=monomerCount;
    dimers=0;
}

int System::getMonomers(){
    return monomers;
}

int System::getDimers(){
    return dimers;
}

void System::changeMonomerCount(int increase){
    if(monomers+increase>=0) {
        monomers = monomers + increase;
    } else {
        throw invalid_argument("Monomer count can't be below 0.");
    }
}

void System::changeDimerCount(int increase){
    if(dimers+increase>=0) {
        dimers = dimers + increase;
    } else {
        throw invalid_argument("Dimer count can't be below 0.");
    }
}

vector<Polymer *> System::getPolymers(){
    return polymers;
}

vector<Conglomerate *> System::getConglomerates(){
    return conglomerates;
}

void System::addPolymer(Polymer * p){
    polymers.push_back(p);
    //p->setIndex(polymers.size()-1);
    changeMonomerCount(-p->getLength());
}

void System::popPolymer(){
    polymers.pop_back();
}

void System::addConglomerate(Conglomerate * c){
    conglomerates.push_back(c);
    //c->setIndex(conglomerates.size()-1);
}

void System::joinPolymers(int ind_one, int ind_two){
    Polymer * point = polymers[ind_two];
    polymers[ind_one]->addPolymer(point, three_prime);
    polymers.erase(polymers.begin()+ind_two);
}

void System::print(){
    for(auto & elem : conglomerates){
        cout << "Conglomerate " << elem->getIndex() << ':' << endl;
        for(auto & eleme : elem->getConnections()){
            cout << "   Polymer one: " << eleme->getPolymers()[0]->getIndex() << endl;
            cout << "   Index one: " << eleme->getIndexes()[0]<< endl;
            cout << "   Polymer two: " << eleme->getPolymers()[1]->getIndex() << endl;
            cout << "   Index two: " << eleme->getIndexes()[1]<< endl;
        }
    }
    for(auto & elem : polymers){
        cout << "Polymer " << elem->getIndex() << ':' << endl;
        cout << "   Sequence: ";
        for(auto & eleme : elem->getSequence()){
            cout << eleme;
        }
        cout << endl;
    }
}

