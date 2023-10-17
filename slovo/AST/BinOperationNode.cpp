#include "BinOperationNode.h"

BinOperationNode::BinOperationNode(Token t, ExpressionNode l, ExpressionNode r) : _operator(t), _rightNode(r), _leftNode(l) {};