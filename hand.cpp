/*
 * Author: Dustin Wilson, 06325157
 * File: hand.cpp
 * -------------------
 * This file is responsible for implementing the functions for storing the
 * cards dealt to a player, evaluating player hand types and for calculating the values
 * associated with the certain types of hands.
 */

#include "hand.h"
#include "card.h"
#include "cardcomparer.h"

#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <sstream>
#include <iostream>

using namespace std;

const int HAND_SIZE = 5;
const int NUM_OF_RANKS = 13;

/*
 * Constructor
 * Param: integer given to identfy the player whoes hand this is.
 * Usage: Hand newPlayerHand = Hand(1);
 * ----------------------------------
 * Constructs a new hand and sets the player identifier.
 */
Hand::Hand(int player){

    playerIdentifier = player;

    handValue = 0;

}// end Hand

/*
 * Destructor
 * Usage: implicit
 * ----------------------------------
 * Destructor deletes each Card* in the hand
 */
Hand::~Hand(){

    for (int i = 0; i < HAND_SIZE; i++)
        delete playerHand[i];

}// end ~Deck

/*
 * Function: AddCard
 * Param: Pointer to Card, that will be added to the hand.
 * Usage: hand.AddCard(newCard);
 * -----------------------------------
 * This function adds a Card* to the Hand vector.
 */
void Hand::AddCard(Card *card){

    playerHand.push_back(card);

}// end AddCard

/*
 * Function: Evaluate
 * Usage: hand.Evaluate();
 * -----------------------------------
 * This function is reponsible for determining the type of hand the cards
 * make up, and then calculating a score/value for the type of hand found.
 */
void Hand::Evaluate(){

    sort (playerHand.begin(), playerHand.end(), CardComparer());

    // Variables to store values of ranks found, used for primarily for calculation
    Rank duplicateRank;
    Rank secondDuplicateRank;
    Rank straightRank;

    // Possible Duplicate values
    const int PAIR = 2;
    const int THREEOKIND = 3;
    const int FOUROKIND = 4;

    // Determines the hand-type and calculation method to be used to find the value
    // Checks for Straight and possible Straight Flush
    if (HasStraight(straightRank)){

        if (HasFlush()){

            handType = STRAIGHT_FLUSH;

            // Value is determined by is its highest card found when it checked
            handValue = straightRank;

        } else {

            handType = STRAIGHT;

            // Value is determined by is its highest card found when it checked
            handValue = straightRank;

        }// end else if

    // Checks for Flush
    } else if (HasFlush()){

        handType = FLUSH;
        FlushAndHighCardCalculator();

    // Checks for Four of a Kind
    } else if (HasDuplicateHandType(FOUROKIND, duplicateRank)){

        handType = FOUR_OF_A_KIND;
        handValue = duplicateRank;

    // Checks for Three of a Kind
    } else if (HasDuplicateHandType(THREEOKIND, duplicateRank)) {

        // Checks if it also has a pair in the hand
        bool isFullHouse = HasAdditionalPair(duplicateRank, secondDuplicateRank);

        if(isFullHouse){

            handType = FULL_HOUSE;
            handValue = duplicateRank;

        }else {

            handType = THREE_OF_A_KIND;
            handValue = duplicateRank;

        }// end else if

    // Checks for One Pair
    } else if (HasDuplicateHandType(PAIR, duplicateRank)){

        // Checks for an addition pair in the hand
        bool isTwoPair = HasAdditionalPair(duplicateRank, secondDuplicateRank);

        if (isTwoPair){

            handType = TWO_PAIR;
            TwoPairCalculator(duplicateRank, secondDuplicateRank);

        } else {

            handType = ONE_PAIR;
            PairCalculator(duplicateRank);

        }//end else if

    // Else hands type is High Card
    } else {

        handType = HIGH_CARD;
        FlushAndHighCardCalculator();

    }// end else if

}// end Evaluate


/*
 * Function: HasFlush
 * Usage: isFlush = HasFlush();
 * -----------------------------------
 * This function returns true if and only if all Cards in the player hand
 * has the same suit, else it returns false.
 */
bool Hand::HasFlush(){

    bool isFlush = true;

    for(int i = 1; i < HAND_SIZE; i++){

        if(playerHand.front()->GetSuit() != playerHand[i]->GetSuit()){

            isFlush = false;
            break;

        }// end if

    }//end for loop

    return isFlush;

}// end HasFlush


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
bool Hand::HasStraight(Rank &straightRank){

    // Special case Ranks for TWO - ACE
    Rank specialCase = ACE;
    Rank specialCaseTwo = FIVE;

    // Index of a possible ACE
    const int SPECIALCASEINDEX = 4;

    bool specialCaseCondition = false;
    bool isStraight = true;

    for(int i = 1; i < HAND_SIZE; i++){

        // Special case for ace to five, checks the current index, and current
        // and previous Cards for special case conditions.
        if((SPECIALCASEINDEX == i)&&(playerHand[i]->GetRank() == specialCase)&&(playerHand[i-1]->GetRank()==specialCaseTwo)) {

            isStraight = true;
            straightRank = playerHand[i-1]->GetRank();
            specialCaseCondition = true;
            break;

        } else if(playerHand[i-1]->GetRank() == playerHand[i]->GetRank()){

           isStraight = false;
           break;

        } else if((playerHand[i]->GetRank() - playerHand[i-1]->GetRank())> 1){

           isStraight = false;
           break;

        }// end else if

    }// end for loop

    // In order to avoid a possible overwrite of the rank value used for the
    // special conditon
    if ((isStraight) && (!specialCaseCondition)){

         straightRank = playerHand.back()->GetRank();

    }//end if

    return isStraight;

}//end HasStraight

