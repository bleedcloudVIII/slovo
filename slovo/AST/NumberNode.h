#pragma once
#include "../Token.h"
#include "ExpressionNode.h"

class NumberNode//: public ExpressionNode
	// ����� ��� Node �����
{
public:
	double value;
	double calculate();

	NumberNode(double);
};

