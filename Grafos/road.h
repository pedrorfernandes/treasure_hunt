//  road.h
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

#ifndef _ROAD_H_
#define _ROAD_H_

#define ROAD_COLOR "orange"
#define ROAD_1_VISIT "blue"
#define ROAD_2_VISIT "cyan"
#define ROAD_3_VISIT "light_gray"
#define ROAD_4_VISIT "gray"

#include "city.h"

class Road{
    City * city1;
    City * city2;
    double distance;
    int identification;
    static int numberOfRoads;
    int visits;
    string color;
    static vector<string> roadColors;
public:
    Road(City * city1, City * city2, const double & distance, const bool &isDirected);
    int getID() const;
    const bool isDirected;
    City * getCity1() const;
    City * getCity2() const;
    double getDistance() const;
    void visit();
    string getColor() const;
};

#endif
