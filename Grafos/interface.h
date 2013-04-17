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
     */
    void menu();
    
    /**
     * Updates the game by receiving the next step from the director until the journey is done.
     */
    void mainLoop();
    
};

#endif
