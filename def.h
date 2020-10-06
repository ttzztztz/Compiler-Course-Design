#define register 

#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "parser.tab.h"

#include "string"
#include "unordered_map"
#include "vector"

using std::string, std::unordered_map, std::vector;

#define PRINT_AST 0
#define PRINT_SYMBOL_TABLE 0

#define DX 3 * sizeof(int)

class Operation
{
public:
    int kind;
    int type;
    int const_int;
    float const_float;
    char const_char;
    string id;
    int level;
    int offset;
};

class CodeNode
{
public:
    int op;
    vector<CodeNode*> data;
    Operation opn1, opn2, result;
    CodeNode *next, *prior;
};

class ASTNode
{
public:
    int kind;
    string type_id;
    int type_int; 
    float type_float; 
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
};

ASTNode *make_node(int num, int kind, int pos, ...);
void entrypoint(ASTNode *T);
void bool_expression(ASTNode *T);
void expression(ASTNode *T);
void objectCode(CodeNode *head);
void print_lr(CodeNode *head);
int search_symbol_table_with_flag(const string& name, char flag);