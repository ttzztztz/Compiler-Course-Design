#include "compiler.h"
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

void throw_semantic_error(int line, const string &msg1, const string &msg2 = "")
{
    const string err_msg("Line " + to_string(line) + ", Message: " + msg1 + " " + msg2);
    throw std::runtime_error(err_msg);
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

optional<int> fill_symbol_table(const string &name, const string &alias, int level, int type, char flag)
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
    sym.idx = symbol_table.size();

    symbol_table.emplace_back(sym);
    return symbol_table.size() - 1;
}

int fill_temp_var(const string &name, int level, int type, char flag)
{
    Symbol sym{};

    sym.name = "";
    sym.alias = name;
    sym.level = level;
    sym.type = type;
    sym.flag = flag;
    sym.idx = symbol_table.size();

    symbol_table.emplace_back(sym);
    return symbol_table.size() - 1;
}

int level = 0;

void ext_var_list(ASTNode *node)
{
    switch (node->kind)
    {
    case EXT_DEC_LIST:
        node->ptr[0]->type = node->type;
        node->ptr[1]->type = node->type;
        ext_var_list(node->ptr[0]);
        ext_var_list(node->ptr[1]);
        node->num = node->ptr[1]->num + 1;
        break;
    case ID:
    {
        auto fill_result = fill_symbol_table(get<string>(node->data), new_alias(), level, node->type, 'V');
        if (fill_result == nullopt)
            throw_semantic_error(node->pos, get<string>(node->data), "Redecl Variable");
        else
            node->idx = fill_result.value();
        node->num = 1;
        break;
    }
    }
}

bool match_param(const Symbol &symbol, ASTNode *node)
{
    int num = symbol.paramnum;
    const int pos = node->pos;
    node = node->ptr[0];
    if (num == 0 && node == nullptr)
    {
        return true;
    }

    for (int j = 1; j <= num; j++)
    {
        if (!node)
        {
            throw_semantic_error(pos, "", "Too few parameters to call function!");
            return false;
        }
        int type1 = symbol_table[symbol.idx + j].type;
        int type2 = node->ptr[0]->type;
        if (type1 != type2)
        {
            throw_semantic_error(pos, "", "Function Type doesn't match.");
            return false;
        }
        node = node->ptr[1];
    }
    if (node)
    {
        throw_semantic_error(pos, "", "Too much parameters to call function.");
        return false;
    }
    return true;
}

void bool_expression(ASTNode *node)
{
    if (node)
    {
        switch (node->kind)
        {
        case INT:
        case ID:
        case FLOAT:
            break;
        case RELOP:
        {
            Operation opn1, opn2, result;
            int kind = 0;
            expression(node->ptr[0]);
            expression(node->ptr[1]);
            opn1.kind = ID;
            opn1.data = symbol_table[node->ptr[0]->idx].alias;
            opn2.kind = ID;
            opn2.data = symbol_table[node->ptr[1]->idx].alias;
            result.kind = ID;
            result.data = node->Etrue;
            if (get<string>(node->data) == "<")
                kind = JLT;
            else if (get<string>(node->data) == "<=")
                kind = JLE;
            else if (get<string>(node->data) == ">")
                kind = JGT;
            else if (get<string>(node->data) == ">=")
                kind = JGE;
            else if (get<string>(node->data) == "==")
                kind = EQ;
            else if (get<string>(node->data) == "!=")
                kind = NEQ;
            break;
        }
        case AND:
        case OR:
            if (node->kind == AND)
            {
                node->ptr[0]->Etrue = new_label();
                node->ptr[0]->Efalse = node->Efalse;
            }
            else
            {
                node->ptr[0]->Etrue = node->Etrue;
                node->ptr[0]->Efalse = new_label();
            }
            node->ptr[1]->Etrue = node->Etrue;
            node->ptr[1]->Efalse = node->Efalse;
            bool_expression(node->ptr[0]);
            bool_expression(node->ptr[1]);
            break;
        case NOT:
            node->ptr[0]->Etrue = node->Efalse;
            node->ptr[0]->Efalse = node->Etrue;
            bool_expression(node->ptr[0]);
            break;
        }
    }
}

