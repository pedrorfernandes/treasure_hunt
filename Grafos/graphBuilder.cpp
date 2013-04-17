//  builder.cpp
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

#include "graphBuilder.h"

GraphBuilder::GraphBuilder() {
    graph = new Graph<City *>();
    graphView = new GraphViewer(600, 600, true);
}

bool GraphBuilder::loadFromFile(string &filename){
    
}

bool GraphBuilder::saveToFile(string &filename){
    
}

bool GraphBuilder::addCity(City * city){
    graph->addVertex(city);
    return true;
}

