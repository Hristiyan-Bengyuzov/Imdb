#include <iostream>
#include "MovieList.h"

// returns true if he chose ascending, otherwise false
bool getUserSortingPreference() {
	char* userPreference = readString("Enter your sorting preference (a for ascending, d for descending): ");
	bool ascending = contains(userPreference, "a");
	delete[] userPreference;
	return ascending;
}

bool checkIsAdmin() {
	char* username = readStringWithRetry("Enter your username: ");
	char* password = readStringWithRetry("Enter your password: ");
	bool result = stringComp(username, ADMIN_USERNAME) == 0 && stringComp(password, ADMIN_PASSWORD) == 0;
	delete[] username;
	delete[] password;
	return result;
}

void showHelp(bool isAdmin) {
	std::cout << BOLD << "=============================================\n" << RESET;
	std::cout << BOLD << CYAN << (isAdmin ? "Admin Help Menu:\n" : "User Help Menu:\n") << RESET;
	if (isAdmin) {
		std::cout << GREEN << "  1. " << RESET << "Add a new movie\n";
		std::cout << GREEN << "  2. " << RESET << "Edit movie details\n";
		std::cout << GREEN << "  3. " << RESET << "Delete a movie\n";
		std::cout << GREEN << "  4. " << RESET << "Sort movies by title\n";
		std::cout << GREEN << "  5. " << RESET << "Sort movies by rating\n";
		std::cout << GREEN << "  6. " << RESET << "Search for movies by title\n";
		std::cout << GREEN << "  7. " << RESET << "Search for movies by genre\n";
		std::cout << GREEN << "  8. " << RESET << "Print all movies\n";
		std::cout << GREEN << "  9. " << RESET << "Exit\n";
	}
	else {
		std::cout << GREEN << "  1. " << RESET << "Search for movies by title\n";
		std::cout << GREEN << "  2. " << RESET << "Search for movies by genre\n";
		std::cout << GREEN << "  3. " << RESET << "Sort movies by title\n";
		std::cout << GREEN << "  4. " << RESET << "Sort movies by rating\n";
		std::cout << GREEN << "  5. " << RESET << "Filter movies by minimal rating\n";
		std::cout << GREEN << "  6. " << RESET << "Add rating to movie\n";
		std::cout << GREEN << "  7. " << RESET << "Print all movies\n";
		std::cout << GREEN << "  8. " << RESET << "Exit\n";
	}
	std::cout << std::endl;
	std::cout << BOLD << "=============================================\n" << RESET;
}

void handleAdminChoice(int choice, MovieList& movieList) {
	switch (choice) {
	case 1:
		addNewMovie(movieList);
		break;
	case 2: {
		char* title = readStringWithRetry("Enter movie title to edit: ");
		editMovie(movieList, title);
		delete[] title;
		break;
	}
	case 3: {
		char* title = readStringWithRetry("Enter movie title to delete: ");
		deleteMovieByTitle(movieList, title);
		delete[] title;
		break;
	}
	case 4:
		sortMoviesByTitle(movieList, getUserSortingPreference());
		break;
	case 5:
		sortMoviesByAverageRating(movieList, getUserSortingPreference());
		break;
	case 6: {
		char* title = readStringWithRetry("Enter movie title: ");
		searchMoviesByTitle(movieList, title);
		delete[] title;
		break;
	}
	case 7: {
		char* genre = readStringWithRetry("Enter movie genre: ");
		searchMoviesByGenre(movieList, genre);
		delete[] genre;
		break;
	}
	case 8:
		printMovies(movieList);
		break;
	case 9:
		std::cout << YELLOW << "Exiting the application.\n" << RESET;
		destroyMovieList(movieList);
		exit(0);
	default:
		std::cout << RED << "Invalid choice. Try again.\n" << RESET;
		break;
	}
}

void handleUserChoice(int choice, MovieList& movieList) {
	switch (choice) {
	case 1: {
		char* title = readStringWithRetry("Enter movie title: ");
		searchMoviesByTitle(movieList, title);
		delete[] title;
		break;
	}
	case 2: {
		char* genre = readStringWithRetry("Enter movie genre: ");
		searchMoviesByGenre(movieList, genre);
		delete[] genre;
		break;
	}
	case 3:
		sortMoviesByTitle(movieList, getUserSortingPreference());
		break;
	case 4:
		sortMoviesByAverageRating(movieList, getUserSortingPreference());
		break;
	case 5: {
		float rating = readFloatWithRetry("Enter minimal rating: ", MIN_RATING, MAX_RATING);
		filterMoviesByRating(movieList, rating);
		break;
	}
	case 6:
		addRatingToMovieByTitle(movieList);
		break;
	case 7:
		printMovies(movieList);
		break;
	case 8:
		std::cout << YELLOW << "Exiting the application.\n" << RESET;
		destroyMovieList(movieList);
		exit(0);
	default:
		std::cout << RED << "Invalid choice. Try again.\n" << RESET;
		break;
	}
}

void processChoices(bool isAdmin, MovieList& movieList) {
	showHelp(isAdmin);
	while (true) {
		int choice = readIntWithRetry("Enter your choice: ");
		system("cls");
		showHelp(isAdmin);

		if (isAdmin) {
			handleAdminChoice(choice, movieList);
		}
		else {
			handleUserChoice(choice, movieList);
		}
	}
}

int main() {
	bool isAdmin = checkIsAdmin();
	MovieList movieList;
	initializeMovieList(movieList);

	processChoices(isAdmin, movieList);

	destroyMovieList(movieList);
}
