//  treasureHunter.h
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

#ifndef _TREASURE_HUNTER_H_
#define _TREASURE_HUNTER_H_

#include <vector>
#include <stack>

#include "city.h"

using namespace std;


/**
 * The treasure hunter represents the main "character". He travels from city to city in search for clues to the treasure until he finds it.
 */
class TreasureHunter {
    City * currentCity; /**< The current location of the treasure hunter. */
    stack<City *> stepHistory; /**< The steps given by the treasure hunter until the current location. */
    stack<City *> usedClues; /**< The cities where the treasure hunter used clues. */
    bool foundTreasure; /**< True when the treasure hunter ends his quest. */
    
public:
    /**
     * Treasure Hunter constructor.
     * @param startingCity The city where the hunter starts his quest.
     */
    TreasureHunter(City * startingCity);
    
    /**
     * @return Returns the hunter's current location (city).
     */
    City* getCurrentCity() const;
    
    /**
     * @return Returns the hunter's last location.
     */
    City * getLastCity();

    /**
     * Moves the treasure hunter to his next location.
     * Marks the clue in the previous city as read.
     * If the city has the treasure, the hunter has found it.
     * @param nextCity The city where the hunter travels next.
     * @return Void
     */
    void moveTo(City * nextCity);

    /**
     * Moves the treasure hunter back to the previous city.
     */
    void stepBack();

    /**
     * The clues represent possible cities for the treasure hunter to travel to.
     * Returns all the clues in the treasure hunter's current location.
     * If there are no clues in the current city, returns an empty vector.
     * @return A vector containing all possible cities the hunter should visit.
     */
    vector<City *> getClues();

    /**
     * If the treasure hunter's current city has available clues, adds it to the used clues vector
     * and returns a vector with those clues.
     * @return A vector containing the cities the treasure hunter should visit.
     */
    vector<City *> readClues();

    /**
     * Removes the last city from where clues were read and returns it.
     * @return The last city where clues were read from by the treasure hunter, NULL if its already at the beggining.
     */
    City* getReturnCity();


};

#endif 
