#pragma once
#include "ExpressionNode.h"
#include "NumberNode.h"
#include "VariableNode.h"
#include "../Token.h"
#include <variant>

class BinOperationNode: public ExpressionNode
{
public:
	Token _operator;
	ExpressionNode _leftNode;
	ExpressionNode _rightNode;
	//ExpressionNode _leftNode;
	//ExpressionNode _rightNode;

	BinOperationNode(Token, ExpressionNode, ExpressionNode);
};

