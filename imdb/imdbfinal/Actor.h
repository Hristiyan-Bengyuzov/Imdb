#pragma once
#include "StringUtils.h"

/**
*
* Solution to course project #6
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Hristiyan Bengyuzov
* @idnumber 8MI0600487* @compiler VC
*
* <file containing Actor struct and functions for working with it>
*
*/

struct Actor {
	char* name;
};

void initializeActor(Actor& actor, const char* actorName) {
	actor.name = stringCopy(actorName);
}

void destroyActor(Actor& actor) {
	delete[] actor.name;
}
