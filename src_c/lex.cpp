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

void* parse_word(string str, size_t* idx, vector<Token>* token_list)
{
    TokenValue v = {0};
    size_t i = *idx;
    if (str.find("int") == i)
    {
        Token t(IntegerKeyword, v);
        token_list->push_back(t);
        *idx += 3;
    }
    else if (str.find("return") == i)
    {
        Token t(ReturnKeyword, v);
        token_list->push_back(t);
        *idx += 6;
    }
    else // looking for an identifier
    {
        cout << "YAH" << endl;
        int n = i;
        while (isalpha(str[n]))
        {
            n++;
        }
        *idx = n-1;
        TokenValue v;
        strcpy(v.s, (char*)(str.substr(i, n-i)).c_str());
        Token t(Identifier, v);
        token_list->push_back(t);
    }
}

void* lex(string filename, vector<Token>* token_list)
{
    // char space = ' ';
    ifstream file(filename.c_str());
    string str;
    size_t c;
    TokenValue v = {0};
    while (getline(file, str))
    {
        c = 0;
        while (c < str.length())
        {
            // cout << str[c] << endl;
            if (isspace(str[c]))
            {
                goto next;
            }
            else if (str[c] == '{')
            {
                Token t(OpenBrace, v);
                token_list->push_back(t);
            }
            else if (str[c] == '}')
            {
                Token t(CloseBrace, v);
                token_list->push_back(t);
            }
            else if (str[c] == '(')
            {
                Token t(OpenParen, v);
                token_list->push_back(t);
            }
            else if (str[c] == ')')
            {
                Token t(CloseParen, v);
                token_list->push_back(t);
            }
            else if (str[c] == ';')
            {
                Token t(Semicolon, v);
                token_list->push_back(t);
            }
            else if (is_digit_ascii(str[c]))
            {
                int i = str[c] - '0';
                int n = c; n++;
                while (isdigit(str[n]))
                {
                    i *= 10;
                    i += (str[n] - '0');
                    n++;
                }
                c = n-1;
                TokenValue v; v.i = i;
                Token t(Integer, v);
                token_list->push_back(t);
            }
            else if (is_digit_ascii(str[c]))
            {
                int i = str[c] - '0';
                int n = c; n++;
                while (isdigit(str[n]))
                {
                    i *= 10;
                    i += (str[n] - '0');
                    n++;
                }
                c = n-1;
                TokenValue v;
                v.i = i;
                Token t(Integer, v);
                token_list->push_back(t);
            }
            else
            {
                parse_word(str, &c, token_list);
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
    for (size_t i = 0; i < token_list.size(); ++i)
    {
        if (token_list[i].token_type() == Identifier)
        {
            cout << token_list[i].value().s << ", ";
        }
        if (token_list[i].token_type() == Integer)
        {
            cout << token_list[i].value().i << ", ";
        }
    }
    cout << endl;
    cout << "Lex'd ID: " << (token_list[1].value().s) << endl;
    return 0;
}