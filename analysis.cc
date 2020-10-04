#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include "def.h"
#include "string"

using std::string;
using namespace llvm;

struct symboltable
{
    struct symbol symbols[MAXLENGTH];
    int index;
} symbolTable;

struct symbol_scope_begin
{
    int TX[30];
    int top;
} symbol_scope_TX;

string newAlias()
{
    static int no = 1;
    return "v" + std::to_string(no++);
}

string newLabel()
{
    static int no = 1;
    return "l" + std::to_string(no++);
}

string newTemp()
{
    static int no = 1;
    return "t" + std::to_string(no++);
}

struct codenode *genIR(int op, struct opn opn1, struct opn opn2, struct opn result)
{
    struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
    h->op = op;
    h->opn1 = opn1;
    h->opn2 = opn2;
    h->result = result;
    h->next = h->prior = h;
    return h;
}

struct codenode *genLabel(char *label)
{
    struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
    h->op = LABEL;
    strcpy(h->result.id, label);
    h->next = h->prior = h;
    return h;
}

struct codenode *genGoto(char *label)
{
    struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
    h->op = GOTO;
    strcpy(h->result.id, label);
    h->next = h->prior = h;
    return h;
}

struct codenode *merge(int num, ...)
{
    struct codenode *h1, *h2, *p, *t1, *t2;
    va_list ap;
    va_start(ap, num);
    h1 = va_arg(ap, struct codenode *);
    while (--num > 0)
    {
        h2 = va_arg(ap, struct codenode *);
        if (h1 == NULL)
            h1 = h2;
        else if (h2)
        {
            t1 = h1->prior;
            t2 = h2->prior;
            t1->next = h2;
            t2->next = h1;
            h1->prior = t2;
            h2->prior = t1;
        }
    }
    va_end(ap);
    return h1;
}

void print_lr(struct codenode *head)
{
    LLVMContext TheContext;
    IRBuilder<> Builder(TheContext);
    Module TheModule("code", TheContext);

    std::vector<Type *> parameters(2, Type::getInt32Ty(TheContext));
    FunctionType *FT = FunctionType::get(Type::getVoidTy(TheContext), parameters, false);
    Function *F = Function::Create(FT, Function::ExternalLinkage, "add_fn", TheModule);

    Value *l = nullptr, *r = nullptr;
    int Idx = 0;
    for (auto &Arg : F->args()) {
        Arg.setName(string{ char('a' + Idx) });

        if (Idx == 0) l = &Arg;
        else r = &Arg;

        Idx++;
    }

    BasicBlock *block = BasicBlock::Create(TheContext, "entry", F);
    IRBuilder<> functionBuilder(block);

    struct codenode *h = head;
    do
    {
        Value* val = nullptr;
        switch (h->op)
        {
            case ASSIGNOP:
            string var_name(h->result.id);
            Value* data = ConstantInt::get(Type::getInt32Ty(TheContext), h->opn1.const_int);

            auto* alloc = functionBuilder.CreateAlloca(Type::getInt32Ty(TheContext), nullptr, var_name);
            auto* store = functionBuilder.CreateStore(data, alloc);
            break;
        }

        h = h->next;
    } while (h != head);

    functionBuilder.CreateRetVoid();
    TheModule.print(errs(), nullptr);
}

void semantic_error(int line, const string &msg1, const string &msg2)
{
    printf("Line %d Message: %s %s\n", line, msg1.c_str(), msg2.c_str());
}

void prn_symbol()
{
    return;

    int i = 0;
    printf("%6s %6s %6s  %6s %4s %6s\n", "Name", "Alias", "Level", "Type", "Flag", "Offset");
    for (i = 0; i < symbolTable.index; i++)
        printf("%6s %6s %6d  %6s %4c %6d\n", symbolTable.symbols[i].name,
               symbolTable.symbols[i].alias, symbolTable.symbols[i].level,
               symbolTable.symbols[i].type == INT ? "int" : "float",
               symbolTable.symbols[i].flag, symbolTable.symbols[i].offset);
}

int searchSymbolTable(char *name)
{
    int i;
    for (i = symbolTable.index - 1; i >= 0; i--)
        if (!strcmp(symbolTable.symbols[i].name, name))
            return i;
    return -1;
}

