#pragma once

#include <vector>
#include "Token.h"
#include <string>
#include <variant>
#include "AST/ExpressionNode.h"
#include "AST/NumberNode.h"
#include "AST/VariableNode.h"
#include "AST/BinOperationNode.h"
#include "AST/UnarOperationNode.h"
#include "AST/Statement.h"
#include <stack>
#include "AST/AssignStatement.h"

class Parser
{
private:
	Statement parseStatement();
	bool match(TokenType);
	double expression();
	bool isCurrentTokenOperator();
	
public:
	std::vector<Token> tokens;
	int length;
	int pos = 0;
	Statement* rootStatemnt;

	Parser(std::vector<Token>);

	void parseTokensToAst();
};

