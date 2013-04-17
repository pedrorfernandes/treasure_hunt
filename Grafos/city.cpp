//  city.cpp
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

#include "city.h"

int City::numberOfCities = 0;

City::City(string name): hasTreasure(false){
	this->name = name;
	numberOfCities++;
	identifier = numberOfCities;
}

string City::getName() const {
	return name;
}

int City::getID() const{
	return identifier;
}

vector<City*> City::getClues() const {
	return clues;
}

City::City(string name, const bool hasTreasure):hasTreasure(hasTreasure) {
	this->name = name;
	numberOfCities++;
	identifier = numberOfCities;
}

City::City(string name, const bool hasTreasure, vector<City*> clues):hasTreasure(hasTreasure) {
	this->name = name;
	this->clues = clues;
	numberOfCities++;
	identifier = numberOfCities;
}

bool City::removeClue(City* city) {
	vector<City*>::iterator it = clues.begin();

	for(; it != clues.end(); it++)
		if((*it) == city) {
			clues.erase(it);
			return true;
		}

	return false;
}

bool City::operator == (const City &c2) const{
	if (this->name == c2.name)
		return true;
	else
		return false;
}
