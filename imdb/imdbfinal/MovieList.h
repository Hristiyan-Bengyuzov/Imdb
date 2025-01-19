#pragma once
#include <fstream>
#include "StringUtils.h"
#include "Movie.h"
#include "Serializable.h"
#include "FileUtils.h"
#include "NumberUtils.h"

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
* <file containing MovieList struct and functions for working with it>
*
*/

struct MovieList {
	Movie** movies;
	int size;
	int capacity;
};


void initializeMovieList(MovieList& list, const int initialCapacity = DEFAULT_CAPACITY) {
	list.movies = new Movie * [initialCapacity];
	list.size = DEFAULT_SIZE;
	list.capacity = initialCapacity;
	deserialize(MOVIE_FILE_PATH, list.movies, list.size, list.capacity);
}

void destroyMovieList(MovieList& list) {
	for (int i = 0; i < list.size; ++i) {
		destroyMovie(*list.movies[i]);
	}
	delete[] list.movies;
}

void addMovieToList(MovieList& list, Movie* newMovie) {
	if (!newMovie) {
		std::cout << RED << "Error: Cannot add a null movie.\n" << RESET;
		return;
	}

	if (list.size == list.capacity) {
		list.capacity *= CAPACITY_MULTIPLY;
		Movie** newMovies = new Movie * [list.capacity];
		for (int i = 0; i < list.size; ++i) {
			newMovies[i] = list.movies[i];
		}
		delete[] list.movies;
		list.movies = newMovies;
	}

	list.movies[list.size++] = newMovie;
	std::cout << GREEN << "Movie added successfully.\n" << RESET;
}

void addNewMovie(MovieList& list) {
	char* newTitle = readStringWithRetry("Enter movie title: ");
	int newYear = readIntWithRetry("Enter movie year: ", MIN_MOVIE_YEAR, MAX_MOVIE_YEAR, "Enter a valid movie year.\n");
	char* newGenre = readStringWithRetry("Enter movie genre: ");
	char* newDirector = readStringWithRetry("Enter movie director: ");

	Movie* newMovie = new Movie;
	initializeMovie(*newMovie, newTitle, newYear, newGenre, newDirector);
	addRatingToMovie(*newMovie, DEFAULT_RATING);

	int actorCount = readIntWithRetry("Enter the number of actors: ", MIN_ACTOR_COUNT, MAX_ACTOR_COUNT, "Invalid actor count.\n");
	for (int i = 0; i < actorCount; ++i) {
		char* actorName = readStringWithRetry("Enter name of actor: ");
		addActorToMovie(*newMovie, actorName);
		delete[] actorName;
	}

	addMovieToList(list, newMovie);
	serialize(MOVIE_FILE_PATH, list.movies, list.size);
}

void editMovie(MovieList& list, const char* movieTitle) {
	for (int i = 0; i < list.size; ++i) {
		if (contains(list.movies[i]->title, movieTitle)) {
			std::cout << YELLOW << "Editing Movie: " << list.movies[i]->title << std::endl << RESET;

			updateStringField(list.movies[i]->title, "Enter new title (or press Enter to keep): ");

			int newYear = readIntWithRetry("Enter new year (or press 0 to keep): ", 0, MAX_MOVIE_YEAR);
			if (newYear != 0) {
				list.movies[i]->year = newYear;
			}

			updateStringField(list.movies[i]->genre, "Enter new genre (or press Enter to keep): ");

			updateStringField(list.movies[i]->director, "Enter new director (or press Enter to keep): ");

			float newRating = readFloatWithRetry("Enter new rating (or press 0 to keep the current ratings): ", 0, MAX_RATING);
			if (newRating >= MIN_RATING && newRating <= MAX_RATING) {
				clearRatingList(list.movies[i]->ratings);
				addRatingToMovie(*list.movies[i], newRating);
			}

			char* editActors = readString("Would you like to edit the actors? (y/n): ");

			if (contains(editActors, "y")) {
				clearActorList(list.movies[i]->actors);

				int actorCount = readIntWithRetry("Enter the number of actors: ", MIN_ACTOR_COUNT, MAX_ACTOR_COUNT);
				for (int j = 0; j < actorCount; ++j) {
					char* actorName = readStringWithRetry("Enter actor name: ");
					addActorToMovie(*list.movies[i], actorName);
					delete[] actorName;
				}
			}

			delete[] editActors;
			std::cout << GREEN << "Movie edited successfully.\n" << RESET;
			serialize(MOVIE_FILE_PATH, list.movies, list.size);
			return;
		}
	}
	std::cout << RED << "Movie with title \"" << movieTitle << "\" not found.\n" << RESET;
}


