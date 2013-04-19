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
}

bool Director::calculateNextPath() {
	City* currentCity = treasureHunter->getCurrentCity();
	vector<City*> currentCityClues = treasureHunter->readClues();

	//In case backtracking is enabled, if the hunter's current city doesn't have valid clues and there is no treasure in it
	//The hunter should just go back to the last city where he read clues and use a different clue
	if(backtracking && currentCityClues.empty() && !currentCity->hasTreasure) {
		City* returnCity = treasureHunter->getReturnCity();
		if(returnCity == NULL)
			return false;

		stack<City*> buffer;
		while(currentCity != returnCity) {
			currentCity = treasureHunter->getLastCity();
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

	if(shortestPath.empty())
		return false;

	for(int i = (int)shortestPath.size() - 1; i >= 1; i--)
		currentPath.push(shortestPath[i]);

	return true;
}

City* Director::nextStep() {    
	City* nextCity = currentPath.top();
	treasureHunter->moveTo(nextCity);
	currentPath.pop();

	if(currentPath.empty() && !nextCity->hasTreasure)
		if(!calculateNextPath())
			return NULL;

	return nextCity;
}
