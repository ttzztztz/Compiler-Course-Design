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
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

#include "def.h"
#include "iostream"

using namespace llvm;
using std::pair;

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

    vector<BasicBlock *> block_stack;
    vector<IRBuilder<>> builder_stack;
    vector<Function*> function_stack;

    unordered_map<string, pair<Function*, FunctionType*>> function_table;
    unordered_map<string, Value *> val_table;
    unordered_map<string, BasicBlock*> label_table;

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

            auto *alloc = builder_stack.back().CreateAlloca(Type::getInt32Ty(TheContext), nullptr, var_name);
            auto *store = builder_stack.back().CreateStore(l, alloc);
            val_table[var_name] = alloc;
            break;
        }

        case PLUS:
        {
            auto *res = builder_stack.back().CreateAdd(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }

        case MINUS:
        {
            auto *res = builder_stack.back().CreateSub(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }

        case STAR:
        {
            auto *res = builder_stack.back().CreateMul(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }

        case DIV:
        {
            auto *res = builder_stack.back().CreateSDiv(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }

        case MOD:
        {
            auto *res = builder_stack.back().CreateSRem(l, r, h->result.id);
            val_table[h->result.id] = res;
            break;
        }

        case RETURN:
        {
            if (h->result.kind)
            {
                builder_stack.back().CreateRet(val_table[h->result.id]);
            }
            else
            {
                builder_stack.back().CreateRetVoid();
            }

            break;
        }
        case FUNCTION:
        {
            const string &function_name = h->result.id;
            const int idx = search_symbol_table_with_flag(function_name, 'F');

            vector<Type *> parameters;
            for (int i = 0; i < symbol_table[idx].paramnum; i++)
            {
                const int offset = i + idx + 1;
                if (symbol_table[offset].type == INT)
                {
                    parameters.push_back(Type::getInt32Ty(TheContext));
                }
                else if (symbol_table[offset].type == FLOAT)
                {
                    parameters.push_back(Type::getFloatTy(TheContext));
                }
            }
            Type *return_type = Type::getInt32Ty(TheContext);
            FunctionType *function_type = FunctionType::get(return_type, parameters, false);
            Function *function_value = Function::Create(function_type, Function::ExternalLinkage, function_name, TheModule);
            BasicBlock *next_block = BasicBlock::Create(TheContext, "entry", function_value);
            function_table[function_name] = {function_value, function_type};
            int ptr = idx + 1;
            for (auto &arg : function_value->args())
            {
                val_table[symbol_table[ptr].alias] = &arg;
                arg.setName(symbol_table[ptr].alias);
                ptr++;
            }
            IRBuilder<> next_builder(next_block);
            builder_stack.push_back(next_builder);
            block_stack.push_back(next_block);
            function_stack.push_back(function_value);
            break;
        }
        case CALL: {
            auto [fn, fn_type] = function_table[h->opn1.id];
            vector<Value*> parameters;
            for (auto arg : h->data) {
                parameters.push_back(val_table[arg->result.id]);
            }

            val_table[h->result.id] = builder_stack.back().CreateCall(fn_type, fn, parameters, h->result.id);
            break;
        }

        case LABEL: {
            BasicBlock *next_block = BasicBlock::Create(TheContext, h->result.id, function_stack.back());
            block_stack.push_back(next_block);
            builder_stack.push_back(IRBuilder<>(next_block));
            label_table[h->result.id] = next_block;
            break;
        }
        }

        h = h->next;
    } while (h != head);

    TheModule.print(errs(), nullptr);
}