int fillSymbolTable(const string &name, const string &alias, int level, int type, char flag, int offset)
{
    int i;
    for (i = symbolTable.index - 1; i >= 0 && (symbolTable.symbols[i].level == level || level == 0); i--)
    {
        if (level == 0 && symbolTable.symbols[i].level == 1)
            continue;
        if (!strcmp(symbolTable.symbols[i].name, name.c_str()))
            return -1;
    }
    strcpy(symbolTable.symbols[symbolTable.index].name, name.c_str());
    strcpy(symbolTable.symbols[symbolTable.index].alias, alias.c_str());
    symbolTable.symbols[symbolTable.index].level = level;
    symbolTable.symbols[symbolTable.index].type = type;
    symbolTable.symbols[symbolTable.index].flag = flag;
    symbolTable.symbols[symbolTable.index].offset = offset;
    return symbolTable.index++;
}

int fill_Temp(const string &name, int level, int type, char flag, int offset)
{
    strcpy(symbolTable.symbols[symbolTable.index].name, "");
    strcpy(symbolTable.symbols[symbolTable.index].alias, name.c_str());
    symbolTable.symbols[symbolTable.index].level = level;
    symbolTable.symbols[symbolTable.index].type = type;
    symbolTable.symbols[symbolTable.index].flag = flag;
    symbolTable.symbols[symbolTable.index].offset = offset;
    return symbolTable.index++;
}

int LEV = 0;
int func_size;

void ext_var_list(struct ASTNode *T)
{
    int rtn, num = 1;
    switch (T->kind)
    {
    case EXT_DEC_LIST:
        T->ptr[0]->type = T->type;
        T->ptr[0]->offset = T->offset;
        T->ptr[1]->type = T->type;
        T->ptr[1]->offset = T->offset + T->width;
        T->ptr[1]->width = T->width;
        ext_var_list(T->ptr[0]);
        ext_var_list(T->ptr[1]);
        T->num = T->ptr[1]->num + 1;
        break;
    case ID:
        rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'V', T->offset);
        if (rtn == -1)
            semantic_error(T->pos, T->type_id, "Redecl Variable");
        else
            T->place = rtn;
        T->num = 1;
        break;
    }
}

int match_param(int i, struct ASTNode *T)
{
    int j, num = symbolTable.symbols[i].paramnum;
    int type1, type2, pos = T->pos;
    T = T->ptr[0];
    if (num == 0 && T == NULL)
        return 1;
    for (j = 1; j <= num; j++)
    {
        if (!T)
        {
            semantic_error(pos, "", "Too few parameters to call function!");
            return 0;
        }
        type1 = symbolTable.symbols[i + j].type;
        type2 = T->ptr[0]->type;
        if (type1 != type2)
        {
            semantic_error(pos, "", "Function Type doesn't match.");
            return 0;
        }
        T = T->ptr[1];
    }
    if (T)
    {
        semantic_error(pos, "", "Too much parameters to call function.");
        return 0;
    }
    return 1;
}

void boolExp(struct ASTNode *T)
{
    struct opn opn1, opn2, result;
    int op;
    int rtn;
    if (T)
    {
        switch (T->kind)
        {
        case INT:
            break;
        case FLOAT:
            break;
        case ID:
            break;
        case RELOP:
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            Exp(T->ptr[0]);
            T->width = T->ptr[0]->width;
            Exp(T->ptr[1]);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            opn2.kind = ID;
            strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
            opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
            result.kind = ID;
            strcpy(result.id, T->Etrue);
            if (strcmp(T->type_id, "<") == 0)
                op = JLT;
            else if (strcmp(T->type_id, "<=") == 0)
                op = JLE;
            else if (strcmp(T->type_id, ">") == 0)
                op = JGT;
            else if (strcmp(T->type_id, ">=") == 0)
                op = JGE;
            else if (strcmp(T->type_id, "==") == 0)
                op = EQ;
            else if (strcmp(T->type_id, "!=") == 0)
                op = NEQ;
            T->code = genIR(op, opn1, opn2, result);
            T->code = merge(4, T->ptr[0]->code, T->ptr[1]->code, T->code, genGoto(T->Efalse));
            break;
        case AND:
        case OR:
            if (T->kind == AND)
            {
                strcpy(T->ptr[0]->Etrue, newLabel().c_str());
                strcpy(T->ptr[0]->Efalse, T->Efalse);
            }
            else
            {
                strcpy(T->ptr[0]->Etrue, T->Etrue);
                strcpy(T->ptr[0]->Efalse, newLabel().c_str());
            }
            strcpy(T->ptr[1]->Etrue, T->Etrue);
            strcpy(T->ptr[1]->Efalse, T->Efalse);
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            boolExp(T->ptr[0]);
            T->width = T->ptr[0]->width;
            boolExp(T->ptr[1]);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            if (T->kind == AND)
                T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code);
            else
                T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Efalse), T->ptr[1]->code);
            break;
        case NOT:
            strcpy(T->ptr[0]->Etrue, T->Efalse);
            strcpy(T->ptr[0]->Efalse, T->Etrue);
            boolExp(T->ptr[0]);
            T->code = T->ptr[0]->code;
            break;
        }
    }
}

