#include "Token.h"

Token::Token(TokenType& t, std::string txt, int p) : _type(t), _text(txt), _pos(p) {};

Token::Token(const Token& t) : _type(t._type), _text(t._text), _pos(t._pos) {};


std::string Token::getText()
{
	return _text;
}