//  director.cpp
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

#include "director.h"

Director::Director(TreasureHunter * hunter, Graph<City *> * graph, bool isBacktracking){
	this->treasureHunter = hunter;
	this->graph = graph;
	this->backtracking = isBacktracking;
    this->numberOfCities = graph->getNumVertex();
    this->numberOfRoads = graph->getNumVertex();
	calculateNextPath();
}

Director::Director(TreasureHunter * hunter, Graph<City *> * graph, bool isBacktracking, bool performanceMode, unsigned long numberOfCities, unsigned long numberOfRoads){
	this->treasureHunter = hunter;
	this->graph = graph;
	this->backtracking = isBacktracking;
	this->performanceMode = performanceMode;
    this->numberOfCities = numberOfCities;
    this->numberOfRoads = numberOfRoads;
	calculateNextPath();
}

bool Director::calculateNextPath() {
	City* currentCity = treasureHunter->getCurrentCity();
	vector<City*> currentCityClues = treasureHunter->readClues();
    
    if (!currentCityClues.empty() ){
        stringstream foundClues;
        foundClues << "The treasure hunter found clues to: ";
        for (unsigned int i = 0; i < currentCityClues.size(); ++i) {
            foundClues << currentCityClues.at(i)->getName();
            if (i != currentCityClues.size()-1)
                foundClues << ", ";
        }
        events.push(foundClues.str());
    }
    
	// if the hunter isn't backtracking, quest ends here.
	if (currentCityClues.empty() && !backtracking )
		return false;

	//In case backtracking is enabled, if the hunter's current city doesn't have valid clues and there is no treasure in it
	//The hunter should just go back to the last city where he read clues and use a different clue
	if(backtracking && currentCityClues.empty() && !currentCity->hasTreasure) {

		treasureHunter->setBacktracking(true);

		City* returnCity = treasureHunter->getReturnCity();

		if(returnCity == NULL) {
			events.push(STUCK_AT_START);
			return false;
		}

		events.push(NO_CLUES);

		treasureHunter->setDestination(returnCity);
		events.push(BACKTRACK_TO_DESTINATION);

		stack<City*> buffer;
		while( (*currentCity) != returnCity) {
			currentCity = treasureHunter->stepBackHistory();
			buffer.push(currentCity);
		}

		while(!buffer.empty()) {
			currentPath.push(buffer.top());
			buffer.pop();
		}

		return true;
	}

#ifdef USE_TIMER
	if(performanceMode) {
        events.push(RUNNING_TESTS);
		stringstream performance;
		unsigned long average1 = checkPerformance(currentCity, OPTIMISED_DIJKSTRA);
		unsigned long average2 = checkPerformance(currentCity, BELLMAN_FORD);
		unsigned long average3 = checkPerformance(currentCity, DIJKSTRA);
        //unsigned long average4 = checkPerformance(currentCity, FLOYD_WARSHALL);
		performance << "Optimised Dijkstra performance: " << average1 << " microseconds." << endl;
		performance << "Bellman-Ford performance: " << average2 << " microseconds." << endl;
        performance << "Dijkstra performance: " << average3 << " microseconds." << endl;
		//performance << "Floyd Warshall performance: " << average4 << " microseconds." << endl;
		events.push( performance.str() );
	}
#endif
    
    if ( currentCityClues.empty() ) return false;
    
    /* 
     Optimisation: if the number of roads is 10x bigger than the number of cities
     our analysis tells us that our enhanced dijkstra will work better.
     (example: 1 000 cities and 10 000 roads will work better with dijkstra)
     For a lower number of roads, bellman-ford algorithm is faster.
     */
    if ( numberOfRoads >= numberOfCities * 10 ){
        graph->optimisedDijkstraShortestPath(currentCity);
    } else {
        graph->bellmanFordShortestPath(currentCity);
    }
    
	City* closestClue = currentCityClues[0];
	double shortestDist = graph->getVertex(currentCityClues[0])->getDist();

	for(unsigned int i = 1; i < currentCityClues.size(); i++) {
		double dist = graph->getVertex(currentCityClues[i])->getDist();

		if(dist < shortestDist){
			closestClue = currentCityClues[i];
            shortestDist = dist;
        }
	}

	vector<City*> shortestPath = graph->getPath(currentCity, closestClue);
	treasureHunter->setDestination(closestClue);
	events.push(DESTINATION);
	currentCity->removeClue(closestClue);

	if(shortestPath.empty())
		return false;

	for(int i = (int)shortestPath.size() - 1; i >= 1; i--)
		currentPath.push(shortestPath[i]);

	return true;
}

City* Director::nextStep() {
	City* nextCity = NULL;
	if ( !currentPath.empty() ){
		nextCity = currentPath.top();
		currentPath.pop();
		treasureHunter->moveTo(nextCity);
		events.push(ARRIVED_AT_A_CITY);
	}
    return nextCity;
}

bool Director::updatePath() {
	if(treasureHunter->isBacktracking() && currentPath.empty())
		treasureHunter->setBacktracking(false);

	if(currentPath.empty() )
		if(!calculateNextPath()) {
			events.push(NO_PATH);
            throw noPathToTake();
			return false;
		}

	return true;
}

#ifdef USE_TIMER
inline void Director::startTimer() {
	gettimeofday(&clockStart, NULL);
	return;
}

inline unsigned long Director::stopTimer(){
	gettimeofday(&clockEnd, NULL);
    unsigned long mtime, seconds, useconds;
	seconds  = clockEnd.tv_sec  - clockStart.tv_sec;
	useconds = clockEnd.tv_usec - clockStart.tv_usec;

	mtime = ((seconds) * 1000000 + useconds);
	return mtime;
}

unsigned long Director::checkPerformance(City * start, int algorithm){
	unsigned long time = 0;
    switch (algorithm) {
		case DIJKSTRA:
		{
            unsigned long runs = RUNS;
			startTimer();
            for (unsigned long run = 0; run < runs; run++) {
                graph->dijkstraShortestPath(start);
            }
			time = stopTimer();
            time /= runs;
			break;
		}
		case BELLMAN_FORD:
		{
            unsigned long runs = RUNS;
			startTimer();
            for (unsigned long run = 0; run < runs; ++run) {
                graph->bellmanFordShortestPath(start);
            }
			time = stopTimer();
            time /= runs;
			break;
		}
		case FLOYD_WARSHALL:
		{
            unsigned long runs = 1;
			startTimer();
            for (unsigned long run = 0; run < runs; ++run) {
                graph->floydWarshallShortestPath();
            }
			time = stopTimer();
            time /= runs;
			break;
		}
		case OPTIMISED_DIJKSTRA:
		{
            unsigned long runs = RUNS;
			startTimer();
            for (unsigned long run = 0; run < runs; ++run) {
                graph->optimisedDijkstraShortestPath(start);
            }
			time = stopTimer();
            time /= runs;
			break;
		}
		default:
			break;
    }
	return time;
}
#endif
