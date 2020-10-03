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
    ASSIGNOP = 274,                /* ASSIGNOP  */
    AND = 275,                     /* AND  */
    OR = 276,                      /* OR  */
    NOT = 277,                     /* NOT  */
    IF = 278,                      /* IF  */
    ELSE = 279,                    /* ELSE  */
    WHILE = 280,                   /* WHILE  */
    RETURN = 281,                  /* RETURN  */
    FOR = 282,                     /* FOR  */
    SWITCH = 283,                  /* SWITCH  */
    CASE = 284,                    /* CASE  */
    COLON = 285,                   /* COLON  */
    DEFAULT = 286,                 /* DEFAULT  */
    EXT_DEF_LIST = 287,            /* EXT_DEF_LIST  */
    EXT_VAR_DEF = 288,             /* EXT_VAR_DEF  */
    FUNC_DEF = 289,                /* FUNC_DEF  */
    FUNC_DEC = 290,                /* FUNC_DEC  */
    EXT_DEC_LIST = 291,            /* EXT_DEC_LIST  */
    PARAM_LIST = 292,              /* PARAM_LIST  */
    PARAM_DEC = 293,               /* PARAM_DEC  */
    VAR_DEF = 294,                 /* VAR_DEF  */
    DEC_LIST = 295,                /* DEC_LIST  */
    DEF_LIST = 296,                /* DEF_LIST  */
    COMP_STM = 297,                /* COMP_STM  */
    STM_LIST = 298,                /* STM_LIST  */
    EXP_STMT = 299,                /* EXP_STMT  */
    IF_THEN = 300,                 /* IF_THEN  */
    IF_THEN_ELSE = 301,            /* IF_THEN_ELSE  */
    FUNC_CALL = 302,               /* FUNC_CALL  */
    ARGS = 303,                    /* ARGS  */
    FUNCTION = 304,                /* FUNCTION  */
    PARAM = 305,                   /* PARAM  */
    ARG = 306,                     /* ARG  */
    CALL = 307,                    /* CALL  */
    LABEL = 308,                   /* LABEL  */
    GOTO = 309,                    /* GOTO  */
    JLT = 310,                     /* JLT  */
    JLE = 311,                     /* JLE  */
    JGT = 312,                     /* JGT  */
    JGE = 313,                     /* JGE  */
    EQ = 314,                      /* EQ  */
    NEQ = 315,                     /* NEQ  */
    UMINUS = 316,                  /* UMINUS  */
    LOWER_THEN_ELSE = 317          /* LOWER_THEN_ELSE  */
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

#line 133 "parser.tab.h"

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
