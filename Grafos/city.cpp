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
	this->color = CITY_COLOR;
}

City::City(string name, const bool hasTreasure, int x, int y):hasTreasure(hasTreasure) {
	this->name = name;
	numberOfCities++;
	identifier = numberOfCities;
	this->x = x;
	this->y = y;
	if (!hasTreasure) this->color = CITY_COLOR;
	else {
        this->color = TREASURE_COLOR;
        this->addClue(this);
    }
}

City::City(string name, const bool hasTreasure, vector<City*> clues, int x, int y):hasTreasure(hasTreasure) {
	this->name = name;
	this->clues = clues;
	numberOfCities++;
	identifier = numberOfCities;
	this->x = x;
	this->y = y;
	if (!hasTreasure) this->color = CITY_COLOR;
	else {
        this->color = TREASURE_COLOR;
        this->addClue(this);
    }
}

string City::getName() const {
	return name;
}

void City::setName(string name) {
	this->name = name;
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

string City::getColor() const{
	return color;
}

bool City::addClue(City * clue){
	// there can only be clues to the same city
	// if it has the treasure
	if ( (*this) == clue && !this->hasTreasure )
		return false;

	vector<City*>::iterator it = clues.begin();

	for(; it != clues.end(); ++it)
		if( (*(*it)) == clue) {
			return false;
		}

	clues.push_back(clue);
	return true;
}

int City::getX() const{
	return x;
}

int City::getY() const{
	return y;
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
	if (this->name == c2->name || ( this->x == c2->getX() && this->y == c2->getY() ))
		return true;
	else
		return false;
}

bool City::operator != (const City *c2) const{
	if (this->name != c2->name && ( this->x != c2->getX() && this->y != c2->getY() ))
		return true;
	else
		return false;
}

ostream& operator <<(ostream& out, City& c) {
	out << c.getName() << endl;
	out << "X Position: " << c.getX() << endl;
	out << "Y Position: " << c.getY() << endl;
	out << "Has treasure: ";
	if(c.hasTreasure)
		cout << "yes" << endl;
	else
		cout << "no" << endl;

	return out;
}
