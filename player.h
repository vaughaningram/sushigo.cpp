/*
 * Name: Vaughan Ingram
 * player.h
 * Sushi Go
 * Defines the class for player in Sushigo!, managing game attributes
 */
 
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "termfuncs.h"
#include "vector.h"
#include "card.h" 
#include <iostream>

using namespace std;

class Player {
public:
    // Constructor
    Player();

    // Destructor
    ~Player();

    // Getters
    int getPuddingCount();  
    int getScore();
    int getPassingHandSize();  
    Vector *getPassingHand();
    Vector *getRevealedCards();
    int getLastSelectedIndex();
    Card *getChopstick();
    Card *getChoiceCard();

    // Setters
    void setPassingHand(Vector* newHand);
    void setLastSelectedIndex(int index);
    void setChopstick(Card* selectedCard);
    void setChoiceCard(Card *selectedCard);

    // Modifiers
    void addToPassingHand(Card* card);
    void addToRevealedCards(Card* card);
    void handsClear();
    Card* takeCardFromPassingHand(int index);

    // Gameplay Mechanics
    void increasePudding();
    void boolean1Reset();
    void boolean2Reset();
    void resetRound();
    void updateScore(int amount);

    // Attributes
    int chopsticks;
    int maki;
    int tempura; 
    int sashimi;
    int dumpling;
    int wasabi;
    int nigiri;
    bool booleanX;
    bool booleanY;
    int tieX;
    int tieX2;

private:
    int score;
    int pudding;
    Vector *passing;
    Vector *revealed;
    int lastSelectedIndex = -1;
    Card *chopstick;
    Card *choiceCard;
};

#endif
