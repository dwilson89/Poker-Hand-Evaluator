/*
 * Author: Dustin Wilson, 06325157
 * File: handcomparer.cpp
 * --------------------------
 * This file implements an ordering for determining if
 * one Hand object is less than aother Hand object.
 */

#include "handcomparer.h"
#include "hand.h"

/*
 * Function: operator()
 * param one: Pointer to Hand one.
 * param two: Pointer to Hand two.
 * Usage: sort (hands.begin(), hands.end(), HandComparer());
 * ------------------------
 * This function returns true if and only if the first Hand has a lower
 * rank than the second Hand.
 */
bool HandComparer::operator()(Hand* one, Hand* two){

    // If hand types are equal, check there hand values against each other
    if(one->GetHandType() == two->GetHandType()){

        return one->GetValue() < two->GetValue();

    }// end if

    return one->GetHandType() < two->GetHandType();

}// end operator()

