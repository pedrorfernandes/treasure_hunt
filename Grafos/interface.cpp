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
	return (citiesWithTreasure > 0 && (numberOfCities >= 2));
}

bool Interface::mainMenu() {
	int numberOfOptions = 3;
	bool exitMenu = false;

	cout << "~* Treasure Hunt *~" << endl;
    builder = new GraphBuilder();
	while(!exitMenu) {

		cout << endl <<
				"----- Main Menu -----" << endl <<
				"0 - Exit" << endl <<
				"1 - Options" << endl <<
				"2 - Edit the map" << endl <<
				"3 - Load map from file" << endl;

		if(graphIsReady()) {
			cout << "4 - Save map to file" << endl <<
					"5 - Start journey" << endl;
			numberOfOptions = 5;
		}
		else {
			numberOfOptions = 3;
			cout << "Don't forget you need a treasure and at least two cities to start!" << endl;
		}

		int option = getOption(numberOfOptions);

		switch(option) {
		case 1:
			optionsMenu();
			break;
		case 2:
			editMapMenu();
			break;
		case 3:
			loadMapMenu();
			break;
		case 4:
			saveMapMenu();
			break;
		case 5:
			return true;
			break;
		case 0:
			return false;
			break;
		}
	}

	return false;
}

void Interface::optionsMenu() {

	int numberOfOptions = 2;
	bool exitMenu = false;

	while(!exitMenu) {

		cout << endl <<
				"--- Options Menu ---" << endl <<
				"0 - Go back" << endl;
		if(performanceMode)
			cout << "1 - Deactivate performance test mode" << endl;
		else
			cout << "1 - Activate performance test mode" << endl;
		if(backtracking)
			cout << "2 - Deactivate backtracking" << endl;
		else
			cout << "2 - Activate backtracking" << endl;
		int option = getOption(numberOfOptions);

		switch(option) {
		case 1:
			performanceMode = !performanceMode;
			break;
		case 2:
			backtracking = !backtracking;
			break;
		case 0:
			exitMenu = true;
			break;
		}
	}

}

void Interface::editMapMenu() {
	int numberOfOptions = 6;
	bool exitMenu = false;

	while(!exitMenu) {

		cout << endl <<
				"--- Map Edition Menu ---" << endl <<
				"0 - Go back" << endl <<
				"1 - Edit hunter location" << endl <<
				"2 - Edit cities" << endl <<
				"3 - Edit roads" << endl <<
				"4 - Edit clues" << endl <<
				"5 - Generate random map" << endl;

		int option = getOption(numberOfOptions);

		switch(option) {
		case 1:
			hunterSpawnMenu();
			break;
		case 2:
			citiesMenu();
			break;
		case 3:
			roadsMenu();
			break;
		case 4:
			cluesMenu();
			break;
		case 5:
			if(randomGraphMenu())
				exitMenu = true;
			break;
		case 0:
			exitMenu = true;
			break;
		}
	}
}

void Interface::hunterSpawnMenu() {
	cout << "- Hunter spawn menu -" << endl;
	cout << "Please pick a city to be the hunter's starting point" << endl;
	vector<City*> cities = builder->getCities();
	City* spawnCity = displayVector(cities);
	if(spawnCity == NULL)
		return;

	builder->spawnTreasureHunter(spawnCity);
    
    builder->getGraphViewer()->rearrange();
	cout << "Treasure hunter set to spawn on " << spawnCity->getName() << endl;
	cout << "Press enter to continue..." << endl;
	getchar();
}

bool Interface::randomGraphMenu() {
	cout << "--- Random map generator ---" << endl;
	cout << "WARNING: Generating a random map deletes your current one" << endl;
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
    
    cout << "Please set the desired map height (0 to default)" << endl;
	int height;
	height = getNumber();
    
	cout << "Please set the desired map width (0 to default)" << endl;
	int width;
	width = getNumber();
	resetBuilder(width, height);
	builder->createGraph(numberOfCitiesToCreate, numberOfRoads, numberOfClues);
	numberOfCities =  (int)builder->getCities().size();
	citiesWithTreasure = 1;
	cout << "Random map is ready!" << endl;
	cout << "Press enter to continue..." << endl;
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
			cout << "3 - Edit a city name" << endl;
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
			editCityName();
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
    bool accept = getAnswer("Would you like this city to hold the treasure? (Y/N)");
    if(accept)
        cityHasTreasure = true;
    else
        cityHasTreasure = false;
	
    
	if(builder->addCity(name, cityHasTreasure, x, y)) {
        builder->getGraphViewer()->rearrange();
		cout << "City created!" << endl;
		numberOfCities++;
		if(cityHasTreasure)
			citiesWithTreasure++;
		cout << "Press enter to continue..." << endl;
		getchar();
	}
	else {
		cout << "Couldn't create this city, does it already exist?" << endl;
		cout << "Press enter to continue..." << endl;
		getchar();
	}
}

