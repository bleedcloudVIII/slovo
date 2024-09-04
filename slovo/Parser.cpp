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
	//std::stack<NumberNode> numbers;
	//std::stack<char> operators;

	std::vector<NumberNode> numbers;
	std::vector<char> operators;


	while (tokens[pos].type != TokenType::SEMICOLON)
	{
		if (tokens[pos].type == TokenType::NUMBER) numbers.push_back(NumberNode(stod(tokens[pos].text)));
		else if (tokens[pos].type == TokenType::VARIABLE) numbers.push_back(codesVariables[tokens[pos].text]);
		else if (isCurrentTokenOperator()) operators.push_back(tokens[pos].text[0]);
		else {} // ?

		pos++;
	}
	pos++; // Chtobi yiti ot ;
	
	for (int i = 0; i < operators.size(); i++)
	{ 
		if (operators[i] == '*')
		{
			numbers[i] = NumberNode(BinOperationNode('*', numbers[i], numbers[i + 1]).calculate());
			numbers.erase(numbers.begin() + i + 1);
			operators.erase(operators.begin() + i);
		}
		else if (operators[i] == '/')
		{
			numbers[i] = NumberNode(BinOperationNode('/', numbers[i], numbers[i + 1]).calculate());
			numbers.erase(numbers.begin() + i + 1);
			operators.erase(operators.begin() + i);
		}
	}

	if (operators.size() == 0)
	{
		// Znacit bilo tolko delenie ili umnozenie
		return numbers[0].calculate();
	}

	BinOperationNode tmp;
	
	for (int i = operators.size() - 1; i >= 0; i--)
	{
		if (i == operators.size() - 1)
		{
			tmp = BinOperationNode(operators[i], numbers[i], numbers[i + 1]);
		}
		else
		{
			tmp = BinOperationNode(operators[i], numbers[i], tmp.calculate());
		}
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
			pos += 2; // Chtobi yuti ot nazvaniya peremennoi i "="
			
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
