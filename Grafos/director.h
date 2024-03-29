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

#include <sstream>

#define NO_CLUES "No clues nor treasure here, maybe we should have picked a better clue... Let's go back!\n"
#define STUCK_AT_START "Guess we are back to the starting point and we have nowhere to go...\n"
#define BACKTRACK_TO_DESTINATION "Returning to " + returnCity->getName() + "!\n"
#define DESTINATION "Heading towards " + closestClue->getName() + "!\n"
#define NO_PATH "No path to take! Quest over.\n"
#define ARRIVED_AT_A_CITY "Arrived at " + nextCity->getName() + "!"
#define RUNNING_TESTS "Running speed tests! Please wait\n"

#if defined __APPLE__ || defined linux || defined (__CYGWIN32__)
#define USE_TIMER
#endif

#ifdef USE_TIMER
#include <sys/time.h>
#include <unistd.h>
#endif

#define DIJKSTRA 1
#define BELLMAN_FORD 2
#define FLOYD_WARSHALL 3
#define OPTIMISED_DIJKSTRA 4
#define RUNS 1000

/**
 * The director is the main engine class. It stores the graph holding all the cities and the treasure hunter.
 * It is responsible for figuring out which algorithms to apply in the graph and use the generated paths to move the treasure hunter in the best direction.
 */
class Director {
	TreasureHunter * treasureHunter; /**< The treasure hunter. */
	Graph<City *> * graph; /**< The graph containing all the cities and roads. Can be interpreted as a map. */
	stack<City *> currentPath; /**< The current path the hunter must take. If it's empty, the hero stops in the current city. */
	bool backtracking; /**< If true, when the hero reaches a dead end (city with no clues), he goes back to the latest visited city. If false, the journey ends in the dead end. */
	bool performanceMode; /**< If true, performance measuring is done during the program run. */
    unsigned long numberOfCities, numberOfRoads; /**< Variables for optimisation purposes. */

#ifdef USE_TIMER
	struct timeval clockStart, clockEnd; /**< Values that are used for timing performance. */
#endif
public:
	queue<string> events; /**< A queue of outputs that tell the interface what is happening in the journey */
	/**
	 * Creates a new director.
	 * @param hunter The treasure hunter.
	 * @param graph The pre-made graph.
	 * @param isBacktracking If the algorithm uses backtracking.
	 */
	Director(TreasureHunter * hunter, Graph<City *> * graph, bool isBacktracking);

	/**
	 * Creates a new director.
	 * @param hunter The treasure hunter.
	 * @param graph The pre-made graph.
	 * @param isBacktracking If the algorithm uses backtracking.
	 * @param performanceMode If the program is making performance measurements.
     * @param numberOfCities The number of cities inside the graph.
     * @param numberOfRoads The number of roads inside the graph.
	 */
	Director(TreasureHunter * hunter, Graph<City *> * graph, bool isBacktracking, bool performanceMode, unsigned long numberOfCities, unsigned long numberOfRoads);
    
	/**
	 * This function must get the hunter's next location choices and determines which is the closest.
	 * It takes into account the type of the graph so that it can optimise and choose the best algorithm to do this task.
	 * The generated path is stacked into the currentPath variable.
	 * @return True if successful. If there is no path to take, false is returned.
	 */
	bool calculateNextPath();

	/**
	 * The next step moves the hunter closer to his current destination.
	 * @return The city where the treasure hunter goes next. NULL if he stops.
	 */
	City * nextStep();

    /**
     * Checks if the treasure hunter reached his destination and if he arrived, orders him to calculate a new path according to the clues he find.
     * If there is no path to take, an exception is thrown.
     * @return True if the hunter hasn't arrived to his destination or if a new path is calculated. False if a new path is needed and can't be calculated.
     */
	bool updatePath();

#ifdef USE_TIMER
    /**
     * Starts a timer to measure performance time of a function.
     */
	void startTimer();
    
    /**
     * Stops the timer started by startTimer() function.
     * @return The elapsed time between the start and stop.
     */
	unsigned long stopTimer();
    
    /**
     * Checks the performance of a shortest path algorithm.
     * Does 1000 runs for each algorithm (except Floyd-Warshall's because it takes too long) and measures the average of those runs.
     * @param start The starting city.
     * @param algorithm The algorithm to test. ( (1)Optimised Dijkstra, (2)Bellman-Ford, (3)Dijkstra and (4)Floyd-Warshall).
     * @return The average performance of the algorithm.
     */
	unsigned long checkPerformance(City * start, int algorithm);
#endif

};

/**
 * An exception to be thrown were no path is avaiable
 */
class noPathToTake {
public:
    /**
     * Creates an exception
     */
    noPathToTake() {};
};

#endif 