void expression(ASTNode *node)
{
    if (node)
    {
        switch (node->kind)
        {
        case INT:
        {
            Operation opn1, opn2, result;
            node->idx = fill_temp_var(new_temp(), level, node->type, 'T');
            node->type = INT;
            opn1.kind = INT;
            opn1.data = get<int>(node->data);
            result.kind = ID;
            result.data = symbol_table[node->idx].alias;
            break;
        }
        case ID:
        {
            auto fill_result = search_symbol_table(get<string>(node->data));
            if (fill_result == nullopt)
                throw_semantic_error(node->pos, get<string>(node->data), "Variable not declared.");
            if (fill_result.value().flag == 'F')
                throw_semantic_error(node->pos, get<string>(node->data), "Type doesn't match.");
            else
            {
                node->idx = fill_result.value().idx;
                node->type = fill_result.value().type;
            }
            break;
        }
        case FLOAT:
        {
            Operation opn1, opn2, result;
            node->idx = fill_temp_var(new_temp(), level, node->type, 'T');
            node->type = FLOAT;
            opn1.kind = FLOAT;
            opn1.data = get<float>(node->data);
            result.kind = ID;
            result.data = symbol_table[node->idx].alias;
            break;
        }
        case ASSIGNOP:
        {
            Operation opn1, opn2, result;

            if (node->ptr[0]->kind != ID)
            {
                throw_semantic_error(node->pos, "", "Assign Expression needs to be left value.");
            }
            else
            {
                expression(node->ptr[0]);
                expression(node->ptr[1]);
                node->type = node->ptr[0]->type;
                opn1.kind = ID;
                opn1.data = symbol_table[node->ptr[1]->idx].alias;
                result.kind = ID;
                result.data = symbol_table[node->ptr[0]->idx].alias;
            }
            break;
        }
        case RELOP: // todo
            node->type = INT;
            expression(node->ptr[0]);
            expression(node->ptr[1]);
            break;
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
        case MOD:
        {
            Operation opn1, opn2, result;

            expression(node->ptr[0]);
            expression(node->ptr[1]);
            // todo: err handle
            if (node->ptr[0]->type == FLOAT || node->ptr[1]->type == FLOAT)
                node->type = FLOAT;
            else
                node->type = INT;
            node->idx = fill_temp_var(new_temp(), level, node->type, 'T');
            opn1.kind = ID;
            opn1.data = symbol_table[node->ptr[0]->idx].alias;
            opn1.type = node->ptr[0]->type;
            opn2.kind = ID;
            opn2.data = symbol_table[node->ptr[1]->idx].alias;
            opn2.type = node->ptr[1]->type;
            result.kind = ID;
            result.data = symbol_table[node->idx].alias;
            result.type = node->type;
            break;
        }
        case NOT: // todo
            break;
        case UMINUS: // todo
            break;
        case FUNC_CALL:
        {
            Operation opn1, opn2, result;

            auto fill_result = search_symbol_table(get<string>(node->data));
            if (fill_result == nullopt)
            {
                throw_semantic_error(node->pos, get<string>(node->data), "Function not declared.");
                break;
            }
            if (fill_result.value().flag != 'F')
            {
                throw_semantic_error(node->pos, get<string>(node->data), "Not a function!");
                break;
            }
            node->type = fill_result.value().type;
            const int width = node->type == INT ? 4 : 8;
            if (node->ptr[0])
            {
                expression(node->ptr[0]);
            }
            match_param(fill_result.value(), node);
            ASTNode *ptr = node->ptr[0];
            while (ptr)
            {
                result.kind = ID;
                result.data = symbol_table[ptr->ptr[0]->idx].alias;
                ptr = ptr->ptr[1];
            }
            node->idx = fill_temp_var(new_temp(), level, node->type, 'T');
            opn1.kind = ID;
            opn1.data = node->data;
            result.kind = ID;
            result.data = symbol_table[node->idx].alias;

            break;
        }
        case ARGS:
            expression(node->ptr[0]);
            if (node->ptr[1])
            {
                expression(node->ptr[1]);
            }
            break;
        }
    }
}

vector<ASTNode *> semantic_stack;
optional<ASTNode *> find_last_loop_statement()
{
    for (int i = semantic_stack.size() - 1; i >= 0; i--)
    {
        if (semantic_stack[i]->kind == WHILE)
            return semantic_stack[i];
    }
    return nullopt;
}

