#pragma once
#include "ExpressionNode.h"
#include <vector>
#include <string>

class StatementsNode//: public ExpressionNode 
	// Класс для строчки кода
{
public:
	std::vector<ExpressionNode> codeStrings;

	StatementsNode();

	void addNode(ExpressionNode);

};

