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

class ExpressionNode
{
public:
	BinOperationNode* _binNode = nullptr;
	NumberNode* _numNode = nullptr;
	StatementsNode* _stateNode = nullptr;
	UnarOperationNode* _unarNode = nullptr;
	VariableNode* _varNode = nullptr;

	ExpressionNode(BinOperationNode*);
	ExpressionNode(NumberNode*);
	ExpressionNode(StatementsNode*);
	ExpressionNode(UnarOperationNode*);
	ExpressionNode(VariableNode*);
	ExpressionNode();
};

