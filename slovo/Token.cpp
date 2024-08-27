#include "Token.h"

Token::Token(TokenType& t, std::string txt, int p) : type(t), text(txt), pos(p) {};

Token::Token(const Token& t) : type(t.type), text(t.text), pos(t.pos) {};

Token::Token() : text(""), pos(-1)
{
	TokenType a;
	type = a;
};

std::string Token::getText()
{
	return text;
}

//void Token::operator=(Token t)
//{
//	type = t.type;
//	pos = t.pos;
//	text = t.text;
//}