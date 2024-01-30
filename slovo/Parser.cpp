#include "Parser.h"
#include <iostream>
#include <stack>

Parser::Parser(std::vector<Token> t) : _tokens(t) {};

bool _find(std::vector<TokenType> tokenList, Token token)
{
	for (int i = 0; i < tokenList.size(); i++)
		if (tokenList[i]._name == token._type._name) return true;
	return false;
}

std::variant<Token, int> Parser::_match(std::vector<TokenType> expected)
{
	if (_pos < _tokens.size())
	{
		const Token currentToken = _tokens[_pos];

		if (_find(expected, currentToken))
		{
			_pos += 1;
			return currentToken;
		}
	}
	return -1;
};

Token Parser::_require(std::vector<TokenType> expected)
{
	const std::variant<Token, int> token = _match(expected);
	if (token.index() == 1)
	{
		std::cout << "Error on pos " << _pos << std::endl;
		std::cout << "Ошибка на позиции " << _pos << std::endl;
	}
	return std::get<Token>(token);
};

std::string removeKavichki(std::string str)
{
	std::string result = "";
	for (int i = 1; i < str.size() - 1; i++)
		result.push_back(str[i]);
	return result;
};

ExpressionNode Parser::_parseVariableOrNumber()
{
	const std::variant<Token, int> string = _match({ *TokenTypeList["KAVICHKI"] });
	if (string.index() != 1)
	{
		StringNode* strNode = new StringNode(std::get<Token>(string));
		strNode->_str._text = removeKavichki(strNode->_str._text);
		return ExpressionNode(strNode);
	};
	const std::variant<Token, int> number = _match({ *TokenTypeList["NUMBER"] });
	if (number.index() != 1) return ExpressionNode(new NumberNode(std::get<Token>(number)));
	const std::variant<Token, int> variable = _match({ *TokenTypeList["VARIABLE"] });
	if (variable.index() != 1) return ExpressionNode(new VariableNode(std::get<Token>(variable)));
	std::cout << "Error. Ozhidalos chislo ili peremennaya ili stroka." << std::endl;
	std::cout << "Ошибка. Ожидалось или число, или переменная." << std::endl;
	throw "ERROR";

}

ExpressionNode Parser::_parseParenthese()
{
	if (_match({ *TokenTypeList["LPAR"] }).index() != 1)
	{
		ExpressionNode node = _parseFormula();
		_require({ *TokenTypeList["RPAR"] });
		return node;
	}
	else
	{
		return _parseVariableOrNumber();
	}
}

ExpressionNode Parser::_parsePrint()
{
	std::variant<Token, int> t = _match({ *TokenTypeList["LOG"]});
	if (t.index() != 1)
	{
		return ExpressionNode(new UnarOperationNode(std::get<Token>(t), _parseFormula()));
	}
	std::cout << "ERROR." << std::endl;
	throw "Ожидается унарный оператор log.[Ozhidalsya unarniy operator log]";
}


ExpressionNode Parser::_parseFormula()
{
	ExpressionNode leftNode = _parseParenthese();
	std::variant<Token, int> oprtr = _match({ *TokenTypeList["MINUS"], *TokenTypeList["PLUS"], *TokenTypeList["UMNOJ"], *TokenTypeList["DELENIE"] });
	while (oprtr.index() != 1)
	{
		const ExpressionNode rightNode = _parseParenthese();
		leftNode = ExpressionNode(new BinOperationNode(std::get<Token>(oprtr), leftNode, rightNode));
		oprtr = _match({ *TokenTypeList["MINUS"], *TokenTypeList["PLUS"], *TokenTypeList["UMNOJ"], *TokenTypeList["DELENIE"] });
	}
	return leftNode;
}

ExpressionNode Parser::_parseExpression()
{

	const std::variant<Token, int> m = _match({ *TokenTypeList["VARIABLE"]});
	if (m.index() == 1)
	{
		// Если не переменная, то ожидаем консоль(log)
		ExpressionNode printNode = _parsePrint();
		return printNode;
	}
	_pos -= 1; // Возвращаем обратно позицию, т.к. в _match() делали + 1
	ExpressionNode variableNode = _parseVariableOrNumber();
	const std::variant<Token, int> assignOperator = _match({ *TokenTypeList["ASSIGN"] });
	if (assignOperator.index() != 1) // If on _pos assign
	{
		const ExpressionNode rightFormulaNode = _parseFormula();
		BinOperationNode* binaryNode = new BinOperationNode(std::get<Token>(assignOperator), variableNode, rightFormulaNode);
		return ExpressionNode(binaryNode);
	}
	std::cout << "Error. After peremennoi ozhidaetsya operator prisvoeniya." << std::endl;
	std::cout << "Ошибка. После переменной ожидается оператор присвоения на позиции " << _pos << std::endl;
	throw "ERROR";
};

