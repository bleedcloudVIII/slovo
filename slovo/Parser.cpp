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
		std::cout << "Error on pos " << _pos << std::endl;
		std::cout << "Ошибка на позиции " << _pos << std::endl;
	}
	return std::get<Token>(token);
};

ExpressionNode Parser::_parseVariableOrNumber()
{
	const std::variant<Token, int> number = _match({ *TokenTypeList["NUMBER"] });
	if (number.index() != 1) return NumberNode(std::get<Token>(number));
	const std::variant<Token, int> variable = _match({ *TokenTypeList["VARIABLE"] });
	if (variable.index() != 1) return VariableNode(std::get<Token>(variable));
	std::cout << "Error. Ozhidalos chislo ili peremennaya." << std::endl;
	std::cout << "Ошибка. Ожидалось или число, или переменная." << std::endl;
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
	throw "Ожидается унарный опепатор log.[Ozhidalsya unarniy operator log]";
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
		// Если не переменная, то ожидаем консоль(log)
		ExpressionNode printNode = _parsePrint();
		return printNode;
	}
	_pos -= 1; // Возвращаем обратно позицию, т.к. в _match() делали + 1
	ExpressionNode variableNode = _parseVariableOrNumber();
	const std::variant<Token, int> assignOperator = _match({ *TokenTypeList["ASSIGN"] });
	if (assignOperator.index() != 1)
	{
		const ExpressionNode rightFormulaNode = _parseFormula();
		BinOperationNode binaryNode = BinOperationNode(std::get<Token>(assignOperator), variableNode, rightFormulaNode);
		return binaryNode;
	}
	std::cout << "Error. After peremennoi ozhidaetsya operator prisvoeniya." << std::endl;
	std::cout << "Ошибка. После переменной ожидается оператор присвоения." << std::endl;
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
 //inline bool instanceof(const T *ptr)
 inline bool instanceof(const T*)
 {
	 return std::is_base_of<Base, T>::value;
	 //return dynamic_cast<const Base*>(ptr) != nullptr;
 }
 /*
 std::unordered_map<std::string, TokenType*>  TokenTypeList = {
	{"VARIABLE", new TokenType("VARIABLE", "[a-z]*")},
	{"ASSIGN", new TokenType("ASSIGN", "\\=")},
	{"NUMBER", new TokenType("NUMBER", "[0-9]*")},
	{"SEMICOLON", new TokenType("SEMICOLON", "\\;")},
	{"SPACE", new TokenType("SPACE", "[ \\n \\t \\r \\s]")},
	{"LOG", new TokenType("LOG", "log")},
	{"PLUS", new TokenType("PLUS", "\\+")},
	{"MINUS", new TokenType("MINUS", "\\-")},
	{"LPAR", new TokenType("LPAR", "\\(")},
	{"RPAR", new TokenType("RPAR", "\\)")}
};
 */



 std::pair<int, std::string> Parser::run(ExpressionNode* node)
 {
	 std::cout << "HEHEHE" << std::endl;
	 std::cout << TokenTypeList["LOG"]->_name << std::endl;
	 std::cout << TokenTypeList["LOG"]->_regex << std::endl;

	 std::cout << instanceof<NumberNode>(node) << std::endl;
	 std::cout << instanceof<BinOperationNode>(node) << std::endl;
	 std::cout << instanceof<UnarOperationNode>(node) << std::endl;
	 std::cout << instanceof<VariableNode>(node) << std::endl;
	 std::cout << instanceof<ExpressionNode>(node) << std::endl;
	 std::cout << instanceof<StatementsNode>(node) << std::endl;
	 //std::cout << instanceof<ExpressionNode>(node) << std::endl;




	 if (instanceof<NumberNode>(node))
	 {
		// return int
		// return parseInt(node.number.text);
		 std::cout << "A1" << std::endl;
		 NumberNode* numNode{ static_cast<NumberNode*>(node) };
		 std::cout << "A2" << std::endl;

		 std::cout << numNode->_number._text << std::endl;
	 }
	 if (instanceof<UnarOperationNode>(node))
	 {
		 std::cout << "A3" << std::endl;

		 UnarOperationNode* unarNode{ static_cast<UnarOperationNode*>(node) };
		 if (unarNode->_operator._type._name == TokenTypeList["LOG"]->_name)
		 {
			 (run(new ExpressionNode(unarNode->_operand))); // !!!!!!!!!!!!!!!!!!!!!!!
			 return std::pair<int, std::string>{0, ""};

		 }
		 std::cout << "A4" << std::endl;

	 }
	 if (instanceof<BinOperationNode>(node))
	 {
		 std::cout << "A5" << std::endl;

		 BinOperationNode* binNode{ static_cast<BinOperationNode*>(node) };
		 if (binNode->_operator._type._name == TokenTypeList["PLUS"]->_name)
		 {
			 return std::pair<int, std::string>{ run(new ExpressionNode(binNode->_leftNode)).first + run(new ExpressionNode(binNode->_rightNode)).first, ""}; // !!!!!!!!!!!!!!!!!!!!
		 }
		 else if (binNode->_operator._type._name == TokenTypeList["MINUS"]->_name)
		 {
			 return std::pair<int, std::string>{ run(new ExpressionNode(binNode->_leftNode)).first - run(new ExpressionNode(binNode->_rightNode)).first, ""}; // !!!!!!!!!!!!!!!!!!!!
		 }
		 else if (binNode->_operator._type._name == TokenTypeList["ASSIGN"]->_name)
		 {
			 auto result = run( new ExpressionNode(binNode->_rightNode));
			 VariableNode* varNode{ static_cast<VariableNode*>(new ExpressionNode(binNode->_leftNode)) };
			 _scope[varNode->_variable._text] = result.first;
			 return result;
		 }
		 std::cout << "A6" << std::endl;

	 }
	 if (instanceof<VariableNode>(node))
	 {
		 std::cout << "A7" << std::endl;

		 VariableNode* varNode{ static_cast<VariableNode*>(node) };
		 //std::unordered_map<std::string, std::string> _scope;
		 if (_scope[varNode->_variable._text] != "")
		 {
			 return std::pair<int, std::string>{ 0, _scope[varNode->_variable._text] };
		 }
		 else throw "Error. Peremennaya c nazvaniem ... ne obnaruzhena";
		 std::cout << "A8" << std::endl;

	 }
	 if (instanceof<StatementsNode>(node))
	 {
		 std::cout << "A9" << std::endl;

		 StatementsNode* stateNode{ static_cast<StatementsNode*>(node) };
		 for (ExpressionNode codeString : stateNode->_codeStrings)
		 {
			 run(new ExpressionNode(codeString));
		 };
		 std::cout << "A10" << std::endl;

		 return std::pair<int, std::string>{0, ""};
	 }
	 std::cout << "A11" << std::endl;
	 return std::pair<int, std::string>{0, ""};

	 //throw "ERROREORROER";

 }