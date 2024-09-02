#include "BinOperationNode.h"

BinOperationNode::BinOperationNode(char t, ExpressionNode l, ExpressionNode r) : _operator(t), rightNode(r), leftNode(l) {};

double BinOperationNode::getValue()
{
	switch (_operator)
	{
		case '-': return leftNode.getValue() - rightNode.getValue();
		case '+': return leftNode.getValue() + rightNode.getValue();
		case '*': return leftNode.getValue() * rightNode.getValue();
		case '/': return leftNode.getValue() / rightNode.getValue();
	};
}