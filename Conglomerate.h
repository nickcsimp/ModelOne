//
// Created by Nicholas Simpson on 20/10/2021.
//
#include <iostream>
#include <vector>
using namespace std;
#include "Polymer.h"
#include "Connection.h"
#include "UnconnectedNeighbours.h"
#include "ConnectedNeighbours.h"

#ifndef TESTTWO_CONGLOMERATE_H
#define TESTTWO_CONGLOMERATE_H


class Conglomerate{
private:
    int index;

    int number_of_families;
    int number_of_monomer_types;

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

    vector<vector<int>> available_template_bonds;

    int valid_neighbours_binding;
    vector<UnconnectedNeighbours *> valid_unconnected_neighbours;

    int valid_neighbours_unbinding;
    vector<ConnectedNeighbours *> valid_connected_neighbours;
public:

    Conglomerate(vector<Connection *> con, int family_count, int monomer_type_count);

    Conglomerate(Polymer * polymer, int family_count, int monomer_type_count);

    void update();

    int getIndex();

    void setIndex(int ind);

    vector<Polymer*> getPolymersInConglomerate();

    void addConnection(Connection* con);

    void addConnections(vector<Connection*> cons);

    vector<Conglomerate *> removeConnection(Connection* con);

    vector<Polymer *> getTree(Polymer * p, vector<Polymer *> connected_polymers);

    vector<vector<Connection *>> updateConnectivity();

    vector<Connection *> getConnections();

    void updatePolymersInConglomerate();

    vector<tuple<Polymer*, int>> getPossibleSites(int type, int family);

    //void updateTemplateBond();

    void updateAvailableTemplateBonds();

    int getTemplateBonds();

    vector<vector<int>> getAvailableTemplateBonds();

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

    void updateValidNeighboursBinding();

    int getValidNeighboursBinding();

    bool validNeighbourBindingOptions(Connection * con, Polymer * p, int direction, Polymer * original_polymer);

    void updateValidNeighboursUnbinding();

    int getValidNeighboursUnbinding();

    bool operator==(Conglomerate c);

    vector<ConnectedNeighbours *> getValidConnectedNeighbours();

    vector<UnconnectedNeighbours *> getValidUnconnectedNeighbours();

    Polymer * joinPolymers(UnconnectedNeighbours * neighbours);

    Polymer * separatePolymers(ConnectedNeighbours * neighbours);
};

#endif //TESTTWO_CONGLOMERATE_H
