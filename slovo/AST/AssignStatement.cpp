#include "AssignStatement.h"

std::map<std::string, double> codesVariables {};

AssignStatement::AssignStatement(std::string s, ExpressionNode en) : variable(s), expression(en) {};

void AssignStatement::execute()
{
	double result = expression.calculate();
	codesVariables[variable] = result;
};