//  interface.cpp
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

#include "interface.h"

#define PROMPT "> "

int getOption(int maxOption) {
	string input = "";
	int option;

	do {
		cout << PROMPT;
		getline(cin, input);
		stringstream stream(input);

		if (stream >> option && option >= 0 && option <= maxOption)
			break;

		cout << "Please enter a valid option" << endl;
	} while(true);

	return option;
}

int getNumber() {
	string input = "";
	int number;

	do {
		cout << PROMPT;
		getline(cin, input);
		stringstream stream(input);

		if (stream >> number && number >= 0)
			break;

		cout << "Please enter a positive number" << endl;
	} while(true);

	return number;
}

int getNumber(int minNumber) {
	string input = "";
	int number;

	do {
		cout << PROMPT;
		getline(cin, input);
		stringstream stream(input);

		if (stream >> number && (number == 0 || number >= minNumber))
			break;

		cout << "Please enter a positive number" << endl;
	} while(true);

	return number;
}

void Interface::newMapMenu() {
	int numberOfOptions = 5;
	bool exitMenu = false;

	while(!exitMenu) {

		cout << endl <<
				"1 - Edit cities" << endl <<
				"2 - Edit roads" << endl <<
				"3 - Edit clues" << endl <<
				"4 - Generate random map" << endl <<
				"Press 0 to exit" << endl;

		int option = getOption(numberOfOptions);

		switch(option) {
		case 1:
			//editCitiesMenu();
			break;
		case 2:
			//editRoadsMenu();
			break;
		case 3:
			//editCluesMenu();
			break;
		case 4:
			if(randomGraphMenu())
				exitMenu = true;
			break;
		case 0:
			exitMenu = true;
			break;
		}
	}
}

bool Interface::randomGraphMenu() {
	cout << "Number of cities? (0 to cancel)" << endl;
	int numberOfCities = getNumber();

	if(numberOfCities == 0)
		return false;

	cout << "Number of roads? (At least equal to cities, 0 to cancel)" << endl;
	int numberOfRoads = getNumber(numberOfCities);

	if(numberOfRoads == 0)
		return false;

	cout << "Minimum number of clues per city? (0 to cancel)" << endl;
	int numberOfClues = getNumber();

	if(numberOfClues == 0)
		return false;

	builder->createGraph(numberOfCities, numberOfRoads, numberOfClues);
	graphReady = true;
	cout << "Random map is ready!" << endl;
	return true;
}

void Interface::loadMapMenu() {
	//TODO implement, duh
}

bool Interface::mainMenu() {
	int numberOfOptions = 2;
	bool exitMenu = false;

	while(!exitMenu) {

		cout << endl <<
				"1 - Create new map" << endl <<
				"2 - Load map from file" << endl;

		if(graphReady) {
			cout << "3 - Start journey" << endl;
			numberOfOptions = 3;
		}
		else
			numberOfOptions = 2;

		cout << "Press 0 to exit" << endl;

		int option = getOption(numberOfOptions);

		switch(option) {
		case 1:
			newMapMenu();
			break;
		case 2:
			//loadMapMenu();
			break;
		case 3:
			return true;
			break;
		case 0:
			return false;
			break;
		}
	}

	return false;
}

Interface::Interface(){
	builder = new GraphBuilder();
	graphReady = false;
}

void Interface::init(){
	// basic tests
	/*
	string filename = "map.txt";
	builder->loadFromFile(filename);
	 */

	/* string save = "teste.txt";
	builder->saveToFile(save);*/

	if(!mainMenu())
		return;

	view = builder->getGraphViewer();
	view->rearrange();

	this->cities = builder->getCities();
	this->roads = builder->getRoads();
	this->treasureHunter = builder->getTreasureHunter();

	director = new Director(treasureHunter, builder->getGraph(), true);

	cout << "Press enter for each step of the journey!" << endl;

	cout << director->events.front() << endl;
	director->events.pop();
	cin.get();
	mainLoop();
}

void Interface::mainLoop(){
	while ( !treasureHunter->foundTreasure ) {
		City * nextCity; City * destination; City * lastCity;

		if ( director->nextStep() == NULL ){
			while ( !director->events.empty() ) {
				cout << director->events.front() << endl;
				director->events.pop();
			}
			return;
		}

		lastCity = treasureHunter->getLastCity();
		nextCity = treasureHunter->getCurrentCity();
		repaintRoad(lastCity, nextCity);
		destination = treasureHunter->getDestination();
		view->setVertexColor(treasureHunter->getLastCity()->getID(), treasureHunter->getLastCity()->getColor());
		while(!director->events.empty()) {
			cout << director->events.front() << endl;
			director->events.pop();
		}
		view->setVertexColor(nextCity->getID(), HUNTER_COLOR);
		view->rearrange();
		if (!director->updatePath() ){
			while ( !director->events.empty() ) {
				cout << director->events.front() << endl;
				director->events.pop();
			}
			return;
		}
		if (!treasureHunter->foundTreasure) cin.get();
	}

	cout << "\nThe hero found the treasure! Hurrah!" << endl;
	return;
}

void Interface::repaintRoad(City * city1, City * city2){
	vector<Road *>::iterator roadItr;
	for (roadItr = roads.begin(); roadItr != roads.end(); ++roadItr) {
		if ( ( (*roadItr)->getCity1()->getID() == city1->getID() && (*roadItr)->getCity2()->getID() == city2->getID() )
				|| ( (*roadItr)->getCity2()->getID() == city1->getID() && (*roadItr)->getCity1()->getID() == city2->getID() ) ){
			(*roadItr)->visit();
			view->setEdgeColor( (*roadItr)->getID(), (*roadItr)->getColor() );
		}
	}
}
