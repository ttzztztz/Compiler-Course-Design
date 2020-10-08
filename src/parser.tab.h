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
    CONTINUE = 288,                /* CONTINUE  */
    BREAK = 289,                   /* BREAK  */
    EXT_DEF_LIST = 290,            /* EXT_DEF_LIST  */
    EXT_VAR_DEF = 291,             /* EXT_VAR_DEF  */
    FUNC_DEF = 292,                /* FUNC_DEF  */
    FUNC_DEC = 293,                /* FUNC_DEC  */
    EXT_DEC_LIST = 294,            /* EXT_DEC_LIST  */
    PARAM_LIST = 295,              /* PARAM_LIST  */
    PARAM_DEC = 296,               /* PARAM_DEC  */
    VAR_DEF = 297,                 /* VAR_DEF  */
    DEC_LIST = 298,                /* DEC_LIST  */
    DEF_LIST = 299,                /* DEF_LIST  */
    COMP_STM = 300,                /* COMP_STM  */
    STM_LIST = 301,                /* STM_LIST  */
    EXP_STMT = 302,                /* EXP_STMT  */
    IF_THEN = 303,                 /* IF_THEN  */
    IF_THEN_ELSE = 304,            /* IF_THEN_ELSE  */
    FUNC_CALL = 305,               /* FUNC_CALL  */
    ARGS = 306,                    /* ARGS  */
    FUNCTION = 307,                /* FUNCTION  */
    PARAM = 308,                   /* PARAM  */
    ARG = 309,                     /* ARG  */
    CALL = 310,                    /* CALL  */
    LABEL = 311,                   /* LABEL  */
    GOTO = 312,                    /* GOTO  */
    JLT = 313,                     /* JLT  */
    JLE = 314,                     /* JLE  */
    JGT = 315,                     /* JGT  */
    JGE = 316,                     /* JGE  */
    EQ = 317,                      /* EQ  */
    NEQ = 318,                     /* NEQ  */
    UMINUS = 319,                  /* UMINUS  */
    LOWER_THEN_ELSE = 320          /* LOWER_THEN_ELSE  */
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
	class ASTNode *ptr;

#line 136 "parser.tab.h"

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
