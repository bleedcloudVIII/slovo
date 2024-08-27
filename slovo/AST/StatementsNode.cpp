#include "StatementsNode.h"

void StatementsNode::addNode(ExpressionNode n)
{
	codeStrings.push_back(n);
}

StatementsNode::StatementsNode() : codeStrings({}) {};