#include "BinOperationNode.h"

BinOperationNode::BinOperationNode(char t, ExpressionNode l, ExpressionNode r) : _operator(t), rightNode(r), leftNode(l) {};

double BinOperationNode::calculate()
{
	switch (_operator)
	{
		case '-': return leftNode.calculate() - rightNode.calculate();
		case '+': return leftNode.calculate() + rightNode.calculate();
		case '*': return leftNode.calculate() * rightNode.calculate();
		case '/': return leftNode.calculate() / rightNode.calculate();
	};
}