void Interface::deleteExistingCity() {
	cout << endl << "- Delete city -" << endl;

	vector<City*>cities = builder->getCities();
	if(cities.empty()) {
		cout << "You have no cities to delete!" << endl;
		cout << "Press enter to continue..." << endl;
		getchar();
		return;
	}

	cout << endl << "Chose city to delete:" << endl;

	City* cityToDelete = displayVector(cities);

	if(cityToDelete == NULL)
		return;
	else {
		if(builder->deleteCity(cityToDelete)) {
            builder->getGraphViewer()->rearrange();
			cout << "City was deleted." << endl;
        } else
			cout << "Failed to delete that city!" << endl;

		cout << "Press enter to continue..." << endl;
		getchar();
	}
}

void Interface::editCityName() {
	cout << endl << "- Change city name -" << endl;

	cout << "Chose city to rename:" << endl;

	vector<City*> cities = builder->getCities();
	City* cityToRename = displayVector(cities);
    
    if (cityToRename == NULL)
        return;

	while(true) {
		string name;
		cout << "New name (0 cancels):" << endl << PROMPT;
		getline(cin, name);

		if(name.compare("0") == 0)
			break;

		if(builder->getCity(name) == NULL) {
			cityToRename->setName(name);
            builder->getGraphViewer()->setVertexLabel(cityToRename->getID(), name);
            builder->getGraphViewer()->rearrange();
			cout << "Renamed city to " << name << endl;
			break;
		}
		else
			cout << "That name already exists, pick a different one!" << endl;
	}

	cout << "Press enter to continue..." << endl;
	getchar();
}

void Interface::roadsMenu() {
	int numberOfOptions = 2;
	bool exitMenu = false;

	while(!exitMenu) {

		cout << endl <<
				"--- Roads Menu ---" << endl <<
				"0 - Go back" << endl <<
				"1 - Add a new road" << endl <<
				"2 - Delete a road" << endl;

		int option = getOption(numberOfOptions);

		switch(option) {
		case 1:
			addNewRoad();
			break;
		case 2:
			deleteExistingRoad();
			break;
		case 0:
			exitMenu = true;
			break;
		}
	}
}

void Interface::addNewRoad() {
	cout << "- Add road -" << endl;

	vector<City*> cities = builder->getCities();

	cout << "Choose a city for the origin" << endl;
	cout << "Press enter to continue..." << endl;
	getchar();
	City* originCity = displayVector(cities);
    
    if (originCity == NULL)
        return;

	cout << "Choose a city for the destination" << endl;
	cout << "Press enter to continue..." << endl;
	getchar();
	City* destinationCity = displayVector(cities);
    
    if (destinationCity == NULL)
        return;

	if(builder->connect(originCity, destinationCity, false)) {
        builder->getGraphViewer()->rearrange();
		cout << "Created road!" << endl;
	} else
		cout << "Failed to create road, does it already exist?" << endl;

	cout << "Press enter to continue..." << endl;
	builder->getGraphViewer()->rearrange();
	getchar();
}

void Interface::deleteExistingRoad() {
	cout << "- Delete road -" << endl;

	vector<City*> cities = builder->getCities();

	cout << "Choose a city for the origin" << endl;
	cout << "Press enter to continue..." << endl;
	getchar();
	City* originCity = displayVector(cities);
    
    if (originCity == NULL)
        return;

	cout << "Choose a city for the destination" << endl;
	cout << "Press enter to continue..." << endl;
	getchar();
	City* destinationCity = displayVector(cities);
    
    if (destinationCity == NULL)
        return;

	if( builder->deleteRoad(originCity, destinationCity) ) {
        builder->getGraphViewer()->rearrange();
		cout << "Deleted road!" << endl;
	} else
		cout << "There is no road between those cities!" << endl;

	cout << "Press enter to continue..." << endl;
	builder->getGraphViewer()->rearrange();
	getchar();
}

void Interface::cluesMenu() {
	int numberOfOptions = 2;
	bool exitMenu = false;

	while(!exitMenu) {

		cout << endl <<
				"--- Clues Menu ---" << endl <<
				"0 - Go back" << endl <<
				"1 - Add a new clue" << endl <<
				"2 - Delete a clue" << endl;

		int option = getOption(numberOfOptions);

		switch(option) {
		case 1:
			addNewClue();
			break;
		case 2:
			deleteExistingClue();
			break;
		case 0:
			exitMenu = true;
			break;
		}
	}
}

