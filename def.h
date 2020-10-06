#define register 

#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "parser.tab.h"

#include "string"
#include "unordered_map"
#include "vector"
#include "variant"

using std::string, std::unordered_map, std::vector, std::variant, std::get;
#define PRINT_AST 0
#define PRINT_SYMBOL_TABLE 0

#define DX 3 * sizeof(int)

class Operation
{
public:
    int kind;
    int type;
    variant<int, float, string> data;
    int level;
    int offset;

    Operation();
};

class CodeNode
{
public:
    int op;
    vector<CodeNode*> data;
    Operation opn1, opn2, result;
    CodeNode *next, *prior;

    CodeNode();
};

class ASTNode
{
public:
    int kind;
    variant<int, float, string> data;
    ASTNode *ptr[4];
    int place;
    string Etrue, Efalse;
    string Snext;
    CodeNode *code;
    int type;
    int pos;
    int offset;
    int width;
    int num;

    ASTNode();
};

class Symbol
{
public:
    string name;
    int level;
    int type;
    int paramnum;
    string alias;
    char flag;
    char offset;

    Symbol();
};

ASTNode *make_node(int kind, int pos, vector<ASTNode*> nodes = vector<ASTNode*>{});
void entrypoint(ASTNode *T);
void bool_expression(ASTNode *T);
void expression(ASTNode *T);
void objectCode(CodeNode *head);
void print_lr(CodeNode *head);
int search_symbol_table_with_flag(const string& name, char flag);
