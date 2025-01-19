#pragma once
#include "ActorList.h"
#include "RatingList.h"
#include "Constants.h"

struct Movie {
    char* title;
    int year;
    char* genre;
    char* director;
    ActorList actors;
    RatingList ratings;
};

void initializeMovie(Movie& movie, const char* movieTitle, int movieYear, const char* movieGenre, const char* movieDirector) {
    movie.title = stringCopy(movieTitle);
    movie.year = movieYear;
    movie.genre = stringCopy(movieGenre);
    movie.director = stringCopy(movieDirector);

    initializeActorList(movie.actors, DEFAULT_CAPACITY);
    initializeRatingList(movie.ratings, DEFAULT_CAPACITY);
}

void destroyMovie(Movie& movie) {
    delete[] movie.title;
    delete[] movie.genre;
    delete[] movie.director;
    destroyActorList(movie.actors);
    destroyRatingList(movie.ratings);
}

void addActorToMovie(Movie& movie, const char* actorName) {
    addActorToList(movie.actors, actorName);
}

void addRatingToMovie(Movie& movie, float rating) {
    addRatingToList(movie.ratings, rating);
}

void printMovieDetails(const Movie& movie) {
    std::cout << "  Title: " << GREEN << movie.title << RESET << std::endl
        << "  Year: " << YELLOW << movie.year << RESET << std::endl
        << "  Genre: " << BLUE << movie.genre << RESET << std::endl
        << "  Director: " << MAGENTA << movie.director << RESET << std::endl
        << "  Average Rating: " << CYAN << calculateAverageRating(movie.ratings) << RESET << std::endl
        << "  Actors: ";
    printActorList(movie.actors);
    std::cout << std::endl;
}
