#pragma once
#include "../Token.h"
#include "ExpressionNode.h"

class NumberNode: public ExpressionNode
{
public:
	Token _number;

	NumberNode(Token);
	
};

