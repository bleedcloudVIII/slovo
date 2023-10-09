#include "Lexer.h"
#include <regex>
#include <iostream>
//
std::unordered_map<std::string, TokenType*>  TokenTypeList = {
	{"VARIABLE", new TokenType("VARIABLE", "[a-z]*")},
	{"ASSIGN", new TokenType("ASSIGN", "\\=")},
	{"NUMBER", new TokenType("NUMBER", "[0-9]*")},
	{"SEMICOLON", new TokenType("SEMICOLON", "\\;")},
	{"SPACE", new TokenType("SPACE", "[ \\n\\t\\r\\s]")},
	{"LOG", new TokenType("LOG", "log")},
	{"PLUS", new TokenType("PLUS", "\\+")},
	{"MINUS", new TokenType("MINUS", "\\-")},
	{"LPAR", new TokenType("LPAR", "\\(")},
	{"RPAR", new TokenType("RPAR", "\\)")}
};

//std::vector<TokenType*>  TokenTypeList = {
//	new TokenType("VARIABLE", "[a-z]*"),
//	new TokenType("ASSIGN", "\\="),
//	new TokenType("NUMBER", "[0-9]*"),
//	new TokenType("SEMICOLON", "\\;"),
//	new TokenType("SPACE", "[ \\n\\t\\r\\s]"),
//	new TokenType("LOG", "log"),
//	new TokenType("PLUS", "\\+"),
//	new TokenType("MINUS", "\\-"),
//	new TokenType("LPAR", "\\("),
//	new TokenType("RPAR", "\\)")
//};

Lexer::Lexer(std::string c) : _code(c) {};

Lexer::Lexer(const Lexer& l): _code(l._code), _pos(l._pos), _tokenList(l._tokenList) {}

Lexer::Lexer() : _code(""), _tokenList({}) {};

std::vector<Token> Lexer::getTokenList()
{
	return _tokenList;
}

std::vector<TokenType*> _getValues()
{
	std::vector<TokenType*> v;
	for (auto e : TokenTypeList)
	//for (int i = 0; i < TokenTypeList.size(); i++)
	{
		//std::cout << e.second->getName() << std::endl;
		//v.push_back(TokenTypeList)
		v.push_back(e.second);
	}
	//for (int i = 0; i < v.size(); i++)
	//{
	//	std::cout << v[i]->getName() << std::endl;
	//}
	//std::cout << "-------------------" << std::endl;
	return v;
}


std::vector<Token> Lexer::lexAnalysis()
{
	while (this->nextToken()) {}
	for (int i = 0; i < _tokenList.size(); i++)
	{
		std::string typeOfToken = _tokenList[i]._type._name;
		std::vector<int> deleteIndex;
		if (_tokenList[i]._type._name == TokenTypeList["SPACE"]->_name)
		{
			_tokenList.erase(_tokenList.begin() + i);
			deleteIndex.push_back(i);
			i--;
		}
	}
	return _tokenList;
};

bool Lexer::nextToken()
{
	if (this->_pos >= this->_code.length()) return false;
	const std::vector<TokenType*> tokenTypesValues = _getValues();
	std::cout << "---------------------------------" << std::endl;
	for (int i = 0; i < tokenTypesValues.size(); i++)
	{
		std::cout << tokenTypesValues[i]->_regex << std::endl;
	}
	std::cout << "---------------------------------" << std::endl;
	std::cout << _code << std::endl;
	for (int i = 0; i < tokenTypesValues.size(); i++)
	{
		//std::cout << "index: " << i << std::endl;
		TokenType* tokenType = tokenTypesValues[i];
		//std::cout << tokenType->_regex << std::endl;
		const std::regex regex('^' + tokenType->_regex);
		//std::cout << code << std::endl;
		std::string _substr = _code.substr(_pos);
		std::smatch match_result;
		std::regex_search(_substr, match_result, regex);
		std::string result = match_result.str();
		if (match_result.length() > 0)
		{	
			std::cout << _pos << std::endl;
			std::cout << "MATCH" << std::endl;
			std::cout << result << std::endl;
			Token token(*tokenType, result, _pos);
			_pos += result.length();
			_tokenList.push_back(token);
			return true;
		}
	}
	std::cout << "Ошибка на:" << _pos << std::endl;
	throw "На позиции _ обнаружена ошибка!";
	
};