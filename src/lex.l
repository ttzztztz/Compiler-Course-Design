%{
#include "parser.tab.h"
#include "string.h"
#include "compiler.h"
int yycolumn=1;
#define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
typedef union {
	int type_int;
	int type_float;
	char type_id[32];
	struct node *ptr;
} YYLVAL;
#define YYSTYPE YYLVAL
%}
%option yylineno

id     [A-Za-z_][A-Za-z0-9_]*  
int    [0-9]+
float  ([0-9]*\.[0-9]+)|([0-9]+\.)

%%
{int}        {yylval.type_int = atoi(yytext); printf("(int, %s) ", yytext); return INT;}
{float}      {yylval.type_float = atof(yytext); printf("(float, %s) ", yytext); return FLOAT;}
"int"        {strcpy(yylval.type_id, yytext); printf("(type, int) "); return TYPE;}
"float"      {strcpy(yylval.type_id, yytext);printf("(type, float) "); return TYPE;}
"i32"        {strcpy(yylval.type_id, "int");printf("(type, int) "); return TYPE;}
"f32"        {strcpy(yylval.type_id, "float");printf("(type, float) "); return TYPE;}

"return"     {printf("(token, return) "); return RETURN;}
"if"         {printf("(token, if) "); return IF;}
"else"       {printf("(token, else) "); return ELSE;}
"while"      {printf("(token, while) "); return WHILE;}
"continue"	 {printf("(token, continue) "); return CONTINUE;}
"break"		 {printf("(token, break) "); return BREAK;}

{id}        {printf("(id, %s) ", yytext); strcpy(yylval.type_id, yytext); return ID;}
";"			{printf("(token, semi) "); return SEMI;}
","			{printf("(token, comma) "); return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {printf("(token, cmp_operator) "); strcpy(yylval.type_id, yytext);;return RELOP;}
"="			{printf("(token, =) "); return ASSIGNOP;}
"+"			{printf("(token, +) "); return PLUS;}
"-"			{printf("(token, -) "); return MINUS;}
"*"			{printf("(token, *) "); return STAR;}
"%"			{printf("(token, %) "); return MOD;}
"/"			{printf("(token, /) "); return DIV;}
"&&"        {printf("(token, &&) "); return AND;}
"||"        {printf("(token, ||) "); return OR;}
"!"			{printf("(token, !) "); return NOT;}
"("			{printf("(token, () "); return LP;}
")"			{printf("(token, )) "); return RP;}
"{"			{printf("(token,{) "); return LC;}
"}"			{printf("(token, }) "); return RC;}
[\n]        {printf("(token, \\n) "); yycolumn=1;}   
[ \r\t]     {}
.			{printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n", yytext, yylineno);}
%%

int yywrap() {
    return 1;
}
