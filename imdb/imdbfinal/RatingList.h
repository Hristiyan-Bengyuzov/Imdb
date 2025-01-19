#pragma once
#include <iostream>

struct RatingList {
    float* ratings;
    int size;
    int capacity;
};

void initializeRatingList(RatingList& list, int initialCapacity = 2) {
    list.ratings = new float[initialCapacity];
    list.size = 0;
    list.capacity = initialCapacity;
}

void destroyRatingList(RatingList& list) {
    delete[] list.ratings;
}

void clearRatingList(RatingList& list) {
    delete[] list.ratings;
    list.ratings = new float[list.capacity];
    list.size = 0;
}

void addRatingToList(RatingList& list, float rating) {
    if (list.size == list.capacity) {
        list.capacity *= 2;
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
