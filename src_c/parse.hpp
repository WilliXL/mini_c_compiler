# include "lex.hpp"
#include <stdexcept>

using namespace std;

namespace parser
{

class Expression
{
    public:
        Expression(int i) { integer = i; }
        int get_int(void) { return integer; }
    private:
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
        Function(string name, Statement* statement)
        {
            id = name;
            s = statement;
        }
        Statement* get_statement(void) { return s; }
        string get_id(void) { return id; }
    private:
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
        bool has_next(void) { return curr_token < tokens.size() - 1; }
        lexer::Token next(void) { curr_token++; return tokens[curr_token]; }
        Program* root;
};

} // namspace parser