#pragma once
#include "ExpressionNode.h"
#include "NumberNode.h"
#include "VariableNode.h"
#include "../Token.h"
#include <variant>

class BinOperationNode//:  public ExpressionNode
{
public:
	Token _operator;
	ExpressionNode leftNode;
	ExpressionNode rightNode;
	//ExpressionNode _leftNode;
	//ExpressionNode _rightNode;

	BinOperationNode(Token, ExpressionNode, ExpressionNode);
};

