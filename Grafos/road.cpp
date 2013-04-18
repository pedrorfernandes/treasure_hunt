//  road.cpp
//
//  Projeto CAL
//  Parte 1
//
//  Turma 1 Grupo D
//
//  ei11089 - Diogo Santos
//  ei11122 - Pedro Fernandes
//  ei11132 - Daniel Pereira
//

#include "road.h"

int Road::numberOfRoads = 0;

Road::Road(City * city1, City * city2, const double &distance, const bool &isDirected): isDirected(isDirected){
    this->city1 = city1;
    this->city2 = city2;
    this->distance = distance;
    numberOfRoads++;
    identification = numberOfRoads;
}

int Road::getID() const{
    return identification;
}

City * Road::getCity1() const{
    return city1;
}

City * Road::getCity2() const{
    return city2;
}

double Road::getDistance() const{
    return distance;
}