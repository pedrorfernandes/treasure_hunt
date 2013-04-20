//  treasureHunter.cpp
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

#include "treasureHunter.h"

TreasureHunter::TreasureHunter(City* startingCity) {
	currentCity = startingCity;
    lastCity = startingCity;
    stepHistory.push(startingCity);
	foundTreasure = false;
    destination = NULL;
}

City * TreasureHunter::getCurrentCity() const {
	return currentCity;
}

City * TreasureHunter::getLastCity() {
	return lastCity;
}

City * TreasureHunter::stepBackHistory() {
	lastCity = stepHistory.top();
	stepHistory.pop();
	return lastCity;
}

void TreasureHunter::setDestination(City * destination){
    this->destination = destination;
}

City * TreasureHunter::getDestination() const{
    return destination;
}

void TreasureHunter::moveTo(City* nextCity) {

	if(!backtracking)
		stepHistory.push(currentCity);
    
    lastCity = currentCity;
	currentCity = nextCity;

	if(currentCity->hasTreasure)
		foundTreasure = true;
}

void TreasureHunter::removeClue(City* cityClue) {
	currentCity->removeClue(cityClue);
}

void TreasureHunter::stepBack() {
	currentCity = stepHistory.top();
	stepHistory.pop();
}

vector<City *> TreasureHunter::readClues() {
	vector<City *> clues = getClues();

	if(!clues.empty())
		usedClues.push(currentCity);

	return clues;
}

vector<City*> TreasureHunter::getClues() {
	return currentCity->getClues();
}

bool TreasureHunter::isBacktracking() const {
	return backtracking;
}

void TreasureHunter::setBacktracking(bool val) {
	backtracking = val;
}

City* TreasureHunter::getReturnCity() {
	if(usedClues.empty())
		return NULL;

	City* returnCity = usedClues.top();
	usedClues.pop();
	return returnCity;
}
