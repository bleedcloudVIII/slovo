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

ExpressionNode Parser::_parseVariableOrNumber()
{
	const std::variant<Token, int> number = _match({ *TokenTypeList["NUMBER"] });
	if (number.index() != 1) return new NumberNode(number);
	const std::variant<Token, int> variable = _match({ *TokenTypeList["VARIABLE"] });
	if (variable.index() != 1) return new VariableNode(variable);
	std::cout << "������. ��������� ��� �����, ��� ����������." << std::endl;
	throw "ERROR";

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
	variableNode = _parseVariableOrNumber();
	const std::variant<Token, int> assignOperator = _match({ *TokenTypeList["ASSIGN"] });
	if (assignOperator.index() != 1)
	{

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