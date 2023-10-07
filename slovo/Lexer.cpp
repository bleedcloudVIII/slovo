#include "Lexer.h"
#include <regex>
#include <iostream>

std::unordered_map<std::string, TokenType*>  TokenTypeList = {
	{"NUMBER", new TokenType("NUMBER", "[0-9]*")},
	{"VARIABLE", new TokenType("VARIABLE", "[a-z]*")},
	{"SEMICOLON", new TokenType("SEMICOLON", ";")},
	{"SPACE", new TokenType("SPACE", "\\n\\t\\r")},
	{"ASSIGN", new TokenType("ASSIGN", "=")},
	{"LOG", new TokenType("LOG", "log")},
	{"PLUS", new TokenType("PLUS", "+")},
	{"MINUS", new TokenType("MINUS", "-")},
	{"LPAR", new TokenType("LPAR", "\\(")},
	{"RPAR", new TokenType("RPAR", "\\)")}
};

std::vector<Token> Lexer::getTokenList()
{
	return tokenList;
}

std::vector<TokenType*> _getValues()
{
	std::vector<TokenType*> v;
	for (auto e : TokenTypeList)
	{
		//std::cout << e.second->getName() << std::endl;
		v.push_back(e.second);
	}
	//for (int i = 0; i < v.size(); i++)
	//{
	//	std::cout << v[i]->getName() << std::endl;
	//}
	//std::cout << "-------------------" << std::endl;
	return v;
}

Lexer::Lexer(std::string c) : code(c) {};

std::vector<Token>& Lexer::lexAnalysis()
{
	while (this->nextToken()) {}
	return tokenList;
};

bool Lexer::nextToken()
{
	if (this->pos >= this->code.length()) return false;
	//std::cout << code << std::endl;
	const std::vector<TokenType*> tokenTypesValues = _getValues();
	//for (int i = 0; i < tokenTypesValues.size(); i++)
	//{
	//	std::cout << tokenTypesValues[i]->getName() << std::endl;
	//}
	//std::cout << tokenTypesValues[0]->getName() << std::endl;
	//std::cout << tokenTypesValues.size() << std::endl;
	for (int i = 0; i < tokenTypesValues.size(); i++)
	{
		TokenType* tokenType = tokenTypesValues[i];
		const std::regex regex("^" + tokenType->getRegex());
		std::cout << i << "<- i" << std::endl;
		std::string _substr = code.substr(pos);
		std::cout << 1 << std::endl;
		std::smatch match_result;
		std::cout << 2 << std::endl;
		std::regex_search(_substr, match_result, regex);
		std::cout << 3 << std::endl;
		std::string result = match_result.str();
		//std::cout << result << "<- ss" << std::endl;
		std::cout << 4 << std::endl;
		std::cout << result[0] << std::endl;
		std::cout << 123 << std::endl;
		if (result[0])
		{	
			std::cout << result[0] << std::endl;
			std::cout << 5 << std::endl;
			Token token(*tokenType, result, pos);
			std::cout << 6 << std::endl;
			pos += result.length();
			std::cout << 7 << std::endl;
			tokenList.push_back(token);
			std::cout << 8 << std::endl;
			return true;
		}
	}
	std::cout << pos << std::endl;
	throw "На позиции _ обнаружена ошибка!";
	
};