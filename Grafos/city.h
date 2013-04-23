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
#include <iostream>

#define CITY_COLOR "red"
#define TREASURE_COLOR "green"

using namespace std;

/**
 * The city is a location that the treasure hunter can travel to. It may contain a list of clues to the treasure.
 */
class City {
	string name; /**< The city name. It must be unique.*/
	vector<City *> clues; /**< A set of clues that indicate cities that might have the treasure */
	int identifier; /**< The city ID */
	static int numberOfCities; /**< The total number of cities */
    int x; /**< The X coordinates of the city. */
    int y; /**< The Y coordinates of the city. */
    string color; /**< The city color for display. */
public:
	/**
	 * Creates a new city with no treasure.
     * @param name The city name.
     * @param x The X coordinates of the new city.
     * @param y The Y coordinates of the new city.
	 */
	City(string name, int x, int y);

	/**
	 * @return Returns the city's name
	 */
	string getName() const;

	/**
	 * @return Returns the city's unused clues
	 */
	vector<City *> getClues() const;

	/**
	 * Sets clues to other cities.
	 * @param The new set of clues.
	 */
	void setClues(vector<City *> clues);
    
    /**
     * Adds a clue to the city.
     * @param clue The new clue.
     * @return True if the clue was added. False if it already exists.
     */
    bool addClue(City * clue);

	/**
	 * @return Returns the city identifier.
	 */
	int getID() const;
    
    /**
     * @return The X coordinates of the city.
     */
    int getX() const;
    
    /**
     * @return The Y coordinates of the city.
     */
    int getY() const;
    
    /**
     * @return The color of the city.
     */
    string getColor() const;

	const bool hasTreasure; /**< Determines if the city has the treasure or not */

	/**
	 * Creates a city with no clues
	 * @param name The city name.
	 * @param hasTreasure True if the city has a treasure, false if it's a dead end.
     * @param x The X coordinates of the new city.
     * @param y The Y coordinates of the new city.
	 */
	City(string name, const bool hasTreasure, int x, int y);

	/**
	 * Creates a city with clues to find the treasure.
	 * @param name The city name.
	 * @param hasTreasure True if the city has a treasure.
	 * @param clues The clues to possible treasure locations.
     * @param x The X coordinates of the new city.
     * @param y The Y coordinates of the new city.
	 */
	City(string name, const bool hasTreasure, vector<City *> clues, int x, int y);

	/**
	 * Removes a given clue from a city
	 * @param city The clue to be removed
	 * @return True if the clue was removed, false if it doesn't exist.
	 */
	bool removeClue(City * city);

	/**
	 * Checks if two cities are the same.
	 * @param c2 The other city for comparison.
	 * @return True if the cities have the same name.
	 */
	bool operator == (const City *c2) const;

	/**
	 * Checks if two cities are different.
	 * @param c2 The other city for comparison.
	 * @return True if the cities have different names.
	 */
	bool operator != (const City *c2) const;

	/**
	 * Outputs the city name, position and if it has treasure.
	 * @param out Where the output goes
	 * @param c The city to output
	 * @return Modified out
	 */
	friend ostream & operator << (ostream &out, City &c);

};

#endif
