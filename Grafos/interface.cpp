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
    
    City c1("Porto");
    City c2("Lisboa");
    City c3("Coimbra");
    builder->addCity(c1);
    builder->addCity(c2);
    builder->addCity(c3);
    builder->connect(c1, c3, 10, false);
    builder->connect(c3, c2, 300, false);
    builder->spawnTreasureHunter(c1);
     /*
    string filename = "map.txt";
    builder->loadFromFile(filename);
    */
    view = builder->getGraphViewer();
    view->rearrange();
    
}