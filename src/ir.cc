#include "compiler.h"
#include "iostream"
#include "memory"
#include "list"
#include "unordered_set"

using std::pair, std::tuple, std::list, std::make_unique, std::unordered_set;

extern vector<Symbol> symbol_table;

pair<Value *, int> prepare_opn(LLVMContext &TheContext, unordered_map<string, pair<Value *, int>> &val_table, const Operation &operation)
{
    switch (operation.kind)
    {
    case INT:
        return {ConstantInt::get(Type::getInt32Ty(TheContext), get<int>(operation.data)), INT};
    case FLOAT:
        return {ConstantFP::get(Type::getFloatTy(TheContext), get<float>(operation.data)), FLOAT};
    case ID:
        if (val_table.count(get<string>(operation.data)))
            return val_table[get<string>(operation.data)];
    }

    return {nullptr, 0};
}

void print_llvm_ir(shared_ptr<CodeNode> head)
{
    LLVMContext TheContext;
    Module TheModule("code", TheContext);

    vector<BasicBlock *> block_stack;
    vector<IRBuilder<>> builder_stack;
    vector<Function *> function_stack;

    unordered_map<string, pair<Function *, FunctionType *>> function_table;
    unordered_map<string, pair<Value *, int>> val_table;
    unordered_map<string, BasicBlock *> label_table;
    unordered_set<BasicBlock *> finished_block;

    typedef tuple<Instruction *, Value *, string, string> DeferredBrStatementType;

    unordered_map<string, vector<Instruction *>> deferred_goto_statement;
    list<DeferredBrStatementType> deferred_br_statement;

    builder_stack.emplace_back(IRBuilder<>(TheContext));
    auto [printf_func, printf_func_type, print_int_func, print_int_func_type] = inject_print_function(TheContext, builder_stack.back(), TheModule);
    function_table["printf"] = {printf_func, printf_func_type};
    function_table["print_int"] = {print_int_func, print_int_func_type};

    auto create_goto = [&](const string &label) -> void {
        auto *current_basic_block = block_stack.back();
        if (finished_block.count(current_basic_block))
            return;
        finished_block.insert(current_basic_block);

        if (label_table.count(label))
        {
            builder_stack.back().CreateBr(label_table[label]);
        }
        else
        {
            Instruction *fake_node = builder_stack.back().CreateRetVoid();
            deferred_goto_statement[label].emplace_back(fake_node);
        }
    };

    shared_ptr<CodeNode> cur = head;
    do
    {
        auto [l, l_type] = prepare_opn(TheContext, val_table, cur->opn1);
        auto [r, r_type] = prepare_opn(TheContext, val_table, cur->opn2);
        switch (cur->kind)
        {
        case ASSIGNOP:
        {
            string var_name(get<string>(cur->result.data));

            Value *alloc = nullptr;
            if (val_table.count(var_name))
            {
                alloc = val_table[var_name].first;
            }
            else
            {
                auto type = l_type == FLOAT ? Type::getFloatTy(TheContext) : Type::getInt32Ty(TheContext);

                alloc = builder_stack.back().CreateAlloca(type, nullptr, var_name);
                val_table[var_name] = {alloc, l_type};
            }

            if (l->getType()->isPointerTy())
            {
                l = builder_stack.back().CreateLoad(l_type == FLOAT ? Type::getFloatTy(TheContext) : Type::getInt32Ty(TheContext), l, "");
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
            bool have_float_type = false;
            if (l->getType()->isFloatTy() || r->getType()->isFloatTy() || l_type == FLOAT || r_type == FLOAT)
            {
                have_float_type = true;
            }

            if (l->getType()->isPointerTy())
            {
                auto type = l_type == FLOAT ? Type::getFloatTy(TheContext) : Type::getInt32Ty(TheContext);
                l = builder_stack.back().CreateLoad(type, l, "");
            }
            if (r->getType()->isPointerTy())
            {
                auto type = r_type == FLOAT ? Type::getFloatTy(TheContext) : Type::getInt32Ty(TheContext);
                r = builder_stack.back().CreateLoad(type, r, "");
            }
            Value *res = nullptr;

            if (cur->kind == PLUS)
            {
                if (have_float_type)
                {
                    res = builder_stack.back().CreateFAdd(l, r, get<string>(cur->result.data));
                }
                else
                {
                    res = builder_stack.back().CreateAdd(l, r, get<string>(cur->result.data));
                }
            }
            else if (cur->kind == MINUS)
            {
                if (have_float_type)
                {
                    res = builder_stack.back().CreateFSub(l, r, get<string>(cur->result.data));
                }
                else
                {
                    res = builder_stack.back().CreateSub(l, r, get<string>(cur->result.data));
                }
            }
            else if (cur->kind == STAR)
            {
                if (have_float_type)
                {
                    res = builder_stack.back().CreateFMul(l, r, get<string>(cur->result.data));
                }
                else
                {
                    res = builder_stack.back().CreateMul(l, r, get<string>(cur->result.data));
                }
            }
            else if (cur->kind == DIV)
            {
                if (have_float_type)
                {
                    res = builder_stack.back().CreateFDiv(l, r, get<string>(cur->result.data));
                }
                else
                {
                    res = builder_stack.back().CreateSDiv(l, r, get<string>(cur->result.data));
                }
            }
            else if (cur->kind == MOD)
            {
                if (have_float_type)
                {
                    throw std::runtime_error("cannot mod float value.");
                }
                else
                {
                    res = builder_stack.back().CreateSRem(l, r, get<string>(cur->result.data));
                }
            }

            val_table[get<string>(cur->result.data)] = {res, have_float_type ? FLOAT : INT};
            break;
        }
        case RETURN:
        {
            if (cur->result.kind)
            {
                auto [return_val, return_type] = val_table[get<string>(cur->result.data)];
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
            const string &label = get<string>(cur->result.data);
            create_goto(label);
            break;
        }
        case FUNCTION:
        {
            const string &function_name = get<string>(cur->result.data);
            const auto fill_result = search_symbol_table_with_flag(function_name, 'F');

            vector<Type *> parameters;
            for (int i = 0; i < fill_result.value().paramnum; i++)
            {
                const int offset = i + fill_result.value().idx + 1;
                parameters.push_back(symbol_table[offset].type == FLOAT ? Type::getFloatTy(TheContext) : Type::getInt32Ty(TheContext));
            }
            Type *return_type = Type::getInt32Ty(TheContext);
            FunctionType *function_type = FunctionType::get(return_type, parameters, false);
            Function *function_value = Function::Create(function_type, Function::ExternalLinkage, function_name, TheModule);
            BasicBlock *next_block = BasicBlock::Create(TheContext, "entry", function_value);
            function_table[function_name] = {function_value, function_type};
            int ptr = fill_result.value().idx + 1;
            for (auto &arg : function_value->args())
            {
                val_table[symbol_table[ptr].alias] = {&arg, symbol_table[ptr].type};
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
            auto [fn, fn_type] = function_table[get<string>(cur->opn1.data)];
            vector<Value *> parameters;
            for (auto arg : cur->data)
            {
                auto [val, val_type] = val_table[get<string>(arg->result.data)];
                if (val->getType()->isPointerTy())
                {
                    auto type = val_type == FLOAT ? Type::getFloatTy(TheContext) : Type::getInt32Ty(TheContext);
                    val = builder_stack.back().CreateLoad(type, val, "");
                }

                parameters.push_back(val);
            }

            val_table[get<string>(cur->result.data)] = {builder_stack.back().CreateCall(fn_type, fn, parameters, get<string>(cur->result.data)), fn_type->getReturnType()->isFloatTy() ? FLOAT : INT};
            break;
        }

        case LABEL:
        {
            const string &label = get<string>(cur->result.data);
            BasicBlock *next_block = BasicBlock::Create(TheContext, label, function_stack.back());
            label_table[label] = next_block;

            if (deferred_goto_statement.count(label))
            {
                for (auto val : deferred_goto_statement[label])
                {
                    BranchInst::Create(next_block, val);
                    val->eraseFromParent();
                }
                deferred_goto_statement.erase(label);
            }

            for (auto it = deferred_br_statement.begin(); it != deferred_br_statement.end();)
            {
                auto [val, icmp_val, true_label, false_label] = *it;
                if (label_table.count(true_label) && label_table.count(false_label))
                {
                    BranchInst::Create(label_table[true_label], label_table[false_label], icmp_val, val);
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
            const string &label = get<string>(cur->result.data);
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
            Value *val = nullptr;

            if (l_type != r_type)
            {
                throw std::runtime_error("inconsistency float and int type.");
            }

            bool cmp_float = l_type == FLOAT || r_type == FLOAT;
            if (cmp_float)
            {
                if (l && l->getType()->isPointerTy())
                    l = builder_stack.back().CreateLoad(Type::getFloatTy(TheContext), l, "");
                if (r && r->getType()->isPointerTy())
                    r = builder_stack.back().CreateLoad(Type::getFloatTy(TheContext), r, "");

                if (cur->kind == EQ)
                    val = builder_stack.back().CreateFCmpOEQ(l, r, "cmpres");
                else if (cur->kind == NEQ)
                    val = builder_stack.back().CreateFCmpONE(l, r, "cmpres");
                else if (cur->kind == JGE)
                    val = builder_stack.back().CreateFCmpOGE(l, r, "cmpres");
                else if (cur->kind == JGT)
                    val = builder_stack.back().CreateFCmpOGT(l, r, "cmpres");
                else if (cur->kind == JLE)
                    val = builder_stack.back().CreateFCmpOLE(l, r, "cmpres");
                else if (cur->kind == JLT)
                    val = builder_stack.back().CreateFCmpOLT(l, r, "cmpres");
            }
            else
            { // int
                if (l && l->getType()->isPointerTy())
                    l = builder_stack.back().CreateLoad(Type::getInt32Ty(TheContext), l, "");
                if (r && r->getType()->isPointerTy())
                    r = builder_stack.back().CreateLoad(Type::getInt32Ty(TheContext), r, "");

                if (cur->kind == EQ)
                    val = builder_stack.back().CreateICmpEQ(l, r, "cmpres");
                else if (cur->kind == NEQ)
                    val = builder_stack.back().CreateICmpNE(l, r, "cmpres");
                else if (cur->kind == JGE)
                    val = builder_stack.back().CreateICmpSGE(l, r, "cmpres");
                else if (cur->kind == JGT)
                    val = builder_stack.back().CreateICmpSGT(l, r, "cmpres");
                else if (cur->kind == JLE)
                    val = builder_stack.back().CreateICmpSLE(l, r, "cmpres");
                else if (cur->kind == JLT)
                    val = builder_stack.back().CreateICmpSLT(l, r, "cmpres");
            }

            const string &true_label = get<string>(cur->result.data), &false_label = get<string>(cur->data[0]->result.data);
            if (label_table.count(true_label) && label_table.count(false_label))
            {
                builder_stack.back().CreateCondBr(val, label_table[true_label], label_table[false_label]);
            }
            else
            {
                Instruction *fake_node = builder_stack.back().CreateRetVoid();
                deferred_br_statement.emplace_back(fake_node, val, true_label, false_label);
            }
        }
        }

        cur = cur->next;
    } while (cur != head);

    if constexpr (PRINT_LLVM_IR == 1)
    {
        TheModule.print(errs(), nullptr);
    }
    verifyModule(TheModule, &(errs()));
}
