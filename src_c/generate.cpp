#include "generate.hpp"

using namespace std;

namespace generator
{

void Generator::generate(string name)
{
    parser::Function* function = root->get_func();
    ofstream out;
    out.open(name);
    out << "\t.globl  " << function->get_id() << "\n";
    out << "\t.type   " << function->get_id() << ", @function\n";
    out << function->get_id() << ":" << "\n";

    parser::Statement* statement = function->get_statement();
    parser::Expression* expression = statement->get_expression();

    out << "\tmov\t$" << expression->get_int() << ", %rax\n";
    out << "\tret\n";
    out.close();
}

} // namespace generator


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

    cout << endl;

    parser::Parser p(L.get_tokens());
    p.parse_program();
    p.print_tree();

    parser::Program* root = p.get_tree();

    generator::Generator* g = new generator::Generator(root);
    string output = (to_lex.substr(0,to_lex.length()-2)).append(".s");
    g->generate(output);

    char make_cmd[40];
    char rm_cmd[30];
    sprintf(make_cmd, "gcc %s -o b.out", output.c_str());
    sprintf(rm_cmd, "rm %s", output.c_str());
    system(((char*)make_cmd));
    system((char*)rm_cmd);
}