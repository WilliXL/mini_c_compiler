#include <fstream>
#include "lex.hpp"

using namespace std;

void* parse_word_or_const(string str, size_t idx, vector<Token>* token_list)
{
    return;
}

void* lex(string filename, vector<Token>* token_list)
{
    // char space = ' ';
    ifstream file(filename.c_str());
    string str;
    while (getline(file, str))
    {
        for (size_t c = 0; c < str.length(); ++c)
        {
            if (str[c] == '{')
            {
                Token t(OpenBrace);
                token_list->push_back(t);
            }
            else if (str[c] == '}')
            {
                Token t(CloseBrace);
                token_list->push_back(t);
            }
            else if (str[c] == '(')
            {
                Token t(OpenParen);
                token_list->push_back(t);
            }
            else if (str[c] == ')')
            {
                Token t(CloseParen);
                token_list->push_back(t);
            }
            else if (str[c] == ';')
            {
                Token t(Semicolon);
                token_list->push_back(t);
            }
            else
            {
                parse_word_or_const(str, c, token_list);
            }
        }
    }
}


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        cout << "You did not enter a file to lex" << endl;;
        return 1;
    }
    string to_lex = argv[1];
    if (to_lex.find(".c") == string::npos)
    {
        cout << "NOT a C file, cannot lex" << endl;
        return 1;
    }
    cout << "Now lexing " << to_lex << endl;
    vector<Token> token_list;
    lex(to_lex, &token_list);
    return 0;
}