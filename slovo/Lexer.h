#pragma once

#include "Token.h"
#include "TokenType.h"
#include <string>
#include <vector>

class Lexer
{
	std::string code;
	int pos = 0;
	std::vector<Token> tokenList;
public:
	Lexer(std::string);

	std::vector<Token>& lexAnalysis();
	bool nextToken();
};

