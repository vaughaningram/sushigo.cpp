/*
 * Name: Vaughan Ingram
 * player.cpp
 * Sushi Go
 * 4/21/24
 * Includes useful functions for gameplay in Sushigo!
 */

#include "player.h"

/*
 * Player::Player
 * Input: none
 * Description: constructor for player 
 * Output:
 */
Player::Player():lastSelectedIndex(-1){
    score = 0;
    pudding = 0;
    passing = new Vector;
    revealed = new Vector;
    maki = 0;
    tempura = 0;
    sashimi = 0;
    dumpling = 0;
    nigiri = 0;
    pudding = 0;
    wasabi = 0;
    chopsticks = 0;
    chopstick = nullptr;
    booleanX = false;
    booleanY = false;
}

/*
 * getPassingHand
 * Input: none
 * Description: returns a pointer to the player's current passing hand
 * Output: vector* - pointer to the vector storing revealed cards
 */
Vector *Player::getPassingHand(){
    return passing;
}
/*
 * getPuddingCount
 * Input: none
 * Description: returns count of pudding collected by player
 * Output: int - score of the player
 */
int Player::getPuddingCount(){
    return pudding;
}

/*
 * getPassingHandSize
 * Input: none
 * Description: returns the number of cards in the player's passing hand
 * Output: int - size of passing hand
 */
int Player::getPassingHandSize() {
    return passing->size();
}

/*
* Player::boolean1Reset
* Input: none
* Description: resets player's booleanY to false for tracking game conditions
* Output: none
*/
void Player::boolean1Reset(){
    booleanX = false;
}

/*
* Player::boolean2Reset
* Input: none
* Description: resets player's booleanY to false for tracking game conditions
* Output: none
*/
void Player::boolean2Reset(){
    booleanY = false;
}

/*
* Player::increasePudding
* Input: none
* Description: increments player's pudding count by 1 for end game scoring.
* Output: none
*/
void Player::increasePudding(){
    pudding++;
}

/*
 * addToPassingHand
 * Input: Card* card
 * Description: adds a card to the players collection of revealed cards 
 * Output: none 
 */
void Player::addToPassingHand(Card* card) {
    passing->push_back(card);
}

/*
 * getRevealedCards
 * Input: none
 * Description: returns a pointer to the player's revealed cards
 * Output: vector* - pointer to the vector storing revealed cards
 */
Vector *Player::getRevealedCards(){
    return revealed;
}

/*
 * getScore
 * Input: none
 * Description: returns the count of pudding cards collected by player
 * Output: score of the player
 */
int Player::getScore(){
    return score;
}

/*
* Player::updateScore
* Input: score
* Description: adjusts player's total score by adding the value
* Output: none
*/
void Player::updateScore(int score){
    this->score +=score;
}

/*
 * addToRevealedCards
 * Input: Card* card
 * Description: adds a card to the players collection of revealed cards 
 * Output: none
 */
void Player::addToRevealedCards(Card* card) {
    revealed->push_back(card);
}

/*
 * takeCardFromPassingHand
 * Input: int index
 * Description: removes a card from passing hand at index and returns it
 * Output: Card* - the card removed from passing hand
 */
Card* Player::takeCardFromPassingHand(int index) {
    Card* card = passing->at(index);
    passing->erase(index);
    return card;
}

/*
* Player::setChopstick
* Input: selectedCard 
* Description: sets the player's chopstick card to the Card object
* Output: none
*/
void Player::setChopstick(Card *selectedCard){
    chopstick = selectedCard;
}

/*
* Player::getChoiceCard
* Input: none
* Description: retrieves the card currently chosen by player as choice card
* Output: Card* 
*/
Card *Player::getChoiceCard(){
    return choiceCard;
}

/*
* Player::setChoiceCard
* Input: selectedCard
* Description: sets the player's choiceCard to card object
* Output: none
*/
void Player::setChoiceCard(Card *selectedCard){
    choiceCard = selectedCard;
}

/*
* Player::getChopstick
* Input: none
* Description: gets the chopstick card currently held by the player
* Output: Card*- pointer to the chopstick card if any, otherwise nullptr
*/
Card* Player::getChopstick(){
    return chopstick;
}


/*
 * setPassingHand
 * Input: Vector* newHand
 * Description: sets the player's passing hand to a new member of vector cards
 * Output: none 
 */
void Player::setPassingHand(Vector* newHand) {
    delete passing;
    passing = newHand;
}

/*
 * handsClear
 * Input: none 
 * Description: clears all cards from the player's passing and revealed hands
 * Output: none 
 */
void Player::handsClear() {
    while (!passing->empty()) {
        delete passing->back();  
        passing->pop_back();    
    }

    while (!revealed->empty()) {
        delete revealed->back();  
        revealed->pop_back();     
    }
}

/*
* Player::resetRound
* Input: none
* Description: resets all gameplay related counters and flags to initial states
* Output: none
*/
void Player::resetRound(){
    chopsticks = 0;
    wasabi = 0;
    nigiri = 0;
    booleanX = false;
    booleanY = false;
    sashimi = 0;
    dumpling = 0;
    tempura = 0;
    maki = 0;
}


/*
 * setLastSelectedIndex
 * Input: int index 
 * Description: sets index of the last selected card in player's passing hand
 * Output: none 
 */
void Player::setLastSelectedIndex(int index){
    lastSelectedIndex = index;
}

/*
 * getLastSelectedIndex
 * Input: none
 * Description: returns index of last selected card in player's passing hand
 * Output: int - index of last selected card 
 */
int Player::getLastSelectedIndex(){
    return lastSelectedIndex;
}

/*
 * player destructor
 * Description: cleans up all dynamically allocated memory with the player
 */
Player::~Player(){
    delete passing;
    delete revealed;
}
