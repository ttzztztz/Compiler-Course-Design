#define register 

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"
#include "parser.tab.h"

#include "llvm/IR/Value.h"
#include "llvm/IR/BasicBlock.h"

using llvm::Value, llvm::BasicBlock;

#define MAXLENGTH 200
#define DX 3 * sizeof(int)

struct opn
{
    int kind;
    int type;
    union
    {
        int const_int;
        float const_float;
        char const_char;
        char id[33];
    };
    int level;
    int offset;
    Value* val;
};

struct Branch {
    BasicBlock* block;
    char id[15];
};

struct codenode
{
    int op;
    struct opn opn1, opn2, result;
    struct codenode *next, *prior;
    Value* val;
    Branch* br;
};

struct ASTNode
{
    int kind;
    union
    {
        char type_id[33]; 
        int type_int; 
        float type_float; 
    };
    struct ASTNode *ptr[4];
    int place;
    struct codenode* Etrue, *Efalse, *Snext;
    struct codenode *code;
    int type;
    int pos;
    int offset;
    int width;
    int num;
};

struct symbol
{
    char name[33];
    int level;
    int type;
    int paramnum;
    char alias[10];
    char flag;
    char offset;
};

struct ASTNode *mknode(int num, int kind, int pos, ...);
void semantic_Analysis0(struct ASTNode *T);
void boolExp(struct ASTNode *T);
void Exp(struct ASTNode *T);
void objectCode(struct codenode *head);
