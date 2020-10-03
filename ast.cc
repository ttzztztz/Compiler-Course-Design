#include "def.h"
#include "parser.tab.h"

struct ASTNode *mknode(int num, int kind, int pos, ...)
{
    struct ASTNode *T = (struct ASTNode *)calloc(sizeof(struct ASTNode), 1);
    int i = 0;
    T->kind = kind;
    T->pos = pos;
    va_list pArgs;
    va_start(pArgs, pos);
    for (i = 0; i < num; i++)
        T->ptr[i] = va_arg(pArgs, struct ASTNode *);
    while (i < 4)
        T->ptr[i++] = NULL;
    va_end(pArgs);
    return T;
}

void display(struct ASTNode *T, int indent)
{
    int i = 1;
    struct ASTNode *T0;
    if (T)
    {
        switch (T->kind)
        {
        case EXT_DEF_LIST:
            display(T->ptr[0], indent);
            display(T->ptr[1], indent);
            break;
        case EXT_VAR_DEF:
            printf("%*cVariable Declaration: (%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 2);
            printf("%*cVariable Name: \n", indent + 2, ' ');
            display(T->ptr[1], indent + 4);
            break;
        case TYPE:
            printf("%*cType: %s\n", indent, ' ', T->type_id);
            break;
        case EXT_DEC_LIST:
            display(T->ptr[0], indent);
            display(T->ptr[1], indent);
            break;
        case FUNC_DEF:
            printf("%*cFunction Declaration: (%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 2);
            display(T->ptr[1], indent + 2);
            display(T->ptr[2], indent + 2);
            break;
        case FUNC_DEC:
            printf("%*cFunction Name: %s\n", indent, ' ', T->type_id);
            if (T->ptr[0])
            {
                printf("%*cFunction Parameters: \n", indent, ' ');
                display(T->ptr[0], indent + 2);
            }
            else
                printf("%*cFunction without Parameters: \n", indent + 2, ' ');
            break;
        case PARAM_LIST:
            display(T->ptr[0], indent);
            display(T->ptr[1], indent);
            break;
        case PARAM_DEC:
            printf("%*cType: %s, Parameter Name: %s\n", indent, ' ', T->ptr[0]->type == INT ? "int" : "float", T->ptr[1]->type_id);
            break;
        case EXP_STMT:
            printf("%*cExpression:(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 2);
            break;
        case RETURN:
            printf("%*cReturn Expression:(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 2);
            break;
        case COMP_STM:
            printf("%*cComposite Expression: (%d)\n", indent, ' ', T->pos);
            printf("%*cVariable Declaration (Composite Expression) :\n", indent + 2, ' ');
            display(T->ptr[0], indent + 4);
            printf("%*cExpression (Composite Expression) :\n", indent + 2, ' ');
            display(T->ptr[1], indent + 4);
            break;
        case STM_LIST:
            display(T->ptr[0], indent);
            display(T->ptr[1], indent);
            break;
        case WHILE:
            printf("%*cLoop Statement: (%d)\n", indent, ' ', T->pos);
            printf("%*cLoop Condition: \n", indent + 2, ' ');
            display(T->ptr[0], indent + 4);
            printf("%*cLoop Body: (%d)\n", indent + 2, ' ', T->pos);
            display(T->ptr[1], indent + 4);
            break;
        case IF_THEN:
            printf("%*cIF Expression: (%d)\n", indent, ' ', T->pos);
            printf("%*cIF Conds:\n", indent + 2, ' ');
            display(T->ptr[0], indent + 4);
            printf("%*cIF Body:(%d)\n", indent + 2, ' ', T->pos);
            display(T->ptr[1], indent + 4);
            break;
        case IF_THEN_ELSE:
            printf("%*cIF Expression - Else: (%d)\n", indent, ' ', T->pos);
            printf("%*cIF Conds: \n", indent + 2, ' ');
            display(T->ptr[0], indent + 4);
            printf("%*cIF Body: (%d)\n", indent + 2, ' ', T->pos);
            display(T->ptr[1], indent + 4);
            printf("%*cELSE Body: (%d)\n", indent + 4, ' ', T->pos);
            display(T->ptr[2], indent + 4);
            break;
        case DEF_LIST:
            display(T->ptr[0], indent);
            display(T->ptr[1], indent); 
            break;
        case VAR_DEF:
            printf("%*cVariable Decl: (%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 2);
            display(T->ptr[1], indent + 2);
            break;
        case DEC_LIST:
            printf("%*cVariable Name Decl:\n", indent, ' ');
            T0 = T;
            while (T0)
            {
                if (T0->ptr[0]->kind == ID)
                    printf("%*c %s\n", indent + 4, ' ', T0->ptr[0]->type_id);
                else if (T0->ptr[0]->kind == ASSIGNOP)
                {
                    printf("%*c %s ASSIGNOP\n ", indent + 4, ' ', T0->ptr[0]->ptr[0]->type_id);
                    display(T0->ptr[0]->ptr[1], indent + strlen(T0->ptr[0]->ptr[0]->type_id) + 7);
                }
                T0 = T0->ptr[1];
            }
            break;
        case ID:
            printf("%*cID: %s\n", indent, ' ', T->type_id);
            break;
        case INT:
            printf("%*cINT: %d\n", indent, ' ', T->type_int);
            break;
        case FLOAT:
            printf("%*cFLAOT: %f\n", indent, ' ', T->type_float);
            break;
        case ASSIGNOP:
        case AND:
        case OR:
        case RELOP:
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
            printf("%*c%s\n", indent, ' ', T->type_id);
            display(T->ptr[0], indent + 2);
            display(T->ptr[1], indent + 2);
            break;
        case NOT:
        case UMINUS:
            printf("%*c%s\n", indent, ' ', T->type_id);
            display(T->ptr[0], indent + 2);
            break;
        case FUNC_CALL:
            printf("%*cFunction Call: (%d)\n", indent, ' ', T->pos);
            printf("%*cFunction Name: %s\n", indent + 2, ' ', T->type_id);
            display(T->ptr[0], indent + 2);
            break;
        case ARGS:
            i = 1;
            while (T)
            {
                struct ASTNode *T0 = T->ptr[0];
                printf("%*cParameter #%d Parameter Expression: \n", indent, ' ', i++);
                display(T0, indent + 2);
                T = T->ptr[1];
            }
            printf("\n");
            break;
        }
    }
}

void semantic_Analysis0(struct ASTNode *T) {
    return;
}