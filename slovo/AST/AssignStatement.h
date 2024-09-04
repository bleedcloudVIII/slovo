#pragma once
#include <string>
#include "ExpressionNode.h"
#include <map>

extern std::map<std::string, double> codesVariables;

class AssignStatement
{
public:

	std::string variable;
	double expression;

	void execute();

	AssignStatement(std::string, ExpressionNode);
	AssignStatement(std::string, double);
};

