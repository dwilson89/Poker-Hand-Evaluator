/*
 * Author: Dustin Wilson, 06325157
 * File: card.cpp
 * File implementing card.h which provides the functionality for a playing card
 * type. A playing card has a rank and a suit assigned to it.
 */

#include "card.h"
#include <iostream>

using namespace std;

/*
 * No arg constructor
 * Usage: Card card;
 */
Card::Card(){
}// end Card

/*
 * Constructor
 * Param One: Rank - rank given to card.
 * Param Two: Suit - suit given to card.
 * Usage: Card card = new Card(suit, rank);
 * -------------------------------------
 * Constructs a new card from a given rank and suit.

 */
Card::Card(Rank r, Suit s){

    rank = r;
    suit = s;

}// end Card

/*
 * Destructor
 * Usage: implicit.
 */
Card::~Card(){

    // does nothing

}// end ~Card

/*
 * Accessor
 * Function: GetRank
 * Usage: cardRank = card.GetRank();
 * -------------------------------------
 * This function returns the rank for the Card.
 */
Rank Card::GetRank(){

    return rank;

}// end GetRank

/*
 * Accessor
 * Function: GetSuit
 * Usage: cardSuit = card.GetSuit();
 * -------------------------------------
 * This function returns the suit for the Card.
 */
Suit Card::GetSuit(){

    return suit;

}// end GetSuit

/*
 * Function: ToSting
 * Usage: cardString = card.ToString();
 * -------------------------------------
 * This function produces a string representation of this Card.
 */
string Card::ToString(){

    std::string cardName = "";

    switch (rank){

        case TWO    : cardName += "2"; break;
        case THREE  : cardName += "3"; break;
        case FOUR   : cardName += "4"; break;
        case FIVE   : cardName += "5"; break;
        case SIX    : cardName += "6"; break;
        case SEVEN  : cardName += "7"; break;
        case EIGHT  : cardName += "8"; break;
        case NINE   : cardName += "9"; break;
        case TEN    : cardName += "T"; break;
        case JACK   : cardName += "J"; break;
        case QUEEN  : cardName += "Q"; break;
        case KING   : cardName += "K"; break;
        case ACE    : cardName += "A"; break;

    }// end switch

    switch (suit){

        case CLUBS    : cardName += "C"; break;
        case SPADES   : cardName += "S"; break;
        case DIAMONDS : cardName += "D"; break;
        case HEARTS   : cardName += "H"; break;

    }// end switch

    return cardName;

}// end ToString