ExpressionNode Parser::_parseCode()
{

	StatementsNode* root = new StatementsNode;
	while (_pos < _tokens.size())
	{

		const ExpressionNode codeStringNode = _parseExpression();
		_require({ *TokenTypeList["SEMICOLON"] });
		root->_addNode(codeStringNode);
	}
	return ExpressionNode(root);
};

 std::stack<int> num_stack{};
 std::stack<std::string> str_stack{};

int Parser::run(ExpressionNode* node)
{
	if (node->_numNode != nullptr)
	{
 		num_stack.push(std::stoi(node->_numNode->_number._text));
 		return 0;
	}
	if (node->_strNode != nullptr)
	{
		str_stack.push(node->_strNode->_str._text);
		return 1;
	}
	if (node->_unarNode != nullptr)
	{

		if (node->_unarNode->_operator._type._name == TokenTypeList["LOG"]->_name)
		{
			int result = run(new ExpressionNode(node->_unarNode->_operand));
			if (result == 0)
			{
				std::cout << num_stack.top() << std::endl;
				num_stack.pop();
			}
			else if (result == 1)
			{
				std::cout << str_stack.top() << std::endl;
				str_stack.pop();
			}
			else if (result == 2)
			{
				std::cout << "return 2(null)  ?";
			}
			return 2;
		}
	}
	if (node->_binNode != nullptr)
	{
		if (node->_binNode->_operator._type._name == TokenTypeList["PLUS"]->_name)
		{
			run(new ExpressionNode(node->_binNode->_leftNode));
			int result = num_stack.top();
			num_stack.pop();
			run(new ExpressionNode(node->_binNode->_rightNode));
			result += num_stack.top();
			num_stack.pop();
			num_stack.push(result);
			return 0;
		}
		else if (node->_binNode->_operator._type._name == TokenTypeList["MINUS"]->_name)
		{
			run(new ExpressionNode(node->_binNode->_leftNode));
			int result = num_stack.top();
			num_stack.pop();
			run(new ExpressionNode(node->_binNode->_rightNode));
			result -= num_stack.top();
			num_stack.pop();
			num_stack.push(result);
			return 0;
		}
		else if (node->_binNode->_operator._type._name == TokenTypeList["UMNOJ"]->_name)
		{
			run(new ExpressionNode(node->_binNode->_leftNode));
			int result = num_stack.top();
			num_stack.pop();
			run(new ExpressionNode(node->_binNode->_rightNode));
			result *= num_stack.top();
			num_stack.pop();
			num_stack.push(result);
			return 0;
		}
		else if (node->_binNode->_operator._type._name == TokenTypeList["DELENIE"]->_name)
		{
			run(new ExpressionNode(node->_binNode->_leftNode));
			int result = num_stack.top();
			num_stack.pop();
			run(new ExpressionNode(node->_binNode->_rightNode));
			result /= num_stack.top();
			num_stack.pop();
			num_stack.push(result);
			return 0;
		}
		else if (node->_binNode->_operator._type._name == TokenTypeList["ASSIGN"]->_name)
		{
			int result = run(new ExpressionNode(node->_binNode->_rightNode));
			if (result == 0)
			{
				_scope[node->_binNode->_leftNode._varNode->_variable._text] = std::to_string(num_stack.top());
				num_stack.pop();
				return 2;
			}
			else if (result == 1)
			{
				_scope[node->_binNode->_leftNode._varNode->_variable._text] = str_stack.top();
				str_stack.pop();
				return 2;
			}
			else if (result == 2)
			{
				std::cout << "???" << std::endl;
			}
			return 2;
		}
	}
	if (node->_varNode != nullptr)
	{
		if (_scope[node->_varNode->_variable._text] != "")
		{
			try {
				int result = std::stoi(_scope[node->_varNode->_variable._text]);
				num_stack.push(result);
				return 0;
			}
			catch (...)
			{
				str_stack.push(_scope[node->_varNode->_variable._text]);
				return 1;
			}
		}
		else throw "Error. Peremennaya c nazvaniem ... ne obnaruzhena";
	}
	if (node->_stateNode != nullptr)
	{
		for (ExpressionNode codeString : node->_stateNode->_codeStrings)
		{
			run(new ExpressionNode(codeString));
		};
		return 2;
	}

	throw "ERROREORROER";
 }