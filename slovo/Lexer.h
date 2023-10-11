#pragma once

#include "Token.h"
#include "TokenType.h"
#include <string>
#include <vector>

class Lexer
{
public:
	Lexer(std::string);
	Lexer(const Lexer&);
	Lexer();

	std::string _code;
	int _pos = 0;
	std::vector<Token> _tokenList;

	std::vector<Token> getTokenList();
	std::vector<Token> lexAnalysis();
	bool nextToken();
};

