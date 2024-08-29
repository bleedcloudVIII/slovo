#include "Token.h"

Token::Token(TokenType t, std::string txt) : type(t), text(txt) {};

Token::Token(const Token& t) : type(t.type), text(t.text) {};

//void Token::operator=(Token t)
//{
//	type = t.type;
//	pos = t.pos;
//	text = t.text;
//}