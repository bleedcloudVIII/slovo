#pragma once
#include "ExpressionNode.h"
#include "../Token.h"

class UnarOperationNode//: public ExpressionNode
{
public:
	Token _operator;
	ExpressionNode operand;

	UnarOperationNode(Token, ExpressionNode);
};

