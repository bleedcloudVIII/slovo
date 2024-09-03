#include "Parser.h"
#include <iostream>
#include <stack>
#include <vector>

Parser::Parser(std::vector<Token> tokens) : tokens(tokens), length(tokens.size()) {};

bool Parser::match(TokenType tt) // MB NE NUZHNO
{
	return tokens[pos++].type == tt;
}

ExpressionNode Parser::additive()
{
	ExpressionNode result = multiplication();
};

ExpressionNode Parser::expression()
{
	return additive();
};

Statement Parser::parseStatement()
{
	std::vector<Token> tokensOfCurrentStatement;
	while (tokens[pos].type != TokenType::SEMICOLON) tokensOfCurrentStatement.push_back(tokens[pos]);

	int posOfAssign = -1;

	for (int i = 0; i < tokensOfCurrentStatement.size(); i++)
		if (tokensOfCurrentStatement[i].type == TokenType::ASSIGN) posOfAssign = i;

	if (posOfAssign != -1)
	{
		if (tokensOfCurrentStatement[0].type == TokenType::VARIABLE)
		{
			pos++; // Chtobi yuti ot nazvaniya peremennoi
			pos++; //Chtobi yuti ot "="
			AssignStatement statement(tokensOfCurrentStatement[0].text, expression());
		}
		else throw "Error in statement ASSIGN";
	}
	else
	{
		// Poka eto ne imeet smisla
	}
}

void Parser::parseTokensToAst()
{
	std::vector<Statement> statements {};
	while (pos < length)
	{
		Statement statement = parseStatement();
		statements.push_back(statement);
		/*if (pos == 0)
		{
			rootStatemnt = statement;
			current = statement;
		}
		else
		{
			current->nextStatemnt = statement;
			current = statement;
		}*/
	}
};