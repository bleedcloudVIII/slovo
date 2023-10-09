#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

class TokenType
{

public:
	std::string _name;
	std::string _regex;

	std::string getRegex();
	std::string getName();
	TokenType(std::string, std::string);
};

extern std::unordered_map<std::string, TokenType*> TokenTypeList;