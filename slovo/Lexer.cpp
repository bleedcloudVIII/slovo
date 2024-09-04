#include "Lexer.h"
#include <regex>
#include <iostream>
#include <string>
//


Lexer::Lexer(std::string c) : code(c) {};

Lexer::Lexer(const Lexer& l): code(l.code), pos(l.pos), tokenList(l.tokenList) {}

Lexer::Lexer() : code(""), tokenList({}) {};

std::vector<Token> Lexer::lexAnalysis()
{
	while (pos < length)
	{
		if (isdigit(code[pos])) tokenizeNumber();
		else if (operators.find(code[pos]) != std::string::npos) tokenizeOperator();
		else if (isalpha(code[pos])) tokenizeWord();
		else pos++;
		// if else then spaces
	};
	return tokenList;
};


void Lexer::tokenizeNumber()
{
	std::string numberStr = "";
	while (isdigit(code[pos]))
	{
		numberStr += code[pos];
		pos++;
	}
	tokenList.push_back(Token(TokenType::NUMBER, numberStr));
};

void Lexer::tokenizeOperator()
{
	std::string operatorStr = "";
	while (operators.find(code[pos]) != std::string::npos)
	{
		operatorStr += code[pos];
		pos++;
	}
	// BUG: ERROR WHEN HAVE ");" in code and (( )) 
	if (operatorStr == "+") tokenList.push_back(Token(TokenType::PLUS, operatorStr));
	else if (operatorStr == "-") tokenList.push_back(Token(TokenType::MINUS, operatorStr));
	else if (operatorStr == "=") tokenList.push_back(Token(TokenType::ASSIGN, operatorStr));
	else if (operatorStr == "(") tokenList.push_back(Token(TokenType::LPAR, operatorStr));
	else if (operatorStr == ")") tokenList.push_back(Token(TokenType::RPAR, operatorStr));
	else if (operatorStr == "*") tokenList.push_back(Token(TokenType::MULTIPLICATION, operatorStr));
	else if (operatorStr == "/") tokenList.push_back(Token(TokenType::DIVISON, operatorStr));
	else if (operatorStr == ";") tokenList.push_back(Token(TokenType::SEMICOLON, operatorStr));
	else throw "Error on tokenizeOperator!";
};

// WORD is
// 1) Variable
// 2) name of method or function
// 3) if, else, while, for ...
void Lexer::tokenizeWord()
{
	// Poka tolko variable
	std::string varStr = "";
	while (isalpha(code[pos]))
	{
		varStr += code[pos];
		pos++;
	}
	tokenList.push_back(Token(TokenType::VARIABLE, varStr));
};

bool Lexer::nextToken()
{
	return false;
};