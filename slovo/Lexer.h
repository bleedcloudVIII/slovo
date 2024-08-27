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

	std::string code;
	int pos = 0;
	std::vector<Token> tokenList;

	std::vector<Token> getTokenList();
	std::vector<Token> lexAnalysis();
	bool nextToken();
};

