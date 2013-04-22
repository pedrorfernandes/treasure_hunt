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
			outputs.push(STUCK_AT_START);
			return false;
		}
        
        outputs.push(NO_CLUES);

		treasureHunter->setDestination(returnCity);
		outputs.push(BACKTRACK_TO_DESTINATION);

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

	graph->dijkstraShortestPath(currentCity);

	City* closestClue = currentCityClues[0];
	double shortestDist = graph->getVertex(currentCityClues[0])->getDist();

	for(unsigned int i = 1; i < currentCityClues.size(); i++) {
		double dist = graph->getVertex(currentCityClues[i])->getDist();

		if(dist < shortestDist)
			closestClue = currentCityClues[i];
	}

	vector<City*> shortestPath = graph->getPath(currentCity, closestClue);
	treasureHunter->setDestination(closestClue);
	outputs.push(DESTINATION);
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
        outputs.push(ARRIVED_AT_A_CITY);
    }
	return nextCity;
}

bool Director::updatePath() {
	if(treasureHunter->isBacktracking() && currentPath.empty())
		treasureHunter->setBacktracking(false);

	if(currentPath.empty() && !treasureHunter->getCurrentCity()->hasTreasure)
		if(!calculateNextPath()) {
			outputs.push(NO_PATH);
			return false;
		}

	return true;
}
