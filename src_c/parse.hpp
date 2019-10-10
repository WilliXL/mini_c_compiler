# include "lex.hpp"
#include <stdexcept>

using namespace std;

namespace parser
{

enum NodeType
{
    program,   // 0
    function,  // 1
    statement, // 2
    expression // 3
};

class Expression
{
    public:
        Expression(int i) { integer = i; }
    private:
        int integer;
};

class Statement
{
    public:
        Statement(Expression* e) { exp = e; }
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
    private:
        string id;
        Statement* s;
};

class Program
{
    public:
        Program(Function* f) { func = f; }
    private:
        Function* func;
};

class Parser
{
    public:
        Parser(vector<lexer::Token>* token_list) { tokens = *token_list; }
        void parse_program(void);
        void print_tree(void);
    private:
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