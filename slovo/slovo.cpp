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
    lexer->lexAnalysis();
    Parser* parser = new Parser(lexer->_tokenList);
    ExpressionNode rootNode = parser->_parseCode();
    ExpressionNode* n = new ExpressionNode(rootNode);
    parser->run(n);
}