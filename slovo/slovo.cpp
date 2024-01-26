#include <iostream>
#include <fstream>
#include <string>
//#include <Windows.h>

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
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);

    std::ifstream file("main.slovo");
    std::string code;

    char* line = new char[maxlength];
    while (file.getline(line, maxlength))
    {
        code += line;
    }

    Lexer* lexer = new Lexer(code);
    //std::cout << code << std::endl;
    lexer->lexAnalysis();
    //std::vector<Token> tokenList = lexer->lexAnalysis();
    Parser* parser = new Parser(lexer->_tokenList);
    ExpressionNode rootNode = parser->_parseCode();
    ExpressionNode* n = new ExpressionNode(rootNode);
    parser->run(n);

    //TokenType b("asd", "da");
    //Token t(b, "asd", 0);
    //NumberNode* a = new NumberNode(t);

    //std::cout << instanceof<ExpressionNode>(a);

    //for (int i = 0; i < tokenList.size(); i++)
    //{
    //    std::cout << tokenList[i]._text << std::endl;
    //}
    //std::cout << "----------------" << std::endl;   
    

}