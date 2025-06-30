/*
 * Name: Vaughan Ingram
 * card.cpp
 * Sushi Go
 * 4/21/24
 * Implements the card class and includes useful functions
 */


#include "card.h"

/*
 * Card::Card
 * Input: type (type of sushi), count (amount of each sushi type)
 * Description: constructs a card instance with specified sushi type and count
 * Output: none 
 */
Card::Card(string type, int count){
    sushiType = type;
    makiCount = count;
}

/*
 * Card::getMakiCount
 * Input: none 
 * Description: returns maki count for maki cards 
 * Output: number of maki rolls on card
 */
int Card::getMakiCount(){
    return makiCount;
}
/*
 * Card::getSushiType
 * Input: none
 * Description: returns sushi type of card
 * Output: type of sushi the card represents
 */
string Card::getSushiType(){
    return sushiType;
}
/*
 * Card::~Card 
 * Input: none 
 * Description: destructor for the card class
 * Output: none
 */
Card::~Card(){

}