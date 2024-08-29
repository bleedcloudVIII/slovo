//#include "Parser.h"
//#include <iostream>
//#include <stack>
//
//Parser::Parser(std::vector<Token> t) : tokens(t) {};
//
//bool find(std::vector<TokenType> tokenList, Token token)
//{
//	for (int i = 0; i < tokenList.size(); i++)
//		if (tokenList[i].name == token.type.name) return true;
//	return false;
//}
//
//std::variant<Token, int> Parser::match(std::vector<TokenType> expected)
//{
//	if (pos < tokens.size())
//	{
//		const Token currentToken = tokens[pos];
//
//		if (find(expected, currentToken))
//		{
//			pos += 1;
//			return currentToken;
//		}
//	}
//	return -1;
//};
//
//// Proverka kakaya tekushaya Noda? Sovpadaet li s tem, chto tebe nuzhno
//// Esli da, to pomenyat nazvanie (naprimer "isCurrentNode")
//Token Parser::require(std::vector<TokenType> expected)
//{
//	const std::variant<Token, int> token = match(expected);
//	if (token.index() == 1)
//	{
//		std::cout << "Error on pos " << pos << std::endl;
//		std::cout << "Ошибка на позиции " << pos << std::endl;
//	}
//	return std::get<Token>(token);
//};
//
//std::string removeSTRING(std::string str)
//{
//	std::string result = "";
//	for (int i = 1; i < str.size() - 1; i++)
//		result.push_back(str[i]);
//	return result;
//};
//
//ExpressionNode Parser::parseVariableOrNumber()
//{
//	const std::variant<Token, int> string = match({ *TokenTypeList["STRING"] });
//	if (string.index() != 1)
//	{
//		StringNode* strNode = new StringNode(std::get<Token>(string));
//		strNode->str.text = removeSTRING(strNode->str.text);
//		return ExpressionNode(strNode);
//	};
//	const std::variant<Token, int> number = match({ *TokenTypeList["NUMBER"] });
//	if (number.index() != 1) return ExpressionNode(new NumberNode(std::get<Token>(number)));
//	const std::variant<Token, int> variable = match({ *TokenTypeList["VARIABLE"] });
//	if (variable.index() != 1) return ExpressionNode(new VariableNode(std::get<Token>(variable)));
//	std::cout << "Error. Ozhidalos chislo ili peremennaya ili stroka." << std::endl;
//	std::cout << "Ошибка. Ожидалось или число, или переменная." << std::endl;
//	throw "ERROR";
//
//}
//
//ExpressionNode Parser::parseParenthese()
//{
//	if (match({ *TokenTypeList["LPAR"] }).index() != 1)
//	{
//		ExpressionNode node = parseFormula();
//		require({ *TokenTypeList["RPAR"] });
//		return node;
//	}
//	else
//	{
//		return parseVariableOrNumber();
//	}
//}
//
//ExpressionNode Parser::parsePrint()
//{
//	std::variant<Token, int> t = match({ *TokenTypeList["LOG"]});
//	if (t.index() != 1)
//	{
//		return ExpressionNode(new UnarOperationNode(std::get<Token>(t), parseFormula()));
//	}
//	std::cout << "ERROR." << std::endl;
//	throw "Ожидается унарный оператор log.[Ozhidalsya unarniy operator log]";
//}
//
//
//ExpressionNode Parser::parseFormula()
//{
//	ExpressionNode leftNode = parseParenthese();
//	std::variant<Token, int> oprtr = match({ *TokenTypeList["MINUS"], *TokenTypeList["PLUS"], *TokenTypeList["MULTIPLICATION"], *TokenTypeList["DIVISON"] });
//	while (oprtr.index() != 1)
//	{
//		const ExpressionNode rightNode = parseParenthese();
//		leftNode = ExpressionNode(new BinOperationNode(std::get<Token>(oprtr), leftNode, rightNode));
//		oprtr = match({ *TokenTypeList["MINUS"], *TokenTypeList["PLUS"], *TokenTypeList["MULTIPLICATION"], *TokenTypeList["DIVISON"] });
//	}
//	return leftNode;
//}
//
//ExpressionNode Parser::parseExpression()
//{
//
//	const std::variant<Token, int> m = match({ *TokenTypeList["VARIABLE"]});
//	if (m.index() == 1)
//	{
//		// Если не переменная, то ожидаем консоль(log)
//		ExpressionNode printNode = parsePrint();
//		return printNode;
//	}
//	pos -= 1; // Возвращаем обратно позицию, т.к. в match() делали + 1
//	ExpressionNode variableNode = parseVariableOrNumber();
//	const std::variant<Token, int> assignOperator = match({ *TokenTypeList["ASSIGN"] });
//	if (assignOperator.index() != 1) // If on pos assign
//	{
//		const ExpressionNode rightFormulaNode = parseFormula();
//		BinOperationNode* binaryNode = new BinOperationNode(std::get<Token>(assignOperator), variableNode, rightFormulaNode);
//		return ExpressionNode(binaryNode);
//	}
//	std::cout << "Error. After peremennoi ozhidaetsya operator prisvoeniya." << std::endl;
//	std::cout << "Ошибка. После переменной ожидается оператор присвоения на позиции " << pos << std::endl;
//	throw "ERROR";
//};
//
//// Создание массива StatementNode
//// Sozdanie massiva StatementNode
//ExpressionNode Parser::parseCode()
//{
//
//	StatementsNode* root = new StatementsNode;
//	while (pos < tokens.size())
//	{
//
//		const ExpressionNode codeStringNode = parseExpression();
//		require({ *TokenTypeList["SEMICOLON"] });
//		root->addNode(codeStringNode);
//	}
//	return ExpressionNode(root);
//};
//
// std::stack<int> num_stack{};
// std::stack<std::string> str_stack{};
//
//int Parser::run(ExpressionNode* node)
//{
//	if (node->numNode != nullptr)
//	{
// 		num_stack.push(std::stoi(node->numNode->number.text));
// 		return 0;
//	}
//	if (node->strNode != nullptr)
//	{
//		str_stack.push(node->strNode->str.text);
//		return 1;
//	}
//	if (node->unarNode != nullptr)
//	{
//
//		if (node->unarNode->_operator.type.name == TokenTypeList["LOG"]->name)
//		{
//			int result = run(new ExpressionNode(node->unarNode->operand));
//			if (result == 0)
//			{
//				std::cout << num_stack.top() << std::endl;
//				num_stack.pop();
//			}
//			else if (result == 1)
//			{
//				std::cout << str_stack.top() << std::endl;
//				str_stack.pop();
//			}
//			else if (result == 2)
//			{
//				std::cout << "return 2(null)  ?";
//			}
//			return 2;
//		}
//	}
//	if (node->binNode != nullptr)
//	{
//		if (node->binNode->_operator.type.name == TokenTypeList["PLUS"]->name)
//		{
//			run(new ExpressionNode(node->binNode->leftNode));
//			int result = num_stack.top();
//			num_stack.pop();
//			run(new ExpressionNode(node->binNode->rightNode));
//			result += num_stack.top();
//			num_stack.pop();
//			num_stack.push(result);
//			return 0;
//		}
//		else if (node->binNode->_operator.type.name == TokenTypeList["MINUS"]->name)
//		{
//			run(new ExpressionNode(node->binNode->leftNode));
//			int result = num_stack.top();
//			num_stack.pop();
//			run(new ExpressionNode(node->binNode->rightNode));
//			result -= num_stack.top();
//			num_stack.pop();
//			num_stack.push(result);
//			return 0;
//		}
//		else if (node->binNode->_operator.type.name == TokenTypeList["MULTIPLICATION"]->name)
//		{
//			run(new ExpressionNode(node->binNode->leftNode));
//			int result = num_stack.top();
//			num_stack.pop();
//			run(new ExpressionNode(node->binNode->rightNode));
//			result *= num_stack.top();
//			num_stack.pop();
//			num_stack.push(result);
//			return 0;
//		}
//		else if (node->binNode->_operator.type.name == TokenTypeList["DIVISON"]->name)
//		{
//			run(new ExpressionNode(node->binNode->leftNode));
//			int result = num_stack.top();
//			num_stack.pop();
//			run(new ExpressionNode(node->binNode->rightNode));
//			result /= num_stack.top();
//			num_stack.pop();
//			num_stack.push(result);
//			return 0;
//		}
//		else if (node->binNode->_operator.type.name == TokenTypeList["ASSIGN"]->name)
//		{
//			int result = run(new ExpressionNode(node->binNode->rightNode));
//			if (result == 0)
//			{
//				scope[node->binNode->leftNode.varNode->variable.text] = std::to_string(num_stack.top());
//				num_stack.pop();
//				return 2;
//			}
//			else if (result == 1)
//			{
//				scope[node->binNode->leftNode.varNode->variable.text] = str_stack.top();
//				str_stack.pop();
//				return 2;
//			}
//			else if (result == 2)
//			{
//				std::cout << "???" << std::endl;
//			}
//			return 2;
//		}
//	}
//	if (node->varNode != nullptr)
//	{
//		if (scope[node->varNode->variable.text] != "")
//		{
//			try {
//				int result = std::stoi(scope[node->varNode->variable.text]);
//				num_stack.push(result);
//				return 0;
//			}
//			catch (...)
//			{
//				str_stack.push(scope[node->varNode->variable.text]);
//				return 1;
//			}
//		}
//		else throw "Error. Peremennaya c nazvaniem ... ne obnaruzhena";
//	}
//	if (node->stateNode != nullptr)
//	{
//		for (ExpressionNode codeString : node->stateNode->codeStrings)
//		{
//			run(new ExpressionNode(codeString));
//		};
//		return 2;
//	}
//
//	throw "ERROREORROER";
// }