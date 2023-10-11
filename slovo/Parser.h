#pragma once

#include <vector>
#include "Token.h"
#include <unordered_map>
#include <string>
#include <variant>

class Parser
{
public:
	std::vector<Token> _tokens;
	int _pos = 0;
	std::unordered_map<std::string, std::string> _scope;

	Parser(std::vector<Token>);

	std::variant<Token, int> _match(std::vector<TokenType>);
	Token _require(std::vector<TokenType>);
};

