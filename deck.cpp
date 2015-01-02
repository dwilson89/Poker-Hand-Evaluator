/*
 * Author: Dustin Wilson, 06325157
 * File: deck.cpp
 * ----------------
 * File implements deck.h that provides the functionality of a deck of playing cards.
 */

#include "deck.h"
#include "card.h"
#include "random.h"

#include <iostream>
#include <iomanip>

using namespace std;

const int CARDS_IN_DECK = 52;
const int NUM_SUITS = 4;
const int NUM_RANKS = 13;
const int NUM_SHUFFLES = 1000;

/*
 * Constructor
 * Usage: Deck deck;
 * -------------------------
 * No argument constructor, which creates a dynamic array of Card* objects
 * and initialises them, in addition to intialising cardsDealt to 0.
 */
Deck::Deck(){

    // Creates a new array of cards
    cards = new Card*[CARDS_IN_DECK];

    // Fills the newly created array with new card objects, each with a specific rank (TWO - ACE)
    // and suit (CLUBS - HEARTS)
    for (int suit = 0; suit < NUM_SUITS; suit++)
        for (int rank = 0; rank < NUM_RANKS; rank++)
            cards[suit * NUM_RANKS + rank] = new Card((Rank)rank, (Suit)suit);

    cardsDealt = 0;

}// end Deck

/*
 * Destructor
 * Usage: implicit
 * -------------------------
 * Destructor deletes the contents of the array of Card*, as they are dynamically
 * created.
 */
Deck::~Deck(){

    for (int i = 0; i < CARDS_IN_DECK; i++)
        delete cards[i];
    delete[] cards;

}// end ~Deck

/*
 * Function: DealNextCard
 * Usage: nextCard = deck.DealNextCard();
 * -------------------------
 * This function returns a pointer to the next Card object from the deck, and increments
 * cardsDealt by 1.
 */
Card* Deck::DealNextCard(){

    return cards[cardsDealt++];

}// end DealNextCard

/*
 * Function: Shuffle
 * Usage: deck.shuffle();
 * -------------------------
 * This function shuffles the order of the cards in deck.
 */
void Deck::Shuffle(){

    Random rand;

    for (int i = 0; i < NUM_SHUFFLES; i++){

        // Creates two random indexes
        int indexOne = rand.RandomInteger(0, CARDS_IN_DECK - 1);
        int indexTwo = rand.RandomInteger(0, CARDS_IN_DECK - 1);

        // Stores and then swaps the cards found at the two indexes
        Card* temp = cards[indexOne];
        cards[indexOne] = cards[indexTwo];
        cards[indexTwo] = temp;

    }// end for loop

}// end Shuffle

/*
 * Function: DisplayDeck
 * Usage: deck.DisplayDeck();
 * -------------------------
 * This function outputs the Card objects in the deck to the screen.
 */
void Deck::DisplayDeck(){

    string cardOrder ="Current Deck\ncards. \n\n";

    //used primarily for fomatting a line change every thirteen cards
    int cardCount = 1;

    for(int i = 0; i < CARDS_IN_DECK; i++){

        cardOrder += cards[i]->ToString();

        //if the remainder is equal to zero, go to the next line
        if((cardCount%NUM_RANKS) == 0){

            cardOrder += "\n";

        }

        cardCount++;

    }

    cout << cardOrder << "\n";

}//end DisplayDeck
