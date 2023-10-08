#include "TokenType.h"

TokenType::TokenType(std::string n, std::string r): _name(n), _regex(r) {};

std::string TokenType::getRegex()
{
	return _regex;
}

std::string TokenType::getName()
{
	return _name;
}