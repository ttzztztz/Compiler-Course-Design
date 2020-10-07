#include "def.h"
#include "parser.tab.h"

Operation::Operation() : data(0), kind(0), type(0), level(0) {}
CodeNode::CodeNode() : op(0), next(nullptr), prior(nullptr) {}
ASTNode::ASTNode() : kind(0), ptr{nullptr, nullptr, nullptr, nullptr}, idx(0), type(0), pos(0), num(0), code(nullptr) {}
Symbol::Symbol() : level(0), type(0), paramnum(0), flag(0), idx(0) {}

extern vector<Symbol> symbol_table;

ASTNode *make_node(int kind, int pos, vector<ASTNode *> nodes)
{
    ASTNode *T = new ASTNode();
    T->kind = kind;
    T->pos = pos;

    int i = 0;
    for (i = 0; i < nodes.size(); i++)
        T->ptr[i] = nodes[i];
    while (i < 4)
        T->ptr[i++] = nullptr;

    return T;
}

void print_ast_node(ASTNode *T, int indent)
{
#if PRINT_AST == 0
    return;
#endif

    if (T)
    {
        switch (T->kind)
        {
        case INT:
            printf("%*cINT: %d\n", indent, ' ', get<int>(T->data));
            break;
        case ID:
            printf("%*cID: %s\n", indent, ' ', get<string>(T->data).c_str());
            break;
        case TYPE:
            printf("%*cType: %s\n", indent, ' ', get<string>(T->data).c_str());
            break;
        case FLOAT:
            printf("%*cFLAOT: %f\n", indent, ' ', get<float>(T->data));
            break;
        case WHILE:
            printf("%*cLoop Statement: (%d)\n", indent, ' ', T->pos);
            printf("%*cLoop Condition: \n", indent + 2, ' ');
            print_ast_node(T->ptr[0], indent + 4);
            printf("%*cLoop Body: (%d)\n", indent + 2, ' ', T->pos);
            print_ast_node(T->ptr[1], indent + 4);
            break;
        case RETURN:
            printf("%*cReturn Expression:(%d)\n", indent, ' ', T->pos);
            print_ast_node(T->ptr[0], indent + 2);
            break;
        case EXT_DEF_LIST:
            print_ast_node(T->ptr[0], indent);
            print_ast_node(T->ptr[1], indent);
            break;
        case EXT_VAR_DEF:
            printf("%*cVariable Declaration: (%d)\n", indent, ' ', T->pos);
            print_ast_node(T->ptr[0], indent + 2);
            printf("%*cVariable Name: \n", indent + 2, ' ');
            print_ast_node(T->ptr[1], indent + 4);
            break;
        case FUNC_DEF:
            printf("%*cFunction Declaration: (%d)\n", indent, ' ', T->pos);
            print_ast_node(T->ptr[0], indent + 2);
            print_ast_node(T->ptr[1], indent + 2);
            print_ast_node(T->ptr[2], indent + 2);
            break;
        case FUNC_DEC:
            printf("%*cFunction Name: %s\n", indent, ' ', get<string>(T->data).c_str());
            if (T->ptr[0])
            {
                printf("%*cFunction Parameters: \n", indent, ' ');
                print_ast_node(T->ptr[0], indent + 2);
            }
            else
            {
                printf("%*cFunction without Parameters: \n", indent + 2, ' ');
            }
            break;
        case EXT_DEC_LIST:
            print_ast_node(T->ptr[0], indent);
            print_ast_node(T->ptr[1], indent);
            break;
        case PARAM_LIST:
            print_ast_node(T->ptr[0], indent);
            print_ast_node(T->ptr[1], indent);
            break;
        case PARAM_DEC:
            printf("%*cType: %s, Parameter Name: %s\n", indent, ' ', T->ptr[0]->type == INT ? "int" : "float", get<string>(T->ptr[1]->data).c_str());
            break;
        case VAR_DEF:
            printf("%*cVariable Decl: (%d)\n", indent, ' ', T->pos);
            print_ast_node(T->ptr[0], indent + 2);
            print_ast_node(T->ptr[1], indent + 2);
            break;
        case DEC_LIST:
        {
            printf("%*cVariable Name Decl:\n", indent, ' ');
            ASTNode *T0 = T;
            while (T0)
            {
                if (T0->ptr[0]->kind == ID)
                    printf("%*c %s\n", indent + 4, ' ', get<string>(T0->ptr[0]->data).c_str());
                else if (T0->ptr[0]->kind == ASSIGNOP)
                {
                    printf("%*c %s ASSIGNOP\n ", indent + 4, ' ', get<string>(T0->ptr[0]->ptr[0]->data).c_str());
                    print_ast_node(T0->ptr[0]->ptr[1], indent + get<string>(T0->ptr[0]->ptr[0]->data).size() + 8);
                }
                T0 = T0->ptr[1];
            }
            break;
        }
        case DEF_LIST:
            print_ast_node(T->ptr[0], indent);
            print_ast_node(T->ptr[1], indent);
            break;
        case COMP_STM:
            printf("%*cComposite Expression: (%d)\n", indent, ' ', T->pos);
            printf("%*cVariable Declaration (Composite Expression) :\n", indent + 2, ' ');
            print_ast_node(T->ptr[0], indent + 4);
            printf("%*cExpression (Composite Expression) :\n", indent + 2, ' ');
            print_ast_node(T->ptr[1], indent + 4);
            break;
        case STM_LIST:
            print_ast_node(T->ptr[0], indent);
            print_ast_node(T->ptr[1], indent);
            break;
        case EXP_STMT:
            printf("%*cExpression:(%d)\n", indent, ' ', T->pos);
            print_ast_node(T->ptr[0], indent + 2);
            break;
        case IF_THEN:
            printf("%*cIF Expression: (%d)\n", indent, ' ', T->pos);
            printf("%*cIF Conds:\n", indent + 2, ' ');
            print_ast_node(T->ptr[0], indent + 4);
            printf("%*cIF Body:(%d)\n", indent + 2, ' ', T->pos);
            print_ast_node(T->ptr[1], indent + 4);
            break;
        case IF_THEN_ELSE:
            printf("%*cIF Expression - Else: (%d)\n", indent, ' ', T->pos);
            printf("%*cIF Conds: \n", indent + 2, ' ');
            print_ast_node(T->ptr[0], indent + 4);
            printf("%*cIF Body: (%d)\n", indent + 2, ' ', T->pos);
            print_ast_node(T->ptr[1], indent + 4);
            printf("%*cELSE Body: (%d)\n", indent + 4, ' ', T->pos);
            print_ast_node(T->ptr[2], indent + 4);
            break;
        case FUNC_CALL:
            printf("%*cFunction Call: (%d)\n", indent, ' ', T->pos);
            printf("%*cFunction Name: %s\n", indent + 2, ' ', get<string>(T->data).c_str());
            print_ast_node(T->ptr[0], indent + 2);
            break;
        case ARGS:
        {
            int i = 1;
            while (T)
            {
                ASTNode *T0 = T->ptr[0];
                printf("%*cParameter #%d Parameter Expression: \n", indent, ' ', i++);
                print_ast_node(T0, indent + 2);
                T = T->ptr[1];
            }
            printf("\n");
            break;
        }
        case ASSIGNOP:
        case AND:
        case OR:
        case RELOP:
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
        case MOD:
            printf("%*c%s\n", indent, ' ', get<string>(T->data).c_str());
            print_ast_node(T->ptr[0], indent + 2);
            print_ast_node(T->ptr[1], indent + 2);
            break;
        case NOT:
        case UMINUS:
            printf("%*c%s\n", indent, ' ', get<string>(T->data).c_str());
            print_ast_node(T->ptr[0], indent + 2);
            break;
        }
    }
}

void print_symbol_table()
{
#if PRINT_SYMBOL_TABLE == 0
    return;
#endif

    printf("%6s %6s %6s  %6s %4s %6s\n", "Name", "Alias", "Level", "Type", "Flag");
    for (int i = 0; i < symbol_table.size(); i++)
        printf("%6s %6s %6d  %6s %4c\n", symbol_table[i].name.c_str(),
               symbol_table[i].alias.c_str(), symbol_table[i].level,
               symbol_table[i].type == INT ? "int" : "float");
}