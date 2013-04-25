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

GraphBuilder::GraphBuilder(int width, int height) {
    graph = new Graph<City *>();
    view = new GraphViewer(width, height, false);
    this->width = width;
    this->height = height;
    view->setBackground(BACKGROUND);
    view->createWindow(width, height);
    view->defineEdgeColor(ROAD_COLOR);
    view->defineVertexColor(CITY_COLOR);
    treasureHunter = NULL;
}

GraphBuilder::~GraphBuilder() {
    for (int i = 0; i < cities.size(); ++i) {
        //graph->removeVertex(cities.at(i));
        //view->removeNode(cities.at(i)->getID());
        delete cities.at(i);
    }
    view->closeWindow();
    delete graph; delete view; delete treasureHunter;
    for (int i = 0; i < roads.size(); ++i) {
        delete roads.at(i);
    }
    return;
}

GraphViewer * GraphBuilder::getGraphViewer() const{
    return view;
}

Graph<City *> * GraphBuilder::getGraph() const{
    return graph;
}

TreasureHunter * GraphBuilder::getTreasureHunter() const{
    return treasureHunter;
}

vector<Road *> GraphBuilder::getRoads() const{
    return roads;
}

vector<City *> GraphBuilder::getCities() const{
    return cities;
}

City * GraphBuilder::getCity(const string &cityName) const{
    vector<City *>::const_iterator it;
    for(it = cities.begin() ; it != cities.end(); ++it){
        if ( (*it)->getName() == cityName)
            return (*it);
    }
    return NULL;
}

inline double GraphBuilder::getDistance(City * city1, City * city2){
    int x1 = city1->getX(); int x2 = city2->getX();
    int y1 = city1->getY(); int y2 = city2->getY();
    return sqrt(abs( (x2-x1)*(x2-x1) ) + abs( (y2-y1)*(y2-y1) ) );
}

