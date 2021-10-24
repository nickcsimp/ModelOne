//
// Created by Nicholas Simpson on 20/10/2021.
//

#include "Connection.h"

vector<Polymer *> Connection::getPolymers(){
    vector<Polymer *> output;
    output.push_back(get<0> (one));
    output.push_back(get<0> (two));
    return output;
}

vector<int> Connection::getIndexes(){
    vector<int> output;
    output.push_back(get<1> (one));
    output.push_back(get<1> (two));
    return output;
}

bool Connection::operator==(Connection c){
    vector<Polymer *> p = c.getPolymers();
    vector<int> i = c.getIndexes();
    if(p[0] == get<0>(one)){
        if(p[1] == get<0>(two)){
            if(i[0] == get<1>(one)){
                if(i[1] == get<1>(two)){
                    return true;
                }
            }
        }
    }
    if(p[0] == get<0>(two)){
        if(p[1] == get<0>(one)){
            if(i[0] == get<1>(two)){
                if(i[1] == get<1>(one)){
                    return true;
                }
            }
        }
    }
    return false;
}

void Connection::remove(){
    //TODO this
}
