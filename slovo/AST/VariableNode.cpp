#include "VariableNode.h"


VariableNode::VariableNode(std::string t) : variable(t) {};

double VariableNode::calculate()
{
	return codesVariables[variable];
};