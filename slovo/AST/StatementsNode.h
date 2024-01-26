#pragma once
#include "ExpressionNode.h"
#include <vector>
#include <string>

class StatementsNode//: public ExpressionNode
{
public:
	std::vector<ExpressionNode> _codeStrings;

	StatementsNode();

	void _addNode(ExpressionNode);

};

