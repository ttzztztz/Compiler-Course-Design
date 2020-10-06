%define parse.error verbose
%locations
%{
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);
void display(ASTNode *,int);
int yylex();
%}

%union {
	int    type_int;
	float  type_float;
	char   type_id[32];
	class ASTNode *ptr;
};

%type  <ptr> program ExtDefList ExtDef  Specifier ExtDecList FuncDec CompSt VarList VarDec ParamDec Stmt StmList DefList Def DecList Dec Exp Args

%token <type_int> INT
%token <type_id> ID  RELOP TYPE
%token <type_float> FLOAT

%token DPLUS LP RP LC RC SEMI COMMA
%token PLUS MINUS STAR DIV MOD ASSIGNOP AND OR NOT IF ELSE WHILE RETURN FOR SWITCH CASE COLON DEFAULT
%token EXT_DEF_LIST EXT_VAR_DEF FUNC_DEF FUNC_DEC EXT_DEC_LIST PARAM_LIST PARAM_DEC VAR_DEF DEC_LIST DEF_LIST COMP_STM STM_LIST EXP_STMT IF_THEN IF_THEN_ELSE
%token FUNC_CALL ARGS FUNCTION PARAM ARG CALL LABEL GOTO JLT JLE JGT JGE EQ NEQ


%left ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%left MOD
%right UMINUS NOT DPLUS

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%%

program: ExtDefList    { display($1,0); entrypoint($1);}
         ;
ExtDefList: {$$=NULL;}
          | ExtDef ExtDefList {$$=make_node(EXT_DEF_LIST,yylineno,{$1,$2});}
          ;
ExtDef:   Specifier ExtDecList SEMI   {$$=make_node(EXT_VAR_DEF,yylineno,{$1,$2});}
         |Specifier FuncDec CompSt    {$$=make_node(FUNC_DEF,yylineno,{$1,$2,$3});}
         | error SEMI   {$$=NULL;}
         ;
Specifier:  TYPE    {$$=make_node(TYPE,yylineno);$$->type_id = $1;$$->type=($1 == "float")?FLOAT:INT;}   
           ;
ExtDecList:  VarDec      {$$=$1;}
           | VarDec COMMA ExtDecList {$$=make_node(EXT_DEC_LIST,yylineno,{$1,$3});}
           ;  
VarDec:  ID          {$$=make_node(ID,yylineno);$$->type_id = $1;}
         ;
FuncDec: ID LP VarList RP   {$$=make_node(FUNC_DEC,yylineno,{$3});$$->type_id = $1;}
		|ID LP  RP   {$$=make_node(FUNC_DEC,yylineno);$$->type_id = $1;$$->ptr[0]=NULL;}

        ;
VarList: ParamDec  {$$=make_node(PARAM_LIST,yylineno,{$1});}
        | ParamDec COMMA  VarList  {$$=make_node(PARAM_LIST,yylineno,{$1,$3});}
        ;
ParamDec: Specifier VarDec         {$$=make_node(PARAM_DEC,yylineno,{$1,$2});}
         ;

CompSt: LC DefList StmList RC    {$$=make_node(COMP_STM,yylineno,{$2,$3});}
       ;

StmList: {$$=NULL; }  
        | Stmt StmList  {$$=make_node(STM_LIST,yylineno,{$1,$2});}
        ;
Stmt:   Exp SEMI    {$$=make_node(EXP_STMT,yylineno,{$1});}
      | CompSt      {$$=$1;}
      | RETURN Exp SEMI   {$$=make_node(RETURN,yylineno,{$2});}
      | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE   {$$=make_node(IF_THEN,yylineno,{$3,$5});}
      | IF LP Exp RP Stmt ELSE Stmt   {$$=make_node(IF_THEN_ELSE,yylineno,{$3,$5,$7});}
      | WHILE LP Exp RP Stmt {$$=make_node(WHILE,yylineno,{$3,$5});}
      ;
DefList: {$$=NULL; }
        | Def DefList {$$=make_node(DEF_LIST,yylineno,{$1,$2});}
        | error SEMI   {$$=NULL;}
        ;
Def:    Specifier DecList SEMI {$$=make_node(VAR_DEF,yylineno,{$1,$2});}
        ;
DecList: Dec  {$$=make_node(DEC_LIST,yylineno,{$1});}
       | Dec COMMA DecList  {$$=make_node(DEC_LIST,yylineno,{$1,$3});}
	   ;
Dec:     VarDec  {$$=$1;}
       | VarDec ASSIGNOP Exp  {$$=make_node(ASSIGNOP,yylineno,{$1,$3});$$->type_id = "ASSIGNOP";}
       ;
Exp:    Exp ASSIGNOP Exp {$$=make_node(ASSIGNOP,yylineno,{$1,$3});$$->type_id = "ASSIGNOP";}
      | Exp AND Exp   {$$=make_node(AND,yylineno,{$1,$3});$$->type_id = "AND";}
      | Exp OR Exp    {$$=make_node(OR,yylineno,{$1,$3});$$->type_id = "OR";}
      | Exp RELOP Exp {$$=make_node(RELOP,yylineno,{$1,$3});$$->type_id = $2;}
      | Exp PLUS Exp  {$$=make_node(PLUS,yylineno,{$1,$3});$$->type_id = "PLUS";}
      | Exp MINUS Exp {$$=make_node(MINUS,yylineno,{$1,$3});$$->type_id = "MINUS";}
      | Exp STAR Exp  {$$=make_node(STAR,yylineno,{$1,$3});$$->type_id = "STAR";}
      | Exp MOD Exp  {$$=make_node(MOD,yylineno,{$1,$3});$$->type_id = "MOD";}
      | Exp DIV Exp   {$$=make_node(DIV,yylineno,{$1,$3});$$->type_id = "DIV";}
      | LP Exp RP     {$$=$2;}
      | MINUS Exp %prec UMINUS   {$$=make_node(UMINUS,yylineno,{$2});$$->type_id = "UMINUS";}
      | NOT Exp       {$$=make_node(NOT,yylineno,{$2});$$->type_id = "NOT";}
      | DPLUS  Exp      {$$=make_node(DPLUS,yylineno,{$2});$$->type_id = "DPLUS";}
      |   Exp DPLUS      {$$=make_node(DPLUS,yylineno,{$1});$$->type_id = "DPLUS";}
      | ID LP Args RP {$$=make_node(FUNC_CALL,yylineno,{$3});$$->type_id = $1;}
      | ID LP RP      {$$=make_node(FUNC_CALL,yylineno);$$->type_id = $1;}
      | ID            {$$=make_node(ID,yylineno);$$->type_id = $1;}
      | INT           {$$=make_node(INT,yylineno);$$->type_int=$1;$$->type=INT;}
      | FLOAT         {$$=make_node(FLOAT,yylineno);$$->type_float=$1;$$->type=FLOAT;}
      ;
Args:    Exp COMMA Args    {$$=make_node(ARGS,yylineno,{$1,$3});}
       | Exp               {$$=make_node(ARGS,yylineno,{$1});}
       ;
       
%%

int main(int argc, char *argv[]) {
    yyin = fopen(argv[1], "r");
    if (!yyin) exit(0);
    yylineno = 1;
    yyparse();
    return 0;
}

#include<stdarg.h>
void yyerror(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}
