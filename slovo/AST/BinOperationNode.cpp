#include "BinOperationNode.h"

BinOperationNode::BinOperationNode(Token t, ExpressionNode l, ExpressionNode r) : _operator(t), rightNode(r), leftNode(l) {};