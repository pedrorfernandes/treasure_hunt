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
    
    builder->createGraph(100, 2500, 10);
    string save = "teste.txt";
	builder->saveToFile(save);

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
