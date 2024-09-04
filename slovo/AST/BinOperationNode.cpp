#include "BinOperationNode.h"


BinOperationNode::BinOperationNode(char t, double l, double r) : _operator(t), left(l), right(r) {};

BinOperationNode::BinOperationNode(char t, ExpressionNode l, ExpressionNode r) : _operator(t), left(l.calculate()), right(r.calculate()) {};

BinOperationNode::BinOperationNode(char t, NumberNode l, NumberNode r) : _operator(t), left(l.calculate()), right(r.calculate()) {};

BinOperationNode::BinOperationNode() : _operator(), right(0), left(0) {}; // MB oshibka



double BinOperationNode::calculate()
{
	switch (_operator)
	{
		case '-': return left - right;
		case '+': return left + right;
		case '*': return left * right;
		case '/': return left / right;
	};
}

//BinOperationNode::BinOperationNode(char t, ExpressionNode l, ExpressionNode r) : _operator(t), rightNode(r), leftNode(l) {};
//
//BinOperationNode::BinOperationNode() : _operator(), rightNode(), leftNode() {}; // MB oshibka



//double BinOperationNode::calculate()
//{
//	switch (_operator)
//	{
//		case '-': return leftNode.calculate() - rightNode.calculate();
//		case '+': return leftNode.calculate() + rightNode.calculate();
//		case '*': return leftNode.calculate() * rightNode.calculate();
//		case '/': return leftNode.calculate() / rightNode.calculate();
//	};
//}