#pragma once

#include "Token.h"
#include <string>
#include <vector>

class Lexer
{
public:
	Lexer(std::string);
	Lexer(const Lexer&);
	Lexer();

	std::string code; // Stroka koda
	int pos = 0; // Tekushee pozicia pri analize
	int length = code.length(); // Dlina stroki koda
	std::vector<Token> tokenList; // Spisok tokenov
	std::string operators = "()-+=*/;";


	std::vector<Token> lexAnalysis();

	void tokenizeNumber();
	void tokenizeOperator();
	void tokenizeWord();

	bool nextToken();
};

