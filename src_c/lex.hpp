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
<<<<<<< HEAD
};

union TokenValue
{
    char s[100];
    int i;
=======
>>>>>>> 6496488d62609fc338be2aa0dd38efe6198d8585
};

class Token
{
    public:
<<<<<<< HEAD
        Token(TokenType type, TokenValue v) { t = type; val = v; }
        // void set_val(TokenValue value) { val = value; }
        TokenType token_type(void) { return t; }
        TokenValue value(void) { return val; }
=======
        Token(TokenType type) { t = type; val = NULL; }
        void set_val(void* value) { val = value; }
        TokenType token_type(void) { return t; }
        void* value(void) { return val; }
>>>>>>> 6496488d62609fc338be2aa0dd38efe6198d8585
    private:
        TokenType t;
        TokenValue val; // used for identifiers and literals
};