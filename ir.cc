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

extern vector<Symbol> symbol_table;

Value *prepare_opn(LLVMContext &TheContext, unordered_map<string, Value *> &val_table, const Operation &op)
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

void print_lr(CodeNode *head)
{
    LLVMContext TheContext;
    Module TheModule("code", TheContext);

    vector<BasicBlock*> block;
    vector<IRBuilder<>> builder;
    unordered_map<string, Value *> val_table;

    CodeNode *h = head;
    do
    {
        Value *val = nullptr;

        Value *l = prepare_opn(TheContext, val_table, h->opn1), *r = prepare_opn(TheContext, val_table, h->opn2);
        switch (h->op)
        {
        case ASSIGNOP:
        {
            string var_name(h->result.id);

            auto *alloc = builder.back().CreateAlloca(Type::getInt32Ty(TheContext), nullptr, var_name);
            auto *store = builder.back().CreateStore(l, alloc);
            val_table[var_name] = alloc;
            break;
        }

        case PLUS:
        {
            auto *res = builder.back().CreateAdd(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }
        case MINUS:
        {
            auto *res = builder.back().CreateSub(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }
        case STAR:
        {
            auto *res = builder.back().CreateMul(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }
        case DIV:
        {
            auto *res = builder.back().CreateSDiv(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }
        case MOD:
        {
            auto *res = builder.back().CreateSRem(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }
        case RETURN:
        {
            if (h->result.kind) {
                builder.back().CreateRet(val_table[h->result.id]);
            } else {
                builder.back().CreateRetVoid();
            }

            // builder.pop_back();
            // block.pop_back();
            break;
        }
        case FUNCTION:
        {
            const string& function_name = h->result.id;
            const int idx = searchSymbolTableWithFlag(function_name, 'F');
            if (idx == -1) {
                // panic
                exit(1);
            }

            vector<Type*> parameters;
            for (int i = 0; i < symbol_table[idx].paramnum; i++) {
                const int offset = i + idx + 1;
                if (symbol_table[offset].type == INT) {
                    parameters.push_back(Type::getInt32Ty(TheContext));
                } else if (symbol_table[offset].type == FLOAT) {
                    parameters.push_back(Type::getFloatTy(TheContext));
                }
            }
            Type* return_type = Type::getInt32Ty(TheContext);
            FunctionType *function_type = FunctionType::get(return_type, parameters, false);
            Function *function_value = Function::Create(function_type, Function::ExternalLinkage, function_name, TheModule);
            BasicBlock *next_block = BasicBlock::Create(TheContext, "entry", function_value);

            int ptr = idx + 1;
            for (auto& arg : function_value->args()) {
                arg.setName(symbol_table[ptr].name);
                ptr++;
            }
            IRBuilder<> next_builder(next_block);
            builder.push_back(next_builder);
            block.push_back(next_block);
            break;
        }
        }

        h = h->next;
    } while (h != head);

    TheModule.print(errs(), nullptr);
}
