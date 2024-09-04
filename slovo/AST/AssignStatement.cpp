#include "AssignStatement.h"

std::map<std::string, double> codesVariables {};

AssignStatement::AssignStatement(std::string s, ExpressionNode en) : variable(s), expression(en.calculate()) {};

AssignStatement::AssignStatement(std::string s, double n) : variable(s), expression(n) {};

void AssignStatement::execute()
{
	//codesVariables[variable] = result;
};