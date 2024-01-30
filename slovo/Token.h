#pragma once
#include <string>
#include "TokenType.h"

class Token
{

public:
	TokenType _type;
	std::string _text;
	int _pos;

	Token(TokenType&, std::string, int);
	Token(const Token&);
	Token();

	std::string getText();
};

