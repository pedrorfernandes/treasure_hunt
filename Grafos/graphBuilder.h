//  builder.h
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

#ifndef _GRAPH_BUILDER_H_
#define _GRAPH_BUILDER_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

// includes for the random graph
#include <algorithm>    
#include <ctime>    
#include <cstdlib>
#include <string>
#include <set>

#include "graph.h"
#include "treasureHunter.h"
#include "graphviewer.h"
#include "city.h"
#include "edgetype.h"
#include "road.h"

#define WIDTH 1000
#define HEIGHT 1000
#define BACKGROUND "map.png"
#define ROAD_COLOR "orange"
#define CITY_COLOR "red"
#define HUNTER_COLOR "blue"
#define TREASURE_COLOR "green"
#define ROAD_THICKNESS 5

#define EQUALS '='
#define SEPARATOR ','
#define CITY "CITY"
#define ROAD "ROAD"
#define CLUE "CLUE"
#define HUNTER "HUNTER"
#define PRECISION 3

/**
 * The graph builder class reads the vertexes and edges from a file or generates it's own graph.
 * Besides building a graph internally it must also build the graph that has to be displayed.
 */
class GraphBuilder {
    Graph<City *> * graph; /**< The graph that's being built */
    TreasureHunter * treasureHunter; /**< The hunter with it's starting point. */
    GraphViewer * view; /**< The graph to be displayed */
    vector<Road *> roads;
    vector<City *> cities;
    
public:
    /**
     * Initializes a new graph and graphView
     */
    GraphBuilder();
    
    /**
     * @return The pointer to the graph viewer.
     */
    GraphViewer * getGraphViewer() const;
    
    /**
     * @return The pointer to the graph.
     */
    Graph<City *> * getGraph() const;
    
    /**
     * @return The pointer to the treasure hunter.
     */
    TreasureHunter * getTreasureHunter() const;
    
    /**
     * @return The roads vector.
     */
    vector<Road *> getRoads() const;
    
    /**
     * @return The cities vector.
     */
    vector<City *> getCities() const;
    
    /**
     * @return The distance between two cities.
     */
    static double getDistance(City * city1, City * city2);
    
    /**
     * Finds a city created by the builder specified by name.
     * @param cityName The name of the city to find.
     * @return Pointer to a created city. Null if it doesn't exist.
     */
    City * getCity(const string cityName) const;
    
    /**
     * Generates a graph from a templated file with city names, clues and roads.
     * @return True if load was successful, false otherwise.
     */
    bool loadFromFile(const string &filename);
    
    /**
     * Saves the current graph in a templated style to a file.
     * @return True if saving to file was successful, false otherwise.
     */
    bool saveToFile(const string &filename);
    
    /**
     * Adds a city to the graph.
     * @param cityName The name of the new city.
     * @param hasTreasure If the new city has treasure.
     * @param x The X coordinates of the new city.
     * @param y The Y coordinates of the new city.
     * @return False if an error occurred, true if ok.
     */
    bool addCity(string cityName, bool hasTreasure, int x, int y);

    /**
     * Adds an road (edge) between two cities.
     * @param city1 The first city.
     * @param city2 The second city.
     * @param isDirected If true you can only travel from city1 to city2 on this road.
     * @return False if an error occurred, true if ok.
     */
    bool connect(City * city1, City * city2, const bool &isDirected);
    
    /**
     * Creates a treasure hunter in the specified city.
     * @param city The starting point.
     * @return False if the city doesn't exist, true otherwise.
     */
    bool spawnTreasureHunter(City * city);
    
    /**
     * Randomly generates a graph with cities and a hero following the specified conditions.
     * @param numberOfCities The number of created cities.
     * @param numberOfRoads The number of roads created.
     * @param numberOfClues The number of clues created.
     */
    void createGraph(const unsigned int &numberOfCities, const unsigned int &numberOfRoads, const unsigned int &numberOfClues);
    
    bool roadExists(City * city1, City* city2);

};

#endif 