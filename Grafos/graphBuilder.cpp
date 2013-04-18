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
    view = new GraphViewer(WIDTH, HEIGHT, true);
    view->setBackground(BACKGROUND);
    view->createWindow(WIDTH, HEIGHT);
    view->defineEdgeColor(ROAD_COLOR);
    view->defineVertexColor(CITY_COLOR);
}

GraphViewer * GraphBuilder::getGraphViewer() const{
    return view;
}

City * GraphBuilder::getCity(const string cityName) const{
    vector<City *>::const_iterator it;
    for(it = cities.begin() ; it != cities.end(); ++it){
        if ( (*it)->getName() == cityName)
            return (*it);
    }
    return NULL;
}

bool GraphBuilder::loadFromFile(const string &filename){
    ifstream file;
    file.open(filename.c_str());
    string line;
    
    while( getline( file, line ) )
    {
        istringstream iss(line);
        string object;
        if( getline(iss, object, EQUALS) )
        {
            if( object == CITY )
            {
                string cityName; string treasure;
                bool hasTreasure = false;
                getline(iss, cityName, SEPARATOR);
                getline(iss, treasure, SEPARATOR);
                if (treasure == "1") hasTreasure = true;
                addCity(cityName, hasTreasure);
            }
            
            if( object == ROAD )
            {
                string city1Name; string city2Name;
                City * city1; City * city2;
                string distance;
                string directed; bool isDirected = false;
                getline(iss, city1Name, SEPARATOR);
                getline(iss, city2Name, SEPARATOR);
                getline(iss, distance, SEPARATOR);
                getline(iss, directed, SEPARATOR);
                city1 = getCity(city1Name);
                city2 = getCity(city2Name);
                if (directed == "1") isDirected = true;
                if (city1 != NULL & city2 != NULL) {
                    connect(city1, city2, atof(distance.c_str()), isDirected);
                }
            }
            
            if( object == CLUE )
            {
                string cityName; City * city;
                string clueName; City * clue; vector<City *> clues;
                getline(iss, cityName, SEPARATOR);
                city = getCity(cityName);
                if (city != NULL){
                    while (getline(iss, clueName, SEPARATOR) ) {
                        clue = getCity(clueName);
                        if (clue != NULL) clues.push_back(clue);
                    }
                    city->setClues(clues);
                }
            }
            
            if (object == HUNTER )
            {
                string cityName; City * city;
                getline(iss, cityName, SEPARATOR);
                city = getCity(cityName);
                spawnTreasureHunter(city);
            }
        }
    }
    return true;
}

bool GraphBuilder::saveToFile(const string &filename){
    ofstream file;
    file.open(filename.c_str(), fstream::trunc);
    vector<City *>::iterator cityItr;
    vector<Road *>::iterator roadItr;
    for (cityItr = cities.begin(); cityItr != cities.end(); ++cityItr) {
        file << CITY << EQUALS << (*cityItr)->getName() << SEPARATOR;
        file << noboolalpha << (*cityItr)->hasTreasure << endl;
    }
    for (roadItr = roads.begin(); roadItr != roads.end(); ++roadItr) {
        file << ROAD << EQUALS << (*roadItr)->getCity1()->getName() << SEPARATOR;
        file << (*roadItr)->getCity2()->getName() << SEPARATOR;
        file << setprecision(PRECISION) << (*roadItr)->getDistance() << SEPARATOR;
        file << noboolalpha << (*roadItr)->isDirected << endl;
    }
    for (cityItr = cities.begin(); cityItr != cities.end(); ++cityItr) {
        if ( (*cityItr)->getClues().size() != 0 ){
            file << CLUE << EQUALS << (*cityItr)->getName() << SEPARATOR;
            vector<City *> clues = (*cityItr)->getClues();
            vector<City *>::iterator clueItr = clues.begin();
            while (clueItr != clues.end()) {
                file << (*clueItr)->getName();
                ++clueItr;
                if (clueItr != clues.end() )
                    file << SEPARATOR;
            }
            file << endl;
        }
    }
    file << HUNTER << EQUALS << treasureHunter->getCurrentCity()->getName() << endl;
    return true;
}

bool GraphBuilder::addCity(string cityName, bool hasTreasure){
    City * city = new City(cityName, hasTreasure);
    if ( !graph->addVertex(city) ) return false;
    if ( !view->addNode(city->getID()) ) return false;
    cities.push_back(city);
    view->setVertexLabel( city->getID(), city->getName() );
    return true;
}

bool GraphBuilder::connect(City * city1, City * city2, const double &distance, const bool &isDirected){
    
    Road * road = new Road(city1, city2, distance, isDirected);
    if (isDirected){
        if ( !graph->addEdge(city1, city2, distance) ) return false;
        if ( !view->addEdge(road->getID(), city1->getID(), city2->getID(), EdgeType::DIRECTED) ) return false;

    } else {
        if ( !graph->addEdge(city1, city2, distance) ) return false;
        if ( !graph->addEdge(city2, city1, distance) ) return false;
        if ( !view->addEdge(road->getID(), city1->getID(), city2->getID(), EdgeType::UNDIRECTED) ) return false;
    }
    
    roads.push_back(road);
    view->setEdgeThickness(road->getID(), ROAD_THICKNESS);
    view->setEdgeWeight(road->getID(), (int)distance);
    
    return true;
}

bool GraphBuilder::spawnTreasureHunter(City * city){
    treasureHunter = new TreasureHunter(city);
    view->setVertexColor(city->getID(), HERO_COLOR);
    return true;
}

