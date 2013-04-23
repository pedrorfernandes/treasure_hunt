//  interface.h
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

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "director.h"
#include "graphviewer.h"
#include "graphBuilder.h"

/**
 * The interface must do all the output and input operations and also handle the graphviewer API so that it correctly displays the current state of the map and the treasure hunter's progress.
 */
class Interface {
    Director * director; /**< The director that controls the journey */
    GraphViewer * view; /**< The graph that will be displayed */
    GraphBuilder * builder; /**< The builder in charge of creating graphs */
    vector<City *> cities;
    vector<Road *> roads;
    TreasureHunter * treasureHunter;
    bool graphReady; /**< Tells if the graph is ready to be displayed */
public:
    /**
     * Initializes a new interface
     */
    Interface();
    
    /**
     * Creates a graph builder that generates the graph for the director and for displaying.
     * Calls the main loop after initializing is done.
     */
    void init();
    
    /**
     * The menu that displays options to the user. Options include building a new map and starting a journey.
     * @return True if the game should start, false if it should terminate.
     */
    bool mainMenu();
    
    /**
     * This menu displays options related to map creation and editing to the user.
     */
    void newMapMenu();

    /**
     * This menu prompts the user for options to create a random map.
     * @return True if a map has been created, false if cancelled.
     */
    bool randomGraphMenu();

    /**
     * This menu provides the user with options to load a saved map
     */
    void loadMapMenu();

    /**
     * Updates the game by receiving the next step from the director until the journey is done.
     */
    void mainLoop();
    
    void repaintRoad(City * city1, City * city2);
    
};

#endif
