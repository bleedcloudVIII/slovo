#include "Parser.h"
#include <iostream>
#include <stack>
#include <vector>

Parser::Parser(std::vector<Token> tokens) : tokens(tokens), length(tokens.size()) {};

bool Parser::match(TokenType tt) // MB NE NUZHNO
{
	return tokens[pos++].type == tt;
};

bool Parser::isCurrentTokenOperator()
{
	return tokens[pos].type == TokenType::DIVISON or
		tokens[pos].type == TokenType::MINUS or
		tokens[pos].type == TokenType::PLUS or
		tokens[pos].type == TokenType::MULTIPLICATION;
};

double Parser::expression()
{
	std::stack<NumberNode> numbers;
	std::stack<char> operators;

	while (tokens[pos].type != TokenType::SEMICOLON)
	{
		if (tokens[pos].type == TokenType::NUMBER) numbers.push(NumberNode(stod(tokens[pos].text)));
		else if (tokens[pos].type == TokenType::VARIABLE) numbers.push(codesVariables[tokens[pos].text]);
		else if (isCurrentTokenOperator()) operators.push(tokens[pos].text[0]);
		else {} // ?

		pos++;
	}
	pos++; // Chtobi yiti ot ;
	// Poka tolko binarnie operatori

	BinOperationNode tmp;
	int count = operators.size();
	for (int i = count; i > 0; i--)
	{
		if (i == count)
		{
			
			NumberNode _tmp = numbers.top();
			numbers.pop();
			tmp = BinOperationNode(operators.top(), _tmp, numbers.top());
			numbers.pop();
		}
		else
		{
			tmp = BinOperationNode(operators.top(), numbers.top(), tmp.calculate());
			numbers.pop();
			
		}

		operators.pop();
	}
	return tmp.calculate();
};

Statement Parser::parseStatement()
{
	std::vector<Token> tokensOfCurrentStatement;
	int _pos = pos;
	while (tokens[_pos].type != TokenType::SEMICOLON)
	{
		tokensOfCurrentStatement.push_back(tokens[_pos]);
		_pos++;
	}

	int posOfAssign = -1;

	for (int i = 0; i < tokensOfCurrentStatement.size(); i++)
		if (tokensOfCurrentStatement[i].type == TokenType::ASSIGN) posOfAssign = i;

	if (posOfAssign != -1)
	{
		if (tokensOfCurrentStatement[0].type == TokenType::VARIABLE)
		{
			pos++; // Chtobi yuti ot nazvaniya peremennoi
			pos++; //Chtobi yuti ot "="
			//AssignStatement statement(tokensOfCurrentStatement[0].text, expression());
			codesVariables[tokensOfCurrentStatement[0].text] = expression();
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
	double d = codesVariables["a"];
	std::cout << "end\n";
};
