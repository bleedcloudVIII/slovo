#pragma once
#include "../Token.h"
#include "ExpressionNode.h"

class NumberNode//: public ExpressionNode
	// ����� ��� Node �����
{
public:
	double value;
	virtual double eval();

	NumberNode(double);
};

