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

void Connection::changePolymer(int which_polymer, Polymer * new_polymer){
    if(which_polymer==0) {
        if(*get<0>(two)==*new_polymer){
            cout << "ERROR: Connections cannot be made on the same polymer" << endl;
            return;
        }
        one = make_tuple(new_polymer,get<1>(one));
    } else if (which_polymer==1) {
        if(*get<0>(one)==*new_polymer){
            cout << "ERROR: Connections cannot be made on the same polymer" << endl;
            return;
        }
        two = make_tuple(new_polymer, get<1>(two));
    }
}

void Connection::setIndex(int which_polymer, int new_index){
    if(new_index<0){
        cout << "ERROR: Connection cannot be made with index less than 0" << endl;
        return;
    }
    if(which_polymer==0) {
        if(new_index>=get<0>(one)->getLength()){
            cout << "ERROR: Connection cannot be made with index greater than polymer length" << endl;
            return;
        }
        one = make_tuple(get<0>(one), new_index);
    } else if (which_polymer==1) {
        if(new_index>=get<0>(two)->getLength()){
            cout << "ERROR: Connection cannot be made with index greater than polymer length" << endl;
            return;
        }
        two = make_tuple(get<0>(two), new_index);
    }
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
