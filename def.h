#define register 

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"
#include "parser.tab.h"

#define MAXLENGTH 200
#define DX 3 * sizeof(int)

struct opn
{
    int kind;
    int type;
    int const_int;
    float const_float;
    char const_char;
    string id;
    int level;
    int offset;
};

struct codenode
{
    int op;
    struct opn opn1, opn2, result;
    struct codenode *next, *prior;
};

struct ASTNode
{
    int kind;
    union
    {
        string type_id;
        int type_int; 
        float type_float; 
    };
    struct ASTNode *ptr[4];
    int place;
    string Etrue, Efalse;
    string Snext;
    struct codenode *code;
    int type;
    int pos;
    int offset;
    int width;
    int num;
};

struct symbol
{
    string name;
    int level;
    int type;
    int paramnum;
    string alias;
    char flag;
    char offset;
};

struct ASTNode *mknode(int num, int kind, int pos, ...);
void semantic_Analysis0(struct ASTNode *T);
void boolExp(struct ASTNode *T);
void Exp(struct ASTNode *T);
void objectCode(struct codenode *head);
void print_lr(struct codenode *head);