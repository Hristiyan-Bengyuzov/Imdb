#pragma once
#include "Constants.h"

// returns length of the string
size_t stringLen(const char* str) {
	if (!str)
		return 0;

	size_t len = 0;

	while (str[len])
	{
		len++;
	}

	return len;
}

// allocates memory and copies a string
char* stringCopy(const char* str)
{
	if (!str || *str == '\0')
		return nullptr;

	size_t lenStr = stringLen(str);
	char* result = new char[lenStr + 1];

	for (size_t i = 0; i < lenStr + 1; i++)
	{
		result[i] = str[i];
	}

	return result;
}

// compares two strings lexicographically
int stringComp(const char* const str1, const char* const str2) {
	size_t i = 0;
	size_t j = 0;

	while (str1[i] && str2[j])
	{
		if (str1[i] != str2[j])
			return str1[i] - str2[j];

		i++;
		j++;
	}

	return str1[i] - str2[j];
}

bool isUpperCase(char c) {
	return c >= 'A' && c <= 'Z';
}

bool isDigit(char c) {
	return c >= '0' && c <= '9';
}

char toLowerChar(char c) {
	if (isUpperCase(c))
	{
		return c + TO_LOWER_CONVERSION;
	}
	return c;
}

// case insensitive search for a substring
bool contains(const char* const str, const char* const searched, bool caseSensitive = false)
{
	if (!str || !searched)
		return false;

	size_t lenStr = stringLen(str);
	size_t lenSearched = stringLen(searched);

	if (lenSearched > lenStr)
		return false;

	for (size_t i = 0; i <= lenStr - lenSearched; i++)
	{
		bool found = true;
		for (size_t j = 0; j < lenSearched; j++)
		{
			char c1 = str[i + j];
			char c2 = searched[j];

			if (!caseSensitive)
			{
				c1 = toLowerChar(c1);
				c2 = toLowerChar(c2);
			}

			if (c1 != c2)
			{
				found = false;
				break;
			}
		}

		if (found)
			return true;
	}

	return false;
}

// first occurence of a character in a string
const char* customStrChr(const char* str, char ch) {
	while (*str != '\0') {
		if (*str == ch) {
			return str;
		}
		++str;
	}
	return nullptr;
}

// tokenizes string based on delimeters
char* customStrtok(char* str, const char* delimiters) {
	static char* nextToken = nullptr;
	if (str) {
		nextToken = str;
	}
	if (!nextToken) {
		return nullptr;
	}

	char* tokenStart = nextToken;
	while (*nextToken && customStrChr(delimiters, *nextToken) == nullptr) {
		++nextToken;
	}

	if (*nextToken) {
		*nextToken++ = '\0';
	}
	else {
		nextToken = nullptr;
	}

	return *tokenStart ? tokenStart : nullptr;
}

// converts string to int
int customAtoi(const char* str) {
	if (!str)
		return MIN_INT_SIZE;

	int num = 0;
	int sign = 1;
	if (*str == '-') {
		sign = -1;
		++str;
	}

	while (isDigit(*str)) {
		num = num * 10 + (*str + TO_INT_CONVERSION);
		++str;
	}

	if (*str != '\0')
		return MIN_INT_SIZE;

	return sign * num;
}

// converts string to float
float customAtof(const char* str) {
	if (!str)
		return MIN_FLOAT_SIZE;

	float num = 0.0f;
	float factor = 1.0f;
	int sign = 1;

	if (*str == '-') {
		sign = -1;
		++str;
	}

	while (isDigit(*str)) {
		num = num * 10 + (*str + TO_INT_CONVERSION);
		++str;
	}

	if (*str == '.') {
		++str;
		while (isdigit(*str)) {
			num = num * 10 + (*str + TO_INT_CONVERSION);
			factor *= 10;
			++str;
		}
	}

	if (*str != '\0')
		return MIN_FLOAT_SIZE;

	return sign * num / factor;
}

char* readString(const char* const prompt)
{
	std::cout << prompt;
	char str[BUFFER_SIZE];
	std::cin.getline(str, BUFFER_SIZE);
	return stringCopy(str);
}

char* readStringWithRetry(const char* const prompt, const char* errorMessage = "Invalid input. Please try again\n") {
	char* input = readString(prompt);
	if (!input || *input == '\0') {
		std::cout << RED << errorMessage << RESET;
		delete[] input;
		return readStringWithRetry(prompt);
	}
	return input;
}

int readInt(const char* prompt) {
	char* input = readString(prompt);

	if (!input)
	{
		delete[] input;
		return MIN_INT_SIZE;
	}

	int result = customAtoi(input);
	delete[] input;
	return result;
}

int readIntWithRetry(const char* const prompt, const int min = MIN_INT_SIZE, const int max = MAX_INT_SIZE, const char* const errorMessage = "Please enter a valid integer.\n") {
	int value;
	while (true) {
		value = readInt(prompt);
		if (value == MIN_INT_SIZE) {
			std::cout << RED << errorMessage << RESET;
			continue;
		}

		if (value < min || value > max) {
			std::cout << RED << "Input out of range.\n" << RESET;
			continue;
		}

		return value;
	}
}

float readFloat(const char* prompt) {
	char* input = readString(prompt);

	if (!input || *input == '\0') {
		delete[] input;
		return MIN_FLOAT_SIZE;
	}

	float result = customAtof(input);
	delete[] input;
	return result;
}

float readFloatWithRetry(const char* prompt, float min = MIN_FLOAT_SIZE, float max = MAX_FLOAT_SIZE, const char* const errorMessage = "Please enter a valid float.\n") {
	float value;
	while (true) {
		value = readFloat(prompt);
		if (value == MIN_FLOAT_SIZE) {
			std::cout << RED << errorMessage << RESET;
			continue;
		}

		if (value < min || value > max) {
			std::cout << "Input out of range.\n";
			continue;
		}

		return value;
	}
}

void updateStringField(char*& field, const char* prompt) {
	char* newField = readString(prompt);
	if (stringLen(newField) > 0) {
		delete[] field;
		field = newField;
	}
	else
	{
		delete[] newField;
	}
}