#pragma once
#include "ExpressionNode.h"
#include "../Token.h"

class VariableNode//: public ExpressionNode
	// ����� ��� ���������� Node
{
public:
	Token variable;
	VariableNode(Token);
};

