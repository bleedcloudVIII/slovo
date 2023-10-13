#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.h"
#include "Token.h"

const int maxlength = INT_MAX;

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

    for (int i = 0; i < tokenList.size(); i++)
    {
        std::cout << tokenList[i]._text << std::endl;
    }
    std::cout << "----------------" << std::endl;

    int b;
    std::cin >> b;
}