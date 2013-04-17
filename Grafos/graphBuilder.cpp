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
    graph = new Graph<City>();
    graphView = new GraphViewer(600, 600, true);
}

bool GraphBuilder::loadFromFile(string &filename){
    
}

bool GraphBuilder::saveToFile(string &filename){
    
}

bool GraphBuilder::addCity(City &city){
    graph->addVertex(city);
    graphView->addNode(city.getID());
    graphView->setVertexColor(city.getID(), CITY_COLOR);
    return true;
}

bool GraphBuilder::connect(City &city1, City &city2, const double &distance, const bool &isDirected){
    if (isDirected){
        graph->addEdge(city1, city2, distance);
        Road * road = new Road(&city1, &city2);
        roads.push_back(road);
        graphView->addEdge(road->getID(), city1.getID(), city2.getID(), EdgeType::DIRECTED);
        //graphView->setEdgeLabel(road->getID(), "");
        graphView->setEdgeColor(road->getID(), ROAD_COLOR);
        //graphView->setEdgeThickness(road->getID(), 5);
    }
    return true;
}

bool spawnTreasureHunter(City &city){
    // new treasurehunter
}

