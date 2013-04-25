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
#include "displayWithPages.h"

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
    bool performanceMode;
    bool backtracking;

    int citiesWithTreasure; /**< Tells if the graph has a city with treasure on it */
    int numberOfCities; /**< Number of cities created by user */

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
     * Resets the graph builder (deletes the current map), resetting the necessary variables.
     */
    void resetBuilder(int width, int height);

    /**
     * Checks if a functional map is ready to be played.
     * @return True if there is at least two cities and one of them has the treasure, false otherwise.
     */
    bool graphIsReady();

    /**
     * The menu that displays options to the user. Options include building a new map and starting a journey.
     * @return True if the game should start, false if it should terminate.
     */
    bool mainMenu();
    
    /**
     * Provides settings about the program for the user to change.
     */
    void optionsMenu();

    /**
     * Lets the user spawn a treasure hunter.
     */
    void hunterSpawnMenu();

    /**
     * This menu displays options related to map creation and editing to the user.
     */
    void editMapMenu();

    /**
     * This menu prompts the user for options to create a random map.
     * @return True if a map has been created, false if cancelled.
     */
    bool randomGraphMenu();

    /**
     * This menu lets the user create or delete cities, or edit them.
     */
    void citiesMenu();

    /**
     * Lets the user add a new city.
     */
     void addNewCity();

     /**
      * Lets the user delete an existing city.
      */
     void deleteExistingCity();

     /**
      * Lets the user edit a city's name.
      */
     void editCityName();

     /**
      * Menu for adding or removing roads.
      */
     void roadsMenu();

     /**
      * Lets the user add a new road.
      */
     void addNewRoad();

     /**
      * Lets the user delete an existing road.
      */
     void deleteExistingRoad();

     /**
      * Menu for adding or removing clues.
      */
     void cluesMenu();

     /**
      * Lets the user add a new clue.
      */
     void addNewClue();

     /**
      * Lets the user remove an existing clue.
      */
     void deleteExistingClue();

    /**
     * This menu provides the user with options to load a saved map.
     */
    void loadMapMenu();

    /**
     * This menu lets the user save a created map.
     */
    void saveMapMenu();

    /**
     * Updates the game by receiving the next step from the director until the journey is done.
     */
    void mainLoop();
    
    void repaintRoad(City * city1, City * city2);
    
};

#endif
