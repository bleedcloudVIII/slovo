#pragma once

//#include "BinOperationNode.h";
//#include "NumberNode.h";
//#include "StatementsNode.h";
//#include "UnarOperationNode.h";
//#include "VariableNode.h";

class ExpressionNode // �������� ����� ��� ���� Node
{
public:
	
	virtual double calculate();
	virtual ~ExpressionNode();
};

