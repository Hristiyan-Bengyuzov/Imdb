#pragma once
#include "Constants.h"

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