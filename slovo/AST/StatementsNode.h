#pragma once
#include "ExpressionNode.h"
#include <vector>
#include <string>

class StatementsNode//: public ExpressionNode
{
public:
	std::vector<ExpressionNode> codeStrings;

	StatementsNode();

	void addNode(ExpressionNode);

};

