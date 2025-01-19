#pragma once
#include "StringUtils.h"

struct Actor {
	char* name;
};

void initializeActor(Actor& actor, const char* actorName) {
    actor.name = stringCopy(actorName);
}

void destroyActor(Actor& actor) {
    delete[] actor.name;
}
