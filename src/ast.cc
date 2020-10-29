#include "compiler.h"
#include "parser.tab.h"

Operation::Operation() : data(0), kind(0), type(0), level(0) {}
CodeNode::CodeNode() : kind(0), next(nullptr), prev(nullptr) {}
ASTNode::ASTNode() : kind(0), ptr(4, nullptr), idx(0), type(0), pos(0), num(0), code(nullptr) {}
Symbol::Symbol() : level(0), type(0), paramnum(0), flag(0), idx(0) {}

extern vector<Symbol> symbol_table;

ASTNode *make_node(int kind, int pos, vector<ASTNode *> nodes)
{
    ASTNode *node = new ASTNode();
    node->kind = kind;
    node->pos = pos;

    int i = 0;
    for (i = 0; i < nodes.size(); i++)
    {
        node->ptr[i] = nodes[i];
    }

    while (i < 4)
    {
        node->ptr[i++] = nullptr;
    }

    return node;
}

void print_ast_node(ASTNode *node, int indent)
{
    if constexpr (PRINT_AST == 0)
    {
        return;
    }

    if (node)
    {
        switch (node->kind)
        {
        case INT:
            printf("%*cINT: %d\n", indent, ' ', get<int>(node->data));
            break;
        case ID:
            printf("%*cID: %s\n", indent, ' ', get<string>(node->data).c_str());
            break;
        case TYPE:
            printf("%*cType: %s\n", indent, ' ', get<string>(node->data).c_str());
            break;
        case FLOAT:
            printf("%*cFLAOT: %f\n", indent, ' ', get<float>(node->data));
            break;
        case WHILE:
            printf("%*cLoop Statement: (%d)\n", indent, ' ', node->pos);
            printf("%*cLoop Condition: \n", indent + 2, ' ');
            print_ast_node(node->ptr[0], indent + 4);
            printf("%*cLoop Body: (%d)\n", indent + 2, ' ', node->pos);
            print_ast_node(node->ptr[1], indent + 4);
            break;
        case RETURN:
            printf("%*cReturn Expression:(%d)\n", indent, ' ', node->pos);
            print_ast_node(node->ptr[0], indent + 2);
            break;
        case CONTINUE:
            printf("%*cContinue Statement\n", indent, ' ');
            break;
        case BREAK:
            printf("%*cBreak Statement\n", indent, ' ');
            break;
        case EXT_DEF_LIST:
            print_ast_node(node->ptr[0], indent);
            print_ast_node(node->ptr[1], indent);
            break;
        case EXT_VAR_DEF:
            printf("%*cVariable Declaration: (%d)\n", indent, ' ', node->pos);
            print_ast_node(node->ptr[0], indent + 2);
            printf("%*cVariable Name: \n", indent + 2, ' ');
            print_ast_node(node->ptr[1], indent + 4);
            break;
        case FUNC_DEF:
            printf("%*cFunction Declaration: (%d)\n", indent, ' ', node->pos);
            print_ast_node(node->ptr[0], indent + 2);
            print_ast_node(node->ptr[1], indent + 2);
            print_ast_node(node->ptr[2], indent + 2);
            break;
        case FUNC_DEC:
            printf("%*cFunction Name: %s\n", indent, ' ', get<string>(node->data).c_str());
            if (node->ptr[0])
            {
                printf("%*cFunction Parameters: \n", indent, ' ');
                print_ast_node(node->ptr[0], indent + 2);
            }
            else
            {
                printf("%*cFunction without Parameters: \n", indent + 2, ' ');
            }
            break;
        case EXT_DEC_LIST:
            print_ast_node(node->ptr[0], indent);
            print_ast_node(node->ptr[1], indent);
            break;
        case PARAM_LIST:
            print_ast_node(node->ptr[0], indent);
            print_ast_node(node->ptr[1], indent);
            break;
        case PARAM_DEC:
            printf("%*cType: %s, Parameter Name: %s\n", indent, ' ', node->ptr[0]->type == INT ? "int" : "float", get<string>(node->ptr[1]->data).c_str());
            break;
        case VAR_DEF:
            printf("%*cVariable Decl: (%d)\n", indent, ' ', node->pos);
            print_ast_node(node->ptr[0], indent + 2);
            print_ast_node(node->ptr[1], indent + 2);
            break;
        case DEC_LIST:
        {
            printf("%*cVariable Name Decl:\n", indent, ' ');
            ASTNode *ptr = node;
            while (ptr)
            {
                if (ptr->ptr[0]->kind == ID)
                    printf("%*c %s\n", indent + 4, ' ', get<string>(ptr->ptr[0]->data).c_str());
                else if (ptr->ptr[0]->kind == ASSIGNOP)
                {
                    printf("%*c %s ASSIGNOP\n ", indent + 4, ' ', get<string>(ptr->ptr[0]->ptr[0]->data).c_str());
                    print_ast_node(ptr->ptr[0]->ptr[1], indent + get<string>(ptr->ptr[0]->ptr[0]->data).size() + 8);
                }
                ptr = ptr->ptr[1];
            }
            break;
        }
        case DEF_LIST:
            print_ast_node(node->ptr[0], indent);
            print_ast_node(node->ptr[1], indent);
            break;
        case COMP_STM:
            printf("%*cComposite Expression: (%d)\n", indent, ' ', node->pos);
            printf("%*cVariable Declaration (Composite Expression) :\n", indent + 2, ' ');
            print_ast_node(node->ptr[0], indent + 4);
            printf("%*cExpression (Composite Expression) :\n", indent + 2, ' ');
            print_ast_node(node->ptr[1], indent + 4);
            break;
        case STM_LIST:
            print_ast_node(node->ptr[0], indent);
            print_ast_node(node->ptr[1], indent);
            break;
        case EXP_STMT:
            printf("%*cExpression:(%d)\n", indent, ' ', node->pos);
            print_ast_node(node->ptr[0], indent + 2);
            break;
        case IF_THEN:
            printf("%*cIF Expression: (%d)\n", indent, ' ', node->pos);
            printf("%*cIF Conds:\n", indent + 2, ' ');
            print_ast_node(node->ptr[0], indent + 4);
            printf("%*cIF Body:(%d)\n", indent + 2, ' ', node->pos);
            print_ast_node(node->ptr[1], indent + 4);
            break;
        case IF_THEN_ELSE:
            printf("%*cIF Expression - Else: (%d)\n", indent, ' ', node->pos);
            printf("%*cIF Conds: \n", indent + 2, ' ');
            print_ast_node(node->ptr[0], indent + 4);
            printf("%*cIF Body: (%d)\n", indent + 2, ' ', node->pos);
            print_ast_node(node->ptr[1], indent + 4);
            printf("%*cELSE Body: (%d)\n", indent + 4, ' ', node->pos);
            print_ast_node(node->ptr[2], indent + 4);
            break;
        case FUNC_CALL:
            printf("%*cFunction Call: (%d)\n", indent, ' ', node->pos);
            printf("%*cFunction Name: %s\n", indent + 2, ' ', get<string>(node->data).c_str());
            print_ast_node(node->ptr[0], indent + 2);
            break;
        case ARGS:
        {
            int i = 1;
            while (node)
            {
                ASTNode *ptr = node->ptr[0];
                printf("%*cParameter #%d Parameter Expression: \n", indent, ' ', i++);
                print_ast_node(ptr, indent + 2);
                node = node->ptr[1];
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
        {
            if (node->data.index() == 2)
            {
                printf("%*c%s\n", indent, ' ', get<string>(node->data).c_str());
            }
            print_ast_node(node->ptr[0], indent + 2);
            print_ast_node(node->ptr[1], indent + 2);
            break;
        }
        case NOT:
        case UMINUS:
            printf("%*c%s\n", indent, ' ', get<string>(node->data).c_str());
            print_ast_node(node->ptr[0], indent + 2);
            break;
        }
    }
}

void print_symbol_table()
{
    if constexpr (PRINT_SYMBOL_TABLE == 0)
    {
        return;
    }

    printf("%9s %9s %9s %9s %9s\n", "Name", "Alias", "Level", "Type", "Flag");
    for (int i = 0; i < symbol_table.size(); i++)
        printf("%9s %9s %9d %9s %9c\n", symbol_table[i].name.c_str(),
               symbol_table[i].alias.c_str(), symbol_table[i].level,
               symbol_table[i].type == INT ? "int" : "float", symbol_table[i].flag);
    printf("\n\n");
}
