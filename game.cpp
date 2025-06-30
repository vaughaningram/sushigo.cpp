/*
* Vaughan Ingram
* game.cpp
* Sushi Go
* This program implements the card game Sushi Go! where players draw, pass,
* and reveal sushi cards to score points based on sets and combinations.
* 4/21/24
*/

#include "game.h"
#include "vector.h"
#include "board.h"
#include "card.h"

/*
* Game::Game
* Input: filename, play_chopsticks
* Description: constructs the game instance by loading cards from a file
* Output: none
*/
Game::Game(string filename, string play_chopsticks) {
    // Include chopsticks or not
    this->play_chopsticks = (play_chopsticks == "true");

    ifstream infile(filename); 
    if (infile.fail()) { // make sure file opens 
        cerr << "Failed to open deck file: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    string inputType; // stores type of sushi
    int inputCount; // stores amount of sushi
    // read each card's type from file 
    while (infile >> inputType) {
        inputCount = 0;  
        if (inputType == "Maki"){
            infile >> inputCount;
        }
        if (this->play_chopsticks || inputType != "Chopsticks") {
            Card *makeCard = new Card(inputType, inputCount); 
            deck.push_back(makeCard); 
            //adds card to deck
        }
    }
    infile.close();
}

/*
* Game::dealCards
* Input: none
* Description: deals cards from the main deck to each player's passing hand
* Output: none
*/
void Game::dealCards() {
    // iterate number of cards that are to be dealt to each player
    for (int card = 0; card < CARD_HAND; card++) {
        for (int player = 0; player < PLAYER_COUNT; player++) {
            // deal last card in deck to current player
            Card *temporaryCard = deck.back(); // access card
            players[player].getPassingHand()->push_back(temporaryCard);
            deck.pop_back(); //remove card from deck
        }
    }
}


/*
* Game::passDeck
* Input: loop - loop count of current card passing
* Description: passes cards between players circularly 
* Output: none
*/
void Game::passDeck(int loop) {
    Vector tempCardStorage;  // temp storage for cards before reveal
    // loop through the cards to be passed this loop
    for (int i = 0; i < (CARD_HAND - 1) - loop; i++) {
        // store the current card from player 0 hand
        tempCardStorage.push_back(players[0].getPassingHand()->at(i));
        // remove current card from player 0 hand
        players[0].getPassingHand()->erase(i);
        // get the card from player 2, give to player 0
        players[0].getPassingHand()->insert(i, 
        players[2].getPassingHand()->at(i));

        // remove the card from player 2 hand, which player 0 just took
        players[2].getPassingHand()->erase(i);
        // get the card from player 1, give to player 2
        players[2].getPassingHand()->insert(i, 
        players[1].getPassingHand()->at(i));

        // give player 1 the card that was originally in player 0 hand
        players[1].getPassingHand()->erase(i);
        players[1].getPassingHand()->insert(i, tempCardStorage.at(i));
    }
}

/*
* Game::selectCard
* Input: loop
* Description: handles card selection, stores until revealed, validates input,
* applies chopstick rule if used
* Output: none
*/
void Game::selectCard(int loop) {
    int card_index;
    for (int player = 0; player < PLAYER_COUNT; player++) {
        board.drawBoard(players, player);
        cout << " Player " << player + 1 << ", select a card: ";
        cin >> card_index; // prompt and store user for card selection
        if(!cin){ //check for invalid input
            cerr << " INVALID INPUT: No game for you!\n";
            exit(EXIT_FAILURE);
        }
        while (card_index < 1 || card_index > loop) { // if card out of bounds
            cout << "     Please enter a valid number between 1 and " 
            << loop << ": ";
            cin >> card_index; }
        int adjustedIndex = (card_index -1);
        Card* selectedCard = 
                        players[player].getPassingHand()->at(adjustedIndex);
        players[player].setChoiceCard(selectedCard); // direct access
        if (loop > 1 && play_chopsticks){
            checkChopsticks(selectedCard, player, card_index, loop);
        } // if chopsticks is selected
        players[player].getPassingHand()->erase(adjustedIndex);
    }
    for (int player = 0; player < PLAYER_COUNT; ++player) { //revealing cards
        Card* mainCard   = players[player].getChoiceCard();
        players[player].getRevealedCards()->push_back(mainCard);
        Card* chopstickCard = players[player].getChopstick();
        if (chopstickCard != nullptr) {  //check for additional chopstick card
            players[player].getRevealedCards()->push_back(chopstickCard);
            players[player].setChopstick(nullptr);
        }
    }
}

/*
* Game::boolean1Reset
* Input: none
* Description: resets the boolean1 flag for all players
* Output: none
*/
void Game::boolean1Reset() {
    // iterate through each player and reset boolean1
    int i = 0;
    while (i < PLAYER_COUNT) {
        players[i].boolean1Reset();
        i++;
    }
}

/*
* Game::boolean2Reset
* Input: none
* Description: resets the boolean2 flag for all players
* Output: none
*/
void Game::boolean2Reset() {
    // iterate through each player and reset boolean2
    int i = 0;
    while (i < PLAYER_COUNT) {
        players[i].boolean2Reset();
        i++;
    }
}

/*
* countOfCards
* Input: none
* Description: calculates and updates players' scores based on cards
* Output: none
*/
void Game::countOfCards() {
    for (int player = 0; player < PLAYER_COUNT; player++) { 
        for (int cardIndex = 0; cardIndex < CARD_HAND; cardIndex++) {
            Card* currentCard = 
            players[player].getRevealedCards()->at(cardIndex);
            const std::string& type = currentCard->getSushiType();
            int length = type.length(); // length of sushi type string 
            // functions for each type of sushi card
            auto applyMaki = [&]() { players[player].maki += 
            currentCard->getMakiCount(); };
            auto applyTempura = [&]() { players[player].tempura++; };
            auto applySashimi = [&]() { players[player].sashimi++; };
            auto applyDumpling = [&]() { players[player].dumpling++; };
            auto applyWasabi = [&]() { players[player].wasabi++; };
            auto applyPudding = [&]() { players[player].increasePudding(); };
            auto applyNigiri = [&]() {
                int multiplier = (players[player].wasabi > 0 ? 3 : 1); 
                players[player].nigiri += 
                (length == 13 ? 2 : length == 12 ? 3 : 1) * multiplier;
                if (players[player].wasabi > 0) players[player].wasabi--;
            }; // multipliers for wasabi
            if (type == "Maki") applyMaki();
            else if (type == "Tempura") applyTempura();
            else if (type == "Sashimi") applySashimi();
            else if (type == "Dumpling") applyDumpling();
            else if (type == "Wasabi") applyWasabi();
            else if (type == "Pudding") applyPudding();
            else if (length > 8 && type != "Chopsticks") applyNigiri();
        } // apply the approptiate scoring based on type of sushi
    }
}

/*
* Game::resetRound
* Input: none
* Description: resets each player's game state
* Output: none
*/
void Game::resetRound() {
    // iterate through each player to reset their game state 
    for (int player = 0; player < PLAYER_COUNT; player++) {
        Vector* revealedCards = players[player].getRevealedCards();
        // clear the revealed cards for each player
        while (!revealedCards->empty()) {
            delete revealedCards->back();
            revealedCards->pop_back();
        }
        // reset round settings for each player
        players[player].resetRound();

        // initialize tie counters for the round
        tieX = 1;
        tieX2 = 0;
    }
}

/*
* tieBreak
* Input: none
* Description: determines winner in event of a tie based on pudding count
* Output: index of winning player or -1 if tie persists 
*/
int Game::tieBreak() {
    int index;
    int highestPudding = -1;
    tieX = 1;
    // iterate through all players to determine highest pudding 
    for (int player = 0; player < PLAYER_COUNT; player++) {
        if (!players[player].booleanX) continue;

        //compare player's pudding count to the current highest
        // if player's pudding is higher, update highest count and reset tie
        if (players[player].getPuddingCount() >= highestPudding) {
            if (players[player].getPuddingCount() > highestPudding) {
                highestPudding = players[player].getPuddingCount();
                index = player;
                tieX = 1;
                boolean2Reset();
            } else {
                tieX++;
            }
            players[player].booleanY = true;
        }   
    } // return player with highest pudding, if tie then return -1
    return (tieX == 1) ? index : -1;
}

/*
* Game::findWinner
* Input: none
* Description: identifies and displays winner based on highest score
* Output: none
*/
void Game::findWinner() {
    int topScore = -1;
    int winner;
    tieX = 1;  // initialize tie count

    for (int player = 0; player < PLAYER_COUNT; player++) {
        int currentScore = players[player].getScore();
        if (currentScore > topScore) {
            topScore = currentScore; // update top score
            winner = player; 
            tieX = 1; 
            boolean1Reset(); 
            players[player].booleanX = true; // set current player's boolean 
        } else if (currentScore == topScore) {
            tieX++; // increment tie count if scores equal
            players[player].booleanX = true; // set current player's boolean 
        }
    }

    if (tieX == 1) {
        board.drawWinner(players, winner); // draw winner if no tie
    } else {
        board.drawWinner(players, tieBreak()); // else, tiebreak
    }
}

/*
* updatePudding
* Input: none
* Description: adjusts players' scores based on pudding card counts
* Output: none
*/
void Game::updatePudding() {
    if (tieX2 != PLAYER_COUNT) {  // check if not all players are tied
        for (int player = 0; player < PLAYER_COUNT; ++player) {
            // adjust scores for players based on boolean flags
            // positive score adjustment for winners
            if (players[player].booleanX) {
                int scoreAdjustment = 6 / tieX;  
                players[player].updateScore(scoreAdjustment);
            }
            // negative score adjustment for losers
            if (players[player].booleanY) {
                int scorePenalty = -6 / tieX2;  
                players[player].updateScore(scorePenalty);
            }
        }
    }
}

/*
* Game::scorePudding
* Input: none
* Description: records highest and lowest pudding counts
* Output: none
*/
void Game::scorePudding() {
    int highestPudding = -1, lowestPudding = 28;
    tieX = tieX2 = 1; // reset ties
    for (int player = 0; player < PLAYER_COUNT; ++player) {
        int puddingCount = players[player].getPuddingCount();
        if (puddingCount > highestPudding) { //check if pudding is highest
            highestPudding = puddingCount;
            tieX = 1;
            boolean1Reset();
            players[player].booleanX = true;  // set booleanX 
        } else if (puddingCount == highestPudding) {
            tieX++; // increment tie if count is same as highest
            players[player].booleanX = true;  // set booleanX 
        }
        if (puddingCount < lowestPudding) { //check if pudding is lowest
            lowestPudding = puddingCount;
            tieX2 = 1;
            boolean2Reset();
            players[player].booleanY = true;  // set booleanY 
        } else if (puddingCount == lowestPudding) {
            tieX2++; //increment tie 2 for lowest if equal
            players[player].booleanY = true;  // set booleanY 
        }
    }
}

/*
* Game::updateScores
* Input: none
* Description: calculates and updates score for each player
* Output: none
*/
void Game::updateScores() {
    for (int player = 0; player < PLAYER_COUNT; ++player) {
        Player& p = players[player];  // reference to player for easier access
        //apply bonuses and penalties for lowest and highest
        if (p.booleanX) {
            p.updateScore(6 / tieX); 
        }
        if (p.booleanY) {
            p.updateScore(3 / tieX2); 
        }
        //update scores for different sushi types
        if (p.tempura > 1) {
            p.updateScore(5 * (p.tempura / 2));
        }
        if (p.sashimi > 2) {
            p.updateScore(10 * (p.sashimi / 3));
        }
        if (p.dumpling > 0) {
            p.updateScore(p.dumpling 
                        >= 5 ? 15 : p.dumpling * (p.dumpling + 1) / 2);
        }
        if (p.nigiri > 0) {
            p.updateScore(p.nigiri);
        }
    }
}

/*
* Game::getMakiScore
* Input: none
* Description: caluclates and updates maki scores for each player
* Output: none
*/
void Game::getMakiScore() {
    int topMakiCount = -1, secondTopMakiCount = -1, currentMaki;
    tieX = 1;

    // loop through players to calculate maki scores
    for (int player = PLAYER_COUNT - 1; player >= 0; --player) {
        currentMaki = players[player].maki; 
        if (currentMaki >= topMakiCount) { //check if count is new highest
            tieX = (currentMaki == topMakiCount) ? tieX + 1 : 1; 
            if (currentMaki != topMakiCount) {
                secondTopMakiCount = topMakiCount; // update second highest
                boolean1Reset();
            }
            topMakiCount = currentMaki; //set new highest
            players[player].booleanX = true; // mark player with highest
        } else if (currentMaki >= secondTopMakiCount) {
            secondTopMakiCount = currentMaki;
        }
    }
    // check for ties
    if (tieX == 1) { 
        tieX2 = 0;
        // loop through players to determine second highest count
        for (int player = 0; player < PLAYER_COUNT; ++player) {
            if (players[player].maki == secondTopMakiCount) {
                tieX2++;
                players[player].booleanY = true;
            }
        }
    }
}

/*
* Game::doChopsticks
* Input: loop, player, index
* Description: allows player with a chopsticks card to select additional card
* Output: none
*/
void Game::doChopsticks(int loop, int player, int index) {
    players[player].chopsticks = (players[player].chopsticks -1);

    // prompt user for second chopsticks card selection
    cout << "     Select a second card: ";
    int bonusCardChoice;
    cin >> bonusCardChoice;
    while (bonusCardChoice < 1 || bonusCardChoice > loop || 
                            bonusCardChoice == index) {
        if (bonusCardChoice == index) { // if bonus card is invalid
            cout << "     That card has already been selected." << endl;
        } else {
            if (index == 1) { // if card is selected card
                cout << "     Please enter a valid number between 2 and " 
                                            << loop << ": ";
            } else { 
                cout << "     Please enter a valid number between 1 and "
                                             << loop
                     << " (other than " << index << "): ";
            }
        } 
        cin >> bonusCardChoice; // new choice card 
    }
    completeChopsticks(bonusCardChoice, player);
}

/*
* Game::completeChopsticks
* Input: selection, player
* Description: finalizes use of chopsticks by the player
* Output: none
*/
void Game::completeChopsticks(int selection, int player) {
    int adjustedSelection = (selection - 1);
    Vector *passingHand = players[player].getPassingHand();
    Card *selectedCard2 = passingHand->at(adjustedSelection);
    players[player].setChopstick(selectedCard2);
    // adjust selection index, retrieve selected card. set as chopstick card

    Vector *revealedCards = players[player].getRevealedCards();
    // iterate revealed cards to find and remove old chopstick cards
    for (int size = 0; size < revealedCards->size(); size++) {
        if (revealedCards->at(size)->getSushiType() == "Chopsticks") {
            delete revealedCards->at(size); // clean up old chopstick card
            revealedCards->erase(size);
        }
    } // remove used chopstick card
    passingHand->erase(adjustedSelection);
    Card *replacementCard = new Card("Chopsticks", 0); //replacement chopstick
    passingHand->insert(adjustedSelection, replacementCard);
    // insert new chopstick card
}

/*
* Game::checkChopsticks
* Input: *selectedCard, player, index, loop
* Description: offers player to use chopsticks card for additional selection
* Output: none
*/
void Game::checkChopsticks(Card *selectedCard, int player, 
                            int index, int loop){
    int chopstickCount = 0;
    // announce selected card, prompt user to use chopsticks card
    if (players[player].chopsticks > 0) {
        cout << "     " << selectedCard->getSushiType() 
                            << " selected!" << endl;
        cout << "     Would you like to use your Chopsticks card to select a"
        << " second card from your hand? (y/n): ";
        string useChopsticks; 
        cin >> useChopsticks;
        if (useChopsticks == "y") { // if user says yes perform card seelction
            doChopsticks(loop, player, index);
            chopstickCount --;
            return;
        }
    }

    if (selectedCard->getSushiType() == "Chopsticks") {
        players[player].chopsticks++; //increment chopstick count
    }
}

/*
* Game::playGame
* Input: none 
* Description: controls flow of game, calling all major functions 
* Output: none
*/
void Game::playGame(){
    string play_on;
    //play three rounds
    for(int round = 0; round < ROUNDS; round++){
        dealCards(); // deal 9 cards to each player
        // loop through each card to select and pass them around
        for(int card = 0; card < CARD_HAND; card++){
            selectCard(CARD_HAND - card);
            passDeck(card);
        }
        countOfCards(); // count and categorize selected cards
        getMakiScore(); // calculate score based on maki cards
        updateScores(); // update scores based on all card types
        board.drawScore(players);
        // check if the player wants to do another round
        if (round < 2){
            cout << " End of round! Ready for Round " << round + 2 
                                            << " ? (y/n): ";
            cin >> play_on;
            if (play_on != "y"){
                resetRound();
                break; // exit if player doesnt want to continue
            }   
        }
        resetRound(); // reset game state for next round
    }
    scorePudding(); // final scoring based on pudding 
    updatePudding(); // apply final pudding related adjustments
    findWinner(); // determine game winner
}

/*
* Game::~Game
* Input: none 
* Description: cleans up dynamically allocated memory used during game
* Output: none 
*/
Game::~Game(){
    while(!deck.empty()){
        delete deck.back();
        deck.pop_back();
    }
}
        