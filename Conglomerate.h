//
// Created by Nicholas Simpson on 20/10/2021.
//
#include <iostream>
#include <vector>
using namespace std;
#include "Polymer.h"
#include "Connection.h"

#ifndef TESTTWO_CONGLOMERATE_H
#define TESTTWO_CONGLOMERATE_H


class Conglomerate{
private:
    int index;

    vector<Connection *> connections; //All connections in conglomerate - most important

    //Need to know which backbone bonds exist and can break
    vector<Polymer *> polymers_in_conglomerate;
    int backbone_bonds; //save bonds in same order as polymers?

    //Need to know which connections are on which polymers and where
    vector<vector<Connection *>> polymer_connections;
    vector<vector<int>> polymer_connection_indexes;

    //Need to know which template bonds can unbind
    vector<Connection *> tail_unbinding_connections;
    int tail_unbinding_sites;

    //Need to know which tails can bind
    vector<Connection *> tail_binding_connections;
    int tail_binding_sites;

    int template_bonds; //available template bonds

    int valid_neighbours;
public:

    Conglomerate(vector<Connection *> con);

    Conglomerate(Polymer *p, int index, int monomer_type);

    Conglomerate(Polymer * p_one, int index_one, Polymer * p_two, int index_two);

    int getIndex();

    void setIndex(int ind);

    vector<Polymer*> getPolymersInConglomerate();

    void addConnection(Connection* con);

    void removeConnection(Connection* con);

    vector<Connection *> getConnections();

    void updatePolymersInConglomerate();

    void updateTemplateBond();

    int getTemplateBonds();

    int getBackboneBonds();

    void updateBackboneBonds();

    void updatePolymerConnections();

    vector<vector<Connection * >> getPolymerConnections();

    vector<vector<int>> getPolymerConnectionIndexes();

    int getTailUnbindingSites();

    int getTailBindingSites();

    vector<Connection *> getTailUnbindingConnections();

    vector<Connection *> getTailBindingConnections();

    void makePolymerConnections();

    void updateTailUnbindingSites();

    void updateTailBindingSites();

    bool tailConnectionOptions(Connection *con, Polymer * p, int direction, tuple<Polymer *, int > original_site);

    void updateValidNeighbours();

    int getValidNeighbours();

    bool validNeighbourOptions(Connection * con, Polymer * p, int direction, Polymer * original_polymer);

    void remove();
};

#endif //TESTTWO_CONGLOMERATE_H
