#include "Token.h"

Token::Token(TokenType& t, std::string txt, int p) : type(t), text(txt), pos(p) {};