/*
 * Author: Dustin Wilson, 06325157
 * File: card.h
 * ------------------------
 * Interface defining the functionality for a playing card type. A playing card
 * has a rank and a suit assigned to it.
 */

#include <string>

using namespace std;

#ifndef _card_h
#define _card_h

// Enumeration types for the thirteen ranks and four suits of standard playing
// cards
enum Rank{TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN,
        KING, ACE};
enum Suit{CLUBS, SPADES, DIAMONDS, HEARTS};

/* Card type definition consisting of a rank and a suit */
class Card {

    public:

        /*
         * No arg constructor
         * Usage: Card card;
         */
        Card();

        /*
         * Constructor
         * Param One: Rank - rank given to card.
         * Param Two: Suit - suit given to card.
         * Usage: Card card = new Card(suit, rank);
         * -------------------------------------
         * Constructs a new card from a given rank and suit.
         */
        Card(Rank, Suit);

        /* Destructor
         * Usage: implicit.
         */
        ~Card();


        /*
         * Accessor
         * Function: GetRank
         * Usage: cardRank = card.GetRank();
         * -------------------------------------
         * This function returns the rank for the Card.
         */
        Rank GetRank();

        /*
         * Accessor
         * Function: GetSuit
         * Usage: cardSuit = card.GetSuit();
         * -------------------------------------
         * This function returns the suit for the Card.
         */
        Suit GetSuit();

        /*
         * Function: ToSting
         * Usage: cardString = card.ToString();
         * -------------------------------------
         * This function produces a string representation of this Card.
         */
        string ToString();

    private:
        Rank rank;
        Suit suit;
};

#endif // _card_h
