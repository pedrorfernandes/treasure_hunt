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

bool Director::calculateNextPath() {
	City* currentCity = treasureHunter->getCurrentCity();
	vector<City*> currentCityClues = currentCity->getClues();

	if(currentCityClues.empty() && !currentCity->hasTreasure) {
		treasureHunter->stepBack();
		return calculateNextPath();
	}

	graph->dijkstraShortestPath(currentCity);

	vector<City> shortestPath = graph->getPath(currentCity, currentCityClues[0]);

	for(unsigned int i = 1; i < currentCityClues.size(); i++) {
		vector<City&> path = graph->getPath(currentCity, currentCityClues[i]);

		if(path.size() < shortestPath.size())
			shortestPath = path;
	}

	if(shortestPath.empty())
		return false;

	for(unsigned int i = shortestPath.size() - 1; i >= 0; i--)
		currentPath.push(&shortestPath[i]);

	return true;
}

City* Director::nextStep() {
}
