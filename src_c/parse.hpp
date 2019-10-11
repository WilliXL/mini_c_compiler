# include "lex.hpp"
#include <stdexcept>

using namespace std;

namespace parser
{

class Expression
{
    public:
        Expression(int i, lexer::TokenType t) { integer = i; type = t;}
        int get_int(void) { return integer; }
        lexer::TokenType get_type(void) { return type; }
    private:
        lexer::TokenType type;
        int integer;
};

class Statement
{
    public:
        Statement(Expression* e) { exp = e; }
        Expression* get_expression(void) { return exp; }
    private:
        Expression* exp;
};

class Function
{
    public:
        Function(string name, Statement* statement, lexer::TokenType rt)
        {
            id = name;
            s = statement;
            return_type = rt;
        }
        Statement* get_statement(void) { return s; }
        string get_id(void) { return id; }
        string get_return_type(void) { return lexer::get_string(return_type); }
    private:
        lexer::TokenType return_type;
        string id;
        Statement* s;
};

class Program
{
    public:
        Program(Function* f) { func = f; }
        Function* get_func(void) { return func; }
    private:
        Function* func;
};

class Parser
{
    public:
        Parser(vector<lexer::Token>* token_list) { tokens = *token_list; }
        void parse_program(void);
        void print_tree(void);
        Program* get_tree(void) { return root; }
    private:
        void print_function(Function* f);
        void print_statement(Statement* s);
        void print_expression(Expression* e);
        void fail_format(string err);
        Function* parse_function(void);
        Statement* parse_statement(void);
        Expression* parse_expression(void);
        vector<lexer::Token> tokens;
        int curr_token = -1;
        bool has_next(void) { return curr_token < (int)tokens.size() - 1; }
        lexer::Token next(void) { curr_token++; return tokens[curr_token]; }
        Program* root;
};

} // namspace parser