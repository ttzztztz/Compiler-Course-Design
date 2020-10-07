#include "def.h"
#include "string"
#include "iostream"
#include "unordered_map"
#include "vector"

using std::string, std::vector, std::to_string;
vector<Symbol> symbol_table;
vector<int> symbol_scope_chain_stack;

string new_alias()
{
    static int no = 1;
    return "v" + std::to_string(no++);
}

string new_label()
{
    static int no = 1;
    return "l" + std::to_string(no++);
}

string new_temp()
{
    static int no = 1;
    return "t" + std::to_string(no++);
}

CodeNode *generate_code_node(int op, Operation opn1, Operation opn2, Operation result)
{
    CodeNode *h = new CodeNode();
    h->op = op;
    h->opn1 = opn1;
    h->opn2 = opn2;
    h->result = result;
    h->next = h->prior = h;
    return h;
}

CodeNode *generate_label(const string &label)
{
    CodeNode *h = new CodeNode();
    h->op = LABEL;
    h->result.data = label;
    h->next = h->prior = h;
    return h;
}

CodeNode *generate_goto(const string &label)
{
    CodeNode *h = new CodeNode();
    h->op = GOTO;
    h->result.data = label;
    h->next = h->prior = h;
    return h;
}

CodeNode *merge_code_node(const vector<CodeNode *> &list)
{
    CodeNode *h1 = list[0], *h2 = nullptr;

    for (int ptr = 1; ptr < list.size(); ptr++)
    {
        h2 = list[ptr];
        if (h1 == nullptr)
            h1 = h2;
        else if (h2)
        {
            CodeNode *t1 = h1->prior;
            CodeNode *t2 = h2->prior;
            t1->next = h2;
            t2->next = h1;
            h1->prior = t2;
            h2->prior = t1;
        }
    }
    return h1;
}

void throw_semantic_error(int line, const string &msg1, const string &msg2 = "")
{
    const string err_msg("Line " + to_string(line) + ", Message: " + msg1 + " " + msg2);
    throw std::runtime_error(err_msg);
}

void print_symbol_table()
{
#if PRINT_SYMBOL_TABLE == 0
    return;
#endif

    printf("%6s %6s %6s  %6s %4s %6s\n", "Name", "Alias", "Level", "Type", "Flag", "Offset");
    for (int i = 0; i < symbol_table.size(); i++)
        printf("%6s %6s %6d  %6s %4c %6d\n", symbol_table[i].name.c_str(),
               symbol_table[i].alias.c_str(), symbol_table[i].level,
               symbol_table[i].type == INT ? "int" : "float",
               symbol_table[i].flag, symbol_table[i].offset);
}

optional<Symbol> search_symbol_table(const string &name)
{
    for (int i = symbol_table.size() - 1; i >= 0; i--)
        if (symbol_table[i].name == name)
            return symbol_table[i];
    return nullopt;
}

optional<Symbol> search_symbol_table_with_flag(const string &name, char flag)
{
    for (int i = symbol_table.size() - 1; i >= 0; i--)
        if (symbol_table[i].name == name && symbol_table[i].flag == flag)
            return symbol_table[i];
    return nullopt;
}

optional<Symbol> search_symbol_table_with_alias(const string &alias)
{
    for (int i = symbol_table.size() - 1; i >= 0; i--)
        if (symbol_table[i].alias == alias)
            return symbol_table[i];
    return nullopt;
}

optional<int> fill_symbol_table(const string &name, const string &alias, int level, int type, char flag, int offset)
{
    for (int i = symbol_table.size() - 1; i >= 0 && (symbol_table[i].level == level || level == 0); i--)
    {
        if (level == 0 && symbol_table[i].level == 1)
            continue;
        if (symbol_table[i].name == name)
            return nullopt;
    }

    Symbol sym{};

    sym.name = name;
    sym.alias = alias;
    sym.level = level;
    sym.type = type;
    sym.flag = flag;
    sym.offset = offset;
    sym.idx = symbol_table.size();

    symbol_table.emplace_back(sym);
    return symbol_table.size() - 1;
}

int fill_temp_var(const string &name, int level, int type, char flag, int offset)
{
    Symbol sym{};

    sym.name = "";
    sym.alias = name;
    sym.level = level;
    sym.type = type;
    sym.flag = flag;
    sym.offset = offset;
    sym.offset = symbol_table.size();

    symbol_table.emplace_back(sym);
    return symbol_table.size() - 1;
}

int level = 0;