/*
 * Function: PairCalculator
 * Param One: Rank for the pair found.
 * Usage: PairCalculator(duplicateRank);
 * -----------------------------------
 * This function calculates the value for the players hand if the hand-type
 * was found to be a pair, using the found rank of the pair as a starting point.
 */
void Hand::PairCalculator(Rank duplicateRank){

    int maxPower = 3;
    int power = 0;

    handValue = duplicateRank * pow(NUM_OF_RANKS, maxPower);

    for(int i = 0; i < HAND_SIZE; i++){

        if (playerHand[i]->GetRank() != duplicateRank){

            handValue += (playerHand[i]->GetRank()) * pow(NUM_OF_RANKS,power);
            power++;

        }// end if

    }// end for loop

}// end PairCalculator

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
void Hand::TwoPairCalculator(Rank duplicateRank, Rank secondDuplicateRank){

    if (duplicateRank > secondDuplicateRank){

        handValue = (duplicateRank * pow(NUM_OF_RANKS,2)) + (secondDuplicateRank * pow(NUM_OF_RANKS,1));

    } else {

        handValue = (secondDuplicateRank * pow(NUM_OF_RANKS,2)) + (duplicateRank * pow(NUM_OF_RANKS,1));

    }// end else if

    // Used to add the last card
    for (int i = 0; i < HAND_SIZE; i++){

        if((playerHand[i]->GetRank() != duplicateRank) && (playerHand[i]->GetRank() != secondDuplicateRank)){

            handValue += playerHand[i]->GetRank() * pow(NUM_OF_RANKS,0);

        }// end if

    }// end for loop

}// end TwoPairCalculator

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
bool Hand::HasAdditionalPair(Rank duplicateRank, Rank &secondDuplicateRank){

    const int PAIR = 2;

    // Used to store the current duplicateRank, and then be used to update
    // for a possible second pair rank
    Rank dupHolder = duplicateRank;

    bool hasAnotherPair = HasDuplicateHandType(PAIR, dupHolder);

    secondDuplicateRank = dupHolder;

    return hasAnotherPair;

}// end HasAdditionalPair


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
bool Hand::HasDuplicateHandType(int duplicateCount, Rank &duplicateRank){

    int count = 1;
    bool isTrue = false;

    // Used to skip ahead of checked ranks
    int cardSkip = 1;

    for(int i = 0; i < HAND_SIZE; i+= cardSkip){

        count = 1;

        for(int j = 1 + i; j < HAND_SIZE; j++){

            // If duplicateRank already has a value will not recheck those values
            if((playerHand[i]->GetRank() == playerHand[j]->GetRank())&&
               (playerHand[i]->GetRank() != duplicateRank)) {

                count++;
                cardSkip++;

            }// end if

        }// end for loop

        if(count == duplicateCount){

            isTrue = true;
            duplicateRank = playerHand[i]->GetRank();
            break;

        }// end if

    }// end for loop

    return isTrue;

}// end HasDuplicateHandType

/*
 * Function: FlushAndHighCardCalculator
 * Usage: FlushAndHighCardCalculator
 * -----------------------------------
 * This function calculates the value for the players hand if the hand-type
 * was found to be a Flush or High Card.
 */
void Hand::FlushAndHighCardCalculator(){

    for(int i = 0; i < HAND_SIZE; i++){

        handValue += pow(NUM_OF_RANKS,i)* playerHand[i]->GetRank();

    }// end for loop

}// end FlushAndHighCardCalculator

/*
 * Accessor
 * Function: GetValue
 * Usage: handValue = hand.GetValue();
 * -----------------------------------
 * This function returns the "value" of the hand.
 */
int Hand::GetValue(){

    return handValue;

}// end GetValue

/*
 * Accessor
 * Function: GetHandType
 * Usage: handType = hand.GetHandType();
 * -----------------------------------
 * This function returns the hand-type of the hand.
 */
HandType Hand::GetHandType(){

    return handType;

}// emd GetHandType

/*
 * Function: ToString
 * Usage: handString = hand.ToString();
 * -----------------------------------
 * This function creates a string representation of the hand to output
 * the player's identity, cards in hand, and its hand-type.
 */
string Hand::ToString(){

    string playerCards;
    string playerInfo;
    string playerHandInfo;
    string playerNumber;

    // Used to convert an int to a string
    stringstream convert;
    convert << playerIdentifier;

    // Used for neat formating of the player identity
    if (playerIdentifier < 10) {

         playerNumber = " " + convert.str();

    } else {

        playerNumber = convert.str();

    }// end else if

    for (int i = 0; i < HAND_SIZE; i++){

        playerCards += playerHand[i]->ToString() + " ";

    }// end for loop

    switch (handType){

        case HIGH_CARD      : playerHandInfo = "- High Card";       break;
        case ONE_PAIR       : playerHandInfo = "- One Pair";        break;
        case TWO_PAIR       : playerHandInfo = "- Two Pair";        break;
        case THREE_OF_A_KIND: playerHandInfo = "- Three of a Kind"; break;
        case STRAIGHT       : playerHandInfo = "- Straight";        break;
        case FLUSH          : playerHandInfo = "- Flush";           break;
        case FULL_HOUSE     : playerHandInfo = "- Full House";      break;
        case FOUR_OF_A_KIND : playerHandInfo = "- Four of a Kind";  break;
        case STRAIGHT_FLUSH : playerHandInfo = "- Straight Flush";  break;

    }// end switch

    playerInfo = "Player " + playerNumber + " - " + playerCards + playerHandInfo;

    return playerInfo;

}// end ToString
