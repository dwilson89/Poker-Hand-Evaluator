/*
 * Author: Dustin Wilson, 06325157
 * File: deck.h
 * ----------------
 * Interface defining the functionality of a deck of playing cards
 */
#include "card.h"
#include "random.h"

#ifndef _deck_h
#define _deck_h

/* Deck type definition */
class Deck
{
    public:

        /*
         * Constructor
         * Usage: Deck deck;
         * -------------------------
         * No argument constructor, which creates a dynamic array of Card* objects
         * and initialises them, in addition to intialising cardsDealt to 0.
         */
        Deck();

        /*
         * Destructor
         * Usage: implicit
         * -------------------------
         * This function deletes the contents of the array of Card*, as they are dynamically
         * created.
         */
        ~Deck();

        /*
         * Function: DealNextCard
         * Usage: nextCard = deck.DealNextCard();
         * -------------------------
         * This function returns a pointer to the next Card object from the deck, and increments
         * cardsDealt by 1.
         */
        Card* DealNextCard();

        /*
         * Function: Shuffle
         * Usage: deck.shuffle();
         * -------------------------
         * This function shuffles the order of the cards in deck.
         */
        void Shuffle();

        /*
         * Function: DisplayDeck
         * Usage: deck.DisplayDeck();
         * -------------------------
         * This function outputs the Card objects in the deck to the screen.
         */
        void DisplayDeck();

    private:
        Card** cards;
        int cardsDealt;
};

#endif // _deck_h
