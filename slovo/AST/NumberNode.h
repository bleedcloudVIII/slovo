#pragma once
#include "../Token.h"
#include "ExpressionNode.h"

class NumberNode//: public ExpressionNode
	// Класс для Node числа
{
public:
	double value;
	virtual double eval();

	NumberNode(double);
};

