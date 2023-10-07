#include "Lexer.h"


std::vector<TokenType*> TokenTypeList = {
	new TokenType("NUMBER", "[0-9]]*"),
	new TokenType("VARIABLE", "[a-z]]*"),
	new TokenType("SEMICOLON", ";"),
	new TokenType("SPACE", "[\\n\\t\\r]"),
	new TokenType("ASSIGN", "="),
	new TokenType("LOG", "log"),
	new TokenType("PLUS", "+"),
	new TokenType("MINUS", "-"),
	new TokenType("LPAR", "\\("),
	new TokenType("RPAR", "\\)"),
};

Lexer::Lexer(std::string c) : code(c) {};

std::vector<Token>& Lexer::lexAnalysis()
{
	while (this->nextToken()) {}
	
};

bool Lexer::nextToken()
{
	if (this->pos >= this->code.length()) return false;
	for (int i = 0; i < TokenTypeList.size(); i++)
	{
		TokenType* tokenType = TokenTypeList[i];

	}
	
};