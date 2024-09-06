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
		if (i == operators.size() - 1) tmp = BinOperationNode(operators[i], numbers[i], numbers[i + 1]);
		else tmp = BinOperationNode(operators[i], numbers[i], tmp.calculate());
	}
	return tmp.calculate();
};

double Parser::calculateExpressionWithPars(std::vector<NumberNode> numbers, std::vector<char> operators)
{
	while (std::find(operators.begin(), operators.end(), '(') != operators.end() or std::find(operators.begin(), operators.end(), ')') != operators.end())
	{
		auto start = std::find(operators.begin(), operators.end(), '(');
		auto end = std::find(operators.begin(), operators.end(), ')');

		int start_index = start - operators.begin();
		int end_index = end - operators.begin();

		std::vector<char>::iterator begin_itr(operators.begin() + start_index + 1);
		std::vector<char>::iterator end_itr(operators.begin() + end_index - 1);		 
		std::vector<char>::iterator begin_itr_find(operators.begin() + end_index + 1);
		std::vector<char>::iterator end_itr_find(operators.end());
		std::vector<char>::iterator new_end;
		bool flag = 0;
		while (std::find(begin_itr, end_itr, ')') != end_itr or std::find(begin_itr, end_itr, '(') != end_itr)
		{
			new_end = std::find(begin_itr_find, end_itr_find, ')');
			auto diff = std::find(begin_itr, end_itr, '(');
			begin_itr = diff + 1;
			
			begin_itr_find = new_end + 1;

			if (new_end != end_itr_find) flag = 1;
		}
		
		if (flag)
		{

			int begin_index = start - operators.begin();
			int end_index = new_end - operators.begin();

			std::vector<NumberNode> n;
			std::vector<char> o;

			std::copy(numbers.begin() + begin_index + 1, numbers.begin() + end_index + 1, std::back_inserter(n));
			std::copy(operators.begin() + begin_index + 1, operators.begin() + end_index, std::back_inserter(o));

			double resultOfExpression = calculateExpressionWithPars(n, o);

			for (int i = 0; i <= end_index - start_index; i++) numbers.erase(numbers.begin() + start_index);
			for (int i = 0; i <= end_index - start_index; i++) operators.erase(operators.begin() + start_index);
			numbers[start_index] = resultOfExpression;
		}


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

		auto nbegin = std::find(operators.begin(), operators.end(), '(');
		auto nend = std::find(operators.begin(), operators.end(), ')');

		if (nbegin != operators.end() and nend != operators.end())
		{
			std::copy(numbers.begin() + (nbegin - operators.begin()) + 1, numbers.begin() + (nend - operators.begin()) + 1, std::back_inserter(n));
			std::copy(operators.begin() + (nbegin - operators.begin()) + 1, operators.begin() + (nend - operators.begin()), std::back_inserter(o));

			double resultOfPars = calculateExpressionWithPars(n, o);
			end_index = nend - operators.begin();
			start_index = nbegin - operators.begin();

			for (int i = 0; i <= end_index - start_index; i++) numbers.erase(numbers.begin() + start_index);
			for (int i = 0; i <= end_index - start_index; i++) operators.erase(operators.begin() + start_index);
			numbers[start_index] = resultOfPars;
		}
	}
	return calculateExpression(numbers, operators);
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

	double result = calculateExpressionWithPars(numbers, operators);

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
