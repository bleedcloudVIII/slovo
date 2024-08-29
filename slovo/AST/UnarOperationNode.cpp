#include "UnarOperationNode.h"

UnarOperationNode::UnarOperationNode(char oprtr, ExpressionNode oprnd) : _operator(oprtr), operand(oprnd) {};

double UnarOperationNode::eval()
{
	switch (_operator)
	{
		case '-': return -operand.eval();
		case '+': return operand.eval();
	}
}