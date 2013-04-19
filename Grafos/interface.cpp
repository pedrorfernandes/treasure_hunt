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
    string filename = "map.txt";
    builder->loadFromFile(filename);
    
    string save = "teste.txt";
    builder->saveToFile(save);
    
    view = builder->getGraphViewer();
    //view->rearrange();
    
    this->cities = builder->getCities();
    this->roads = builder->getRoads();
    this->treasureHunter = builder->getTreasureHunter();
    
    director = new Director(treasureHunter, builder->getGraph(), true);
    
    getchar();
    mainLoop();
}

void Interface::mainLoop(){
    while ( !treasureHunter->foundTreasure ) {
        City * nextCity;
        City * destination;
        director->nextStep();
        nextCity = treasureHunter->getCurrentCity();
        destination = treasureHunter->getDestination();
        view->setVertexColor(treasureHunter->getLastCity()->getID(), CITY_COLOR);
        cout << "The hunter is headed to " << destination->getName() << "!" <<  endl;
        cout << "Hunter moved to " << nextCity->getName() << endl;
        view->setVertexColor(nextCity->getID(), HUNTER_COLOR);
        view->rearrange();
        if (! director->updatePath() ){
            cout << "No path to take! Quest over." << endl;
            return;
        }
        getchar();
    }
    cout << "The hero found the treasure! Hurrah!" << endl;
    return;
}