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
#define MINIMUM_NUMBER_OF_CITIES 2

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

bool getAnswer(string question) {
	string input;
	bool answer;

	while(true) {
		cout << question << endl << PROMPT;
		getline(cin, input);

		if(input.compare("Yes") == 0 || input.compare("yes") == 0 || input.compare("Y") == 0 || input.compare("y") == 0) {
			answer = true;
			break;
		}

		if(input.compare("No") == 0 || input.compare("no") == 0 || input.compare("N") == 0 || input.compare("n") == 0) {
			answer = false;
			break;
		}
	}

	return answer;
}

bool Interface::graphIsReady() {
	return (hasCityWithTreasure && (numberOfCities >= 2));
}

bool Interface::mainMenu() {
	int numberOfOptions = 2;
	bool exitMenu = false;

	cout << "~* Treasure Hunter *~" << endl;

	while(!exitMenu) {

		cout << endl <<
				"----- Main Menu -----" << endl <<
				"0 - Exit" << endl <<
				"1 - Create and edit a map" << endl <<
				"2 - Load map from file" << endl;

		if(graphIsReady()) {
			cout << "3 - Save map to file" << endl <<
					"4 - Start journey" << endl;
			numberOfOptions = 4;
		}
		else {
			numberOfOptions = 2;
			cout << "Don't forget you need a treasure and at least two cities to play!" << endl;
		}

		int option = getOption(numberOfOptions);

		switch(option) {
		case 1:
			newMapMenu();
			break;
		case 2:
			//loadMapMenu();
			break;
		case 3:
			saveMapMenu();
			break;
		case 4:
			return true;
			break;
		case 0:
			return false;
			break;
		}
	}

	return false;
}

void Interface::newMapMenu() {
	int numberOfOptions = 5;
	bool exitMenu = false;

	while(!exitMenu) {

		cout << endl <<
				"--- Map Creation Menu ---" << endl <<
				"0 - Go back" << endl <<
				"1 - Edit cities" << endl <<
				"2 - Edit roads" << endl <<
				"3 - Edit clues" << endl <<
				"4 - Generate random map" << endl;

		int option = getOption(numberOfOptions);

		switch(option) {
		case 1:
			citiesMenu();
			break;
		case 2:
			//roadsMenu();
			break;
		case 3:
			//cluesMenu();
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
	cout << "--- Random map generator ---" << endl;
	cout << "Number of cities? (At least two, 0 to cancel)" << endl;
	int numberOfCitiesToCreate = getNumber(MINIMUM_NUMBER_OF_CITIES);

	if(numberOfCitiesToCreate == 0)
		return false;

	cout << "Number of roads? (At least equal to cities, 0 to cancel)" << endl;
	int numberOfRoads = getNumber(numberOfCitiesToCreate);

	if(numberOfRoads == 0)
		return false;

	cout << "Minimum number of clues to generate? (0 to cancel)" << endl;
	int numberOfClues = getNumber();

	if(numberOfClues == 0)
		return false;

	builder->createGraph(numberOfCitiesToCreate, numberOfRoads, numberOfClues);
	numberOfCities =  builder->getCities().size();
	hasCityWithTreasure = true;
	cout << "Random map is ready!" << endl;
	getchar();
	return true;
}

void Interface::citiesMenu() {
	int numberOfOptions = 2;
	bool exitMenu = false;

	while(!exitMenu) {

		cout << endl <<
				"--- Cities Menu ---" << endl <<
				"0 - Go back" << endl <<
				"1 - Add a new city" << endl <<
				"2 - Delete a city" << endl;

		if(graphIsReady()) {
			cout << "3 - Edit a city name" << endl <<
					"4 - Edit a city position" << endl;
			numberOfOptions = 4;
		}
		else {
			numberOfOptions = 2;
			cout << "Don't forget you need a treasure and at least two cities to play!" << endl;
		}

		int option = getOption(numberOfOptions);

		switch(option) {
		case 1:
			addNewCity();
			break;
		case 2:
			deleteExistingCity();
			break;
		case 3:
			//editCityName();
			break;
		case 4:
			//editCityPosition();
			break;
		case 0:
			exitMenu = true;
			break;
		}
	}
}

void Interface::addNewCity() {
	cout << endl << "- New city -" << endl;

	cout << "City name?" << endl << PROMPT;
	string name = "";
	getline(cin, name);

	cout << "x coordinate?" << endl;
	int x = getNumber();

	cout << "y coordinate?" << endl;
	int y = getNumber();

	bool cityHasTreasure = false;
	if(!hasCityWithTreasure) {
		bool accept = getAnswer("Would you like this city to hold the treasure? (Y/N)");
		if(accept)
			cityHasTreasure = true;
		else
			cityHasTreasure = false;
	}

	if(builder->addCity(name, cityHasTreasure, x, y)) {
		cout << "City created!" << endl;
		numberOfCities++;
		if(cityHasTreasure)
			hasCityWithTreasure = true;
		getchar();
	}
	else {
		cout << "Couldn't create this city, does it already exist?" << endl;
		getchar();
	}
}

void Interface::deleteExistingCity() {
	cout << endl << "- Delete city -" << endl;

	vector<City*>cities = builder->getCities();
	if(cities.empty()) {
		cout << "You have no cities to delete!" << endl;
		getchar();
		return;
	}

	City* cityToDelete = displayVector(cities);

	if(cityToDelete == NULL)
		return;
	else {
		if(builder->deleteCity(cityToDelete))
			cout << "City was deleted." << endl;
		else
			cout << "Failed to delete that city!" << endl;

		getchar();
	}
}

void Interface::editCityName() {
	//TODO implement
}

void Interface::editCityPosition() {
	//TODO implement
}

void Interface::loadMapMenu() {
	//TODO implement
}

void Interface::saveMapMenu() {
	cout << "--- Save map ---" << endl;

	string filename;
	cout << "Save map to:" << endl << PROMPT;
	getline(cin, filename);

	if(filename.empty())
		cout << "That's not a valid filename..." << endl;
	else {
		filename += ".txt";
		builder->saveToFile(filename);
		cout << endl << "Saved map!" << endl;
		getchar();
	}
}

Interface::Interface(){
	builder = new GraphBuilder();
	numberOfCities = 0;
	hasCityWithTreasure = false;
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