void semantic_analysis(ASTNode *node, const string &function_name = "")
{
    if (node)
    {
        semantic_stack.push_back(node);
        switch (node->kind)
        {
        case CONTINUE:
        case BREAK:
        {
            auto last_loop_statement = find_last_loop_statement();
            if (last_loop_statement == nullopt)
            {
                throw_semantic_error(node->pos, "Break or continue statement invalid");
                break;
            }
            Operation opn1, opn2, result;
            result.kind = ID;
            result.data = last_loop_statement.value()->Snext;

            node->Snext = last_loop_statement.value()->Snext;
            break;
        }
        case RETURN:
        {
            Operation opn1, opn2, result;
            if (node->ptr[0])
            {
                expression(node->ptr[0]);

                result.kind = ID;
                result.data = symbol_table[node->ptr[0]->idx].alias;

                auto function_symbol = search_symbol_table_with_flag(function_name, 'F');
                auto return_var_name = get<string>(result.data);
                auto return_var_symbol = search_symbol_table_with_alias(get<string>(result.data));
                const int return_type = function_symbol.value().type;
                if (return_var_symbol.value().type != return_type)
                {
                    throw_semantic_error(node->ptr[0]->pos, "Return type doesn't match.");
                }
            }
            else
            {
                result.kind = 0;
            }
            break;
        }
        case EXT_DEF_LIST:
            if (!node->ptr[0])
            {
                break;
            }
            semantic_analysis(node->ptr[0], function_name);
            if (node->ptr[1])
            {
                semantic_analysis(node->ptr[1], function_name);
            }
            break;
        case EXT_VAR_DEF:
            node->type = node->ptr[1]->type = get<string>(node->ptr[0]->data) == "int" ? INT : FLOAT;
            ext_var_list(node->ptr[1]);
            break;
        case FUNC_DEF:
            node->ptr[1]->type = get<string>(node->ptr[0]->data) == "int" ? INT : FLOAT;
            semantic_analysis(node->ptr[1], get<string>(node->ptr[1]->data));
            // T->ptr[2]->Snext = new_label();
            semantic_analysis(node->ptr[2], get<string>(node->ptr[1]->data));
            break;
        case FUNC_DEC:
        {
            Operation opn1, opn2, result;
            const auto fill_result = fill_symbol_table(get<string>(node->data), new_alias(), level, node->type, 'F');
            if (fill_result == nullopt)
            {
                throw_semantic_error(node->pos, get<string>(node->data), "Function Redeclaration.");
                break;
            }
            else
            {
                node->idx = fill_result.value();
            }
            result.kind = ID;
            result.data = node->data;
            if (node->ptr[0])
            {
                semantic_analysis(node->ptr[0], function_name);
                symbol_table[fill_result.value()].paramnum = node->ptr[0]->num;
            }
            else
            {
                symbol_table[fill_result.value()].paramnum = 0;
            }
            break;
        }
        case PARAM_LIST:
            semantic_analysis(node->ptr[0], function_name);
            if (node->ptr[1])
            {
                semantic_analysis(node->ptr[1], function_name);
                node->num = node->ptr[0]->num + node->ptr[1]->num;
            }
            else
            {
                node->num = node->ptr[0]->num;
            }
            break;
        case PARAM_DEC:
        {
            Operation opn1, opn2, result;
            auto fill_result = fill_symbol_table(get<string>(node->ptr[1]->data), new_alias(), 1, node->ptr[0]->type, 'P');
            if (fill_result == nullopt)
            {
                throw_semantic_error(node->ptr[1]->pos, get<string>(node->ptr[1]->data), "Function Parameter name re-declaration.");
            }
            else
            {
                node->ptr[1]->idx = fill_result.value();
            }
            node->num = 1;
            result.kind = ID;
            result.data = symbol_table[fill_result.value()].alias;
            // T->code = generate_code_node(PARAM, opn1, opn2, result);
            break;
        }
        case VAR_DEF:
        {
            Operation opn1, opn2, result;
            node->ptr[1]->type = get<string>(node->ptr[0]->data) == "int" ? INT : FLOAT;
            ASTNode *ptr = node->ptr[1];
            int num = 0;
            while (ptr)
            {
                num++;
                ptr->ptr[0]->type = ptr->type;
                if (ptr->ptr[1])
                {
                    ptr->ptr[1]->type = ptr->type;
                }

                if (ptr->ptr[0]->kind == ID)
                {
                    auto fill_result = fill_symbol_table(get<string>(ptr->ptr[0]->data), new_alias(), level, ptr->ptr[0]->type, 'V');
                    if (fill_result == nullopt)
                    {
                        throw_semantic_error(ptr->ptr[0]->pos, get<string>(ptr->ptr[0]->data), "Variable re-declared.");
                    }
                    else
                    {
                        ptr->ptr[0]->idx = fill_result.value();
                    }
                }
                else if (ptr->ptr[0]->kind == ASSIGNOP)
                {
                    auto fill_result = fill_symbol_table(get<string>(ptr->ptr[0]->ptr[0]->data), new_alias(), level, ptr->ptr[0]->type, 'V');
                    if (fill_result == nullopt)
                        throw_semantic_error(ptr->ptr[0]->ptr[0]->pos, get<string>(ptr->ptr[0]->ptr[0]->data), "Variable re-declared.");
                    else
                    {
                        ptr->ptr[0]->idx = fill_result.value();
                        expression(ptr->ptr[0]->ptr[1]);
                        opn1.kind = ID;
                        opn1.data = symbol_table[ptr->ptr[0]->ptr[1]->idx].alias;
                        result.kind = ID;
                        result.data = symbol_table[ptr->ptr[0]->idx].alias;
                    }
                }
                ptr = ptr->ptr[1];
            }
            break;
        }
        case DEF_LIST:
            if (node->ptr[0])
            {
                semantic_analysis(node->ptr[0], function_name);
            }
            if (node->ptr[1])
            {
                semantic_analysis(node->ptr[1], function_name);
            }
            break;
        case COMP_STM:
            level++;
            symbol_scope_chain_stack.push_back(symbol_table.size());
            if (node->ptr[0])
            {
                semantic_analysis(node->ptr[0], function_name);
            }
            if (node->ptr[1])
            {
                node->ptr[1]->Snext = node->Snext;
                semantic_analysis(node->ptr[1], function_name);
            }
            print_symbol_table();
            level--;
            symbol_table.resize(symbol_scope_chain_stack.back());
            symbol_scope_chain_stack.pop_back();
            break;
        case STM_LIST:
            if (!node->ptr[0])
            {
                break;
            }
            if (node->ptr[1])
                node->ptr[0]->Snext = new_label();
            else
                node->ptr[0]->Snext = node->Snext;
            semantic_analysis(node->ptr[0], function_name);
            if (node->ptr[1])
            {
                node->ptr[1]->Snext = node->Snext;
                semantic_analysis(node->ptr[1], function_name);
            }
            break;
        case EXP_STMT:
            semantic_analysis(node->ptr[0], function_name);
            break;
        case IF_THEN:
            node->ptr[0]->Etrue = new_label();
            node->ptr[0]->Efalse = node->Snext;
            bool_expression(node->ptr[0]);
            node->ptr[1]->Snext = node->Snext;
            semantic_analysis(node->ptr[1], function_name);
            break;
        case IF_THEN_ELSE:
            node->ptr[0]->Etrue = new_label();
            node->ptr[0]->Efalse = new_label();
            bool_expression(node->ptr[0]);
            node->ptr[1]->Snext = node->Snext;
            semantic_analysis(node->ptr[1], function_name);
            node->ptr[2]->Snext = node->Snext;
            semantic_analysis(node->ptr[2], function_name);
            break;
        case WHILE:
            node->ptr[0]->Etrue = new_label();
            node->ptr[0]->Efalse = node->Snext;
            bool_expression(node->ptr[0]);
            node->ptr[1]->Snext = new_label();
            semantic_analysis(node->ptr[1], function_name);
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
            expression(node);
            break;
        }
        semantic_stack.pop_back();
    }
}

void entrypoint(ASTNode *node)
{
    semantic_stack.clear();

    fill_symbol_table("print_int", "", 0, INT, 'F');
    symbol_table[0].paramnum = 1;
    fill_symbol_table("0", "", 1, INT, 'P');

    semantic_analysis(node);
}
