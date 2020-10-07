#define register 

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"

#include "cstdio"
#include "string"
#include "unordered_map"
#include "vector"
#include "variant"
#include "tuple"
#include "optional"

#include "parser.tab.h"

using namespace llvm;
using std::string, std::unordered_map, std::vector, std::variant, std::get, std::tuple, std::optional, std::nullopt;

#define PRINT_AST 1
#define PRINT_SYMBOL_TABLE 1

class Operation
{
public:
    int kind;
    int type;
    variant<int, float, string> data;
    int level;

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
    int idx;
    string Etrue, Efalse;
    string Snext;
    CodeNode *code;
    int type;
    int pos;
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
    int idx;

    Symbol();
};

ASTNode *make_node(int kind, int pos, vector<ASTNode*> nodes = vector<ASTNode*>{});
void entrypoint(ASTNode *T);
void bool_expression(ASTNode *T);
void expression(ASTNode *T);
void print_llvm_ir(CodeNode *head);
optional<Symbol> search_symbol_table_with_flag(const string& name, char flag);
tuple<Function*, FunctionType*, Function*, FunctionType*> inject_print_function(LLVMContext &ctx, IRBuilder<> &builder, Module &module);
void print_symbol_table();
