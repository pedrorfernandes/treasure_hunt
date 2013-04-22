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
vector<string> Road::roadColors;

Road::Road(City * city1, City * city2, const double &distance, const bool &isDirected): isDirected(isDirected){
    this->city1 = city1;
    this->city2 = city2;
    this->distance = distance;
    numberOfRoads++;
    identification = numberOfRoads;
    this->visits = 0;
    if (roadColors.empty() ){
        roadColors.push_back(ROAD_COLOR);
        roadColors.push_back(ROAD_1_VISIT);
        roadColors.push_back(ROAD_2_VISIT);
        roadColors.push_back(ROAD_3_VISIT);
        roadColors.push_back(ROAD_4_VISIT);
    }
    this->color = roadColors.at(visits);

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

void Road::visit(){
    visits++;
    if (visits >= roadColors.size() ) return;
    this->color = roadColors.at(visits);
}

string Road::getColor() const{
    return color;
}