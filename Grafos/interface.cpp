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
    
    view = builder->getGraphViewer();
    view->rearrange();
    
}