void ext_var_list(ASTNode *T)
{
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
    {
        auto fill_result = fill_symbol_table(get<string>(T->data), new_alias(), level, T->type, 'V', T->offset);
        if (fill_result == nullopt)
            throw_semantic_error(T->pos, get<string>(T->data), "Redecl Variable");
        else
            T->place = fill_result.value();
        T->num = 1;
        break;
    }
    }
}

bool match_param(const Symbol &symbol, ASTNode *T)
{
    int num = symbol.paramnum;
    const int pos = T->pos;
    T = T->ptr[0];
    if (num == 0 && T == nullptr)
        return true;
    for (int j = 1; j <= num; j++)
    {
        if (!T)
        {
            throw_semantic_error(pos, "", "Too few parameters to call function!");
            return false;
        }
        int type1 = symbol_table[symbol.idx + j].type;
        int type2 = T->ptr[0]->type;
        if (type1 != type2)
        {
            throw_semantic_error(pos, "", "Function Type doesn't match.");
            return false;
        }
        T = T->ptr[1];
    }
    if (T)
    {
        throw_semantic_error(pos, "", "Too much parameters to call function.");
        return false;
    }
    return true;
}

void bool_expression(ASTNode *T)
{
    if (T)
    {
        switch (T->kind)
        {
        case INT:
        case FLOAT:
        case ID:
            break;
        case RELOP:
        {
            Operation opn1, opn2, result;
            int op = 0;
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            expression(T->ptr[0]);
            T->width = T->ptr[0]->width;
            expression(T->ptr[1]);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            opn1.kind = ID;
            opn1.data = symbol_table[T->ptr[0]->place].alias;
            opn1.offset = symbol_table[T->ptr[0]->place].offset;
            opn2.kind = ID;
            opn2.data = symbol_table[T->ptr[1]->place].alias;
            opn2.offset = symbol_table[T->ptr[1]->place].offset;
            result.kind = ID;
            result.data = T->Etrue;
            if (get<string>(T->data) == "<")
                op = JLT;
            else if (get<string>(T->data) == "<=")
                op = JLE;
            else if (get<string>(T->data) == ">")
                op = JGT;
            else if (get<string>(T->data) == ">=")
                op = JGE;
            else if (get<string>(T->data) == "==")
                op = EQ;
            else if (get<string>(T->data) == "!=")
                op = NEQ;
            T->code = generate_code_node(op, opn1, opn2, result);
            T->code->data.push_back(generate_goto(T->Efalse));
            T->code = merge_code_node({T->ptr[0]->code, T->ptr[1]->code, T->code});
            break;
        }
        case AND:
        case OR:
            if (T->kind == AND)
            {
                T->ptr[0]->Etrue = new_label();
                T->ptr[0]->Efalse = T->Efalse;
            }
            else
            {
                T->ptr[0]->Etrue = T->Etrue;
                T->ptr[0]->Efalse = new_label();
            }
            T->ptr[1]->Etrue = T->Etrue;
            T->ptr[1]->Efalse = T->Efalse;
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            bool_expression(T->ptr[0]);
            T->width = T->ptr[0]->width;
            bool_expression(T->ptr[1]);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            if (T->kind == AND)
                T->code = merge_code_node({T->ptr[0]->code, generate_label(T->ptr[0]->Etrue), T->ptr[1]->code});
            else
                T->code = merge_code_node({T->ptr[0]->code, generate_label(T->ptr[0]->Efalse), T->ptr[1]->code});
            break;
        case NOT:
            T->ptr[0]->Etrue = T->Efalse;
            T->ptr[0]->Efalse = T->Etrue;
            bool_expression(T->ptr[0]);
            T->code = T->ptr[0]->code;
            break;
        }
    }
}

