#pragma once

//#include "BinOperationNode.h";
//#include "NumberNode.h";
//#include "StatementsNode.h";
//#include "UnarOperationNode.h";
//#include "VariableNode.h";

class BinOperationNode;
class NumberNode;
class StatementsNode;
class UnarOperationNode;
class VariableNode;
class StringNode;

class ExpressionNode
{
public:
	BinOperationNode* binNode = nullptr;
	NumberNode* numNode = nullptr;
	StatementsNode* stateNode = nullptr;
	UnarOperationNode* unarNode = nullptr;
	VariableNode* varNode = nullptr;
	StringNode* strNode = nullptr;

	ExpressionNode(BinOperationNode*);
	ExpressionNode(NumberNode*);
	ExpressionNode(StatementsNode*);
	ExpressionNode(UnarOperationNode*);
	ExpressionNode(VariableNode*);
	ExpressionNode(StringNode*);
	ExpressionNode();
};

