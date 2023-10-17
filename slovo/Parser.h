#pragma once

#include <vector>
#include "Token.h"
#include <unordered_map>
#include <string>
#include <variant>
#include "AST/ExpressionNode.h"
#include "AST/StatementsNode.h"
#include "AST/NumberNode.h"
#include "AST/VariableNode.h"


class Parser
{
public:
	std::vector<Token> _tokens;
	int _pos = 0;
	std::unordered_map<std::string, std::string> _scope;

	Parser(std::vector<Token>);

	std::variant<Token, int> _match(std::vector<TokenType>);
	Token _require(std::vector<TokenType>);
	ExpressionNode _parseExpression();
	ExpressionNode _parseVariableOrNumber();
	StatementsNode _parseCode();
};

