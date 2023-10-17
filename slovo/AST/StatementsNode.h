#pragma once
#include "ExpressionNode.h"
#include "UnarOperationNode.h"
#include "BinOperationNode.h"
#include <vector>
#include <string>
#include <variant>

class StatementsNode: public ExpressionNode
{
public:
	std::vector<std::variant<UnarOperationNode*, BinOperationNode*>> _codeStrings;

	void _addNode(std::variant<UnarOperationNode*, BinOperationNode*>);

};

