#include "UnarOperationNode.h"

UnarOperationNode::UnarOperationNode(char oprtr, ExpressionNode oprnd) : _operator(oprtr), operand(oprnd) {};

double UnarOperationNode::getValue()
{
	switch (_operator)
	{
		case '-': return -operand.getValue();
		case '+': return operand.getValue();
	}
}