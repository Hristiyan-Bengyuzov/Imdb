#pragma once
#include <iostream>

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
* <file containing RatingList struct and functions for working with it>
*
*/

struct RatingList {
	float* ratings;
	int size;
	int capacity;
};

void initializeRatingList(RatingList& list, int initialCapacity = DEFAULT_CAPACITY) {
	list.ratings = new float[initialCapacity];
	list.size = DEFAULT_SIZE;
	list.capacity = initialCapacity;
}

void destroyRatingList(RatingList& list) {
	delete[] list.ratings;
}

void clearRatingList(RatingList& list) {
	destroyRatingList(list);
	list.ratings = new float[list.capacity];
	list.size = DEFAULT_SIZE;
}

void addRatingToList(RatingList& list, float rating) {
	if (list.size == list.capacity) {
		list.capacity *= CAPACITY_MULTIPLY;
		float* newRatings = new float[list.capacity];
		for (int i = 0; i < list.size; ++i) {
			newRatings[i] = list.ratings[i];
		}
		delete[] list.ratings;
		list.ratings = newRatings;
	}
	list.ratings[list.size++] = rating;
}

float calculateAverageRating(const RatingList& list) {
	if (list.size == 0) return 0.0f;
	float sum = 0.0f;
	for (int i = 0; i < list.size; ++i) {
		sum += list.ratings[i];
	}
	return sum / list.size;
}

void printRatingList(const RatingList& list) {
	for (int i = 0; i < list.size; ++i) {
		std::cout << list.ratings[i];
		if (i < list.size - 1) std::cout << ",";
	}
}
