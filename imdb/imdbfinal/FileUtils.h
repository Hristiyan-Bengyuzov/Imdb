#pragma once
#include <fstream>
#include "Movie.h"
#include "MovieList.h"

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
* <file containing functions for working with files>
*
*/

char* readStringFromFile(std::ifstream& ifs, char* buffer, size_t size) {
	if (ifs.getline(buffer, size)) {
		return stringCopy(buffer);
	}
	return nullptr;
}

int readIntFromFile(std::ifstream& ifs, char* buffer, size_t size) {
	if (ifs.getline(buffer, size)) {
		return customAtoi(buffer);
	}
	return 0;
}

int countItemsInBuffer(const char* buffer, const size_t size) {
	int count = 0;
	for (int i = 0; i < size && buffer[i] != '\0'; ++i) {
		if (buffer[i] == ',') {
			count++;
		}
	}
	return count + 1;
}

float* readRatingsFromFile(std::ifstream& ifs, char* buffer, const size_t size, int& ratingCount) {
	if (ifs.getline(buffer, size)) {
		// Count ratings
		ratingCount = countItemsInBuffer(buffer, size);

		float* ratings = new float[ratingCount];
		char* context = nullptr;
		char* ratingToken = customStrtok(buffer, ",", &context);
		int index = 0;
		while (ratingToken) {
			ratings[index++] = customAtof(ratingToken);
			ratingToken = customStrtok(nullptr, ",", &context);
		}

		return ratings;
	}

	return nullptr;
}

char** readActorsFromFile(std::ifstream& ifs, char* buffer, const size_t size, int& actorCount) {
	if (ifs.getline(buffer, size)) {
		// Count actors
		actorCount = countItemsInBuffer(buffer, size);

		char** actors = new char* [actorCount];
		char* context = nullptr; 
		char* actorToken = customStrtok(buffer, ",", &context);
		int index = 0;
		while (actorToken) {
			actors[index++] = stringCopy(actorToken);
			actorToken = customStrtok(nullptr, ",", &context);
		}

		return actors;
	}

	return nullptr;
}

void deserialize(const char* filePath, Movie**& movies, int& size, int& capacity) {
	std::ifstream ifs(filePath);
	if (!ifs.is_open()) {
		std::cerr << "Error opening file: " << filePath << "\n";
		return;
	}

	char buffer[BUFFER_SIZE];
	while (true) {
		char* title = readStringFromFile(ifs, buffer, BUFFER_SIZE);
		if (!title) break;

		int year = readIntFromFile(ifs, buffer, BUFFER_SIZE);
		char* genre = readStringFromFile(ifs, buffer, BUFFER_SIZE);
		char* director = readStringFromFile(ifs, buffer, BUFFER_SIZE);

		int ratingCount = 0;
		float* ratings = readRatingsFromFile(ifs, buffer, BUFFER_SIZE, ratingCount);

		int actorCount = 0;
		char** actors = readActorsFromFile(ifs, buffer, BUFFER_SIZE, actorCount);

		Movie* movie = new Movie;
		initializeMovie(*movie, title, year, genre, director);

		for (int i = 0; i < ratingCount; ++i) {
			addRatingToMovie(*movie, ratings[i]);
		}

		for (int i = 0; i < actorCount; ++i) {
			addActorToMovie(*movie, actors[i]);
			delete[] actors[i];
		}

		// add the movie
		if (size == capacity) {
			capacity *= CAPACITY_MULTIPLY;
			Movie** newMovies = new Movie * [capacity];
			for (int i = 0; i < size; ++i) {
				newMovies[i] = movies[i];
			}
			delete[] movies;
			movies = newMovies;
		}
		movies[size++] = movie;

		// cleanup
		delete[] title;
		delete[] genre;
		delete[] director;
		delete[] ratings;
		delete[] actors;
	}

	ifs.close();
}



void serialize(const char* filePath, Movie** movies, const int size) {
	if (!filePath || size == 0) {
		return;
	}

	std::ofstream ofs(filePath);
	if (!ofs.is_open()) {
		std::cerr << "Error opening file: " << filePath << "\n";
		return;
	}

	for (int i = 0; i < size; ++i) {
		Movie* movie = movies[i];

		// write general info
		ofs << movie->title << std::endl;
		ofs << movie->year << std::endl;
		ofs << movie->genre << std::endl;
		ofs << movie->director << std::endl;

		// write the ratings
		for (int j = 0; j < movie->ratings.size; ++j) {
			ofs << movie->ratings.ratings[j];
			if (j < movie->ratings.size - 1) {
				ofs << ',';
			}
		}
		ofs << std::endl;

		// write the actors
		for (int j = 0; j < movie->actors.size; ++j) {
			ofs << movie->actors.actors[j]->name;
			if (j < movie->actors.size - 1) {
				ofs << ',';
			}
		}
		ofs << std::endl;
	}

	ofs.close();
}