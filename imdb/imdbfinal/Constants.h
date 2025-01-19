#pragma once
#include <limits>

// colour constants
const char* RESET = "\033[0m";
const char* RED = "\033[31m";
const char* GREEN = "\033[32m";
const char* YELLOW = "\033[33m";
const char* BLUE = "\033[34m";
const char* CYAN = "\033[36m";
const char* MAGENTA = "\033[35m";
const char* BOLD = "\033[1m";

// conversion constants
const char  TO_LOWER_CONVERSION = 'a' - 'A';
const char  TO_INT_CONVERSION = -'0';

// size constants
const int   BUFFER_SIZE = 1024 + 1;
const int   MIN_INT_SIZE = std::numeric_limits<int>::min();
const int   MAX_INT_SIZE = std::numeric_limits<int>::max();
const float MIN_FLOAT_SIZE = std::numeric_limits<float>::min();
const float MAX_FLOAT_SIZE = std::numeric_limits<float>::max();
const int   DEFAULT_CAPACITY = 2;
const int   DEFAULT_SIZE = 0;
const int   CAPACITY_MULTIPLY = 2;

// rating constants
const float MIN_RATING = 1;
const float MAX_RATING = 10;
const float DEFAULT_RATING = 5;

// actor constants
const int MIN_ACTOR_COUNT = 1;
const int MAX_ACTOR_COUNT = 15;

// movie constants
const int MIN_MOVIE_YEAR = 1895; // when movies were invented
const int MAX_MOVIE_YEAR = 2025;

// admin constants
const char* ADMIN_USERNAME = "Admin";
const char* ADMIN_PASSWORD = "Admin123";

// path
const char* MOVIE_FILE_PATH = "s.txt";
