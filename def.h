#define register 

#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "parser.tab.h"

#include "string"
#include "unordered_map"
#include "vector"

using std::string, std::unordered_map, std::vector;

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
    struct Operation opn1, opn2, result;
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

ASTNode *mknode(int num, int kind, int pos, ...);
void semantic_Analysis0(ASTNode *T);
void boolExp(ASTNode *T);
void Exp(ASTNode *T);
void objectCode(CodeNode *head);
void print_lr(CodeNode *head);