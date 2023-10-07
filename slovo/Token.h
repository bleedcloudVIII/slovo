#pragma once
#include <string>
#include "TokenType.h"

class Token
{
	TokenType& type;
	std::string text;
	int pos;

public:
	Token(TokenType&, std::string, int);
	std::string getText();
};

