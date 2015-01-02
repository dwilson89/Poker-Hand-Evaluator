/*
 * Author: Dustin Wilson, 06325157
 * File: cardcomparer.h
 * --------------------------
 * This interface is responsible for providing an ordering for determining if
 * one Card object is less than aother Card object.
 */

#ifndef _cardcomparer_h
#define _cardcomparer_h

#include "card.h"

/* Compare Class */
class CardComparer
{
    public:

        /*
         * Function: operator()
         * param one: Pointer to the first Card.
         * param two: Pointer to second Card.
         * Usage: sort (playerHand.begin(), playerHand.end(), CardComparer());
         * ------------------------
         * This function returns true if the rank of the first Card is less than
         * the rank of the second Card.
         */
        bool operator()(Card *first, Card *second);

};

#endif // _cardcomparer_h
