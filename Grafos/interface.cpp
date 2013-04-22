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

Interface::Interface(){
	builder = new GraphBuilder();
}

void Interface::init(){
	// basic tests
    /*
	string filename = "map.txt";
	builder->loadFromFile(filename);
     */
    
    builder->createGraph(1000, 1000, 1000);
    string save = "teste.txt";
	builder->saveToFile(save);

	view = builder->getGraphViewer();
	view->rearrange();

	this->cities = builder->getCities();
	this->roads = builder->getRoads();
	this->treasureHunter = builder->getTreasureHunter();

	director = new Director(treasureHunter, builder->getGraph(), true);

    cout << "Press enter for each step of the journey!" << endl;
	cin.get();
	mainLoop();
}

void Interface::mainLoop(){
	while ( !treasureHunter->foundTreasure ) {
		City * nextCity;
		City * destination;
		if ( director->nextStep() == NULL ){
            while ( !director->events.empty() ) {
                cout << director->events.front() << endl;
                director->events.pop();
            }
            return;
        }
		nextCity = treasureHunter->getCurrentCity();
		destination = treasureHunter->getDestination();
		view->setVertexColor(treasureHunter->getLastCity()->getID(), CITY_COLOR);
		while(!director->events.empty()) {
            while ( !director->events.empty() ) {
                cout << director->events.front() << endl;
                director->events.pop();
            }
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
		cin.get();
	}

	cout << "The hero found the treasure! Hurrah!" << endl;
	return;
}
