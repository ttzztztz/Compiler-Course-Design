#include "def.h"
#include "iostream"
#include "memory"
#include "list"
#include "unordered_set"

using std::pair, std::tuple, std::list, std::make_unique, std::unordered_set;

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

void print_llvm_ir(CodeNode *head)
{
    LLVMContext TheContext;
    Module TheModule("code", TheContext);

    vector<BasicBlock *> block_stack;
    vector<IRBuilder<>> builder_stack;
    vector<Function *> function_stack;

    unordered_map<string, pair<Function *, FunctionType *>> function_table;
    unordered_map<string, Value *> val_table;
    unordered_map<string, BasicBlock *> label_table;
    unordered_set<BasicBlock*> finished_block;

    typedef pair<Instruction *, IRBuilderBase::InsertPoint> DeferredGotoStatementType;
    typedef tuple<Instruction *, IRBuilderBase::InsertPoint, Value *, string, string> DeferredBrStatementType;

    unordered_map<string, vector<DeferredGotoStatementType>> deferred_goto_statement;
    list<DeferredBrStatementType> deferred_br_statement;

    builder_stack.emplace_back(IRBuilder<>(TheContext));
    auto [printf_func, printf_func_type, print_int_func, print_int_func_type] = inject_print_function(TheContext, builder_stack.back(), TheModule);
    function_table["printf"] = {printf_func, printf_func_type};
    function_table["print_int"] = {print_int_func, print_int_func_type};

    auto create_goto = [&](const string &label) -> void {
        auto* current_basic_block = block_stack.back();
        if (finished_block.count(current_basic_block)) return;
        finished_block.insert(current_basic_block);

        if (label_table.count(label))
        {
            builder_stack.back().CreateBr(label_table[label]);
        }
        else
        {
            Instruction *fake_node = builder_stack.back().CreateRetVoid();
            deferred_goto_statement[label].emplace_back(fake_node, builder_stack.back().saveIP());
        }
    };

    CodeNode *h = head;
    do
    {
        Value *l = prepare_opn(TheContext, val_table, h->opn1), *r = prepare_opn(TheContext, val_table, h->opn2);
        switch (h->op)
        {
        case ASSIGNOP:
        {
            string var_name(get<string>(h->result.data));

            Value *alloc = nullptr;
            if (val_table.count(var_name))
            {
                alloc = val_table[var_name];
            }
            else
            {
                alloc = builder_stack.back().CreateAlloca(Type::getInt32Ty(TheContext), nullptr, var_name);
                val_table[var_name] = alloc;
            }

            if (l->getType()->isPointerTy())
            {
                l = builder_stack.back().CreateLoad(Type::getInt32Ty(TheContext), l, "");
            }
            builder_stack.back().CreateStore(l, alloc);
            break;
        }

        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
        case MOD:
        {
            if (l->getType()->isPointerTy())
            {
                l = builder_stack.back().CreateLoad(Type::getInt32Ty(TheContext), l, "");
            }
            if (r->getType()->isPointerTy())
            {
                r = builder_stack.back().CreateLoad(Type::getInt32Ty(TheContext), r, "");
            }
            Value *res = nullptr;

            if (h->op == PLUS)
                res = builder_stack.back().CreateAdd(l, r, get<string>(h->result.data));
            else if (h->op == MINUS)
                res = builder_stack.back().CreateSub(l, r, get<string>(h->result.data));
            else if (h->op == STAR)
                res = builder_stack.back().CreateMul(l, r, get<string>(h->result.data));
            else if (h->op == DIV)
                res = builder_stack.back().CreateSDiv(l, r, get<string>(h->result.data));
            else if (h->op == MOD)
                res = builder_stack.back().CreateSRem(l, r, get<string>(h->result.data));

            val_table[get<string>(h->result.data)] = res;
            break;
        }
        case RETURN:
        {
            if (h->result.kind)
            {
                Value *return_val = val_table[get<string>(h->result.data)];
                if (return_val->getType()->isPointerTy())
                {
                    return_val = builder_stack.back().CreateLoad(Type::getInt32Ty(TheContext), return_val, "");
                }
                builder_stack.back().CreateRet(return_val);
            }
            else
            {
                builder_stack.back().CreateRetVoid();
            }

            break;
        }
        case CONTINUE:
        case BREAK:
        {
            const string &label = get<string>(h->result.data);
            create_goto(label);
            break;
        }
        case FUNCTION:
        {
            const string &function_name = get<string>(h->result.data);
            const auto fill_result = search_symbol_table_with_flag(function_name, 'F');

            vector<Type *> parameters;
            for (int i = 0; i < fill_result.value().paramnum; i++)
            {
                const int offset = i + fill_result.value().idx + 1;
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
            int ptr = fill_result.value().idx + 1;
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
                auto *load = builder_stack.back().CreateLoad(Type::getInt32Ty(TheContext), val_table[get<string>(arg->result.data)], "");
                parameters.push_back(load);
            }

            val_table[get<string>(h->result.data)] = builder_stack.back().CreateCall(fn_type, fn, parameters, get<string>(h->result.data));
            break;
        }

        case LABEL:
        {
            const string &label = get<string>(h->result.data);
            BasicBlock *next_block = BasicBlock::Create(TheContext, label, function_stack.back());
            label_table[label] = next_block;

            if (deferred_goto_statement.count(label))
            {
                for (auto [val, insert_point] : deferred_goto_statement[label])
                {
                    BranchInst::Create(next_block, val);
                    val->eraseFromParent();
                }
            }

            for (auto it = deferred_br_statement.begin(); it != deferred_br_statement.end();)
            {
                auto [val, insert_point, icmp_val, true_label, false_label] = *it;
                if (label_table.count(true_label) && label_table.count(false_label))
                {
                    IRBuilder<> builder(TheContext);
                    builder.restoreIP(insert_point);
                    builder.CreateCondBr(icmp_val, label_table[true_label], label_table[false_label]);
                    val->eraseFromParent();

                    it = deferred_br_statement.erase(it);
                }
                else
                {
                    it++;
                }
            }

            // builder_stack.back().CreateBr(next_block);
            block_stack.push_back(next_block);
            builder_stack.emplace_back(next_block);
            break;
        }

        case GOTO:
        {
            const string &label = get<string>(h->result.data);
            create_goto(label);
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
            if (l && l->getType()->isPointerTy())
                l = builder_stack.back().CreateLoad(Type::getInt32Ty(TheContext), l, "");
            if (r && r->getType()->isPointerTy())
                r = builder_stack.back().CreateLoad(Type::getInt32Ty(TheContext), r, "");

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
                deferred_br_statement.emplace_back(fake_node, insert_point, val, true_label, false_label);
            }
        }
        }

        h = h->next;
    } while (h != head);

    TheModule.print(errs(), nullptr);
    verifyModule(TheModule, &(errs()));

    std::unique_ptr<Module> ptr(&TheModule);
    ExecutionEngine *engine = EngineBuilder(std::move(ptr)).create();
    engine->finalizeObject();
    engine->runFunction(function_table["main"].first, {});
}
