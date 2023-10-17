#pragma once
#include "ExpressionNode.h"
#include "NumberNode.h"
#include "VariableNode.h"
#include "../Token.h"
#include <variant>

class BinOperationNode: public ExpressionNode
{
public:
	Token _operator;
	std::variant<NumberNode*, VariableNode*> _leftNode;
	std::variant<NumberNode*, VariableNode*> _rightNode;
	//ExpressionNode _leftNode;
	//ExpressionNode _rightNode;

	BinOperationNode(Token, std::variant<NumberNode*, VariableNode*>, std::variant<NumberNode*, VariableNode*>);
};

