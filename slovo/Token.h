#pragma once
#include <string>
#include "TokenType.h"

class Token
{

public:
	TokenType type;
	std::string text;
	int pos;

	Token(TokenType&, std::string, int);
	Token(const Token&);
	Token();

	std::string getText();
};

