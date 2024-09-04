#include "Parser.h"
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

Parser::Parser(std::vector<Token> tokens) : tokens(tokens), length(tokens.size()) {};

bool Parser::match(TokenType tt) // MB NE NUZHNO
{
	return tokens[pos++].type == tt;
};

double Parser::calculateExpression(std::vector<NumberNode>& numbers, std::vector<char>& operators)
{
	// TO DO: Sdelat chto-bi rebotalo so skobkami v skobkah
	while (std::find(operators.begin(), operators.end(), '(') != operators.end() or std::find(operators.begin(), operators.end(), ')') != operators.end())
	{
		auto start = std::find(operators.begin(), operators.end(), '(');
		
		//std::vector<char> copy_vec;
		//copy(operators.begin(), operators.end(), std::back_inserter(copy_vec));
		//std::reverse(copy_vec.begin(), copy_vec.end());

		auto end = std::find(operators.begin(), operators.end(), ')');

		int start_index = start - operators.begin();
		//int end_index = copy_vec.size() - (end - copy_vec.begin()) - 1;
		int end_index = end - operators.begin();

		// NOTE: Sdelat proverku na vtoruy skobru
		// ... = 5 + (5 * 4 - 6) - 3
		// num | oper | i
		// 5     +      0
		// 0     (      1  start_i
		// 5     *      2
		// 4     -      3  
		// 6     )      4  end_i
		// 0     -      5
		// 3            6

		std::vector<NumberNode> n;
		std::vector<char> o;

		for (int i = start_index + 1; i <= end_index; i++) n.push_back(numbers[i]);
		for (int i = start_index + 1; i <= end_index - 1; i++) o.push_back(operators[i]);

		double resultOfPars = calculateExpression(n, o);

		for (int i = 0; i <= end_index - start_index; i++) numbers.erase(numbers.begin() + start_index);
		for (int i = 0; i <= end_index - start_index; i++) operators.erase(operators.begin() + start_index);
		numbers[start_index] = resultOfPars;
	}
	if (operators.size() == 0)
	{
		// Znacit bilo tolko delenie ili umnozenie
		return numbers[0].calculate();
	}

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
	BinOperationNode tmp;
	for (int i = operators.size() - 1; i >= 0; i--)
	{
		if (i == operators.size() - 1) tmp = BinOperationNode(operators[i], numbers[i], numbers[i + 1]);
		else tmp = BinOperationNode(operators[i], numbers[i], tmp.calculate());
	}
	return tmp.calculate();
	
	//return calculateExpression(numbers, operators); // Popadyot suda posle togo kak poschitayutsya vse skobki
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
	std::vector<NumberNode> numbers;
	std::vector<char> operators;


	while (tokens[pos].type != TokenType::SEMICOLON)
	{
		if (tokens[pos].type == TokenType::NUMBER) numbers.push_back(NumberNode(stod(tokens[pos].text)));
		else if (tokens[pos].type == TokenType::VARIABLE) numbers.push_back(codesVariables[tokens[pos].text]);
		else if (isCurrentTokenOperator()) operators.push_back(tokens[pos].text[0]);
		else if (tokens[pos].type == TokenType::LPAR)
		{
			numbers.push_back(NULL);
			operators.push_back(tokens[pos].text[0]);
		}
		else if (tokens[pos].type == TokenType::RPAR)
		{
			operators.push_back(tokens[pos].text[0]);
			numbers.push_back(NULL); // Chtobi skobka bila s 0
			//numbers.push_back(NULL); // Vmesto etogo 0 budet podstavleno znachenie skobki
		}

		else {} // ?

		pos++;
	}
	pos++; // Chtobi yiti ot ;
	
	// Change + to -. And do negative value of number

	for (int i = 0; i < operators.size(); i++)
	{
		if (operators[i] == '-')
		{
			operators[i] = '+';
			numbers[i + 1] = NumberNode(-numbers[i + 1].calculate());
		}
	}

	double result = calculateExpression(numbers, operators);

	return result;
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
