#pragma once
#include "Token.h"
#include "AST/ExpressionNode.h"

class VariableNode: public ExpressionNode // ������������??
{
public:
	Token _variable;

	VariableNode(Token);
};

