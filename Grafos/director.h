//  director.h
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
#ifndef _DIRECTOR_H_
#define _DIRECTOR_H_

#include "treasureHunter.h"
#include "city.h"
#include "graph.h"
#include <stack>

#define NO_CLUES "No clues nor treasure here, maybe we should have picked a better clue... Let's go back!\n"
#define STUCK_AT_START "Guess we are back to the starting point and we have nowhere to go...\n"
#define BACKTRACK_TO_DESTINATION "Heading back to " + returnCity->getName() + "!\n"
#define DESTINATION "Heading towards " + closestClue->getName() + "!\n"
#define NO_PATH "No path to take! Quest over.\n"
#define ARRIVED_AT_A_CITY "Arrived at " + nextCity->getName() + "!"

/**
 * The director is the main engine class. It stores the graph holding all the cities and the treasure hunter.
 * It is responsible for figuring out which algorithms to apply in the graph and use the generated paths to move the treasure hunter in the best direction.
 */
class Director {
    TreasureHunter * treasureHunter; /**< The treasure hunter. */
    Graph<City *> * graph; /**< The graph containing all the cities and roads. Can be interpreted as a map. */
    stack<City *> currentPath; /**< The current path the hunter must take. If it's empty, the hero stops in the current city. */
    bool backtracking; /**< If true, when the hero reaches a dead end (city with no clues), he goes back to the latest visited city. If false, the journey ends in the dead end. */
public:
    queue<string> events;
    /**
     * Creates a new director.
     * @param hunter The treasure hunter.
     * @param graph The pre-made graph.
     * @param isBacktracking If the algorithm uses backtracking.
     */
    Director(TreasureHunter * hunter, Graph<City *> * graph, bool isBacktracking);
    
    /**
     * This function must get the hunter's next location choices and determines which is the closest.
     * It takes into account the type of the graph so that it can optimize and choose the best algorithm to do this task.
     * The generated path is stacked into the currentPath variable.
     * @return True if successful. If there is no path to take, false is returned.
     */
    bool calculateNextPath();
    
    /**
     * The next step moves the hunter closer to his current destination.
     * If the destination is reached and no treasure was found, a new path must be calculated.
     * If a new path can't be calculated, the treasure hunter stops his journey.
     * @return The city where the treasure hunter goes next. NULL if he stops.
     */
    City * nextStep();
    
    bool updatePath();
    
    
    
};

#endif 
