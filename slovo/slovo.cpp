#include <iostream>
#include <fstream>
#include <string>

#include "Lexer.h"
#include "Token.h"
#include "AST/NumberNode.h"
#include "AST/VariableNode.h"
#include "Parser.h"

const int maxlength = INT_MAX;

template<typename Base, typename T>
inline bool instanceof(const T*)
{
    return std::is_base_of<Base, T>::value;
}

int main()
{
    std::ifstream file("main.slovo");
    std::string code;

    char* line = new char[maxlength];
    while (file.getline(line, maxlength))
    {
        code += line;
    }

    Lexer* lexer = new Lexer(code);

    std::vector<Token> list = lexer->lexAnalysis();
    //Parser* parser = new Parser(lexer->tokenList);
    //ExpressionNode rootNode = parser->parseCode(); // Vozvrashaet koren dereva StatementNode
    //ExpressionNode* n = new ExpressionNode(rootNode);
    //parser->run(n);
    Parser p = Parser(list);
    p.parseTokensToAst();
    return 0;
}