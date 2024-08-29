#include "BinOperationNode.h"

BinOperationNode::BinOperationNode(char t, ExpressionNode l, ExpressionNode r) : _operator(t), rightNode(r), leftNode(l) {};

double BinOperationNode::eval()
{
	switch (_operator)
	{
		case '-': return leftNode.eval() - rightNode.eval();
		case '+': return leftNode.eval() + rightNode.eval();
		case '*': return leftNode.eval() * rightNode.eval();
		case '/': return leftNode.eval() / rightNode.eval();
	};
}