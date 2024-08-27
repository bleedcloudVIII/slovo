#include "Lexer.h"
#include <regex>
#include <iostream>
//
std::unordered_map<std::string, TokenType*>  TokenTypeList = {
	{"LOG", new TokenType("LOG", "log")},
	{"STRING", new TokenType("STRING", "\"[a-z]*\"")}, // Ne rabotaut stroki v kavichkah
	{"VARIABLE", new TokenType("VARIABLE", "[a-z]*")},
	{"ASSIGN", new TokenType("ASSIGN", "\\=")},
	{"NUMBER", new TokenType("NUMBER", "[0-9]*")},
	{"SEMICOLON", new TokenType("SEMICOLON", "\\;")},
	{"SPACE", new TokenType("SPACE", "[ \\n \\t \\r]")},
	{"PLUS", new TokenType("PLUS", "\\+")},
	{"MINUS", new TokenType("MINUS", "\\-")},
	{"LPAR", new TokenType("LPAR", "\\(")},
	{"RPAR", new TokenType("RPAR", "\\)")},
	{"MULTIPLICATION", new TokenType("MULTIPLICATION", "\\*")},
	{"DIVISON", new TokenType("DIVISON", "\\/")},
};

Lexer::Lexer(std::string c) : code(c) {};

Lexer::Lexer(const Lexer& l): code(l.code), pos(l.pos), tokenList(l.tokenList) {}

Lexer::Lexer() : code(""), tokenList({}) {};

std::vector<Token> Lexer::getTokenList()
{
	return tokenList;
}

std::vector<TokenType*> getValues()
{
	std::vector<TokenType*> v;
	for (auto e : TokenTypeList)
		v.push_back(e.second);
	
	return v;
}


std::vector<Token> Lexer::lexAnalysis()
{
	while (this->nextToken()) {}
	std::vector<Token> tokenListWithoutSpace;
	for (int i = 0; i < tokenList.size(); i++)
	{
		if (tokenList[i].type.name != "SPACE") tokenListWithoutSpace.push_back(tokenList[i]);
	}

	tokenList = tokenListWithoutSpace;
	return tokenListWithoutSpace;
};

bool Lexer::nextToken()
{
	if (this->pos >= this->code.length()) return false;
	const std::vector<TokenType*> tokenTypesValues = getValues();
	for (int i = 0; i < tokenTypesValues.size(); i++)
	{
		TokenType* tokenType = tokenTypesValues[i];
		const std::regex regex('^' + tokenType->regex);
		std::string substr = code.substr(pos);
		std::smatch match_result;
		std::regex_search(substr, match_result, regex);
		std::string result = match_result.str();
		
		if (match_result.length() > 0)
		{	
			Token token(*tokenType, result, pos);
			pos += result.length();
			tokenList.push_back(token);
			return true;
		}
	}
	std::cout << "Ошибка на:" << pos << std::endl;
	throw "На позиции обнаружена ошибка!";
};