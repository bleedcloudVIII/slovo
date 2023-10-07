#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class TokenType
{
	std::string name;
	std::string regex;

public:
	std::string getRegex();
	std::string getName();
	TokenType(std::string, std::string);
};

//struct TokenTypeList {
//	std::string name;
//	TokenType tokenType
//};

//std::vector<TokenTypeList> tokenTypeList{
//	{"NUMBER", new TokenType("NUMBER", "[0-9]]*")},
//	{"VARIABLE", new TokenType("VARIABLE", "[a-z]]*")},
//	{"SEMICOLON", new TokenType("SEMICOLON", ";")},
//	{"SPACE", new TokenType("SPACE", "[\\n\\t\\r]")},
//	{"ASSIGN", new TokenType("ASSIGN", "=")},
//	{"LOG", new TokenType("LOG", "log")},
//	{"PLUS", new TokenType("PLUS", "+")},
//	{"MINUS", new TokenType("MINUS", "-")},
//	{"LPAR", new TokenType("LPAR", "\\(")},
//	{"RPAR", new TokenType("RPAR", "\\)")},
//};

extern std::unordered_map<std::string, TokenType*> TokenTypeList;
//extern std::vector<TokenType*> TokenTypeList;