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
	calculateNextPath();
}

bool Director::calculateNextPath() {
	City* currentCity = treasureHunter->getCurrentCity();
	vector<City*> currentCityClues = treasureHunter->readClues();

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
    
    unsigned long time = 0;
    startTimer();
    graph->dijkstraShortestPath(currentCity);
    time = stopTimer();
    stringstream performance;
    //unsigned long average1 = checkPerformance(currentCity, DIJKSTRA);
    unsigned long average2 = checkPerformance(currentCity, OPTIMISED_DIJKSTRA);
    unsigned long average3 = checkPerformance(currentCity, BELLMAN_FORD);

    //performance << "Dijkstra performance: " << average1 << " microseconds." << endl;
    performance << "New Dijkstra performance: " << average2 << " microseconds." << endl;
    performance << "Bellman-Ford performance: " << average3 << " microseconds.";
    events.push( performance.str() );
    
	City* closestClue = currentCityClues[0];
	double shortestDist = graph->getVertex(currentCityClues[0])->getDist();

	for(unsigned int i = 1; i < currentCityClues.size(); i++) {
		double dist = graph->getVertex(currentCityClues[i])->getDist();

		if(dist < shortestDist)
			closestClue = currentCityClues[i];
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
			return false;
		}

	return true;
}

void Director::startTimer() {    
    gettimeofday(&clockStart, NULL);
    return;
}

unsigned long Director::stopTimer(){
    unsigned long mtime, seconds, useconds;
    
    gettimeofday(&clockEnd, NULL);
    
    seconds  = clockEnd.tv_sec  - clockStart.tv_sec;
    useconds = clockEnd.tv_usec - clockStart.tv_usec;
    
    mtime = ((seconds) * 1000000 + useconds) + 0.5;
    return mtime;
}

unsigned long Director::checkPerformance(City * start, int algorithm){
    unsigned long time = 0;
    unsigned long runs = 5000;
    unsigned long total = 0;
    for (unsigned int run = 0; run < runs; ++run) {
        switch (algorithm) {
            case DIJKSTRA:
            {
                startTimer();
                graph->dijkstraShortestPath(start);
                time = stopTimer();
                total += time;
                break;
            }
            case BELLMAN_FORD:
            {
                startTimer();
                graph->bellmanFordShortestPath(start);
                time = stopTimer();
                total += time;
                break;
            }
            case FLOYD_WARSHALL:
            {
                startTimer();
                graph->floydWarshallShortestPath();
                time = stopTimer();
                total += time;
                break;
            }
            case OPTIMISED_DIJKSTRA:
            {
                startTimer();
                graph->optimizedDijkstraShortestPath(start);
                time = stopTimer();
                total += time;
                break;
            }
            default:
                break;
        }
    }
    unsigned long average = total / runs;
    return average;
}
