#include "AssignStatement.h"

std::map<std::string, double> codesVariables {};

void AssignStatement::execute()
{
	double result = expression.calculate();
	codesVariables[variable] = result;
};