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

		outputs.push("No clues nor treasure here, maybe we should have picked a better clue... Let's go back!\n");

		treasureHunter->setBacktracking(true);

		City* returnCity = treasureHunter->getReturnCity();

		if(returnCity == NULL) {
			outputs.push("Guess we are back to the starting point and we have nowhere to go...\n");
			return false;
		}

		treasureHunter->setDestination(returnCity);
		outputs.push("Heading towards " + returnCity->getName() + "!\n");

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
	outputs.push("Heading towards " + closestClue->getName() + "!\n");
	currentCity->removeClue(closestClue);

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

	outputs.push("We reached " + nextCity->getName() + "!\n");
	return nextCity;
}

bool Director::updatePath() {
	if(treasureHunter->isBacktracking() && currentPath.empty())
		treasureHunter->setBacktracking(false);

	if(currentPath.empty() && !treasureHunter->getCurrentCity()->hasTreasure)
		if(!calculateNextPath()) {
			outputs.push("No path to take! Quest over.\n");
			return false;
		}

	return true;
}
