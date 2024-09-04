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
	//ExpressionNode leftNode;
	//ExpressionNode rightNode;
	double left;
	double right;
	BinOperationNode(char, ExpressionNode, ExpressionNode);
	BinOperationNode(char, double, double);
	BinOperationNode(char, NumberNode, NumberNode);
	BinOperationNode();

	double calculate();
};

