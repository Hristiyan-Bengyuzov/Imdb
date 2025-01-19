#pragma once
#include "StringUtils.h"
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
* <file containing functions for working with numbers>
*
*/

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
