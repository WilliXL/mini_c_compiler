#include <vector>
#include <cstring>
#include <iostream>

namespace lexer
{

enum TokenType
{
    OpenBrace,      // 0
    CloseBrace,     // 1
    OpenParen,      // 2
    CloseParen,     // 3
    Semicolon,      // 4
    ReturnKeyword,  // 5
    Identifier,     // 6
    IntegerKeyword, // 7
    Integer         // 8
};

union TokenValue
{
    char s[100];
    int i;
};

class Token
{
    public:
        Token(TokenType type, TokenValue v) { t = type; val = v; }
        // void set_val(TokenValue value) { val = value; }
        TokenType token_type(void) { return t; }
        TokenValue value(void) { return val; }
    private:
        TokenType t;
        TokenValue val; // used for identifiers and literals
};

} //namespace lexer