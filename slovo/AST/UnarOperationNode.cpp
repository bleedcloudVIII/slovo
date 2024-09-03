#include "UnarOperationNode.h"

UnarOperationNode::UnarOperationNode(char oprtr, ExpressionNode oprnd) : _operator(oprtr), operand(oprnd) {};

double UnarOperationNode::calculate()
{
	switch (_operator)
	{
		case '-': return -operand.calculate();
		case '+': return operand.calculate();
	}
}