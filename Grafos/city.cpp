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

City::City(string name, int x, int y): hasTreasure(false){
	this->name = name;
	numberOfCities++;
	identifier = numberOfCities;
    this->x = x;
    this->y = y;
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

void City::setClues(vector<City *> clues){
    this->clues = clues;
}

int City::getX() const{
    return x;
}

int City::getY() const{
    return y;
}

City::City(string name, const bool hasTreasure, int x, int y):hasTreasure(hasTreasure) {
	this->name = name;
	numberOfCities++;
	identifier = numberOfCities;
    this->x = x;
    this->y = y;
}

City::City(string name, const bool hasTreasure, vector<City*> clues, int x, int y):hasTreasure(hasTreasure) {
	this->name = name;
	this->clues = clues;
	numberOfCities++;
	identifier = numberOfCities;
    this->x = x;
    this->y = y;
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

bool City::operator == (const City *c2) const{
	if (this->name == c2->name)
		return true;
	else
		return false;
}

bool City::operator != (const City *c2) const{
	if (this->name != c2->name)
		return true;
	else
		return false;
}
