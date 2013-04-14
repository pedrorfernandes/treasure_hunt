//  city.h
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

#ifndef _CITY_H_
#define _CITY_H_

#include <vector>
#include <string>

using namespace std;

/**
 * The city is a location that the treasure hunter can travel to. It may contain a list of clues to the treasure.
 */
class City {
    string name; /**< The city name. It must be unique */
    vector<City *> clues; /**< A set of clues that indicate cities that might have the treasure */
public:
    bool hasTreasure; /**< Determines if the city has the treasure or not */

    /**
     * Creates a city with no clues
     * @param hasTreasure True if the city has a treasure, false if it's a dead end.
     */
    City(bool hasTreasure);
    
    /**
     * Creates a city with clues to find the treasure.
     * @param hasTreasure True if the city has a treasure.
     */
    City(bool hasTreasure, vector<City *> clues);
    
    /**
     * Checks if two cities are the same.
     * @param c2 The other city to compare to.
     * @return True if the cities have the same name.
     */
    bool operator == (const City &c2) const;
    
    /**
     * Outputs the city name
     * @param out Where the output goes
     * @param c The city to output
     * @return Modified out
     */
	friend ostream & operator << (ostream &os, City &c);
    
};

#endif