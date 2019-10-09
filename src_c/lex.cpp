#include <fstream>
#include <ctype.h>
#include "lex.hpp"

using namespace std;

bool is_digit_ascii(char c)
{
    if (c >= 48 && c <= 57)
    {
        return true;
    }
    return false;
}

void* parse_word(string str, size_t idx, vector<Token>* token_list)
{
    if (str.find("int") == idx)
    {
        Token t(IntegerKeyword);
        token_list->push_back(t);
    }
    else if (str.find("return") == idx)
    {
        Token t(ReturnKeyword);
        token_list->push_back(t);
    }
    else // looking for an identifier
    {
        int n = idx;
        while (isalpha(str[n]))
        {
            n++;
        }
        Token t(Identifier);
        const char* id = (str.substr(idx, n-idx+1)).c_str();
        t.set_val((void*)id);
    }
}

void* lex(string filename, vector<Token>* token_list)
{
    // char space = ' ';
    ifstream file(filename.c_str());
    string str;
    size_t c;
    while (getline(file, str))
    {
        c = 0;
        while (c < str.length())
        {
            cout << str[c] << endl;
            if (isspace(str[c]))
            {
                goto next;
            }
            else if (str[c] == '{')
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
            else if (is_digit_ascii(str[c]))
            {
                cout << "YOIT" << endl;
                Token t(Integer);
                int i = str[c] - '0';
                int n = c; n++;
                while (isdigit(str[n]))
                {
                    i *= 10;
                    i += (str[n] - '0');
                    n++;
                }
                c = n-1;
                t.set_val((void*)i);
                token_list->push_back(t);
            }
            else
            {
                parse_word(str, c, token_list);
            }
            next:
                c++;
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
    cout << "Token List Size: " << token_list.size() << endl;
    cout << "Tokens: " << endl;
    for (size_t i = 0; i < token_list.size(); ++i)
    {
        cout << token_list[i].token_type() << ", ";
    }
    cout << endl;
    return 0;
}