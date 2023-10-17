#pragma once
#include "ExpressionNode.h"
#include "../Token.h"

class BinOperationNode: public ExpressionNode
{
public:
	Token _operator;
	ExpressionNode _leftNode;
	ExpressionNode _rightNode;

	BinOperationNode(Token, ExpressionNode, ExpressionNode);
};

