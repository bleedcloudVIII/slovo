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
	if (number.index() != 1) return NumberNode(std::get<Token>(number));
	const std::variant<Token, int> variable = _match({ *TokenTypeList["VARIABLE"] });
	if (variable.index() != 1) return VariableNode(std::get<Token>(variable));
	std::cout << "������. ��������� ��� �����, ��� ����������." << std::endl;
	throw "ERROR";

}

ExpressionNode Parser::_parseParenthese()
{
	if (_match({ *TokenTypeList["LPAR"] }).index() == 1)
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
		return UnarOperationNode(std::get<Token>(t), _parseFormula());
	}
	std::cout << "ERROR." << std::endl;
	throw "��������� ������� �������� log";
};

ExpressionNode Parser::_parseFormula()
{
	ExpressionNode leftNode = _parseParenthese();
	std::variant<Token, int> oprtr = _match({ *TokenTypeList["MINUS"], *TokenTypeList["PLUS"] });
	while (oprtr.index() != 1)
	{
		const ExpressionNode rightNode = _parseParenthese();
		leftNode = BinOperationNode(std::get<Token>(oprtr), leftNode, rightNode);
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
		ExpressionNode printNode = _parsePrint();
		return printNode;
	}
	_pos -= 1; // ���������� ������� �������, �.�. � _match() ������ + 1
	ExpressionNode variableNode = _parseVariableOrNumber();
	const std::variant<Token, int> assignOperator = _match({ *TokenTypeList["ASSIGN"] });
	if (assignOperator.index() != 1)
	{
		const ExpressionNode rightFormulaNode = _parseFormula();
		BinOperationNode binaryNode = BinOperationNode(std::get<Token>(assignOperator), variableNode, rightFormulaNode);
		return binaryNode;
	}
	std::cout << "������. ����� ���������� ��������� �������� ����������." << std::endl;
	throw "ERROR";
};

 ExpressionNode Parser::_parseCode()
{
	 StatementsNode root;
	while (_pos < _tokens.size())
	{
		const ExpressionNode codeStringNode = _parseExpression();
		_require({ *TokenTypeList["SEMICOLON"] });
		root._addNode(codeStringNode);
	}
	return root;
};

 template<typename Base, typename T>
 inline bool instanceof(const T*)
 {
	 return std::is_base_of<Base, T>::value;
 }

 void Parser::run(ExpressionNode* node)
 {
	 if (instanceof<NumberNode>(node))
	 {
		return 
	 }
 }