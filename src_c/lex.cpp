#include <ctype.h>
#include "lex.hpp"

using namespace std;

namespace lexer
{

string get_string(int token)
{
    switch(token)
    {
        case OpenBrace: return "{"; break;
        case CloseBrace: return "}"; break;
        case OpenParen: return "("; break;
        case CloseParen: return ")"; break;
        case Semicolon: return ";"; break;
        case ReturnKeyword: return "RETURN"; break;
        case Identifier: return "ID"; break;
        case IntegerKeyword: return "INT"; break;
        case Integer: return "int"; break;
        case Negation: return "-"; break;
        case Complement: return "~"; break;
        case Bang: return "!"; break;
        default: return "NaN"; break;
    }
}

bool Lexer::has_value(int token)
{
    switch(token)
    {
        case Integer: return true; break;
        case Identifier: return true; break;
        default: return false; break;
    }
}

void Lexer::print_tokens(void)
{
    cout << "Token List:" << endl;
    for (size_t ii = 0; ii < token_list.size(); ++ii)
    {
        Token t = token_list[ii];
        cout << "[" << get_string(t.token_type());
        if (has_value(t.token_type()))
        {
            if (t.token_type() == Integer)
            {
                cout << ": " << t.value().i;
            }
            else if (t.token_type() == Identifier)
            {
                cout << ": " << t.value().s;
            }
        }
        if (ii == token_list.size()-1)
        {
            cout << "]";
        }
        else
        {
            cout << "], ";
        }
    }
    cout << endl;
}

void Lexer::lex_word(string str, size_t* idx)
{
    size_t i = *idx;
    if (str.find("int") == i)
    {
        Token t(IntegerKeyword);
        token_list.push_back(t);
        *idx += 3;
    }
    else if (str.find("return") == i)
    {
        Token t(ReturnKeyword);
        token_list.push_back(t);
        *idx += 6;
    }
    else // looking for an identifier
    {
        int n = i;
        while (isalpha(str[n]))
        {
            n++;
        }
        *idx = n-1;
        TokenValue v;
        strcpy(v.s, (char*)(str.substr(i, n-i)).c_str());
        Token t(Identifier);
        t.set_val(v);
        token_list.push_back(t);
    }
}

void Lexer::lex(string filename)
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
            // cout << str[c] << endl;
            if (isspace(str[c]))
            {
                goto next;
            }
            else if (str[c] == '{')
            {
                Token t(OpenBrace);
                token_list.push_back(t);
            }
            else if (str[c] == '}')
            {
                Token t(CloseBrace);
                token_list.push_back(t);
            }
            else if (str[c] == '(')
            {
                Token t(OpenParen);
                token_list.push_back(t);
            }
            else if (str[c] == ')')
            {
                Token t(CloseParen);
                token_list.push_back(t);
            }
            else if (str[c] == ';')
            {
                Token t(Semicolon);
                token_list.push_back(t);
            }
            else if (str[c] == '-')
            {
                Token t(Negation);
                token_list.push_back(t);
            }
            else if (str[c] == '~')
            {
                Token t(Complement);
                token_list.push_back(t);
            }
            else if (str[c] == '!')
            {
                Token t(Bang);
                token_list.push_back(t);
            }
            else if (isdigit(str[c]))
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
                Token t(Integer);
                t.set_val(v);
                token_list.push_back(t);
            }
            else
            {
                lex_word(str, &c);
            }
            next:
                c++;
        }
    }
}
} // namespace lexer

// int main(int argc, char** argv)
// {
//     if (argc < 2)
//     {
//         cout << "You did not enter a file to lex" << endl;;
//         return 1;
//     }
//     string to_lex = argv[1];
//     if (to_lex.find(".c") == string::npos)
//     {
//         cout << "NOT a C file, cannot lex" << endl;
//         return 1;
//     }
//     cout << "Now lexing " << to_lex << endl;
//     lexer::Lexer L;
//     L.lex(to_lex);
//     L.print_tokens();
//     return 0;
// }