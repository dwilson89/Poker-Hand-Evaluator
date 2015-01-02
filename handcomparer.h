/*
 * Author: Dustin Wilson, 06325157
 * File: handcomparer.h
 * --------------------------
 * This interface is responsible for providing an ordering for determining if
 * one Hand object is less than aother Hand object.
 */

#ifndef _handcomparer_h
#define _handcomparer_h

#include "hand.h"

/* Compare Class */
class HandComparer
{
    public:

        /*
         * Function: operator()
         * param one: Pointer to Hand one.
         * param two: Pointer to Hand two.
         * Usage: sort (hands.begin(), hands.end(), HandComparer());
         * ------------------------
         * This function returns true if and only if the first Hand has a lower
         * rank than the second Hand.
         */
        bool operator()(Hand* one, Hand* two);

};

#endif // _handcomparer_h
