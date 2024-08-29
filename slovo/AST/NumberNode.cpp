#include "NumberNode.h"

double NumberNode::eval()
{
	return value;
};

NumberNode::NumberNode(double a) : value(a) {};