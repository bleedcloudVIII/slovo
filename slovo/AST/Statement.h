#pragma once
#include "ExpressionNode.h"

class Statement
{
public:
	/*ExpressionNode* rootOfStatement;
	Statement* nextStatemnt;*/
	virtual void execute();
};