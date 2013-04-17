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
    view = new GraphViewer(WIDTH, HEIGHT, true);
    view->setBackground(BACKGROUND);
    view->createWindow(WIDTH, HEIGHT);
    view->defineEdgeColor(ROAD_COLOR);
    view->defineVertexColor(CITY_COLOR);
}

GraphViewer * GraphBuilder::getGraphViewer() const{
    return view;
}

bool GraphBuilder::loadFromFile(string &filename){
    
}

bool GraphBuilder::saveToFile(string &filename){
    
}

bool GraphBuilder::addCity(City &city){
    if ( !graph->addVertex(city) ) return false;
    if ( !view->addNode(city.getID()) ) return false;
    view->setVertexLabel( city.getID(), city.getName() );
    return true;
}

bool GraphBuilder::connect(City &city1, City &city2, const double &distance, const bool &isDirected){
    
    Road * road = new Road(&city1, &city2);
    roads.push_back(road);
    if (isDirected){
        if ( !graph->addEdge(city1, city2, distance) ) return false;
        if ( !view->addEdge(road->getID(), city1.getID(), city2.getID(), EdgeType::DIRECTED) ) return false;

    } else {
        if ( !graph->addEdge(city1, city2, distance) ) return false;
        if ( !graph->addEdge(city2, city1, distance) ) return false;
        if ( !view->addEdge(road->getID(), city1.getID(), city2.getID(), EdgeType::UNDIRECTED) ) return false;
    }
    
    view->setEdgeThickness(road->getID(), ROAD_THICKNESS);
    view->setEdgeWeight(road->getID(), (int)distance);
    
    return true;
}

bool GraphBuilder::spawnTreasureHunter(City &city){
    treasureHunter = new TreasureHunter(&city);
    view->setVertexColor(city.getID(), HERO_COLOR);    
    return true;
}

