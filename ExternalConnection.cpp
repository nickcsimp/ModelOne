//
// Created by Nicholas Simpson on 15/11/2021.
//

#include "ExternalConnection.h"

ExternalConnection::ExternalConnection(tuple<Polymer *, int> tone, tuple<Polymer *, int> ttwo, Conglomerate *cone,
                                       Conglomerate *ctwo) {
    one = tone;
    two = ttwo;
    cong_one = cone;
    cong_two = ctwo;
}

vector<Polymer *> ExternalConnection::getPolymers(){
    vector<Polymer *> output;
    output.push_back(get<0>(one));
    output.push_back(get<0>(two));
    return output;
}
vector<int> ExternalConnection::getIndexes(){
    vector<int> output;
    output.push_back(get<1>(one));
    output.push_back(get<1>(two));
    return output;
}
vector<Conglomerate *> ExternalConnection::getConglomerates(){
    vector<Conglomerate *> output;
    output.push_back(cong_one);
    output.push_back(cong_two);
    return output;
}
