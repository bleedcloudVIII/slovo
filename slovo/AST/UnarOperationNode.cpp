#include "UnarOperationNode.h"

UnarOperationNode::UnarOperationNode(Token oprtr, std::variant<BinOperationNode*, std::variant<NumberNode*, VariableNode*>> oprnd) : _operator(oprtr), _operand(oprnd) {};