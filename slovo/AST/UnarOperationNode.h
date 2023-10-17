#pragma once
#include "ExpressionNode.h"
#include "../Token.h"
#include "BinOperationNode.h"
#include "NumberNode.h"
#include "VariableNode.h"
#include <variant>

class UnarOperationNode
{
public:
	Token _operator;
	std::variant<BinOperationNode*, std::variant<NumberNode*, VariableNode*>> _operand;

	UnarOperationNode(Token, std::variant<BinOperationNode*, std::variant<NumberNode*, VariableNode*>>);
};

