#include <vector>
#include <cstring>
#include <iostream>

enum TokenType
{
    OpenBrace,
    CloseBrace,
    OpenParen,
    CloseParen,
    Semicolon,
    Keyword,
    Identifier,
    Integer
};

class Token
{
    public:
        Token(TokenType type) { t = type; }
        void set_val(void* value) { val = value; }
    private:
        TokenType t;
        void* val; // used for keyword, identifier, and literals
};