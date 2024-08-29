#pragma once
#include <string>

/*
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
*/

enum TokenType
{
	STRING,
	NUMBER,

	VARIABLE,

	ASSIGN,
	PLUS,
	MINUS,
	MULTIPLICATION,
	DIVISON,

	SEMICOLON,
	LPAR,
	RPAR,
	SPACE,

};

class Token
{

public:
	TokenType type;
	std::string text;

	Token(TokenType, std::string);
	Token(const Token&);
};

