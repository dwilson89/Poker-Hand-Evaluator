/*
 * Author: Dustin Wilson, 06325157
 * File: PokerEval.cpp
 * -------------------------------
 * This file provides the main funtion for a poker evaulation program. This program
 * creates a deck of cards, shuffles, and deals out five cards to ten different
 * players. It then evaluates each players hand, determining the type of that
 * player's hand, orders the hands from highest to lowest, displaying them to the
 * screen in decending order.
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "deck.h"
#include "card.h"
#include "hand.h"
#include "handcomparer.h"

using namespace std;

const int PLAYERS = 10;
const int CARDS_PER_PLAYER = 5;

int main(int argc, char *argv[]) {

    // Declare Deck and vector of pointer to Hand
    Deck *pokerDeck = new Deck();
    vector<Hand*> hands;

    // create Hand for each player
    for(int i = 1; i <= PLAYERS; i++){

        Hand *newPlayerHand = new Hand(i);

        hands.push_back(newPlayerHand);

    }// end for loop

    // allow for testing from file
    if (argc == 2) {

        // open the file and check it exists
        ifstream infile;
        infile.open(argv[1]);
        if (infile.fail()) {
            cerr <<  "Error: Could not find file" << endl;
            return 1;
        }//end if

        // read the cards into the hands
        int rank, suit;
        for (int card = 0; card < CARDS_PER_PLAYER; card++) {
            for (int i = 0; i < PLAYERS; i++) {
                infile >> rank >> suit;
                Card *card = new Card((Rank)rank, (Suit)suit);
                hands[i]->AddCard(card);

            }// end for loop

        }// end for loop

        // close the file
        infile.close();

    } else {

        // shuffle
        pokerDeck->Shuffle();

        // deal the cards
        for(int i = 0; i < CARDS_PER_PLAYER; i++){
            for (int j = 0; j < PLAYERS; j++){

                Card *newCard = pokerDeck->DealNextCard();

                hands[j]->AddCard(newCard);

            }// end for loop

        }// end for loop

    }// end if else

    // evaluate the hands
    for (int i = 0; i < PLAYERS; i++){

        hands[i]->Evaluate();

    }// end for loop

    // sort the hands
    sort (hands.begin(), hands.end(), HandComparer());

    // output the hands
    for (int i = 9; i >= 0; i--){

        cout << hands[i]->ToString() << endl;

    }// end for loop

    return 0;

}// end main
