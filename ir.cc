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

using namespace llvm;
using std::string, std::unordered_map;

Value *prepare_opn(LLVMContext &TheContext, unordered_map<string, Value *> &val_table, const struct opn &op)
{
    if (op.kind == INT)
    {
        return ConstantInt::get(Type::getInt32Ty(TheContext), op.const_int);
    }
    else if (op.kind == FLOAT)
    {
        return ConstantInt::get(Type::getInt32Ty(TheContext), op.const_float);
    }
    else if (op.kind == ID)
    {
        if (val_table.count(op.id))
            return val_table[op.id];
    }

    return nullptr;
}

void print_lr(struct codenode *head)
{
    LLVMContext TheContext;
    IRBuilder<> Builder(TheContext);
    Module TheModule("code", TheContext);

    FunctionType *FT = FunctionType::get(Type::getVoidTy(TheContext), std::vector<Type *>{}, false);
    Function *F = Function::Create(FT, Function::ExternalLinkage, "add_fn", TheModule);

    BasicBlock *block = BasicBlock::Create(TheContext, "entry", F);
    IRBuilder<> functionBuilder(block);
    unordered_map<string, Value *> val_table;

    struct codenode *h = head;
    do
    {
        Value *val = nullptr;

        Value *l = prepare_opn(TheContext, val_table, h->opn1), *r = prepare_opn(TheContext, val_table, h->opn2);
        switch (h->op)
        {
        case ASSIGNOP:
        {
            string var_name(h->result.id);

            auto *alloc = functionBuilder.CreateAlloca(Type::getInt32Ty(TheContext), nullptr, var_name);
            auto *store = functionBuilder.CreateStore(l, alloc);
            val_table[var_name] = alloc;
            break;
        }

        case PLUS:
        {
            auto *res = functionBuilder.CreateAdd(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }
        case MINUS:
        {
            auto *res = functionBuilder.CreateSub(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }
        case STAR:
        {
            auto *res = functionBuilder.CreateMul(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }
        case DIV:
        {
            auto *res = functionBuilder.CreateSDiv(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }
        case MOD:
        {
            auto *res = functionBuilder.CreateSRem(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }
        case RETURN:
        { // todo: pop stack
            if (h->result.kind) {
                functionBuilder.CreateRet(val_table[h->result.id]);
            } else {
                functionBuilder.CreateRetVoid();
            }
            break;
        }
        }

        h = h->next;
    } while (h != head);

    TheModule.print(errs(), nullptr);
}
