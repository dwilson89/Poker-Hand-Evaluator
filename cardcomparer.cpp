/*
 * Author: Dustin Wilson, 06325157
 * File: cardcomparer.cpp
 * --------------------------
 * This file implements an ordering for determining if
 * one Card object is less than aother Card object.
 */


#include "cardcomparer.h"
#include "card.h"

/*
 * Function: operator()
 * param one: Pointer to the first Card.
 * param two: Pointer to second Card.
 * Usage: sort (playerHand.begin(), playerHand.end(), CardComparer());
 * ------------------------
 * This function returns true if the rank of the first Card is less than
 * the rank of the second Card.
 */
bool CardComparer::operator()(Card *first, Card *second){

    return(first->GetRank() < second->GetRank());

}// end operator()
