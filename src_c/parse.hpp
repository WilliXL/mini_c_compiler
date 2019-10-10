# include "lex.hpp"

using namespace std;

enum NodeType
{
    Program,
    Function,
    Statement,
    Expression
};

class ASTNode
{
    public:
        ASTNode(NodeType t) { type = t; }
    private:
        NodeType type;
};

class Parser
{
    public:
        Parser(vector<lexer::Token>* token_list)
        {
            tokens = *token_list;
        }
    private:
        vector<lexer::Token> tokens;
        int curr_token = -1;
        lexer::Token next(void) { curr_token++; return tokens[curr_token]; }
};