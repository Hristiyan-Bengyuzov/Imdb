#pragma once
const char* RESET = "\033[0m";
const char* RED = "\033[31m";
const char* GREEN = "\033[32m";
const char* YELLOW = "\033[33m";
const char* BLUE = "\033[34m";
const char* CYAN = "\033[36m";
const char* MAGENTA = "\033[35m";
const char* BOLD = "\033[1m";
const char  TO_LOWER_CONVERSION = 'a' - 'A';
const char  TO_INT_CONVERSION = -'0';
const int   BUFFER_SIZE = 1024 + 1;
const int   MIN_INT_SIZE = std::numeric_limits<int>::min();
const int   MAX_INT_SIZE = std::numeric_limits<int>::max();
const float MIN_FLOAT_SIZE = std::numeric_limits<float>::min();
const float MAX_FLOAT_SIZE = std::numeric_limits<float>::max();