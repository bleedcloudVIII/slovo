#include "ExpressionNode.h"

ExpressionNode::ExpressionNode(BinOperationNode* p) : _binNode(p) {};
ExpressionNode::ExpressionNode(NumberNode* p) : _numNode(p) {};
ExpressionNode::ExpressionNode(StatementsNode* p) : _stateNode(p) {};
ExpressionNode::ExpressionNode(UnarOperationNode* p) : _unarNode(p) {};
ExpressionNode::ExpressionNode(VariableNode* p) : _varNode(p) {};
ExpressionNode::ExpressionNode(StringNode* p) : _strNode(p) {};

ExpressionNode::ExpressionNode() : _binNode(nullptr),
								   _numNode(nullptr),
								   _stateNode(nullptr), 
								   _unarNode(nullptr), 
								   _varNode(nullptr) {};