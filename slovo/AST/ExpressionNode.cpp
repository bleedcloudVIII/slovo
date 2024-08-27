#include "ExpressionNode.h"

ExpressionNode::ExpressionNode(BinOperationNode* p) : binNode(p) {};
ExpressionNode::ExpressionNode(NumberNode* p) : numNode(p) {};
ExpressionNode::ExpressionNode(StatementsNode* p) : stateNode(p) {};
ExpressionNode::ExpressionNode(UnarOperationNode* p) : unarNode(p) {};
ExpressionNode::ExpressionNode(VariableNode* p) : varNode(p) {};
ExpressionNode::ExpressionNode(StringNode* p) : strNode(p) {};

ExpressionNode::ExpressionNode() : binNode(nullptr),
								   numNode(nullptr),
								   stateNode(nullptr), 
								   unarNode(nullptr), 
								   varNode(nullptr) {};