#pragma once
#include "ExpressionNode.h"
#include "../Token.h"

class VariableNode//: public ExpressionNode
	// ����� ��� ���������� Node
{
public:
	std::string variable;
	VariableNode(std::string);
};

