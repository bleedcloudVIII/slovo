#pragma once
#include "../Token.h"
#include "ExpressionNode.h"

class NumberNode//: public ExpressionNode
	// ����� ��� Node �����
{
public:
	Token number;

	NumberNode(Token);
};

