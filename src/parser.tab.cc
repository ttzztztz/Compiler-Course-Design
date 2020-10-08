/* A Bison parser, made by GNU Bison 3.6.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.6.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "./parser.y"

#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);
void print_ast_node(ASTNode *,int);
int yylex();

#line 84 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 206 "parser.tab.c"

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
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_RELOP = 5,                      /* RELOP  */
  YYSYMBOL_TYPE = 6,                       /* TYPE  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_DPLUS = 8,                      /* DPLUS  */
  YYSYMBOL_LP = 9,                         /* LP  */
  YYSYMBOL_RP = 10,                        /* RP  */
  YYSYMBOL_LC = 11,                        /* LC  */
  YYSYMBOL_RC = 12,                        /* RC  */
  YYSYMBOL_SEMI = 13,                      /* SEMI  */
  YYSYMBOL_COMMA = 14,                     /* COMMA  */
  YYSYMBOL_PLUS = 15,                      /* PLUS  */
  YYSYMBOL_MINUS = 16,                     /* MINUS  */
  YYSYMBOL_STAR = 17,                      /* STAR  */
  YYSYMBOL_DIV = 18,                       /* DIV  */
  YYSYMBOL_MOD = 19,                       /* MOD  */
  YYSYMBOL_ASSIGNOP = 20,                  /* ASSIGNOP  */
  YYSYMBOL_AND = 21,                       /* AND  */
  YYSYMBOL_OR = 22,                        /* OR  */
  YYSYMBOL_NOT = 23,                       /* NOT  */
  YYSYMBOL_IF = 24,                        /* IF  */
  YYSYMBOL_ELSE = 25,                      /* ELSE  */
  YYSYMBOL_WHILE = 26,                     /* WHILE  */
  YYSYMBOL_RETURN = 27,                    /* RETURN  */
  YYSYMBOL_FOR = 28,                       /* FOR  */
  YYSYMBOL_SWITCH = 29,                    /* SWITCH  */
  YYSYMBOL_CASE = 30,                      /* CASE  */
  YYSYMBOL_COLON = 31,                     /* COLON  */
  YYSYMBOL_DEFAULT = 32,                   /* DEFAULT  */
  YYSYMBOL_CONTINUE = 33,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 34,                     /* BREAK  */
  YYSYMBOL_EXT_DEF_LIST = 35,              /* EXT_DEF_LIST  */
  YYSYMBOL_EXT_VAR_DEF = 36,               /* EXT_VAR_DEF  */
  YYSYMBOL_FUNC_DEF = 37,                  /* FUNC_DEF  */
  YYSYMBOL_FUNC_DEC = 38,                  /* FUNC_DEC  */
  YYSYMBOL_EXT_DEC_LIST = 39,              /* EXT_DEC_LIST  */
  YYSYMBOL_PARAM_LIST = 40,                /* PARAM_LIST  */
  YYSYMBOL_PARAM_DEC = 41,                 /* PARAM_DEC  */
  YYSYMBOL_VAR_DEF = 42,                   /* VAR_DEF  */
  YYSYMBOL_DEC_LIST = 43,                  /* DEC_LIST  */
  YYSYMBOL_DEF_LIST = 44,                  /* DEF_LIST  */
  YYSYMBOL_COMP_STM = 45,                  /* COMP_STM  */
  YYSYMBOL_STM_LIST = 46,                  /* STM_LIST  */
  YYSYMBOL_EXP_STMT = 47,                  /* EXP_STMT  */
  YYSYMBOL_IF_THEN = 48,                   /* IF_THEN  */
  YYSYMBOL_IF_THEN_ELSE = 49,              /* IF_THEN_ELSE  */
  YYSYMBOL_FUNC_CALL = 50,                 /* FUNC_CALL  */
  YYSYMBOL_ARGS = 51,                      /* ARGS  */
  YYSYMBOL_FUNCTION = 52,                  /* FUNCTION  */
  YYSYMBOL_PARAM = 53,                     /* PARAM  */
  YYSYMBOL_ARG = 54,                       /* ARG  */
  YYSYMBOL_CALL = 55,                      /* CALL  */
  YYSYMBOL_LABEL = 56,                     /* LABEL  */
  YYSYMBOL_GOTO = 57,                      /* GOTO  */
  YYSYMBOL_JLT = 58,                       /* JLT  */
  YYSYMBOL_JLE = 59,                       /* JLE  */
  YYSYMBOL_JGT = 60,                       /* JGT  */
  YYSYMBOL_JGE = 61,                       /* JGE  */
  YYSYMBOL_EQ = 62,                        /* EQ  */
  YYSYMBOL_NEQ = 63,                       /* NEQ  */
  YYSYMBOL_UMINUS = 64,                    /* UMINUS  */
  YYSYMBOL_LOWER_THEN_ELSE = 65,           /* LOWER_THEN_ELSE  */
  YYSYMBOL_YYACCEPT = 66,                  /* $accept  */
  YYSYMBOL_program = 67,                   /* program  */
  YYSYMBOL_ExtDefList = 68,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 69,                    /* ExtDef  */
  YYSYMBOL_Specifier = 70,                 /* Specifier  */
  YYSYMBOL_ExtDecList = 71,                /* ExtDecList  */
  YYSYMBOL_VarDec = 72,                    /* VarDec  */
  YYSYMBOL_FuncDec = 73,                   /* FuncDec  */
  YYSYMBOL_VarList = 74,                   /* VarList  */
  YYSYMBOL_ParamDec = 75,                  /* ParamDec  */
  YYSYMBOL_CompSt = 76,                    /* CompSt  */
  YYSYMBOL_StmList = 77,                   /* StmList  */
  YYSYMBOL_Stmt = 78,                      /* Stmt  */
  YYSYMBOL_DefList = 79,                   /* DefList  */
  YYSYMBOL_Def = 80,                       /* Def  */
  YYSYMBOL_DecList = 81,                   /* DecList  */
  YYSYMBOL_Dec = 82,                       /* Dec  */
  YYSYMBOL_Exp = 83,                       /* Exp  */
  YYSYMBOL_Args = 84                       /* Args  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   281

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  56
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  107

#define YYMAXUTOK   320


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    49,    49,    51,    52,    54,    55,    56,    58,    60,
      61,    63,    65,    66,    69,    70,    72,    75,    78,    79,
      81,    82,    83,    84,    85,    86,    87,    88,    90,    91,
      92,    94,    96,    97,    99,   100,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   122,   123
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "ID", "RELOP",
  "TYPE", "FLOAT", "DPLUS", "LP", "RP", "LC", "RC", "SEMI", "COMMA",
  "PLUS", "MINUS", "STAR", "DIV", "MOD", "ASSIGNOP", "AND", "OR", "NOT",
  "IF", "ELSE", "WHILE", "RETURN", "FOR", "SWITCH", "CASE", "COLON",
  "DEFAULT", "CONTINUE", "BREAK", "EXT_DEF_LIST", "EXT_VAR_DEF",
  "FUNC_DEF", "FUNC_DEC", "EXT_DEC_LIST", "PARAM_LIST", "PARAM_DEC",
  "VAR_DEF", "DEC_LIST", "DEF_LIST", "COMP_STM", "STM_LIST", "EXP_STMT",
  "IF_THEN", "IF_THEN_ELSE", "FUNC_CALL", "ARGS", "FUNCTION", "PARAM",
  "ARG", "CALL", "LABEL", "GOTO", "JLT", "JLE", "JGT", "JGE", "EQ", "NEQ",
  "UMINUS", "LOWER_THEN_ELSE", "$accept", "program", "ExtDefList",
  "ExtDef", "Specifier", "ExtDecList", "VarDec", "FuncDec", "VarList",
  "ParamDec", "CompSt", "StmList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320
};
#endif

#define YYPACT_NINF (-40)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-29)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      54,    -9,   -40,     7,   -40,    54,     6,   -40,   -40,   -40,
      10,     4,    37,    11,    52,   -40,    57,    41,   -40,   -40,
      57,    46,    49,   -40,   -40,    53,    57,    69,    41,   -40,
     -40,    63,   -40,    50,    58,    67,   -40,    73,   -40,     5,
       5,     5,     5,    74,    75,     5,    78,    81,   -40,    85,
      69,   106,   -40,   -40,     5,   -40,    57,    97,    90,   124,
      90,    90,     5,     5,   142,   -40,   -40,   -40,   -40,     5,
     -40,   -40,     5,     5,     5,     5,     5,     5,     5,     5,
     214,   -40,   -40,   160,    89,   -40,   178,   196,   -40,    71,
       8,     8,    12,    12,    90,   232,   262,   247,     5,   -40,
      69,    69,   -40,    83,   -40,    69,   -40
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     8,     0,     2,     0,     0,     7,     1,     4,
      11,     0,     9,     0,     0,     5,     0,     0,     6,    13,
       0,     0,    14,    11,    10,     0,     0,    18,     0,    16,
      12,     0,    30,    34,     0,    32,    53,    52,    54,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,     0,
      18,     0,    29,    15,     0,    31,     0,     0,    48,     0,
      46,    47,     0,     0,     0,    26,    27,    17,    19,     0,
      49,    20,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    33,    51,    56,     0,    45,     0,     0,    22,    39,
      40,    41,    42,    44,    43,    36,    37,    38,     0,    50,
       0,     0,    55,    23,    25,     0,    24
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,   104,   -40,    15,    94,   -15,   -40,    84,   -40,
      99,    66,    30,   105,   -40,    61,   -40,   -39,    20
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    11,    12,    13,    21,    22,
      48,    49,    50,    27,    28,    34,    35,    51,    84
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      58,    59,    60,    61,     7,    29,    64,     8,    36,    37,
      10,    33,    38,    39,    40,    80,    70,    15,    83,    14,
      70,    41,    17,    86,    87,    74,    75,    76,    42,    20,
      89,    76,    26,    90,    91,    92,    93,    94,    95,    96,
      97,    33,    25,    26,   -28,   -28,    20,     2,   -28,   -28,
     -28,    16,   -28,   -28,    -3,     1,    30,   -28,     2,    83,
       2,    23,    19,    31,   -28,   -28,    32,   -28,   -28,     2,
      54,    55,    36,    37,   -28,   -28,    38,    39,    40,    70,
      17,    56,    57,    62,    63,    41,    72,    73,    74,    75,
      76,    65,    42,    43,    66,    44,    45,    67,    70,    99,
      36,    37,    46,    47,    38,    39,    40,    82,   105,     9,
      24,    69,    18,    41,    70,    53,    68,    81,   102,    71,
      42,    72,    73,    74,    75,    76,    77,    78,    79,    69,
     103,   104,    70,    52,    85,   106,     0,     0,     0,    72,
      73,    74,    75,    76,    77,    78,    79,    69,     0,     0,
      70,     0,     0,     0,     0,    88,     0,    72,    73,    74,
      75,    76,    77,    78,    79,    69,     0,     0,    70,     0,
       0,     0,     0,     0,    98,    72,    73,    74,    75,    76,
      77,    78,    79,    69,     0,     0,    70,     0,   100,     0,
       0,     0,     0,    72,    73,    74,    75,    76,    77,    78,
      79,    69,     0,     0,    70,     0,   101,     0,     0,     0,
       0,    72,    73,    74,    75,    76,    77,    78,    79,    69,
       0,     0,    70,     0,     0,     0,     0,     0,     0,    72,
      73,    74,    75,    76,    77,    78,    79,    69,     0,     0,
      70,     0,     0,     0,     0,     0,     0,    72,    73,    74,
      75,    76,    69,    78,    79,    70,     0,     0,     0,     0,
       0,     0,    72,    73,    74,    75,    76,    69,    78,     0,
      70,     0,     0,     0,     0,     0,     0,    72,    73,    74,
      75,    76
};

static const yytype_int8 yycheck[] =
{
      39,    40,    41,    42,    13,    20,    45,     0,     3,     4,
       4,    26,     7,     8,     9,    54,     8,    13,    57,     9,
       8,    16,    11,    62,    63,    17,    18,    19,    23,    14,
      69,    19,    17,    72,    73,    74,    75,    76,    77,    78,
      79,    56,     1,    28,     3,     4,    31,     6,     7,     8,
       9,    14,    11,    12,     0,     1,    10,    16,     6,    98,
       6,     4,    10,    14,    23,    24,    13,    26,    27,     6,
      20,    13,     3,     4,    33,    34,     7,     8,     9,     8,
      11,    14,     9,     9,     9,    16,    15,    16,    17,    18,
      19,    13,    23,    24,    13,    26,    27,    12,     8,    10,
       3,     4,    33,    34,     7,     8,     9,    10,    25,     5,
      16,     5,    13,    16,     8,    31,    50,    56,    98,    13,
      23,    15,    16,    17,    18,    19,    20,    21,    22,     5,
     100,   101,     8,    28,    10,   105,    -1,    -1,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,     5,    -1,    -1,
       8,    -1,    -1,    -1,    -1,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,     5,    -1,    -1,     8,    -1,
      -1,    -1,    -1,    -1,    14,    15,    16,    17,    18,    19,
      20,    21,    22,     5,    -1,    -1,     8,    -1,    10,    -1,
      -1,    -1,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,     5,    -1,    -1,     8,    -1,    10,    -1,    -1,    -1,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,     5,
      -1,    -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,     5,    -1,    -1,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,
      18,    19,     5,    21,    22,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    15,    16,    17,    18,    19,     5,    21,    -1,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,
      18,    19
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     6,    67,    68,    69,    70,    13,     0,    68,
       4,    71,    72,    73,     9,    13,    14,    11,    76,    10,
      70,    74,    75,     4,    71,     1,    70,    79,    80,    72,
      10,    14,    13,    72,    81,    82,     3,     4,     7,     8,
       9,    16,    23,    24,    26,    27,    33,    34,    76,    77,
      78,    83,    79,    74,    20,    13,    14,     9,    83,    83,
      83,    83,     9,     9,    83,    13,    13,    12,    77,     5,
       8,    13,    15,    16,    17,    18,    19,    20,    21,    22,
      83,    81,    10,    83,    84,    10,    83,    83,    13,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    14,    10,
      10,    10,    84,    78,    78,    25,    78
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    66,    67,    68,    68,    69,    69,    69,    70,    71,
      71,    72,    73,    73,    74,    74,    75,    76,    77,    77,
      78,    78,    78,    78,    78,    78,    78,    78,    79,    79,
      79,    80,    81,    81,    82,    82,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    84,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     3,     2,     1,     1,
       3,     1,     4,     3,     1,     3,     2,     4,     0,     2,
       2,     1,     3,     5,     7,     5,     2,     2,     0,     2,
       2,     3,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     2,
       4,     3,     1,     1,     1,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize;

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yynerrs = 0;
  yystate = 0;
  yyerrstatus = 0;

  yystacksize = YYINITDEPTH;
  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;


  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 49 "./parser.y"
                       { print_ast_node((yyvsp[0].ptr),0); entrypoint((yyvsp[0].ptr));}
#line 1772 "parser.tab.c"
    break;

  case 3:
#line 51 "./parser.y"
            {(yyval.ptr)=NULL;}
#line 1778 "parser.tab.c"
    break;

  case 4:
#line 52 "./parser.y"
                              {(yyval.ptr)=make_node(EXT_DEF_LIST,yylineno,{(yyvsp[-1].ptr),(yyvsp[0].ptr)});}
#line 1784 "parser.tab.c"
    break;

  case 5:
#line 54 "./parser.y"
                                      {(yyval.ptr)=make_node(EXT_VAR_DEF,yylineno,{(yyvsp[-2].ptr),(yyvsp[-1].ptr)});}
#line 1790 "parser.tab.c"
    break;

  case 6:
#line 55 "./parser.y"
                                      {(yyval.ptr)=make_node(FUNC_DEF,yylineno,{(yyvsp[-2].ptr),(yyvsp[-1].ptr),(yyvsp[0].ptr)});}
#line 1796 "parser.tab.c"
    break;

  case 7:
#line 56 "./parser.y"
                        {(yyval.ptr)=NULL;}
#line 1802 "parser.tab.c"
    break;

  case 8:
#line 58 "./parser.y"
                    {(yyval.ptr)=make_node(TYPE,yylineno);(yyval.ptr)->data = string((yyvsp[0].type_id));(yyval.ptr)->type=(string((yyvsp[0].type_id)) == "float")?FLOAT:INT;}
#line 1808 "parser.tab.c"
    break;

  case 9:
#line 60 "./parser.y"
                         {(yyval.ptr)=(yyvsp[0].ptr);}
#line 1814 "parser.tab.c"
    break;

  case 10:
#line 61 "./parser.y"
                                     {(yyval.ptr)=make_node(EXT_DEC_LIST,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});}
#line 1820 "parser.tab.c"
    break;

  case 11:
#line 63 "./parser.y"
                     {(yyval.ptr)=make_node(ID,yylineno);(yyval.ptr)->data = (yyvsp[0].type_id);}
#line 1826 "parser.tab.c"
    break;

  case 12:
#line 65 "./parser.y"
                            {(yyval.ptr)=make_node(FUNC_DEC,yylineno,{(yyvsp[-1].ptr)});(yyval.ptr)->data = (yyvsp[-3].type_id);}
#line 1832 "parser.tab.c"
    break;

  case 13:
#line 66 "./parser.y"
                             {(yyval.ptr)=make_node(FUNC_DEC,yylineno);(yyval.ptr)->data = (yyvsp[-2].type_id);(yyval.ptr)->ptr[0]=NULL;}
#line 1838 "parser.tab.c"
    break;

  case 14:
#line 69 "./parser.y"
                   {(yyval.ptr)=make_node(PARAM_LIST,yylineno,{(yyvsp[0].ptr)});}
#line 1844 "parser.tab.c"
    break;

  case 15:
#line 70 "./parser.y"
                                   {(yyval.ptr)=make_node(PARAM_LIST,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});}
#line 1850 "parser.tab.c"
    break;

  case 16:
#line 72 "./parser.y"
                                   {(yyval.ptr)=make_node(PARAM_DEC,yylineno,{(yyvsp[-1].ptr),(yyvsp[0].ptr)});}
#line 1856 "parser.tab.c"
    break;

  case 17:
#line 75 "./parser.y"
                                 {(yyval.ptr)=make_node(COMP_STM,yylineno,{(yyvsp[-2].ptr),(yyvsp[-1].ptr)});}
#line 1862 "parser.tab.c"
    break;

  case 18:
#line 78 "./parser.y"
         {(yyval.ptr)=NULL; }
#line 1868 "parser.tab.c"
    break;

  case 19:
#line 79 "./parser.y"
                        {(yyval.ptr)=make_node(STM_LIST,yylineno,{(yyvsp[-1].ptr),(yyvsp[0].ptr)});}
#line 1874 "parser.tab.c"
    break;

  case 20:
#line 81 "./parser.y"
                    {(yyval.ptr)=make_node(EXP_STMT,yylineno,{(yyvsp[-1].ptr)});}
#line 1880 "parser.tab.c"
    break;

  case 21:
#line 82 "./parser.y"
                    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 1886 "parser.tab.c"
    break;

  case 22:
#line 83 "./parser.y"
                          {(yyval.ptr)=make_node(RETURN,yylineno,{(yyvsp[-1].ptr)});}
#line 1892 "parser.tab.c"
    break;

  case 23:
#line 84 "./parser.y"
                                                  {(yyval.ptr)=make_node(IF_THEN,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});}
#line 1898 "parser.tab.c"
    break;

  case 24:
#line 85 "./parser.y"
                                      {(yyval.ptr)=make_node(IF_THEN_ELSE,yylineno,{(yyvsp[-4].ptr),(yyvsp[-2].ptr),(yyvsp[0].ptr)});}
#line 1904 "parser.tab.c"
    break;

  case 25:
#line 86 "./parser.y"
                             {(yyval.ptr)=make_node(WHILE,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});}
#line 1910 "parser.tab.c"
    break;

  case 26:
#line 87 "./parser.y"
                      {(yyval.ptr)=make_node(CONTINUE,yylineno);}
#line 1916 "parser.tab.c"
    break;

  case 27:
#line 88 "./parser.y"
                   {(yyval.ptr)=make_node(BREAK,yylineno);}
#line 1922 "parser.tab.c"
    break;

  case 28:
#line 90 "./parser.y"
         {(yyval.ptr)=NULL; }
#line 1928 "parser.tab.c"
    break;

  case 29:
#line 91 "./parser.y"
                      {(yyval.ptr)=make_node(DEF_LIST,yylineno,{(yyvsp[-1].ptr),(yyvsp[0].ptr)});}
#line 1934 "parser.tab.c"
    break;

  case 30:
#line 92 "./parser.y"
                       {(yyval.ptr)=NULL;}
#line 1940 "parser.tab.c"
    break;

  case 31:
#line 94 "./parser.y"
                               {(yyval.ptr)=make_node(VAR_DEF,yylineno,{(yyvsp[-2].ptr),(yyvsp[-1].ptr)});}
#line 1946 "parser.tab.c"
    break;

  case 32:
#line 96 "./parser.y"
              {(yyval.ptr)=make_node(DEC_LIST,yylineno,{(yyvsp[0].ptr)});}
#line 1952 "parser.tab.c"
    break;

  case 33:
#line 97 "./parser.y"
                            {(yyval.ptr)=make_node(DEC_LIST,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});}
#line 1958 "parser.tab.c"
    break;

  case 34:
#line 99 "./parser.y"
                 {(yyval.ptr)=(yyvsp[0].ptr);}
#line 1964 "parser.tab.c"
    break;

  case 35:
#line 100 "./parser.y"
                              {(yyval.ptr)=make_node(ASSIGNOP,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});(yyval.ptr)->data = "ASSIGNOP";}
#line 1970 "parser.tab.c"
    break;

  case 36:
#line 102 "./parser.y"
                         {(yyval.ptr)=make_node(ASSIGNOP,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});(yyval.ptr)->data = "ASSIGNOP";}
#line 1976 "parser.tab.c"
    break;

  case 37:
#line 103 "./parser.y"
                      {(yyval.ptr)=make_node(AND,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});(yyval.ptr)->data = "AND";}
#line 1982 "parser.tab.c"
    break;

  case 38:
#line 104 "./parser.y"
                      {(yyval.ptr)=make_node(OR,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});(yyval.ptr)->data = "OR";}
#line 1988 "parser.tab.c"
    break;

  case 39:
#line 105 "./parser.y"
                      {(yyval.ptr)=make_node(RELOP,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});(yyval.ptr)->data = (yyvsp[-1].type_id);}
#line 1994 "parser.tab.c"
    break;

  case 40:
#line 106 "./parser.y"
                      {(yyval.ptr)=make_node(PLUS,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});(yyval.ptr)->data = "PLUS";}
#line 2000 "parser.tab.c"
    break;

  case 41:
#line 107 "./parser.y"
                      {(yyval.ptr)=make_node(MINUS,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});(yyval.ptr)->data = "MINUS";}
#line 2006 "parser.tab.c"
    break;

  case 42:
#line 108 "./parser.y"
                      {(yyval.ptr)=make_node(STAR,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});(yyval.ptr)->data = "STAR";}
#line 2012 "parser.tab.c"
    break;

  case 43:
#line 109 "./parser.y"
                     {(yyval.ptr)=make_node(MOD,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});(yyval.ptr)->data = "MOD";}
#line 2018 "parser.tab.c"
    break;

  case 44:
#line 110 "./parser.y"
                      {(yyval.ptr)=make_node(DIV,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});(yyval.ptr)->data = "DIV";}
#line 2024 "parser.tab.c"
    break;

  case 45:
#line 111 "./parser.y"
                      {(yyval.ptr)=(yyvsp[-1].ptr);}
#line 2030 "parser.tab.c"
    break;

  case 46:
#line 112 "./parser.y"
                                 {(yyval.ptr)=make_node(UMINUS,yylineno,{(yyvsp[0].ptr)});(yyval.ptr)->data = "UMINUS";}
#line 2036 "parser.tab.c"
    break;

  case 47:
#line 113 "./parser.y"
                      {(yyval.ptr)=make_node(NOT,yylineno,{(yyvsp[0].ptr)});(yyval.ptr)->data = "NOT";}
#line 2042 "parser.tab.c"
    break;

  case 48:
#line 114 "./parser.y"
                        {(yyval.ptr)=make_node(DPLUS,yylineno,{(yyvsp[0].ptr)});(yyval.ptr)->data = "DPLUS";}
#line 2048 "parser.tab.c"
    break;

  case 49:
#line 115 "./parser.y"
                         {(yyval.ptr)=make_node(DPLUS,yylineno,{(yyvsp[-1].ptr)});(yyval.ptr)->data = "DPLUS";}
#line 2054 "parser.tab.c"
    break;

  case 50:
#line 116 "./parser.y"
                      {(yyval.ptr)=make_node(FUNC_CALL,yylineno,{(yyvsp[-1].ptr)});(yyval.ptr)->data = (yyvsp[-3].type_id);}
#line 2060 "parser.tab.c"
    break;

  case 51:
#line 117 "./parser.y"
                      {(yyval.ptr)=make_node(FUNC_CALL,yylineno);(yyval.ptr)->data = (yyvsp[-2].type_id);}
#line 2066 "parser.tab.c"
    break;

  case 52:
#line 118 "./parser.y"
                      {(yyval.ptr)=make_node(ID,yylineno);(yyval.ptr)->data = (yyvsp[0].type_id);}
#line 2072 "parser.tab.c"
    break;

  case 53:
#line 119 "./parser.y"
                      {(yyval.ptr)=make_node(INT,yylineno);(yyval.ptr)->data=(yyvsp[0].type_int);(yyval.ptr)->type=INT;}
#line 2078 "parser.tab.c"
    break;

  case 54:
#line 120 "./parser.y"
                      {(yyval.ptr)=make_node(FLOAT,yylineno);(yyval.ptr)->data=(yyvsp[0].type_float);(yyval.ptr)->type=FLOAT;}
#line 2084 "parser.tab.c"
    break;

  case 55:
#line 122 "./parser.y"
                           {(yyval.ptr)=make_node(ARGS,yylineno,{(yyvsp[-2].ptr),(yyvsp[0].ptr)});}
#line 2090 "parser.tab.c"
    break;

  case 56:
#line 123 "./parser.y"
                           {(yyval.ptr)=make_node(ARGS,yylineno,{(yyvsp[0].ptr)});}
#line 2096 "parser.tab.c"
    break;


#line 2100 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 126 "./parser.y"


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
