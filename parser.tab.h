/* A Bison parser, made by GNU Bison 3.5.1.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    ID = 259,
    RELOP = 260,
    TYPE = 261,
    FLOAT = 262,
    DPLUS = 263,
    LP = 264,
    RP = 265,
    LC = 266,
    RC = 267,
    SEMI = 268,
    COMMA = 269,
    PLUS = 270,
    MINUS = 271,
    STAR = 272,
    DIV = 273,
    MOD = 274,
    ASSIGNOP = 275,
    AND = 276,
    OR = 277,
    NOT = 278,
    IF = 279,
    ELSE = 280,
    WHILE = 281,
    RETURN = 282,
    FOR = 283,
    SWITCH = 284,
    CASE = 285,
    COLON = 286,
    DEFAULT = 287,
    EXT_DEF_LIST = 288,
    EXT_VAR_DEF = 289,
    FUNC_DEF = 290,
    FUNC_DEC = 291,
    EXT_DEC_LIST = 292,
    PARAM_LIST = 293,
    PARAM_DEC = 294,
    VAR_DEF = 295,
    DEC_LIST = 296,
    DEF_LIST = 297,
    COMP_STM = 298,
    STM_LIST = 299,
    EXP_STMT = 300,
    IF_THEN = 301,
    IF_THEN_ELSE = 302,
    FUNC_CALL = 303,
    ARGS = 304,
    FUNCTION = 305,
    PARAM = 306,
    ARG = 307,
    CALL = 308,
    LABEL = 309,
    GOTO = 310,
    JLT = 311,
    JLE = 312,
    JGT = 313,
    JGE = 314,
    EQ = 315,
    NEQ = 316,
    UMINUS = 317,
    LOWER_THEN_ELSE = 318
  };
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

#line 128 "parser.tab.h"

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
