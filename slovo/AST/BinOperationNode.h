#pragma once
#include "ExpressionNode.h"
#include "NumberNode.h"
#include "VariableNode.h"
#include "../Token.h"
#include <variant>

class BinOperationNode//:  public ExpressionNode
{
public:
	char _operator;
	ExpressionNode leftNode;
	ExpressionNode rightNode;

	BinOperationNode(char, ExpressionNode, ExpressionNode);

	double getValue();
};

