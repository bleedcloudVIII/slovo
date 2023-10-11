#include "StatementsNode.h"

void StatementsNode::_addNode(ExpressionNode n)
{
	_codeStrings.push_back(n);
}