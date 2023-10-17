#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.h"
#include "Token.h"
#include "AST/NumberNode.h"
#include "AST/VariableNode.h"
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
    //lexer->lexAnalysis();
    std::vector<Token> tokenList = lexer->lexAnalysis();
    TokenType b("asd", "da");
    Token t(b, "asd", 0);
    NumberNode* a = new NumberNode(t);

    std::cout << instanceof<ExpressionNode>(a);

    //for (int i = 0; i < tokenList.size(); i++)
    //{
    //    std::cout << tokenList[i]._text << std::endl;
    //}
    //std::cout << "----------------" << std::endl;   
    

}