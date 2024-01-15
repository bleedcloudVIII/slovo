#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class TokenType
{

public:
	std::string _name;
	std::string _regex;

	TokenType(std::string, std::string);
	TokenType();

};

extern std::unordered_map<std::string, TokenType*> TokenTypeList;