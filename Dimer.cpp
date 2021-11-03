//
// Created by Nicholas Simpson on 03/11/2021.
//

#include "Dimer.h"
Dimer::Dimer(int monomer_type, int famOne, int famTwo){
    type = monomer_type;
    familyOne = famOne;
    familyTwo = famTwo;
}
int Dimer::getType(){
    return type;
}
vector<int> Dimer::getFamilies(){
    vector<int> output;
    output.push_back(familyOne);
    output.push_back(familyTwo);
    return output;
}

bool Dimer::operator==(Dimer d){
    if(type == d.getType()){
        vector<int> fams = d.getFamilies();
        if(fams[0]==familyOne){
            if(fams[1]==familyTwo){
                return true;
            }
        }
        if(fams[1]==familyOne) {
            if (fams[0] == familyTwo) {
                return true;
            }
        }
    }
    return false;
}