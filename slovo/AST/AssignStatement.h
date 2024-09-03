#pragma once
#include <string>
#include "ExpressionNode.h"
#include <map>

extern std::map<std::string, double> codesVariables;

class AssignStatement
{
	std::string variable;
	ExpressionNode expression;

	void execute();
};

