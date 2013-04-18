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
	foundTreasure = false;
}

City * TreasureHunter::getCurrentCity() const{
    return currentCity;
}

void TreasureHunter::moveTo(City* nextCity) {
	currentCity->removeClue(nextCity);
	currentCity = nextCity;
	usedClues.push(nextCity);
	if(currentCity->hasTreasure)
		foundTreasure = true;
}

vector<City*> TreasureHunter::getClues() {
	return currentCity->getClues();
}
