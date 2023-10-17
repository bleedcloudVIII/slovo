#include "StatementsNode.h"

void StatementsNode::_addNode(std::variant<UnarOperationNode*, BinOperationNode*> n)
{
	_codeStrings.push_back(n);
	
}