void deleteMovieByTitle(MovieList& list, const char* title) {
	for (int i = 0; i < list.size; ++i) {
		if (contains(list.movies[i]->title, title)) {
			destroyMovie(*list.movies[i]);
			delete list.movies[i];

			for (int j = i; j < list.size - 1; ++j) {
				list.movies[j] = list.movies[j + 1];
			}

			list.size--;
			std::cout << GREEN << "Movie with title \"" << title << "\" deleted successfully.\n" << RESET;
			serialize(MOVIE_FILE_PATH, list.movies, list.size);
			return;
		}
	}
	std::cout << RED << "Movie with title \"" << title << "\" not found.\n" << RESET;
}

void searchMoviesByGenre(const MovieList& list, const char* genre) {
	bool found = false;
	std::cout << CYAN << "------------------------------------" << RESET << std::endl;
	for (int i = 0; i < list.size; ++i) {
		if (contains(list.movies[i]->genre, genre)) {
			printMovieDetails(*list.movies[i]);
			std::cout << CYAN << "------------------------------------" << RESET << std::endl;
			found = true;
		}
	}
	if (!found) {
		std::cout << RED << "No movies found with genre: " << genre << std::endl << RESET;
	}
}

void searchMoviesByTitle(const MovieList& list, const char* title) {
	bool found = false;
	std::cout << CYAN << "------------------------------------" << RESET << std::endl;
	for (int i = 0; i < list.size; ++i) {
		if (contains(list.movies[i]->title, title)) {
			printMovieDetails(*list.movies[i]);
			std::cout << CYAN << "------------------------------------" << RESET << std::endl;
			found = true;
		}
	}
	if (!found) {
		std::cout << RED << "No movies found with title: " << title << std::endl << RESET;
	}
}

void filterMoviesByRating(const MovieList& list, float rating) {

	std::cout << CYAN << "------------------------------------" << RESET << std::endl;
	for (int i = 0; i < list.size; ++i) {
		if (calculateAverageRating(list.movies[i]->ratings) >= rating)
		{
			printMovieDetails(*list.movies[i]);
			std::cout << CYAN << "------------------------------------" << RESET << std::endl;
		}
	}
}

void printMovies(const MovieList& list) {
	std::cout << CYAN << "------------------------------------" << RESET << std::endl;
	for (int i = 0; i < list.size; ++i) {
		std::cout << GREEN << "Movie " << i + 1 << ":" << RESET << std::endl;
		printMovieDetails(*list.movies[i]);
		std::cout << CYAN << "------------------------------------" << RESET << std::endl;
	}
}

void sortMoviesByAverageRating(MovieList& list, bool ascending = true) {
	for (int i = 0; i < list.size - 1; ++i) {
		for (int j = 0; j < list.size - i - 1; ++j) {
			float rating1 = calculateAverageRating(list.movies[j]->ratings);
			float rating2 = calculateAverageRating(list.movies[j + 1]->ratings);

			bool condition = ascending ? rating1 > rating2 : rating1 < rating2;
			if (condition) {
				Movie* temp = list.movies[j];
				list.movies[j] = list.movies[j + 1];
				list.movies[j + 1] = temp;
			}
		}
	}
	std::cout << GREEN << "Movies sorted by average rating " << (ascending ? "ascending" : "descending") << ".\n" << RESET;
}

void sortMoviesByTitle(MovieList& list, bool ascending = true) {
	for (int i = 0; i < list.size - 1; ++i) {
		for (int j = 0; j < list.size - i - 1; ++j) {
			bool condition = ascending
				? stringComp(list.movies[j]->title, list.movies[j + 1]->title) > 0
				: stringComp(list.movies[j]->title, list.movies[j + 1]->title) < 0;
			if (condition) {
				// Swap the movies
				Movie* temp = list.movies[j];
				list.movies[j] = list.movies[j + 1];
				list.movies[j + 1] = temp;
			}
		}
	}
	std::cout << GREEN << "Movies sorted by title " << (ascending ? "ascending" : "descending") << ".\n" << RESET;
}

void addRatingToMovieByTitle(MovieList& list) {
	char* title = readStringWithRetry("Enter the title of the movie to add a rating to: ");

	for (int i = 0; i < list.size; ++i) {
		if (contains(list.movies[i]->title, title)) {
			std::cout << "Found movie: " << GREEN << list.movies[i]->title << std::endl << RESET;
			float newRating = readFloatWithRetry("Enter the new rating (1 to 10): ", MIN_RATING, MAX_RATING);
			addRatingToMovie(*list.movies[i], newRating);
			serialize(MOVIE_FILE_PATH, list.movies, list.size);
			std::cout << GREEN << "Rating added successfully.\n" << RESET;
			delete[] title;
			return;
		}
	}

	std::cout << RED << "Movie with title \"" << title << "\" not found.\n" << RESET;
	delete[] title;
}
