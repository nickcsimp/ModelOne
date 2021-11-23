//
// Created by Nicholas Simpson on 20/10/2021.
//

#include <iostream>
#include <vector>
#include <random>

#include "Polymer.h"
#include "Conglomerate.h"
#include "PotentialSite.h"
#include "ExternalConnection.h"


using namespace std;

#define template_tail_unbind_rate 1
#define template_tail_bind_rate 1
#define template_head_unbind_rate 1
#define template_head_bind_rate 1
#define backbone_bind_rate 1
#define backbone_unbind_rate 1

#ifndef TESTTWO_SYSTEM_H
#define TESTTWO_SYSTEM_H

class System {
private:

    vector<vector<Connection *>> head_binding;
    vector<vector<Connection *>> tail_binding;
    vector<vector<Connection *>> head_unbinding;
    vector<vector<Connection *>> tail_unbinding;
    vector<vector<ConnectedNeighbours *>> connected_neighbours;
    vector<vector<UnconnectedNeighbours *>> unconnected_neighbours;
    vector<vector<ExternalConnection *>> potential_head_connections;
    vector<vector<ExternalConnection *>> potential_tail_connections;

    int number_head_binding;
    int number_tail_binding;
    int number_head_unbinding;
    int number_tail_unbinding;
    int number_connected_neighbours;
    int number_unconnected_neighbours;
    int number_potential_head_connections;
    int number_potential_tail_connections;

    vector<vector<PotentialSite *>> available_head_tail_sites;

    int polymer_index;
    int conglomerate_index;

    int number_of_families;
    int number_of_monomer_types;
    vector<vector<int>> number_of_monomers; //type, family

    vector<Polymer *> polymers;
    vector<Conglomerate *> conglomerates;

public:

    System(int family_count, int monomer_type_count, vector<vector<int>> number_of_monomers, Polymer * initial_template);

    void eraseConglomerate(int index){conglomerates.erase(conglomerates.begin()+index);}
    void erasePolymer(int index){polymers.erase(polymers.begin()+index);}
    vector<Polymer *> getPolymers(){return polymers;}
    vector<vector<ExternalConnection *>> getPotentialHeadConnection(){return potential_head_connections;}
    vector<vector<ExternalConnection *>> getPotentialTailConnection(){return potential_tail_connections;}
    void addConglomerate(Conglomerate * con){con->setIndex(++conglomerate_index); conglomerates.push_back(con);}
    void addPolymer(Polymer * pol){pol->setIndex(++polymer_index); polymers.push_back(pol);}

    vector<Conglomerate *> getConglomerates(){return conglomerates;}


    bool chooseBond(int transition);
    vector<int> getRates();
    void getEverything();
    vector<vector<Connection *>> getHeadBinding();
    vector<vector<Connection *>> getTailBinding();
    vector<vector<Connection *>> getHeadUnbinding();
    vector<vector<Connection *>> getTailUnbinding();
    vector<vector<ConnectedNeighbours *>> getConnectedNeighbours();
    vector<vector<UnconnectedNeighbours *>> getUnconnectedNeighbours();
    vector<vector<PotentialSite *>> getAvailableHeadTailSites();
    void updatePotentialHeadTailSites();

    bool chooseHeadBinding();
    bool performHeadBinding(Conglomerate * conglomerate, Connection * connection);
    bool chooseTailBinding();
    bool performTailBinding(Conglomerate * conglomerate, Connection * connection);
    bool chooseHeadUnbinding();
    bool performHeadUnbinding(Conglomerate * conglomerate, Connection * connection);
    bool chooseTailUnbinding();
    bool performTailUnbinding(Conglomerate * conglomerate, Connection * connection);
    bool chooseNeighboursUnbind();
    bool performNeighboursUnbind(Conglomerate * conglomerate, ConnectedNeighbours * connection);
    bool chooseNeighboursBind();
    bool performNeighboursBind(Conglomerate * conglomerate, UnconnectedNeighbours * connection);
    bool chooseHeadConnection();
    bool performHeadConnection(ExternalConnection * connection);
    bool chooseTailConnection();
    bool performTailConnection(ExternalConnection * connection);

    void print();
};


#endif //TESTTWO_SYSTEM_H
