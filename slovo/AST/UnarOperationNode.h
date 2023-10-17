#pragma once
#include "ExpressionNode.h"
#include "../Token.h"

class UnarOperationNode
{
public:
	Token _operator;
	ExpressionNode _operand;

	UnarOperationNode(Token, ExpressionNode);
};

