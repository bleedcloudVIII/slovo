#include "Token.h"

Token::Token(TokenType& t, std::string txt, int p) : _type(t), _text(txt), _pos(p) {};

Token::Token(const Token& t) : _type(t._type), _text(t._text), _pos(t._pos) {};

Token::Token() : _text(""), _pos(-1)
{
	TokenType a;
	_type = a;
};

std::string Token::getText()
{
	return _text;
}

//void Token::operator=(Token t)
//{
//	_type = t._type;
//	_pos = t._pos;
//	_text = t._text;
//}