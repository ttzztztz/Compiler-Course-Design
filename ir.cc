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
#include "llvm/IR/Instruction.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

#include "def.h"
#include "iostream"
#include "list"

using namespace llvm;
using std::pair, std::tuple, std::list;

extern vector<Symbol> symbol_table;

Value *prepare_opn(LLVMContext &TheContext, unordered_map<string, Value *> &val_table, const Operation &op)
{
    switch (op.kind)
    {
    case INT:
        return ConstantInt::get(Type::getInt32Ty(TheContext), get<int>(op.data));
    case FLOAT:
        return ConstantInt::get(Type::getInt32Ty(TheContext), get<float>(op.data));
    case ID:
        if (val_table.count(get<string>(op.data)))
            return val_table[get<string>(op.data)];
    }

    return nullptr;
}

void print_lr(CodeNode *head)
{
    LLVMContext TheContext;
    Module TheModule("code", TheContext);

    vector<BasicBlock *> block_stack;
    vector<IRBuilder<>> builder_stack;
    vector<Function *> function_stack;

    unordered_map<string, pair<Function *, FunctionType *>> function_table;
    unordered_map<string, Value *> val_table;
    unordered_map<string, BasicBlock *> label_table;

    unordered_map<string, vector<pair<Instruction *, IRBuilderBase::InsertPoint>>> unfinished_goto_statement;
    list<tuple<Instruction *, IRBuilderBase::InsertPoint, Value *, string, string>> unfinished_br_statement;

    CodeNode *h = head;
    do
    {
        Value *val = nullptr;

        Value *l = prepare_opn(TheContext, val_table, h->opn1), *r = prepare_opn(TheContext, val_table, h->opn2);
        switch (h->op)
        {
        case ASSIGNOP:
        {
            string var_name(get<string>(h->result.data));

            auto *alloc = builder_stack.back().CreateAlloca(Type::getInt32Ty(TheContext), nullptr, var_name);
            auto *store = builder_stack.back().CreateStore(l, alloc);

            val_table[var_name] = alloc;
            break;
        }

        case PLUS:
        {
            auto *res = builder_stack.back().CreateAdd(l, r, get<string>(h->result.data));
            val_table[get<string>(h->result.data)] = res;
            break;
        }

        case MINUS:
        {
            auto *res = builder_stack.back().CreateSub(l, r, get<string>(h->result.data));
            val_table[get<string>(h->result.data)] = res;
            break;
        }

        case STAR:
        {
            auto *res = builder_stack.back().CreateMul(l, r, get<string>(h->result.data));
            val_table[get<string>(h->result.data)] = res;
            break;
        }

        case DIV:
        {
            auto *res = builder_stack.back().CreateSDiv(l, r, get<string>(h->result.data));
            val_table[get<string>(h->result.data)] = res;
            break;
        }

        case MOD:
        {
            auto *res = builder_stack.back().CreateSRem(l, r, get<string>(h->result.data));
            val_table[get<string>(h->result.data)] = res;
            break;
        }

        case RETURN:
        {
            if (h->result.kind)
            {
                builder_stack.back().CreateRet(val_table[get<string>(h->result.data)]);
            }
            else
            {
                builder_stack.back().CreateRetVoid();
            }

            break;
        }
        case FUNCTION:
        {
            const string &function_name = get<string>(h->result.data);
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
        case CALL:
        {
            auto [fn, fn_type] = function_table[get<string>(h->opn1.data)];
            vector<Value *> parameters;
            for (auto arg : h->data)
            {
                parameters.push_back(val_table[get<string>(arg->result.data)]);
            }

            val_table[get<string>(h->result.data)] = builder_stack.back().CreateCall(fn_type, fn, parameters, get<string>(h->result.data));
            break;
        }

        case LABEL:
        {
            const string &label = get<string>(h->result.data);
            BasicBlock *next_block = BasicBlock::Create(TheContext, label, function_stack.back());
            label_table[label] = next_block;

            if (unfinished_goto_statement.count(label))
            {
                for (auto [val, insert_point] : unfinished_goto_statement[label])
                {
                    IRBuilder<> builder(TheContext);
                    builder.SetInsertPoint(insert_point.getBlock(), insert_point.getPoint());
                    auto new_val = builder.CreateBr(next_block);

                    val->eraseFromParent();
                }
            }

            for (auto it = unfinished_br_statement.begin(); it != unfinished_br_statement.end();)
            {
                auto [val, insert_point, icmp_val, true_label, false_label] = *it;
                if (label_table.count(true_label) && label_table.count(false_label))
                {
                    IRBuilder<> builder(TheContext);
                    builder.SetInsertPoint(insert_point.getBlock(), insert_point.getPoint());
                    auto new_val = builder.CreateCondBr(icmp_val, label_table[true_label], label_table[false_label]);
                    val->eraseFromParent();

                    it = unfinished_br_statement.erase(it);
                }
                else
                {
                    it++;
                }
            }

            // builder_stack.back().CreateBr(next_block);
            block_stack.push_back(next_block);
            builder_stack.push_back(IRBuilder<>(next_block));
            break;
        }

        case GOTO:
        {
            const string &label = get<string>(h->result.data);
            if (label_table.count(label))
            {
                builder_stack.back().CreateBr(label_table[label]);
            }
            else
            {
                Instruction *fake_node = builder_stack.back().CreateRetVoid();
                auto insert_point = builder_stack.back().saveIP();
                unfinished_goto_statement[label].emplace_back(fake_node, insert_point);
            }
            break;
        }

        case JGE:
        case JGT:
        case JLE:
        case JLT:
        case NEQ:
        case EQ:
        {
            Value *val;

            // type inconsistency
            if (l->getType()->getTypeID() == llvm::Type::TypeID::PointerTyID && r->getType()->getTypeID() != llvm::Type::TypeID::PointerTyID)
                l = builder_stack.back().CreateLoad(l);
            if (l->getType()->getTypeID() != llvm::Type::TypeID::PointerTyID && r->getType()->getTypeID() == llvm::Type::TypeID::PointerTyID)
                r = builder_stack.back().CreateLoad(r);

            if (h->op == EQ)
                val = builder_stack.back().CreateICmpEQ(l, r, "cmpres");
            else if (h->op == NEQ)
                val = builder_stack.back().CreateICmpNE(l, r, "cmpres");
            else if (h->op == JGE)
                val = builder_stack.back().CreateICmpSGE(l, r, "cmpres");
            else if (h->op == JGT)
                val = builder_stack.back().CreateICmpSGT(l, r, "cmpres");
            else if (h->op == JLE)
                val = builder_stack.back().CreateICmpSLE(l, r, "cmpres");
            else if (h->op == JLT)
                val = builder_stack.back().CreateICmpSLT(l, r, "cmpres");

            const string &true_label = get<string>(h->result.data), &false_label = get<string>(h->data[0]->result.data);
            if (label_table.count(true_label) && label_table.count(false_label))
            {
                builder_stack.back().CreateCondBr(val, label_table[true_label], label_table[false_label]);
            }
            else
            {
                Instruction *fake_node = builder_stack.back().CreateRetVoid();
                auto insert_point = builder_stack.back().saveIP();
                unfinished_br_statement.emplace_back(fake_node, insert_point, val, true_label, false_label);
            }
        }
        }

        h = h->next;
    } while (h != head);

    TheModule.print(errs(), nullptr);
}
