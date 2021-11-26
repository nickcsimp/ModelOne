cmake_minimum_required(VERSION 3.20)
project(testTwo)

set(CMAKE_CXX_STANDARD 14)

add_executable(testTwo main.cpp Conglomerate.cpp Conglomerate.h Connection.cpp Connection.h Polymer.cpp Polymer.h System.cpp System.h Tests.cpp Tests.h ConnectedNeighbours.cpp ConnectedNeighbours.h UnconnectedNeighbours.cpp UnconnectedNeighbours.h PotentialSite.cpp PotentialSite.h ExternalConnection.cpp ExternalConnection.h Simulation.cpp Simulation.h)
