#include <vector>
#include <cstring>
#include <iostream>

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

class Token
{
    public:
        Token(TokenType type) { t = type; val = NULL; }
        void set_val(void* value) { val = value; }
        TokenType token_type(void) { return t; }
        void* value(void) { return val; }
    private:
        TokenType t;
        void* val; // used for keyword, identifier, and literals
};