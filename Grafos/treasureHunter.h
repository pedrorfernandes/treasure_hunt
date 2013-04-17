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

using namespace std;

class City;

/**
 * The treasure hunter represents the main "character". He travels from city to city in search for clues to the treasure until he finds it.
 */
class TreasureHunter {
    City * currentCity; /**< The current location of the treasure hunter. */
    stack<City *> usedClues; /**< The last current location of the treasure hunter. */
    bool foundTreasure; /**< True when the treasure hunter ends his quest. */
    
public:
    /**
     * Treasure Hunter constructor.
     * @param startingCity The city where the hunter starts his quest.
     */
    TreasureHunter(City * startingCity);
    
    /**
     * Moves the hero to his next location.
     * Marks the clue in the previous city as read.
     * If the city has the treasure, the hunter has found it.
     * @param nextCity The city where the hunter travels next.
     * @return Void
     */
    void moveTo(City * nextCity);

    /**
     * Gathers all the possible steps the hero can travel to.
     * These steps are the current city clues.
     * If there are no clues in the current city, returns an empty vector.
     * @return A vector containing all possible cities the hunter should visit.
     */
    vector<City *> getNextSteps();

};

#endif 
