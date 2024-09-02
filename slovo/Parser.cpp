#include "Parser.h"
#include <iostream>
#include <stack>
#include <vector>

Parser::Parser(std::vector<Token> tokens) : tokens(tokens), length(tokens.size()) {};

Statement* Parser::parseStatement()
{
	std::vector<Token> tokensOfCurrentStatement;
	while (tokens[pos].type != TokenType::SEMICOLON) tokensOfCurrentStatement.push_back(tokens[pos]);

	int posOfAssign = -1;

	for (int i = 0; i < tokensOfCurrentStatement.size(); i++)
		if (tokensOfCurrentStatement[i].type == TokenType::ASSIGN) posOfAssign = i;

	if (posOfAssign != -1)
	{
		BinOperationNode* bin = new BinOperationNode();
		bin.

	}
	else
	{
		// Poka eto ne imeet smisla
	}
}

void Parser::parseTokensToAst()
{
	Statement* current;
	while (pos < length)
	{
		Statement* statement = parseStatement();
		if (pos == 0)
		{
			rootStatemnt = statement;
			current = statement;
		}
		else
		{
			current->nextStatemnt = statement;
			current = statement;
		}
	}
};