bool GraphBuilder::loadFromFile(const string &filename){
    ifstream file;
    file.open(filename.c_str());
    
    if (!file.is_open())
        return false;
    
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
                int x, y; string xStr, yStr;
                getline(iss, cityName, SEPARATOR);
                getline(iss, treasure, SEPARATOR);
                if (treasure == "1") hasTreasure = true;
                getline(iss, xStr, SEPARATOR);
                getline(iss, yStr, SEPARATOR);
                x = atoi(xStr.c_str());
                y = atoi(yStr.c_str());
                addCity(cityName, hasTreasure, x, y);
            }
            
            if( object == ROAD )
            {
                string city1Name; string city2Name;
                City * city1; City * city2;
                string directed; bool isDirected = false;
                getline(iss, city1Name, SEPARATOR);
                getline(iss, city2Name, SEPARATOR);
                getline(iss, directed, SEPARATOR);
                city1 = getCity(city1Name);
                city2 = getCity(city2Name);
                if (directed == "1") isDirected = true;
                if (city1 != NULL && city2 != NULL) {
                    connect(city1, city2, isDirected);
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
                if (city != NULL)
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
        file << noboolalpha << (*cityItr)->hasTreasure << SEPARATOR;
        file << (*cityItr)->getX() << SEPARATOR;
        file << (*cityItr)->getY() << endl;
    }
    for (roadItr = roads.begin(); roadItr != roads.end(); ++roadItr) {
        file << ROAD << EQUALS << (*roadItr)->getCity1()->getName() << SEPARATOR;
        file << (*roadItr)->getCity2()->getName() << SEPARATOR;
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

bool GraphBuilder::addCity(const string &cityName, const bool &hasTreasure, const int &x, const int &y){
    City * city = new City(cityName, hasTreasure, x, y);
    
    // check if there is an existing x and y coords
    vector<City *>::iterator cityItr;
    for (cityItr = cities.begin(); cityItr != cities.end(); ++cityItr) {
        if ( (*cityItr)->getX() == x && (*cityItr)->getY() == y )
            return false;
    }
    
    if ( !graph->addVertex(city) ) return false;
    if ( !view->addNode(city->getID(), city->getX(), city->getY()) ) return false;
    cities.push_back(city);
    view->setVertexLabel( city->getID(), city->getName() );
    if (city->hasTreasure) view->setVertexColor(city->getID(), TREASURE_COLOR);
    return true;
}

bool GraphBuilder::deleteCity(City* city) {
    vector<City *>::iterator it;
    City * found = NULL;
    for(it = cities.begin() ; it != cities.end(); ++it){
        if ( (*(*it)) == city){
            found = (*it);
            cities.erase(it);
            break;
        }
    }
    
    if (found == NULL) return false;
    
    if ( !graph->removeVertex(found) ) return false;
    if ( !view->removeNode(found->getID()) ) return false;
    vector<Road *> toDestroy = getConnectedRoads(found);
    for (int i = 0; i < toDestroy.size(); ++i) {
        delete toDestroy.at(i);
    }

    for(it = cities.begin() ; it != cities.end(); ++it){
        (*it)->removeClue(found);
    }
    
    delete found;
    return true;
}

bool GraphBuilder::connect(City * city1, City * city2, const bool &isDirected){

    double distance = getDistance(city1, city2);
    if ( roadExists(city1, city2) != NULL ) {
        return false;
    }
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
    if (treasureHunter != NULL){
        view->setVertexColor(treasureHunter->getCurrentCity()->getID(), CITY_COLOR);
        delete treasureHunter;
    }
    treasureHunter = new TreasureHunter(city);
    view->setVertexColor(city->getID(), HUNTER_COLOR);
    return true;
}

Road * GraphBuilder::roadExists(City * city1, City* city2){
    vector<Road *>::iterator roadItr;
    for (roadItr = roads.begin(); roadItr != roads.end(); ++roadItr) {
        // comparing ints is obviously way better than comparing strings!
        if ( ( (*roadItr)->getCity1()->getID() == city1->getID() && (*roadItr)->getCity2()->getID() == city2->getID() )
          || ( (*roadItr)->getCity2()->getID() == city1->getID() && (*roadItr)->getCity1()->getID() == city2->getID() ) ){
            return (*roadItr);
        }
    }
    return NULL;
}

bool compare (pair<City*, double> i, pair<City*, double> j) {
    return (i.second < j.second);
}

void GraphBuilder::createGraph(const unsigned int &numberOfCities, const unsigned int &numberOfRoads, const unsigned int &minNumberOfClues){
    // create a vector containing all possible x and y coordinates avaiable
    vector<int> x; vector<int> y;
    while (x.size() < numberOfCities) {
        for (int i = VERTEX_SIZE; i < width-VERTEX_SIZE; i+=INTERVAL) {
            x.push_back(i);
        }
        for (int j = VERTEX_SIZE; j < height-VERTEX_SIZE; j+=INTERVAL) {
            y.push_back(j);
        }
    }

    // shuffle those coordinates
    srand((unsigned)time(0));
    random_shuffle(x.begin(), x.end());
    random_shuffle(y.begin(), y.end());
    
    int maxInWidth = (int) x.size();
    int maxInHeight = (int) y.size();
    int max = numberOfCities;
    if (maxInHeight < max)
        max = maxInHeight;
    if (maxInWidth < max)
        max = maxInWidth;
    
    City * treasure;
    City * hunter;
    // from the shuffled coordinates, pick the first options and create cities
    for (int i = 0; i < max; ++i) {
        char numberStr[100];
        sprintf(numberStr, "%d", i);
        if (i == 1){
            while ( !addCity(string(numberStr), true, x.at(i), y.at(i)) ){
                x.at(i) = rand() % (width-VERTEX_SIZE);
                y.at(i) = rand() % (height-VERTEX_SIZE);
            }
            treasure = getCity(string(numberStr));
        }
        else {
            while ( !addCity(string(numberStr), false, x.at(i), y.at(i)) ){
                x.at(i) = rand() % (width-VERTEX_SIZE);
                y.at(i) = rand() % (height-VERTEX_SIZE);
            }
        }
        if (i == 0){
            spawnTreasureHunter( getCity(string(numberStr)) );
            hunter = treasureHunter->getCurrentCity();
        }
    }
    
    max = (int)cities.size();
    // now for creating roads
    unsigned int createdRoads = 0;
    vector<City *>::iterator cityItr;
    vector<City *>::iterator neighbourItr;
    int roadsPerCity = numberOfRoads/numberOfCities;
    int roadsLeft = numberOfRoads % numberOfCities;
    for (cityItr = cities.begin(); cityItr != cities.end(); ++cityItr) {
        
        vector<City *> possibleConnections;
        if (roadsPerCity == 1 && roadsLeft == 0){
            // in each city, calculate distance to every unreachable city
            possibleConnections = graph->getUnconnectedEdges(*cityItr);
            if (possibleConnections.size() == 1)
                possibleConnections = cities;
        } else
            // in each city, calculate distance to every other city
            possibleConnections = cities;
        
        vector<pair<City*, double> > distances;
        for (neighbourItr = possibleConnections.begin(); neighbourItr != possibleConnections.end(); ++neighbourItr) {
            double dist = getDistance((*cityItr), (*neighbourItr));
            if (dist != 0)
                distances.push_back(pair<City*, double>((*neighbourItr), dist) );
        }
 
        if (distances.size() == 0)
            continue;
        
        // sort the distances so we can get the closest cities first
        sort(distances.begin(), distances.end(), compare);
        
        unsigned int i = 0;
        unsigned int counter = roadsPerCity;
        if (roadsLeft > 0){
            counter++; roadsLeft--;
        }
        while (counter > 0 && createdRoads < numberOfRoads) {
            if (i >= distances.size() ){
                break;
            }
            
            if (connect(*cityItr, distances.at(i).first, false) ){
                counter--;
            }
            i++;
        }
    }
    
    // to generate the clues we must create a trail for the hunter
    unsigned int cluesGenerated = 0;
    // distances don't matter, the more the hunter moves, the better
    graph->unweightedShortestPath(hunter);
    vector<City*> trail = graph->getPath(hunter, treasure);
    int treasureLocation = treasure->getID();

    // add an extra random clue to the begining
    int randomStart = rand() % max;
    hunter->addClue(cities.at(randomStart) );
    
    for (unsigned int i = 1; i < trail.size(); ++i) {
        int random1 = rand() % max;
        int random2 = rand() % max;
        while (random2 == treasureLocation )
            random2 = rand() % max;
        // we put a clue from A to B and B to C and C to D
        // A and D belong to the trail, B and C are random
        trail.at(i-1)->addClue(cities.at(random1) );
        cities.at(random1)->addClue(cities.at(random2));
        cities.at(random2)->addClue(trail.at(i) );
        cluesGenerated+=2;
    }
    
    // the city containing the treasure must point clue to itself
    (* (trail.end()-1) )->addClue(* (trail.end()-1) );
    
    while (cluesGenerated < minNumberOfClues) {
        int random1 = rand() % max;
        int random2 = rand() % max;
        // there shall only be one clue pointing to the treasure
        while (random2 == treasureLocation )
            random2 = rand() % max;
        if ( cities.at(random1)->addClue(cities.at(random2)) )
            cluesGenerated++;
    }
    
}

vector<Road *> GraphBuilder::getConnectedRoads(City * city1){
    vector<Road *> connected;
    vector<Road *>::iterator roadItr;
    for (roadItr = roads.begin(); roadItr != roads.end(); ++roadItr) {
        if ( (*roadItr)->getCity1()->getID() == city1->getID() ||
            (*roadItr)->getCity2()->getID() == city1->getID() )
            connected.push_back(*roadItr);
    }
    return connected;
}

bool GraphBuilder::deleteRoad(City * city1, City * city2){
    Road * road = roadExists(city1, city2);
    if (road == NULL) return false;
    graph->removeEdge(city1, city2);
    graph->removeEdge(city2, city1);
    view->removeEdge(road->getID());
    vector<Road *>::iterator it;
    for (it = roads.begin(); it != roads.end(); ++it) {
        if (road->getID() == (*it)->getID()){
            roads.erase(it);
            break;
        }
    }
    delete road;
    return true;
}

