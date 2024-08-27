#pragma once
#include "ExpressionNode.h"
#include "../Token.h"

class VariableNode//: public ExpressionNode
	// Класс для переменных Node
{
public:
	Token variable;
	VariableNode(Token);
};

