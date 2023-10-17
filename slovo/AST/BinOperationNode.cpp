#include "BinOperationNode.h"

BinOperationNode::BinOperationNode(Token t, std::variant<NumberNode*, VariableNode*> l, std::variant<NumberNode*, VariableNode*> r) : _operator(t), _rightNode(r), _leftNode(l) {};