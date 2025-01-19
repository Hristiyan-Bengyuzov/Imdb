#pragma once
#include "Actor.h"
#include "Constants.h"

struct ActorList {
	Actor** actors;
	int size;
	int capacity;
};

void initializeActorList(ActorList& list, int initialCapacity = DEFAULT_CAPACITY) {
	list.actors = new Actor * [initialCapacity];
	list.size = DEFAULT_SIZE;
	list.capacity = initialCapacity;
}

void destroyActorList(ActorList& list) {
	for (int i = 0; i < list.size; ++i) {
		destroyActor(*list.actors[i]);
		delete list.actors[i];
	}
	delete[] list.actors;
}

void clearActorList(ActorList& list) {
	destroyActorList(list);
	list.actors = new Actor * [list.capacity];
	list.size = DEFAULT_SIZE;
}

void addActorToList(ActorList& list, const char* actorName) {
	if (list.size == list.capacity) {
		list.capacity *= CAPACITY_MULTIPLY;
		Actor** newActors = new Actor * [list.capacity];
		for (int i = 0; i < list.size; ++i) {
			newActors[i] = list.actors[i];
		}
		delete[] list.actors;
		list.actors = newActors;
	}
	list.actors[list.size] = new Actor;
	initializeActor(*list.actors[list.size], actorName);
	list.size++;
}

void printActorList(const ActorList& list) {
	for (int i = 0; i < list.size; ++i) {
		std::cout << MAGENTA << list.actors[i]->name << RESET;
		if (i < list.size - 1) std::cout << ", ";
	}
}