void expression(ASTNode *T)
{
    if (T)
    {
        switch (T->kind)
        {
        case ID:
        {
            auto fill_result = search_symbol_table(get<string>(T->data));
            if (fill_result == nullopt)
                throw_semantic_error(T->pos, get<string>(T->data), "Variable not declared.");
            if (fill_result.value().flag == 'F')
                throw_semantic_error(T->pos, get<string>(T->data), "Type doesn't match.");
            else
            {
                T->place = fill_result.value().idx;
                T->code = nullptr;
                T->type = fill_result.value().type;
                T->offset = fill_result.value().offset;
                T->width = 0;
            }
            break;
        }
        case INT:
        {
            Operation opn1, opn2, result;
            T->place = fill_temp_var(new_temp(), level, T->type, 'T', T->offset);
            T->type = INT;
            opn1.kind = INT;
            opn1.data = get<int>(T->data);
            result.kind = ID;
            result.data = symbol_table[T->place].alias;
            result.offset = symbol_table[T->place].offset;
            T->code = generate_code_node(ASSIGNOP, opn1, opn2, result);
            T->width = 4;
            break;
        }
        case FLOAT:
        {
            Operation opn1, opn2, result;
            T->place = fill_temp_var(new_temp(), level, T->type, 'T', T->offset);
            T->type = FLOAT;
            opn1.kind = FLOAT;
            opn1.data = get<float>(T->data);
            result.kind = ID;
            result.data = symbol_table[T->place].alias;
            result.offset = symbol_table[T->place].offset;
            T->code = generate_code_node(ASSIGNOP, opn1, opn2, result);
            T->width = 4;
            break;
        }
        case ASSIGNOP:
        {
            Operation opn1, opn2, result;

            if (T->ptr[0]->kind != ID)
            {
                throw_semantic_error(T->pos, "", "Assign Expression needs to be left value.");
            }
            else
            {
                expression(T->ptr[0]);
                T->ptr[1]->offset = T->offset;
                expression(T->ptr[1]);
                T->type = T->ptr[0]->type;
                T->width = T->ptr[1]->width;
                T->code = merge_code_node({T->ptr[0]->code, T->ptr[1]->code});
                opn1.kind = ID;
                opn1.data = symbol_table[T->ptr[1]->place].alias;
                opn1.offset = symbol_table[T->ptr[1]->place].offset;
                result.kind = ID;
                result.data = symbol_table[T->ptr[0]->place].alias;
                result.offset = symbol_table[T->ptr[0]->place].offset;
                T->code = merge_code_node({T->code, generate_code_node(ASSIGNOP, opn1, opn2, result)});
            }
            break;
        }
        case AND:   // todo
        case OR:    // todo
        case RELOP: // todo
            T->type = INT;
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            expression(T->ptr[0]);
            expression(T->ptr[1]);
            break;
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
        case MOD:
        {
            Operation opn1, opn2, result;

            T->ptr[0]->offset = T->offset;
            expression(T->ptr[0]);
            T->ptr[1]->offset = T->offset + T->ptr[0]->width;
            expression(T->ptr[1]);
            // todo: err handle
            if (T->ptr[0]->type == FLOAT || T->ptr[1]->type == FLOAT)
                T->type = FLOAT, T->width = T->ptr[0]->width + T->ptr[1]->width + 4;
            else
                T->type = INT, T->width = T->ptr[0]->width + T->ptr[1]->width + 2;
            T->place = fill_temp_var(new_temp(), level, T->type, 'T', T->offset + T->ptr[0]->width + T->ptr[1]->width);
            opn1.kind = ID;
            opn1.data = symbol_table[T->ptr[0]->place].alias;
            opn1.type = T->ptr[0]->type;
            opn1.offset = symbol_table[T->ptr[0]->place].offset;
            opn2.kind = ID;
            opn2.data = symbol_table[T->ptr[1]->place].alias;
            opn2.type = T->ptr[1]->type;
            opn2.offset = symbol_table[T->ptr[1]->place].offset;
            result.kind = ID;
            result.data = symbol_table[T->place].alias;
            result.type = T->type;
            result.offset = symbol_table[T->place].offset;
            T->code = merge_code_node({T->ptr[0]->code, T->ptr[1]->code, generate_code_node(T->kind, opn1, opn2, result)});
            T->width = T->ptr[0]->width + T->ptr[1]->width + (T->type == INT ? 4 : 8);
            break;
        }
        case NOT: // todo
            break;
        case UMINUS: // todo
            break;
        case FUNC_CALL:
        {
            vector<CodeNode *> call_args;
            Operation opn1, opn2, result;

            auto fill_result = search_symbol_table(get<string>(T->data));
            if (fill_result == nullopt)
            {
                throw_semantic_error(T->pos, get<string>(T->data), "Function not declared.");
                break;
            }
            if (fill_result.value().flag != 'F')
            {
                throw_semantic_error(T->pos, get<string>(T->data), "Not a function!");
                break;
            }
            T->type = fill_result.value().type;
            const int width = T->type == INT ? 4 : 8;
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                expression(T->ptr[0]);
                T->width = T->ptr[0]->width + width;
                T->code = T->ptr[0]->code;
            }
            else
            {
                T->width = width;
                T->code = nullptr;
            }
            match_param(fill_result.value(), T);
            ASTNode *T0 = T->ptr[0];
            while (T0)
            {
                result.kind = ID;
                result.data = symbol_table[T0->ptr[0]->place].alias;
                result.offset = symbol_table[T0->ptr[0]->place].offset;
                call_args.push_back(generate_code_node(ARG, opn1, opn2, result));
                T0 = T0->ptr[1];
            }
            T->place = fill_temp_var(new_temp(), level, T->type, 'T', T->offset + T->width - width);
            opn1.kind = ID;
            opn1.data = T->data;
            opn1.offset = fill_result.value().idx;
            result.kind = ID;
            result.data = symbol_table[T->place].alias;
            result.offset = symbol_table[T->place].offset;

            auto *call_code_node = generate_code_node(CALL, opn1, opn2, result);
            call_code_node->data = call_args;

            T->code = merge_code_node({T->code, call_code_node});
            break;
        }
        case ARGS:
            T->ptr[0]->offset = T->offset;
            expression(T->ptr[0]);
            T->width = T->ptr[0]->width;
            T->code = T->ptr[0]->code;
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                expression(T->ptr[1]);
                T->width += T->ptr[1]->width;
                T->code = merge_code_node({T->code, T->ptr[1]->code});
            }
            break;
        }
    }
}

