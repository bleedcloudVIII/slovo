//#pragma once
//
//#include <vector>
//#include "Token.h"
//#include <unordered_map>
//#include <string>
//#include <variant>
//#include "AST/ExpressionNode.h"
//#include "AST/StatementsNode.h"
//#include "AST/NumberNode.h"
//#include "AST/VariableNode.h"
//#include "AST/BinOperationNode.h"
//#include "AST/UnarOperationNode.h"
//#include "AST/StringNode.h"
//
//class Parser
//{
//public:
//	std::vector<Token> tokens;
//	int pos = 0;
//	std::unordered_map<std::string, std::string> scope;
//
//	Parser(std::vector<Token>);
//
//	std::variant<Token, int> match(std::vector<TokenType>);
//	Token require(std::vector<TokenType>);
//	ExpressionNode parseExpression();
//	ExpressionNode parseVariableOrNumber();
//	ExpressionNode parseCode();
//	ExpressionNode parseFormula();
//	ExpressionNode parseParenthese();
//	ExpressionNode parsePrint();
//	//ExpressionNode _parseSkobki();
//	//std::pair<int, std::string> run(ExpressionNode* node);
//	//int run(ExpressionNode*);
//	int run(ExpressionNode*);
//};
//
