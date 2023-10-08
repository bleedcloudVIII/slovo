#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.h"
#include "Token.h"
int main()
{
    std::ifstream file("main.slovo");
    std::string code = "a = 5 + 9;";
    

    Lexer* lexer = new Lexer(code);
    //lexer->lexAnalysis();
    std::vector<Token> tokenList = lexer->lexAnalysis();
    int size = tokenList.size();

    for (int i = 0; i < tokenList.size(); i++)
    {
        std::cout << tokenList[i]._text << std::endl;
    }
}