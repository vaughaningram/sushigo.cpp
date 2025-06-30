/*
 * Vaughan Ingram
 * game.h
 * Sushi Go
 * 4/21/24
 * Defines the game class in Sushigo! and defines useful gameplay functions
 */

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include <string>
#include "termfuncs.h"
#include "board.h"
#include "vector.h"
using namespace std;

class Game{
    public:
        //constructor/destructor
        Game(string filename, string play_chopsticks);
        ~Game();

        //main gameplay
        void playGame();
        void dealCards();
        void getMakiScore();
        void setChoiceCard();
        void passDeck(int loop);
        void revealCards();
        void selectCard(int loop);
        void updatePudding();
        void updateScores();
        void scorePudding();
        void findWinner();
        void completeChopsticks(int selection, int player);
        void replaceChopstick(int loop, int player, int index);
        void boolean1Reset();
        void boolean2Reset();
        void checkChopsticks(Card *selectedCard, 
                            int player, int index, int loop);
        int tieBreak(); 
        void resetRound();
        void countOfCards();
        void doChopsticks(int loop, int player, int index);

        int tieX; 
        int tieX2;



    private:
        //constants
        static const int PLAYER_COUNT = 3;
        static const int ROUNDS = 3;
        static const int CARD_HAND = 9;
        Card* tempCards[PLAYER_COUNT]; 

        //chopsticks activated true/false
        bool play_chopsticks;

        //card deck
        Vector deck;

        //game objects
        Board board;
        Player players[PLAYER_COUNT];
};

#endif
