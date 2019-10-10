#include "parse.hpp"

using namespace std;

namespace parser
{

void Parser::fail_format(string err)
{
    throw invalid_argument(err);
}

Expression* Parser::parse_expression(void)
{
    lexer::Token t = next();
    int val;
    if (t.token_type() != lexer::Integer)
    {
        fail_format("Expcted integer");
    }
    val = t.value().i;
    Expression* expression = new Expression(val);

    return expression;
}

Statement* Parser::parse_statement(void)
{
    lexer::Token t = next();
    if (t.token_type() != lexer::ReturnKeyword)
    {
        fail_format("Expcted keyword: return");
    }
    Expression* expression = parse_expression();
    Statement* statement = new Statement(expression);
    t = next();
    if (t.token_type() != lexer::Semicolon)
    {
        fail_format("Expected a ;");
    }

    return statement;
}

Function* Parser::parse_function(void)
{
    string name;
    lexer::Token t = next();
    if (t.token_type() != lexer::IntegerKeyword)
    {
        fail_format("Expected keyword: int");
    }
    t = next();
    if (t.token_type() != lexer::Identifier)
    {
        fail_format("Expected an identifer");
    }
    name = t.value().s;
    t = next();
    if (t.token_type() != lexer::OpenParen)
    {
        fail_format("Expcted an (");
    }
    t = next();
    if (t.token_type() != lexer::CloseParen)
    {
        fail_format("Expected a )");
    }
    t = next();
    if (t.token_type() != lexer::OpenBrace)
    {
        fail_format("Expcted an {");
    }
    Statement* statement = parse_statement();
    Function* function = new Function(name, statement);
    t = next();
    if (t.token_type() != lexer::CloseBrace)
    {
        fail_format("Expected a }");
    }
    return function;
}

void Parser::parse_program(void)
{
    Function* function = parse_function();
    Program* program = new Program(function);
    root = program;
}

void Parser::print_expression(Expression* e)
{
    cout << "Expression: " << e->get_int() << endl;
}

void Parser::print_statement(Statement* s)
{
    cout << "Statement" << endl;
    print_expression(s->get_expression());
}

void Parser::print_function(Function* f)
{
    cout << "Function: " << f->get_id() << endl;
    print_statement(f->get_statement());
}

void Parser::print_tree(void)
{
    cout << "Program" << endl;
    print_function(root->get_func());
}

} // namespace parser

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
    lexer::Lexer L;
    L.lex(to_lex);
    L.print_tokens();

    parser::Parser p(L.get_tokens());
    p.parse_program();
    p.print_tree();
}
