/* A Bison parser, made by GNU Bison 3.6.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    ID = 259,                      /* ID  */
    RELOP = 260,                   /* RELOP  */
    TYPE = 261,                    /* TYPE  */
    FLOAT = 262,                   /* FLOAT  */
    DPLUS = 263,                   /* DPLUS  */
    LP = 264,                      /* LP  */
    RP = 265,                      /* RP  */
    LC = 266,                      /* LC  */
    RC = 267,                      /* RC  */
    SEMI = 268,                    /* SEMI  */
    COMMA = 269,                   /* COMMA  */
    PLUS = 270,                    /* PLUS  */
    MINUS = 271,                   /* MINUS  */
    STAR = 272,                    /* STAR  */
    DIV = 273,                     /* DIV  */
    MOD = 274,                     /* MOD  */
    ASSIGNOP = 275,                /* ASSIGNOP  */
    AND = 276,                     /* AND  */
    OR = 277,                      /* OR  */
    NOT = 278,                     /* NOT  */
    IF = 279,                      /* IF  */
    ELSE = 280,                    /* ELSE  */
    WHILE = 281,                   /* WHILE  */
    RETURN = 282,                  /* RETURN  */
    FOR = 283,                     /* FOR  */
    SWITCH = 284,                  /* SWITCH  */
    CASE = 285,                    /* CASE  */
    COLON = 286,                   /* COLON  */
    DEFAULT = 287,                 /* DEFAULT  */
    EXT_DEF_LIST = 288,            /* EXT_DEF_LIST  */
    EXT_VAR_DEF = 289,             /* EXT_VAR_DEF  */
    FUNC_DEF = 290,                /* FUNC_DEF  */
    FUNC_DEC = 291,                /* FUNC_DEC  */
    EXT_DEC_LIST = 292,            /* EXT_DEC_LIST  */
    PARAM_LIST = 293,              /* PARAM_LIST  */
    PARAM_DEC = 294,               /* PARAM_DEC  */
    VAR_DEF = 295,                 /* VAR_DEF  */
    DEC_LIST = 296,                /* DEC_LIST  */
    DEF_LIST = 297,                /* DEF_LIST  */
    COMP_STM = 298,                /* COMP_STM  */
    STM_LIST = 299,                /* STM_LIST  */
    EXP_STMT = 300,                /* EXP_STMT  */
    IF_THEN = 301,                 /* IF_THEN  */
    IF_THEN_ELSE = 302,            /* IF_THEN_ELSE  */
    FUNC_CALL = 303,               /* FUNC_CALL  */
    ARGS = 304,                    /* ARGS  */
    FUNCTION = 305,                /* FUNCTION  */
    PARAM = 306,                   /* PARAM  */
    ARG = 307,                     /* ARG  */
    CALL = 308,                    /* CALL  */
    LABEL = 309,                   /* LABEL  */
    GOTO = 310,                    /* GOTO  */
    JLT = 311,                     /* JLT  */
    JLE = 312,                     /* JLE  */
    JGT = 313,                     /* JGT  */
    JGE = 314,                     /* JGE  */
    EQ = 315,                      /* EQ  */
    NEQ = 316,                     /* NEQ  */
    UMINUS = 317,                  /* UMINUS  */
    LOWER_THEN_ELSE = 318          /* LOWER_THEN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "./parser.y"

	int    type_int;
	float  type_float;
	char   type_id[32];
	struct ASTNode *ptr;

#line 134 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
