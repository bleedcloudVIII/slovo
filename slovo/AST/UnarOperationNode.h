#pragma once
#include "ExpressionNode.h"
#include "../Token.h"

class UnarOperationNode//: public ExpressionNode
{
public:
	char _operator;
	ExpressionNode operand;

	UnarOperationNode(char, ExpressionNode);

	double calculate();
};

