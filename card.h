/*
 * Name: Vaughan Ingram
 * card.h
 * Sushi Go
 * 4/21/24
 * Defines card class for a card in Sushigo!, handling card attricubes
 */

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include "termfuncs.h"
#include <string>

using namespace std;

class Card {
public:
    //constructor
    Card(string type, int count);

    //getters
    int getMakiCount();
    string getSushiType();

    //destructor
    ~Card();
private:
    string sushiType;
    int makiCount;
};

#endif 
