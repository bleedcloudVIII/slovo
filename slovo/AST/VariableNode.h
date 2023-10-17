#pragma once
#include "ExpressionNode.h"
#include "../Token.h"
class VariableNode: public ExpressionNode
{
public:
	Token _variable;
	VariableNode(Token);
};