void Exp(struct ASTNode *T)
{
    int rtn, num, width;
    struct ASTNode *T0;
    struct opn opn1, opn2, result;
    if (T)
    {
        switch (T->kind)
        {
        case ID:
            rtn = searchSymbolTable(T->type_id);
            if (rtn == -1)
                semantic_error(T->pos, T->type_id, "Variable not declared.");
            if (symbolTable.symbols[rtn].flag == 'F')
                semantic_error(T->pos, T->type_id, "Type doesn't match.");
            else
            {
                T->place = rtn;
                T->code = NULL;
                T->type = symbolTable.symbols[rtn].type;
                T->offset = symbolTable.symbols[rtn].offset;
                T->width = 0;
            }
            break;
        case INT:
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
            T->type = INT;
            opn1.kind = INT;
            opn1.const_int = T->type_int;
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.offset = symbolTable.symbols[T->place].offset;
            T->code = genIR(ASSIGNOP, opn1, opn2, result);
            T->width = 4;
            break;
        case FLOAT:
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
            T->type = FLOAT;
            opn1.kind = FLOAT;
            opn1.const_float = T->type_float;
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.offset = symbolTable.symbols[T->place].offset;
            T->code = genIR(ASSIGNOP, opn1, opn2, result);
            T->width = 4;
            break;
        case ASSIGNOP:
            if (T->ptr[0]->kind != ID)
            {
                semantic_error(T->pos, "", "Assign Expression needs to be left value.");
            }
            else
            {
                Exp(T->ptr[0]);
                T->ptr[1]->offset = T->offset;
                Exp(T->ptr[1]);
                T->type = T->ptr[0]->type;
                T->width = T->ptr[1]->width;
                T->code = merge(2, T->ptr[0]->code, T->ptr[1]->code);
                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[T->ptr[1]->place].alias);
                opn1.offset = symbolTable.symbols[T->ptr[1]->place].offset;
                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T->ptr[0]->place].alias);
                result.offset = symbolTable.symbols[T->ptr[0]->place].offset;
                T->code = merge(2, T->code, genIR(ASSIGNOP, opn1, opn2, result));
            }
            break;
        case AND:   // todo
        case OR:    // todo
        case RELOP: // todo
            T->type = INT;
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            Exp(T->ptr[0]);
            Exp(T->ptr[1]);
            break;
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);
            T->ptr[1]->offset = T->offset + T->ptr[0]->width;
            Exp(T->ptr[1]);
            // todo: err handle
            if (T->ptr[0]->type == FLOAT || T->ptr[1]->type == FLOAT)
                T->type = FLOAT, T->width = T->ptr[0]->width + T->ptr[1]->width + 4;
            else
                T->type = INT, T->width = T->ptr[0]->width + T->ptr[1]->width + 2;
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->ptr[0]->width + T->ptr[1]->width);
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
            opn1.type = T->ptr[0]->type;
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            opn2.kind = ID;
            strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
            opn2.type = T->ptr[1]->type;
            opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.type = T->type;
            result.offset = symbolTable.symbols[T->place].offset;
            T->code = merge(3, T->ptr[0]->code, T->ptr[1]->code, genIR(T->kind, opn1, opn2, result));
            T->width = T->ptr[0]->width + T->ptr[1]->width + (T->type == INT ? 4 : 8);
            break;
        case NOT: // todo
            break;
        case UMINUS: // todo
            break;
        case FUNC_CALL:
            rtn = searchSymbolTable(T->type_id);
            if (rtn == -1)
            {
                semantic_error(T->pos, T->type_id, "Function not declared.");
                break;
            }
            if (symbolTable.symbols[rtn].flag != 'F')
            {
                semantic_error(T->pos, T->type_id, "Not a function!");
                break;
            }
            T->type = symbolTable.symbols[rtn].type;
            width = T->type == INT ? 4 : 8;
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                Exp(T->ptr[0]);
                T->width = T->ptr[0]->width + width;
                T->code = T->ptr[0]->code;
            }
            else
            {
                T->width = width;
                T->code = NULL;
            }
            match_param(rtn, T);
            T0 = T->ptr[0];
            while (T0)
            {
                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T0->ptr[0]->place].alias);
                result.offset = symbolTable.symbols[T0->ptr[0]->place].offset;
                T->code = merge(2, T->code, genIR(ARG, opn1, opn2, result));
                T0 = T0->ptr[1];
            }
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->width - width);
            opn1.kind = ID;
            strcpy(opn1.id, T->type_id);
            opn1.offset = rtn;
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.offset = symbolTable.symbols[T->place].offset;
            T->code = merge(2, T->code, genIR(CALL, opn1, opn2, result));
            break;
        case ARGS:
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);
            T->width = T->ptr[0]->width;
            T->code = T->ptr[0]->code;
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                Exp(T->ptr[1]);
                T->width += T->ptr[1]->width;
                T->code = merge(2, T->code, T->ptr[1]->code);
            }
            break;
        }
    }
}

