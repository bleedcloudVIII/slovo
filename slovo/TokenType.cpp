#include "TokenType.h"

TokenType::TokenType(std::string n, std::string r): _name(n), _regex(r) {};

TokenType::TokenType() : _name(""), _regex("") {};