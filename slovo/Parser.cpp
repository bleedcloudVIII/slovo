#include "Parser.h"
#include <iostream>

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
		std::cout << "������ �� ������� " << _pos << std::endl;
	}
	return std::get<Token>(token);
};

std::variant<NumberNode*, VariableNode*> Parser::_parseVariableOrNumber()
{
	const std::variant<Token, int> number = _match({ *TokenTypeList["NUMBER"] });
	if (number.index() != 1) return new NumberNode(number);
	const std::variant<Token, int> variable = _match({ *TokenTypeList["VARIABLE"] });
	if (variable.index() != 1) return new VariableNode(variable);
	std::cout << "������. ��������� ��� �����, ��� ����������." << std::endl;
	throw "ERROR";

}

std::variant<BinOperationNode*, std::variant<NumberNode*, VariableNode*>> Parser::_parseParenthese()
{
	if (_match({ *TokenTypeList["LPAR"] }).index() == 1)
	{
		std::variant<BinOperationNode*, std::variant<NumberNode*, VariableNode*>>  node = _parseFormula();
		_require({ *TokenTypeList["RPAR"] });
		return node;
	}
	else
	{
		return _parseVariableOrNumber();
	}
}

std::variant<BinOperationNode*, std::variant<NumberNode*, VariableNode*>> Parser::_parseFormula()
{
	std::variant<BinOperationNode*, std::variant<NumberNode*, VariableNode*>> leftNode = _parseParenthese();
	std::variant<Token, int> oprtr = _match({ *TokenTypeList["MINUS"], *TokenTypeList["PLUS"] });
	while (oprtr.index() != 1)
	{
		const std::variant<BinOperationNode*, std::variant<NumberNode*, VariableNode*>> rightNode = _parseParenthese();
		leftNode = new BinOperationNode(std::get<Token>(oprtr), std::get<std::variant<NumberNode*, VariableNode*>>(leftNode), std::get<std::variant<NumberNode*, VariableNode*>>(rightNode));
		oprtr = _match({ *TokenTypeList["MINUS"], *TokenTypeList["PLUS"] });
	}
	return leftNode;
}

ExpressionNode Parser::_parseExpression()
{
	//std::vector<TokenType> v{ *TokenTypeList["VARIABLE"] };
	const std::variant<Token, int> m = _match({ *TokenTypeList["VARIABLE"]});
	if (m.index() == 1)
	{
		// ���� �� ����������, �� ������� �������(log)
		const printNode = _parsePrint();
		return printNode;
	}
	_pos -= 1; // ���������� ������� �������, �.�. � _match() ������ + 1
	std::variant <NumberNode*, VariableNode*> variableNode = _parseVariableOrNumber();
	const std::variant<Token, int> assignOperator = _match({ *TokenTypeList["ASSIGN"] });
	if (assignOperator.index() != 1)
	{
		const rightFormulaNode = _parseFormula();
		const BinOperationNode* binaryNode = new BinOperationNode(std::get<Token>(assignOperator), variableNode, rightFormulaNode);
		return binaryNode;
	}
	std::cout << "������. ����� ���������� ��������� �������� ����������." << std::endl;
	throw "ERROR";
};

StatementsNode Parser::_parseCode()
{
	StatementsNode* root = new StatementsNode();
	while (_pos < _tokens.size())
	{
		const ExpressionNode codeStringNode = _parseExpression();
		//std::vector<TokenType> r{ *TokenTypeList["SEMICOLON"] };
		_require({ *TokenTypeList["SEMICOLON"] });
		root->_addNode(codeStringNode);
	}
	return root;
};