void semantic_analysis(ASTNode *T, const string &function_name = "")
{
    if (T)
    {
        switch (T->kind)
        {
        case EXT_DEF_LIST:
            if (!T->ptr[0])
                break;
            T->ptr[0]->offset = T->offset;
            semantic_analysis(T->ptr[0], function_name);
            T->code = T->ptr[0]->code;
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->ptr[0]->offset + T->ptr[0]->width;
                semantic_analysis(T->ptr[1], function_name);
                T->code = merge_code_node({T->code, T->ptr[1]->code});
            }
            break;
        case EXT_VAR_DEF:
            T->type = T->ptr[1]->type = get<string>(T->ptr[0]->data) == "int" ? INT : FLOAT;
            T->ptr[1]->offset = T->offset;
            T->ptr[1]->width = T->type == INT ? 4 : 8;
            ext_var_list(T->ptr[1]);
            T->width = (T->type == INT ? 4 : 8) * T->ptr[1]->num;
            T->code = nullptr;
            break;
        case FUNC_DEF:
            T->ptr[1]->type = get<string>(T->ptr[0]->data) == "int" ? INT : FLOAT;
            T->width = 0;
            T->offset = DX;
            semantic_analysis(T->ptr[1], get<string>(T->ptr[1]->data));
            T->offset += T->ptr[1]->width;
            T->ptr[2]->offset = T->offset;
            // T->ptr[2]->Snext = new_label();
            semantic_analysis(T->ptr[2], get<string>(T->ptr[1]->data));
            symbol_table[T->ptr[1]->place].offset = T->offset + T->ptr[2]->width;
            T->code = merge_code_node({T->ptr[1]->code, T->ptr[2]->code});
            break;
        case FUNC_DEC:
        {
            Operation opn1, opn2, result;
            const auto fill_result = fill_symbol_table(get<string>(T->data), new_alias(), level, T->type, 'F', 0);
            if (fill_result == nullopt)
            {
                throw_semantic_error(T->pos, get<string>(T->data), "Function Redeclaration.");
                break;
            }
            else
            {
                T->place = fill_result.value();
            }
            result.kind = ID;
            result.data = T->data;
            result.offset = fill_result.value();
            T->code = generate_code_node(FUNCTION, opn1, opn2, result);
            T->offset = DX;
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                semantic_analysis(T->ptr[0], function_name);
                T->width = T->ptr[0]->width;
                symbol_table[fill_result.value()].paramnum = T->ptr[0]->num;
                T->code = merge_code_node({T->code, T->ptr[0]->code});
            }
            else
            {
                symbol_table[fill_result.value()].paramnum = 0, T->width = 0;
            }
            break;
        }
        case PARAM_LIST:
            T->ptr[0]->offset = T->offset;
            semantic_analysis(T->ptr[0], function_name);
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                semantic_analysis(T->ptr[1], function_name);
                T->num = T->ptr[0]->num + T->ptr[1]->num;
                T->width = T->ptr[0]->width + T->ptr[1]->width;
                T->code = merge_code_node({T->ptr[0]->code, T->ptr[1]->code});
            }
            else
            {
                T->num = T->ptr[0]->num;
                T->width = T->ptr[0]->width;
                T->code = T->ptr[0]->code;
            }
            break;
        case PARAM_DEC:
        {
            Operation opn1, opn2, result;
            auto fill_result = fill_symbol_table(get<string>(T->ptr[1]->data), new_alias(), 1, T->ptr[0]->type, 'P', T->offset);
            if (fill_result == nullopt)
            {
                throw_semantic_error(T->ptr[1]->pos, get<string>(T->ptr[1]->data), "Function Parameter name re-declaration.");
            }
            else
            {
                T->ptr[1]->place = fill_result.value();
            }
            T->num = 1;
            T->width = T->ptr[0]->type == INT ? 4 : 8;
            result.kind = ID;
            result.data = symbol_table[fill_result.value()].alias;
            result.offset = T->offset;
            // T->code = generate_code_node(PARAM, opn1, opn2, result);
            break;
        }
        case COMP_STM:
            level++;
            symbol_scope_chain_stack.push_back(symbol_table.size());
            T->width = 0;
            T->code = nullptr;
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                semantic_analysis(T->ptr[0], function_name);
                T->width += T->ptr[0]->width;
                T->code = T->ptr[0]->code;
            }
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->offset + T->width;
                T->ptr[1]->Snext = T->Snext;
                semantic_analysis(T->ptr[1], function_name);
                T->width += T->ptr[1]->width;
                T->code = merge_code_node({T->code, T->ptr[1]->code});
            }
            print_symbol_table();
            level--;
            symbol_table.resize(symbol_scope_chain_stack.back());
            symbol_scope_chain_stack.pop_back();
            break;
        case DEF_LIST:
            T->code = nullptr;
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                semantic_analysis(T->ptr[0], function_name);
                T->code = T->ptr[0]->code;
                T->width = T->ptr[0]->width;
            }
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                semantic_analysis(T->ptr[1], function_name);
                T->code = merge_code_node({T->code, T->ptr[1]->code});
                T->width += T->ptr[1]->width;
            }
            break;
        case VAR_DEF:
        {
            Operation opn1, opn2, result;
            T->code = nullptr;
            T->ptr[1]->type = get<string>(T->ptr[0]->data) == "int" ? INT : FLOAT;
            ASTNode *T0 = T->ptr[1];
            int num = 0;
            T0->offset = T->offset;
            T->width = 0;
            int width = T->ptr[1]->type == INT ? 4 : 8;
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
                    auto fill_result = fill_symbol_table(get<string>(T0->ptr[0]->data), new_alias(), level, T0->ptr[0]->type, 'V', T->offset + T->width); // todo: offset count
                    if (fill_result == nullopt)
                    {
                        throw_semantic_error(T0->ptr[0]->pos, get<string>(T0->ptr[0]->data), "Variable re-declared.");
                    }
                    else
                    {
                        T0->ptr[0]->place = fill_result.value();
                    }
                    T->width += width;
                }
                else if (T0->ptr[0]->kind == ASSIGNOP)
                {
                    auto fill_result = fill_symbol_table(get<string>(T0->ptr[0]->ptr[0]->data), new_alias(), level, T0->ptr[0]->type, 'V', T->offset + T->width); // todo: offset count
                    if (fill_result == nullopt)
                        throw_semantic_error(T0->ptr[0]->ptr[0]->pos, get<string>(T0->ptr[0]->ptr[0]->data), "Variable re-declared.");
                    else
                    {
                        T0->ptr[0]->place = fill_result.value();
                        T0->ptr[0]->ptr[1]->offset = T->offset + T->width + width;
                        expression(T0->ptr[0]->ptr[1]);
                        opn1.kind = ID;
                        opn1.data = symbol_table[T0->ptr[0]->ptr[1]->place].alias;
                        result.kind = ID;
                        result.data = symbol_table[T0->ptr[0]->place].alias;
                        T->code = merge_code_node({T->code, T0->ptr[0]->ptr[1]->code, generate_code_node(ASSIGNOP, opn1, opn2, result)});
                    }
                    T->width += width + T0->ptr[0]->ptr[1]->width;
                }
                T0 = T0->ptr[1];
            }
            break;
        }
        case STM_LIST:
            if (!T->ptr[0])
            {
                T->code = nullptr;
                T->width = 0;
                break;
            }
            if (T->ptr[1])
                T->ptr[0]->Snext = new_label();
            else
                T->ptr[0]->Snext = T->Snext;
            T->ptr[0]->offset = T->offset;
            semantic_analysis(T->ptr[0], function_name);
            T->code = T->ptr[0]->code;
            T->width = T->ptr[0]->width;
            if (T->ptr[1])
            {
                T->ptr[1]->Snext = T->Snext;
                T->ptr[1]->offset = T->offset;
                semantic_analysis(T->ptr[1], function_name);
                if (T->ptr[0]->kind == RETURN || T->ptr[0]->kind == EXP_STMT || T->ptr[0]->kind == COMP_STM)
                    T->code = merge_code_node({T->code, T->ptr[1]->code});
                else
                    T->code = merge_code_node({T->code, generate_label(T->ptr[0]->Snext), T->ptr[1]->code});
                if (T->ptr[1]->width > T->width)
                    T->width = T->ptr[1]->width;
            }
            break;
        case IF_THEN:
            T->ptr[0]->Etrue = new_label();
            T->ptr[0]->Efalse = T->Snext;
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            bool_expression(T->ptr[0]);
            T->width = T->ptr[0]->width;
            T->ptr[1]->Snext = T->Snext;
            semantic_analysis(T->ptr[1], function_name);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            T->code = merge_code_node({T->ptr[0]->code, generate_label(T->ptr[0]->Etrue), T->ptr[1]->code, generate_goto(T->ptr[1]->Snext)});
            break;
        case IF_THEN_ELSE:
            T->ptr[0]->Etrue = new_label();
            T->ptr[0]->Efalse = new_label();
            T->ptr[0]->offset = T->ptr[1]->offset = T->ptr[2]->offset = T->offset;
            bool_expression(T->ptr[0]);
            T->width = T->ptr[0]->width;
            T->ptr[1]->Snext = T->Snext;
            semantic_analysis(T->ptr[1], function_name);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            T->ptr[2]->Snext = T->Snext;
            semantic_analysis(T->ptr[2], function_name);
            if (T->width < T->ptr[2]->width)
                T->width = T->ptr[2]->width;
            T->code = merge_code_node({T->ptr[0]->code, generate_label(T->ptr[0]->Etrue), T->ptr[1]->code,
                                       generate_goto(T->Snext), generate_label(T->ptr[0]->Efalse), T->ptr[2]->code, generate_goto(T->Snext)});
            break;
        case WHILE:
            T->ptr[0]->Etrue = new_label();
            T->ptr[0]->Efalse = T->Snext;
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            bool_expression(T->ptr[0]);
            T->width = T->ptr[0]->width;
            T->ptr[1]->Snext = new_label();
            semantic_analysis(T->ptr[1], function_name);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            T->code = merge_code_node({generate_goto(T->ptr[1]->Snext), generate_label(T->ptr[1]->Snext), T->ptr[0]->code,
                                       generate_label(T->ptr[0]->Etrue), T->ptr[1]->code, generate_goto(T->ptr[1]->Snext)});
            break;
        case EXP_STMT:
            T->ptr[0]->offset = T->offset;
            semantic_analysis(T->ptr[0], function_name);
            T->code = T->ptr[0]->code;
            T->width = T->ptr[0]->width;
            break;
        case RETURN:
        {
            Operation opn1, opn2, result;
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                expression(T->ptr[0]);

                T->width = T->ptr[0]->width;
                result.kind = ID;
                result.data = symbol_table[T->ptr[0]->place].alias;
                result.offset = symbol_table[T->ptr[0]->place].offset;
                T->code = merge_code_node({T->ptr[0]->code, generate_code_node(RETURN, opn1, opn2, result)});

                auto function_symbol = search_symbol_table_with_flag(function_name, 'F');
                auto return_var_name = get<string>(result.data);
                auto return_var_symbol = search_symbol_table_with_alias(get<string>(result.data));
                const int return_type = function_symbol.value().type;
                if (return_var_symbol.value().type != return_type)
                {
                    throw_semantic_error(T->ptr[0]->pos, "Return type doesn't match.");
                }
            }
            else
            {
                T->width = 0;
                result.kind = 0;
                T->code = generate_code_node(RETURN, opn1, opn2, result);
            }
            break;
        }
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
            expression(T);
            break;
        }
    }
}

void entrypoint(ASTNode *T)
{
    fill_symbol_table("print_int", "", 0, INT, 'F', 0);
    symbol_table[0].paramnum = 1;
    fill_symbol_table("0", "", 1, INT, 'P', 0);

    T->offset = 0;
    semantic_analysis(T);
    print_llvm_ir(T->code);
}
