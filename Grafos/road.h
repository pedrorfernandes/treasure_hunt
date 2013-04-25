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

/**
 * A road is a path that the treasure hunter can take from city A to city B.
 * It represents an edge in the graph.
 */
class Road{
    City * city1; /**< The first city the road is connected to. */
    City * city2; /**< The second city the road is connected to. */
    double distance; /**< The distance between the two cities. */
    int identification; /**< The ID of the road. */
    static int numberOfRoads; /**< The number of existing roads. */
    int visits; /**< The number of times the treasure hunter used this road. */
    string color; /**< The color of the road. */
    static vector<string> roadColors; /**< All the possible colors roads can have. */
public:
    const bool isDirected; /**< Determines if the road is one way only. */
    
    /**
     * Creates a road between two cities.
     * @param city1 The first city.
     * @param city2 The second city.
     * @param distance The distance between the two cities.
     * @param isDirected If the road is one way only.
     */
    Road(City * city1, City * city2, const double & distance, const bool &isDirected);
    
    /**
     * @return The ID of a road.
     */
    int getID() const;
    
    /**
     * @return The first city the road is connected to.
     */
    City * getCity1() const;
    
    /**
     * @return The second city the road is connected to.
     */
    City * getCity2() const;
    
    /**
     * @return The distance of the road.
     */
    double getDistance() const;
    
    /**
     * Tells the road it has been visited by the hunter.
     */
    void visit();
    
    /**
     * @return The color of the road according to the number of vistis made by the hunter.
     */
    string getColor() const;
};

#endif