void Interface::addNewClue() {
	cout << "- Add clue -" << endl;

	vector<City*> cities = builder->getCities();

	cout << "Choose the city to add the clue" << endl;
	cout << "Press enter to continue..." << endl;
	getchar();
	City* originCity = displayVector(cities);
    
    if (originCity == NULL)
        return;

	cout << "Choose the city the new clue will refer to" << endl;
	cout << "Press enter to continue..." << endl;
	getchar();
	City* destinationCity = displayVector(cities);
    
    if (destinationCity == NULL)
        return;

	if(originCity->addClue(destinationCity))
		cout << "Created clue!" << endl;
	else
		cout << "Failed to create clue, does it already exist? Are you perhaps indicating the same city?" << endl;

	cout << "Press enter to continue..." << endl;
	getchar();
}

void Interface::deleteExistingClue() {
	cout << "- Delete clue -" << endl;

	vector<City*> cities = builder->getCities();

	cout << "Choose the city to delete the clue from" << endl;
	cout << "Press enter to continue..." << endl;
	getchar();
	City* originCity = displayVector(cities);
	if(originCity == NULL)
		return;

	cout << "This city has the following clues" << endl;
	cout << "Press enter to continue..." << endl;
	getchar();
	vector<City*> clues = originCity->getClues();
	City* clue = displayVector(clues);
	if(clue == NULL)
		return;

	while(true) {
		cout << "This clue indicates the following city:" << endl << (*clue) << endl;
		cout << "Delete this clue? (Y/N)" << endl << PROMPT;
		string answer = "";
		getline(cin, answer);
		if(answer.compare("Yes") == 0 || answer.compare("yes") == 0 || answer.compare("Y") == 0 || answer.compare("y") == 0) {
			if(originCity->removeClue(clue))
				cout << "Removed clue to " << clue->getName() << endl;
			else
				cout << "Failed to remove clue" << endl;

			break;
		}
		else if (answer.compare("No") == 0 || answer.compare("no") == 0 || answer.compare("N") == 0 || answer.compare("n") == 0)
			return;

		cout << "Invalid input" << endl;
	}

	cout << "Press enter to continue..." << endl;
	getchar();
}

void Interface::loadMapMenu() {
	cout << "--- Load map ---" << endl;

	string filename;
	cout << "Load a map from which file? (if not found, file must be in the same dir as the program)" << endl << PROMPT;
	getline(cin, filename);

	if(filename.empty())
		cout << "That's not a valid filename..." << endl;
	else {
        resetBuilder(0, 0);
		if ( !builder->loadFromFile(filename) ){
			cout << "File not found! Press enter to continue.."<< endl;
			getchar();
			return;
		}
		vector<City *>::iterator it;
		vector<City*> loadedCities = builder->getCities();
		citiesWithTreasure = 0;
		for (it = loadedCities.begin(); it != loadedCities.end(); ++it) {
			if ( (*it)->hasTreasure ) citiesWithTreasure++;
		}
		numberOfCities = (int)builder->getCities().size();
		builder->getGraphViewer()->rearrange();
		cout << endl << "Loaded map! Press enter to continue" << endl;
		getchar();
	}

}

void Interface::saveMapMenu() {
	cout << "--- Save map ---" << endl;

	string filename;
	cout << "Save map to:" << endl << PROMPT;
	getline(cin, filename);

	if(filename.empty())
		cout << "That's not a valid filename..." << endl;
	else {
		builder->saveToFile(filename);
		cout << endl << "Saved map! Press enter to continue" << endl;
		getchar();
	}
}

Interface::Interface(){
	numberOfCities = 0;
	citiesWithTreasure = 0;
	backtracking = true;
	performanceMode = false;
}

void Interface::init(){

	if(!mainMenu())
		return;

	view = builder->getGraphViewer();
	view->rearrange();

	this->cities = builder->getCities();
	this->roads = builder->getRoads();
	this->treasureHunter = builder->getTreasureHunter();

	director = new Director(treasureHunter, builder->getGraph(), backtracking, performanceMode,cities.size(), roads.size());

	cout << "Press ENTER for each step of the journey!" << endl << endl;

    while ( !director->events.empty() ) {
        cout << director->events.front() << endl;
        director->events.pop();
    }
	mainLoop();
}

void Interface::resetBuilder(int width, int height) {
	delete builder;
    if (width != 0 && height != 0)
        builder = new GraphBuilder(width, height);
    else // default values
        builder = new GraphBuilder();
	numberOfCities = 0;
	citiesWithTreasure = 0;
}

void Interface::mainLoop(){
	while ( !treasureHunter->foundTreasure ) {
		City * nextCity; City * lastCity;

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
		view->setVertexColor(treasureHunter->getLastCity()->getID(), treasureHunter->getLastCity()->getColor());
		while(!director->events.empty()) {
			cout << director->events.front() << endl;
			director->events.pop();
		}
		view->setVertexColor(nextCity->getID(), HUNTER_COLOR);
		view->rearrange();
        
        try {
            director->updatePath();
        } catch (noPathToTake &noPath) {
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
