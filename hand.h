/*
 * Author: Dustin Wilson, 06325157
 * File: hand.h
 * -------------------
 * This interface is responsible for providing functions for storing the
 * cards dealt to a player, evaluating player hand-types and for calculating the values
 * associated with the certain types of hands.
 */

#ifndef _hand_h
#define _hand_h

#include "card.h"
#include <vector>

// Enumeration types for the nine different hand types
enum HandType{HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT, FLUSH,
                FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH};

/* Hand type definition consisting on a hand, hand-type, player identity, and hand value*/
class Hand
{
    public:

        /*
         * Constructor
         * Param: integer given to identfy the player whoes hand this is.
         * Usage: Hand newPlayerHand = Hand(1);
         * ----------------------------------
         * Constructs a new hand and sets the player identifier.
         */
        Hand(int);

        /*
         * Destructor
         * Usage: implicit
         * ----------------------------------
         * Destructor deletes each Card* in the hand
         */
        ~Hand();

        /*
         * Function: AddCard
         * Param: Pointer to Card, that will be added to the hand.
         * Usage: hand.AddCard(newCard);
         * -----------------------------------
         * This function adds a Card* to the Hand vector.
         */
        void AddCard(Card*);

        /*
         * Function: Evaluate
         * Usage: hand.Evaluate();
         * -----------------------------------
         * This function is reponsible for determining the type of hand the cards
         * make up, and then calculating a score/value for the type of hand found.
         */
        void Evaluate();

        /*
         * Accessor
         * Function: GetValue
         * Usage: handValue = hand.GetValue();
         * -----------------------------------
         * This function returns the "value" of the hand.
         */
        int GetValue();

        /*
         * Accessor
         * Function: GetHandType
         * Usage: handType = hand.GetHandType();
         * -----------------------------------
         * This function returns the hand-type of the hand.
         */
        HandType GetHandType();

        /*
         * Function: ToString
         * Usage: handString = hand.ToString();
         * -----------------------------------
         * This function creates a string representation of the hand to output
         * the player's identity, cards in hand, and its hand-type.
         */
        string ToString();

    private:

        int handValue;
        HandType handType;
        int playerIdentifier;
        vector<Card*> playerHand;

        // Additional Private functions in order to help determine handtype and
        // calculate hand value scores.

        /*
         * Function: HasDuplicateHandType
         * Param One: Integer for the number of duplication being looked for
         * Param Two: Reference to a Rank variable, that holds the value of the
         *            rank that has as many duplicates being looked for (param one).
         * Usage: isPair = HasDuplicateHandType(2, duplicateRank);
         * -----------------------------------
         * This function returns true if it has been found to contain a Rank that appears
         * as often as the duplication count(param one), if that is the case the Referenced
         * Rank value (param two) will be updated with the current Rank that has
         * that many duplicates. Else if this is not the case it returns false and
         * doesnt update.
         */
        bool HasDuplicateHandType(int duplicateCount, Rank &duplicateRank);

        /*
         * Function: HasAdditionalPair
         * Param One: Rank variable, that holds the value of the
         *            rank of the first pair.
         * Param Two: Reference to a Rank variable, that holds the value of the
         *            rank of the second pair.
         * Usage: isTwoPair = HasAdditionalPair(duplicateRank, secondDuplicateRank);
         * -----------------------------------
         * This function returns true if an addtional pair has been found.
         * In the case of an addition pair, it updates the referenced Rank
         * variable (param two) with the new found pair. If no other pair is
         * found the function returns false.
         */
        bool HasAdditionalPair(Rank duplicateRank, Rank &secondDuplicateRank);

        /*
         * Function: PairCalculator
         * Param One: Rank for the pair found.
         * Usage: PairCalculator(duplicateRank);
         * -----------------------------------
         * This function calculates the value for the players hand if the hand-type
         * was found to be a pair, using the found rank of the pair as a starting point.
         */
        void PairCalculator(Rank duplicateRank);

        /*
         * Function: FlushAndHighCardCalculator
         * Usage: FlushAndHighCardCalculator
         * -----------------------------------
         * This function calculates the value for the players hand if the hand-type
         * was found to be a Flush or High Card.
         */
        void FlushAndHighCardCalculator();

        /*
         * Function: TwoPairCalculator
         * Param One: Rank for the first pair
         * Param Two: Rank for the second pair
         * Usage: TwoPairCalculator(pairOne, pairTwo);
         * -----------------------------------
         * This function calculates the value for the players hand if the hand-type
         * was found to be a two pair, using both ranks from the found pairs as a
         * starting point.
         */
        void TwoPairCalculator(Rank duplicateRank, Rank secondDuplicateRank);

        /*
         * Function: HasFlush
         * Usage: isFlush = HasFlush();
         * -----------------------------------
         * This function returns true if and only if all Cards in the player hand
         * has the same suit, else it returns false.
         */
        bool HasFlush();

        /*
         * Function: HasStraight
         * Param One: Reference to a Rank variable, that holds the highest rank
         *            of the straight
         * Usage: isSraight = HasStraight(straightRank);
         * -----------------------------------
         * This Function returns true if the hand has been found to contain cards
         * that make up a straight. If true the Rank variable (param one) is updated
         * with the highest rank in the hand. In the case of 2-3-4-5-A, the Rank Variable
         * is updated with the second highest value (5). If a straight is not found function
         * returns false, and Rank Variable is not updated.
         */
        bool HasStraight(Rank &straightRank);

};

#endif // _hand_h
