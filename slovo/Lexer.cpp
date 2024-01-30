#include "Lexer.h"
#include <regex>
#include <iostream>
//
std::unordered_map<std::string, TokenType*>  TokenTypeList = {
	{"LOG", new TokenType("LOG", "log")},
	{"VARIABLE", new TokenType("VARIABLE", "[a-z]*")},
	{"ASSIGN", new TokenType("ASSIGN", "\\=")},
	{"NUMBER", new TokenType("NUMBER", "[0-9]*")},
	{"SEMICOLON", new TokenType("SEMICOLON", "\\;")},
	{"SPACE", new TokenType("SPACE", "[ \\n \\t \\r \\s]")},
	{"PLUS", new TokenType("PLUS", "\\+")},
	{"MINUS", new TokenType("MINUS", "\\-")},
	{"KAVICHKI", new TokenType("SKOBKA", "\"[a-z]*\"")},
	//{"", new TokenType("", "")},
	{"LPAR", new TokenType("LPAR", "\\(")},
	{"RPAR", new TokenType("RPAR", "\\)")}
};

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
		v.push_back(e.second);
	
	return v;
}


std::vector<Token> Lexer::lexAnalysis()
{
	//std::cout << "=============================" << std::endl;
	while (this->nextToken()) {}
	std::vector<Token> tokenListWithoutSpace;
	for (int i = 0; i < _tokenList.size(); i++)
	{
		if (_tokenList[i]._type._name != "SPACE") tokenListWithoutSpace.push_back(_tokenList[i]);
		//std::cout << "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{" << std::endl;
		//std::cout << _tokenList[i]._type._name << std::endl;
		//std::cout << (_tokenList[i]._type._name != "SPACE") << std::endl;
		//std::cout << _tokenList[i]._type._regex << std::endl;
		//std::cout << _tokenList[i]._text << std::endl;
		//std::cout << _tokenList[i]._pos << std::endl;
		//std::cout << "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{" << std::endl;

	}
	//std::cout << "=============================" << std::endl;

	_tokenList = tokenListWithoutSpace;
	return tokenListWithoutSpace;
};

bool Lexer::nextToken()
{
	if (this->_pos >= this->_code.length()) return false;
	const std::vector<TokenType*> tokenTypesValues = _getValues();

	//std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa" << std::endl;
	//for (int i = 0; i < tokenTypesValues.size(); i++)
	//	std::cout << tokenTypesValues[i]->_name << std::endl;
	//std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa" << std::endl;

	for (int i = 0; i < tokenTypesValues.size(); i++)
	{
		TokenType* tokenType = tokenTypesValues[i];
		const std::regex regex('^' + tokenType->_regex);
		std::string _substr = _code.substr(_pos);
		std::smatch match_result;
		std::regex_search(_substr, match_result, regex);
		std::string result = match_result.str();
		
		if (match_result.length() > 0)
		{	
			Token token(*tokenType, result, _pos);
			_pos += result.length();
			_tokenList.push_back(token);
			return true;
		}
	}
	std::cout << "Ошибка на:" << _pos << std::endl;
	throw "На позиции _ обнаружена ошибка!";
};