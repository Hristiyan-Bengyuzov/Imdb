#pragma once
#include "Constants.h"

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
* <file containing functions for working with chars>
*
*/

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