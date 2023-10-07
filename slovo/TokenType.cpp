#include "TokenType.h"

TokenType::TokenType(std::string n, std::string r): name(n), regex(r) {};

std::string TokenType::getRegex()
{
	return regex;
}

std::string TokenType::getName()
{
	return name;
}