void semantic_Analysis(struct ASTNode *T)
{
    int rtn, num, width;
    struct ASTNode *T0;
    struct opn opn1, opn2, result;
    if (T)
    {
        switch (T->kind)
        {
        case EXT_DEF_LIST:
            if (!T->ptr[0])
                break;
            T->ptr[0]->offset = T->offset;
            semantic_Analysis(T->ptr[0]);
            T->code = T->ptr[0]->code;
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->ptr[0]->offset + T->ptr[0]->width;
                semantic_Analysis(T->ptr[1]);
                T->code = merge(2, T->code, T->ptr[1]->code);
            }
            break;
        case EXT_VAR_DEF:
            T->type = T->ptr[1]->type = !strcmp(T->ptr[0]->type_id, "int") ? INT : FLOAT;
            T->ptr[1]->offset = T->offset;
            T->ptr[1]->width = T->type == INT ? 4 : 8;
            ext_var_list(T->ptr[1]);
            T->width = (T->type == INT ? 4 : 8) * T->ptr[1]->num;
            T->code = NULL;
            break;
        case FUNC_DEF:
            T->ptr[1]->type = !strcmp(T->ptr[0]->type_id, "int") ? INT : FLOAT;
            T->width = 0;
            T->offset = DX;
            semantic_Analysis(T->ptr[1]);
            T->offset += T->ptr[1]->width;
            T->ptr[2]->offset = T->offset;
            strcpy(T->ptr[2]->Snext, newLabel().c_str());
            semantic_Analysis(T->ptr[2]);
            symbolTable.symbols[T->ptr[1]->place].offset = T->offset + T->ptr[2]->width;
            T->code = merge(3, T->ptr[1]->code, T->ptr[2]->code, genLabel(T->ptr[2]->Snext));
            break;
        case FUNC_DEC:
            rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'F', 0);
            if (rtn == -1)
            {
                semantic_error(T->pos, T->type_id, "Function Redeclaration.");
                break;
            }
            else
                T->place = rtn;
            result.kind = ID;
            strcpy(result.id, T->type_id);
            result.offset = rtn;
            T->code = genIR(FUNCTION, opn1, opn2, result);
            T->offset = DX;
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                semantic_Analysis(T->ptr[0]);
                T->width = T->ptr[0]->width;
                symbolTable.symbols[rtn].paramnum = T->ptr[0]->num;
                T->code = merge(2, T->code, T->ptr[0]->code);
            }
            else
                symbolTable.symbols[rtn].paramnum = 0, T->width = 0;
            break;
        case PARAM_LIST:
            T->ptr[0]->offset = T->offset;
            semantic_Analysis(T->ptr[0]);
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                semantic_Analysis(T->ptr[1]);
                T->num = T->ptr[0]->num + T->ptr[1]->num;
                T->width = T->ptr[0]->width + T->ptr[1]->width;
                T->code = merge(2, T->ptr[0]->code, T->ptr[1]->code);
            }
            else
            {
                T->num = T->ptr[0]->num;
                T->width = T->ptr[0]->width;
                T->code = T->ptr[0]->code;
            }
            break;
        case PARAM_DEC:
            rtn = fillSymbolTable(T->ptr[1]->type_id, newAlias(), 1, T->ptr[0]->type, 'P', T->offset);
            if (rtn == -1)
                semantic_error(T->ptr[1]->pos, T->ptr[1]->type_id, "Function Parameter name re-declaration.");
            else
                T->ptr[1]->place = rtn;
            T->num = 1;
            T->width = T->ptr[0]->type == INT ? 4 : 8;
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[rtn].alias);
            result.offset = T->offset;
            T->code = genIR(PARAM, opn1, opn2, result);
            break;
        case COMP_STM:
            LEV++;
            symbol_scope_TX.TX[symbol_scope_TX.top++] = symbolTable.index;
            T->width = 0;
            T->code = NULL;
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                semantic_Analysis(T->ptr[0]);
                T->width += T->ptr[0]->width;
                T->code = T->ptr[0]->code;
            }
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->offset + T->width;
                strcpy(T->ptr[1]->Snext, T->Snext);
                semantic_Analysis(T->ptr[1]);
                T->width += T->ptr[1]->width;
                T->code = merge(2, T->code, T->ptr[1]->code);
            }
            prn_symbol();
            LEV--;
            symbolTable.index = symbol_scope_TX.TX[--symbol_scope_TX.top];
            break;
        case DEF_LIST:
            T->code = NULL;
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                semantic_Analysis(T->ptr[0]);
                T->code = T->ptr[0]->code;
                T->width = T->ptr[0]->width;
            }
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                semantic_Analysis(T->ptr[1]);
                T->code = merge(2, T->code, T->ptr[1]->code);
                T->width += T->ptr[1]->width;
            }
            break;
        case VAR_DEF:
            T->code = NULL;
            T->ptr[1]->type = !strcmp(T->ptr[0]->type_id, "int") ? INT : FLOAT;
            T0 = T->ptr[1];
            num = 0;
            T0->offset = T->offset;
            T->width = 0;
            width = T->ptr[1]->type == INT ? 4 : 8;
            while (T0)
            {
                num++;
                T0->ptr[0]->type = T0->type;
                if (T0->ptr[1])
                    T0->ptr[1]->type = T0->type;
                T0->ptr[0]->offset = T0->offset;
                if (T0->ptr[1])
                    T0->ptr[1]->offset = T0->offset + width;
                if (T0->ptr[0]->kind == ID)
                {
                    rtn = fillSymbolTable(T0->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'V', T->offset + T->width); // todo: offset count
                    if (rtn == -1)
                        semantic_error(T0->ptr[0]->pos, T0->ptr[0]->type_id, "Variable re-declared.");
                    else
                        T0->ptr[0]->place = rtn;
                    T->width += width;
                }
                else if (T0->ptr[0]->kind == ASSIGNOP)
                {
                    rtn = fillSymbolTable(T0->ptr[0]->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'V', T->offset + T->width); // todo: offset count
                    if (rtn == -1)
                        semantic_error(T0->ptr[0]->ptr[0]->pos, T0->ptr[0]->ptr[0]->type_id, "Variable re-declared.");
                    else
                    {
                        T0->ptr[0]->place = rtn;
                        T0->ptr[0]->ptr[1]->offset = T->offset + T->width + width;
                        Exp(T0->ptr[0]->ptr[1]);
                        opn1.kind = ID;
                        strcpy(opn1.id, symbolTable.symbols[T0->ptr[0]->ptr[1]->place].alias);
                        result.kind = ID;
                        strcpy(result.id, symbolTable.symbols[T0->ptr[0]->place].alias);
                        T->code = merge(3, T->code, T0->ptr[0]->ptr[1]->code, genIR(ASSIGNOP, opn1, opn2, result));
                    }
                    T->width += width + T0->ptr[0]->ptr[1]->width;
                }
                T0 = T0->ptr[1];
            }
            break;
        case STM_LIST:
            if (!T->ptr[0])
            {
                T->code = NULL;
                T->width = 0;
                break;
            }
            if (T->ptr[1])
                strcpy(T->ptr[0]->Snext, newLabel().c_str());
            else
                strcpy(T->ptr[0]->Snext, T->Snext);
            T->ptr[0]->offset = T->offset;
            semantic_Analysis(T->ptr[0]);
            T->code = T->ptr[0]->code;
            T->width = T->ptr[0]->width;
            if (T->ptr[1])
            {
                strcpy(T->ptr[1]->Snext, T->Snext);
                T->ptr[1]->offset = T->offset;
                semantic_Analysis(T->ptr[1]);
                if (T->ptr[0]->kind == RETURN || T->ptr[0]->kind == EXP_STMT || T->ptr[0]->kind == COMP_STM)
                    T->code = merge(2, T->code, T->ptr[1]->code);
                else
                    T->code = merge(3, T->code, genLabel(T->ptr[0]->Snext), T->ptr[1]->code);
                if (T->ptr[1]->width > T->width)
                    T->width = T->ptr[1]->width;
            }
            break;
        case IF_THEN:
            strcpy(T->ptr[0]->Etrue, newLabel().c_str());
            strcpy(T->ptr[0]->Efalse, T->Snext);
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            boolExp(T->ptr[0]);
            T->width = T->ptr[0]->width;
            strcpy(T->ptr[1]->Snext, T->Snext);
            semantic_Analysis(T->ptr[1]);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code);
            break;
        case IF_THEN_ELSE:
            strcpy(T->ptr[0]->Etrue, newLabel().c_str());
            strcpy(T->ptr[0]->Efalse, newLabel().c_str());
            T->ptr[0]->offset = T->ptr[1]->offset = T->ptr[2]->offset = T->offset;
            boolExp(T->ptr[0]);
            T->width = T->ptr[0]->width;
            strcpy(T->ptr[1]->Snext, T->Snext);
            semantic_Analysis(T->ptr[1]);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            strcpy(T->ptr[2]->Snext, T->Snext);
            semantic_Analysis(T->ptr[2]);
            if (T->width < T->ptr[2]->width)
                T->width = T->ptr[2]->width;
            T->code = merge(6, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code,
                            genGoto(T->Snext), genLabel(T->ptr[0]->Efalse), T->ptr[2]->code);
            break;
        case WHILE:
            strcpy(T->ptr[0]->Etrue, newLabel().c_str());
            strcpy(T->ptr[0]->Efalse, T->Snext);
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            boolExp(T->ptr[0]);
            T->width = T->ptr[0]->width;
            strcpy(T->ptr[1]->Snext, newLabel().c_str());
            semantic_Analysis(T->ptr[1]);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            T->code = merge(5, genLabel(T->ptr[1]->Snext), T->ptr[0]->code,
                            genLabel(T->ptr[0]->Etrue), T->ptr[1]->code, genGoto(T->ptr[1]->Snext));
            break;
        case EXP_STMT:
            T->ptr[0]->offset = T->offset;
            semantic_Analysis(T->ptr[0]);
            T->code = T->ptr[0]->code;
            T->width = T->ptr[0]->width;
            break;
        case RETURN:
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                Exp(T->ptr[0]);

                /*需要判断返回值类型是否匹配*/

                T->width = T->ptr[0]->width;
                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T->ptr[0]->place].alias);
                result.offset = symbolTable.symbols[T->ptr[0]->place].offset;
                T->code = merge(2, T->ptr[0]->code, genIR(RETURN, opn1, opn2, result));
            }
            else
            {
                T->width = 0;
                result.kind = 0;
                T->code = genIR(RETURN, opn1, opn2, result);
            }
            break;
        case ID:
        case INT:
        case FLOAT:
        case ASSIGNOP:
        case AND:
        case OR:
        case RELOP:
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
        case NOT:
        case UMINUS:
        case FUNC_CALL:
            Exp(T);
            break;
        }
    }
}

void semantic_Analysis0(struct ASTNode *T)
{
    symbolTable.index = 0;
    fillSymbolTable("read", "", 0, INT, 'F', 4);
    symbolTable.symbols[0].paramnum = 0;
    fillSymbolTable("write", "", 0, INT, 'F', 4);
    symbolTable.symbols[1].paramnum = 1;
    fillSymbolTable("x", "", 1, INT, 'P', 12);
    symbol_scope_TX.TX[0] = 0;
    symbol_scope_TX.top = 1;
    T->offset = 0;
    semantic_Analysis(T);
    print_lr(T->code);
}
