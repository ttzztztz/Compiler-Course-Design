// A Bison parser, made by GNU Bison 3.7.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 3 "./parser.y"

#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.hh"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);
void display(struct ASTNode *,int);
int yylex();

#line 54 "parser.tab.cc"


#include "parser.tab.hh"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 151 "parser.tab.cc"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  parser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: ExtDefList
#line 51 "./parser.y"
                       { display((yystack_[0].value.ptr),0); semantic_Analysis0((yystack_[0].value.ptr));}
#line 617 "parser.tab.cc"
    break;

  case 3: // ExtDefList: %empty
#line 53 "./parser.y"
            {(yylhs.value.ptr)=NULL;}
#line 623 "parser.tab.cc"
    break;

  case 4: // ExtDefList: ExtDef ExtDefList
#line 54 "./parser.y"
                              {(yylhs.value.ptr)=mknode(2,yy::parser::token::EXT_DEF_LIST,yylineno,(yystack_[1].value.ptr),(yystack_[0].value.ptr));}
#line 629 "parser.tab.cc"
    break;

  case 5: // ExtDef: Specifier ExtDecList SEMI
#line 56 "./parser.y"
                                      {(yylhs.value.ptr)=mknode(2,yy::parser::token::EXT_VAR_DEF,yylineno,(yystack_[2].value.ptr),(yystack_[1].value.ptr));}
#line 635 "parser.tab.cc"
    break;

  case 6: // ExtDef: Specifier FuncDec CompSt
#line 57 "./parser.y"
                                      {(yylhs.value.ptr)=mknode(3,yy::parser::token::FUNC_DEF,yylineno,(yystack_[2].value.ptr),(yystack_[1].value.ptr),(yystack_[0].value.ptr));}
#line 641 "parser.tab.cc"
    break;

  case 7: // ExtDef: error SEMI
#line 58 "./parser.y"
                        {(yylhs.value.ptr)=NULL;}
#line 647 "parser.tab.cc"
    break;

  case 8: // Specifier: TYPE
#line 60 "./parser.y"
                    {(yylhs.value.ptr)=mknode(0,yy::parser::token::TYPE,yylineno);strcpy((yylhs.value.ptr)->type_id,(yystack_[0].value.type_id));(yylhs.value.ptr)->type=!strcmp((yystack_[0].value.type_id),"int")?INT:FLOAT;}
#line 653 "parser.tab.cc"
    break;

  case 9: // ExtDecList: VarDec
#line 62 "./parser.y"
                         {(yylhs.value.ptr)=(yystack_[0].value.ptr);}
#line 659 "parser.tab.cc"
    break;

  case 10: // ExtDecList: VarDec COMMA ExtDecList
#line 63 "./parser.y"
                                     {(yylhs.value.ptr)=mknode(2,yy::parser::token::EXT_DEC_LIST,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));}
#line 665 "parser.tab.cc"
    break;

  case 11: // VarDec: ID
#line 65 "./parser.y"
                     {(yylhs.value.ptr)=mknode(0,yy::parser::token::ID,yylineno);strcpy((yylhs.value.ptr)->type_id,(yystack_[0].value.type_id));}
#line 671 "parser.tab.cc"
    break;

  case 12: // FuncDec: ID LP VarList RP
#line 67 "./parser.y"
                            {(yylhs.value.ptr)=mknode(1,yy::parser::token::FUNC_DEC,yylineno,(yystack_[1].value.ptr));strcpy((yylhs.value.ptr)->type_id,(yystack_[3].value.type_id));}
#line 677 "parser.tab.cc"
    break;

  case 13: // FuncDec: ID LP RP
#line 68 "./parser.y"
                             {(yylhs.value.ptr)=mknode(0,yy::parser::token::FUNC_DEC,yylineno);strcpy((yylhs.value.ptr)->type_id,(yystack_[2].value.type_id));(yylhs.value.ptr)->ptr[0]=NULL;}
#line 683 "parser.tab.cc"
    break;

  case 14: // VarList: ParamDec
#line 71 "./parser.y"
                   {(yylhs.value.ptr)=mknode(1,yy::parser::token::PARAM_LIST,yylineno,(yystack_[0].value.ptr));}
#line 689 "parser.tab.cc"
    break;

  case 15: // VarList: ParamDec COMMA VarList
#line 72 "./parser.y"
                                   {(yylhs.value.ptr)=mknode(2,yy::parser::token::PARAM_LIST,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));}
#line 695 "parser.tab.cc"
    break;

  case 16: // ParamDec: Specifier VarDec
#line 74 "./parser.y"
                                   {(yylhs.value.ptr)=mknode(2,yy::parser::token::PARAM_DEC,yylineno,(yystack_[1].value.ptr),(yystack_[0].value.ptr));}
#line 701 "parser.tab.cc"
    break;

  case 17: // CompSt: LC DefList StmList RC
#line 77 "./parser.y"
                                 {(yylhs.value.ptr)=mknode(2,yy::parser::token::COMP_STM,yylineno,(yystack_[2].value.ptr),(yystack_[1].value.ptr));}
#line 707 "parser.tab.cc"
    break;

  case 18: // StmList: %empty
#line 79 "./parser.y"
         {(yylhs.value.ptr)=NULL; }
#line 713 "parser.tab.cc"
    break;

  case 19: // StmList: Stmt StmList
#line 80 "./parser.y"
                        {(yylhs.value.ptr)=mknode(2,yy::parser::token::STM_LIST,yylineno,(yystack_[1].value.ptr),(yystack_[0].value.ptr));}
#line 719 "parser.tab.cc"
    break;

  case 20: // Stmt: Exp SEMI
#line 82 "./parser.y"
                    {(yylhs.value.ptr)=mknode(1,yy::parser::token::EXP_STMT,yylineno,(yystack_[1].value.ptr));}
#line 725 "parser.tab.cc"
    break;

  case 21: // Stmt: CompSt
#line 83 "./parser.y"
                    {(yylhs.value.ptr)=(yystack_[0].value.ptr);}
#line 731 "parser.tab.cc"
    break;

  case 22: // Stmt: RETURN Exp SEMI
#line 84 "./parser.y"
                          {(yylhs.value.ptr)=mknode(1,yy::parser::token::RETURN,yylineno,(yystack_[1].value.ptr));}
#line 737 "parser.tab.cc"
    break;

  case 23: // Stmt: IF LP Exp RP Stmt
#line 85 "./parser.y"
                                                  {(yylhs.value.ptr)=mknode(2,yy::parser::token::IF_THEN,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));}
#line 743 "parser.tab.cc"
    break;

  case 24: // Stmt: IF LP Exp RP Stmt ELSE Stmt
#line 86 "./parser.y"
                                      {(yylhs.value.ptr)=mknode(3,yy::parser::token::IF_THEN_ELSE,yylineno,(yystack_[4].value.ptr),(yystack_[2].value.ptr),(yystack_[0].value.ptr));}
#line 749 "parser.tab.cc"
    break;

  case 25: // Stmt: WHILE LP Exp RP Stmt
#line 87 "./parser.y"
                             {(yylhs.value.ptr)=mknode(2,yy::parser::token::WHILE,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));}
#line 755 "parser.tab.cc"
    break;

  case 26: // DefList: %empty
#line 89 "./parser.y"
         {(yylhs.value.ptr)=NULL; }
#line 761 "parser.tab.cc"
    break;

  case 27: // DefList: Def DefList
#line 90 "./parser.y"
                      {(yylhs.value.ptr)=mknode(2,yy::parser::token::DEF_LIST,yylineno,(yystack_[1].value.ptr),(yystack_[0].value.ptr));}
#line 767 "parser.tab.cc"
    break;

  case 28: // DefList: error SEMI
#line 91 "./parser.y"
                       {(yylhs.value.ptr)=NULL;}
#line 773 "parser.tab.cc"
    break;

  case 29: // Def: Specifier DecList SEMI
#line 93 "./parser.y"
                               {(yylhs.value.ptr)=mknode(2,yy::parser::token::VAR_DEF,yylineno,(yystack_[2].value.ptr),(yystack_[1].value.ptr));}
#line 779 "parser.tab.cc"
    break;

  case 30: // DecList: Dec
#line 95 "./parser.y"
              {(yylhs.value.ptr)=mknode(1,yy::parser::token::DEC_LIST,yylineno,(yystack_[0].value.ptr));}
#line 785 "parser.tab.cc"
    break;

  case 31: // DecList: Dec COMMA DecList
#line 96 "./parser.y"
                            {(yylhs.value.ptr)=mknode(2,yy::parser::token::DEC_LIST,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));}
#line 791 "parser.tab.cc"
    break;

  case 32: // Dec: VarDec
#line 98 "./parser.y"
                 {(yylhs.value.ptr)=(yystack_[0].value.ptr);}
#line 797 "parser.tab.cc"
    break;

  case 33: // Dec: VarDec ASSIGNOP Exp
#line 99 "./parser.y"
                              {(yylhs.value.ptr)=mknode(2,yy::parser::token::ASSIGNOP,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));strcpy((yylhs.value.ptr)->type_id,"ASSIGNOP");}
#line 803 "parser.tab.cc"
    break;

  case 34: // Exp: Exp ASSIGNOP Exp
#line 101 "./parser.y"
                         {(yylhs.value.ptr)=mknode(2,yy::parser::token::ASSIGNOP,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));strcpy((yylhs.value.ptr)->type_id,"ASSIGNOP");}
#line 809 "parser.tab.cc"
    break;

  case 35: // Exp: Exp AND Exp
#line 102 "./parser.y"
                      {(yylhs.value.ptr)=mknode(2,yy::parser::token::AND,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));strcpy((yylhs.value.ptr)->type_id,"AND");}
#line 815 "parser.tab.cc"
    break;

  case 36: // Exp: Exp OR Exp
#line 103 "./parser.y"
                      {(yylhs.value.ptr)=mknode(2,yy::parser::token::OR,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));strcpy((yylhs.value.ptr)->type_id,"OR");}
#line 821 "parser.tab.cc"
    break;

  case 37: // Exp: Exp RELOP Exp
#line 104 "./parser.y"
                      {(yylhs.value.ptr)=mknode(2,yy::parser::token::RELOP,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));strcpy((yylhs.value.ptr)->type_id,(yystack_[1].value.type_id));}
#line 827 "parser.tab.cc"
    break;

  case 38: // Exp: Exp PLUS Exp
#line 105 "./parser.y"
                      {(yylhs.value.ptr)=mknode(2,yy::parser::token::PLUS,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));strcpy((yylhs.value.ptr)->type_id,"PLUS");}
#line 833 "parser.tab.cc"
    break;

  case 39: // Exp: Exp MINUS Exp
#line 106 "./parser.y"
                      {(yylhs.value.ptr)=mknode(2,yy::parser::token::MINUS,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));strcpy((yylhs.value.ptr)->type_id,"MINUS");}
#line 839 "parser.tab.cc"
    break;

  case 40: // Exp: Exp STAR Exp
#line 107 "./parser.y"
                      {(yylhs.value.ptr)=mknode(2,yy::parser::token::STAR,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));strcpy((yylhs.value.ptr)->type_id,"STAR");}
#line 845 "parser.tab.cc"
    break;

  case 41: // Exp: Exp DIV Exp
#line 108 "./parser.y"
                      {(yylhs.value.ptr)=mknode(2,yy::parser::token::DIV,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));strcpy((yylhs.value.ptr)->type_id,"DIV");}
#line 851 "parser.tab.cc"
    break;

  case 42: // Exp: LP Exp RP
#line 109 "./parser.y"
                      {(yylhs.value.ptr)=(yystack_[1].value.ptr);}
#line 857 "parser.tab.cc"
    break;

  case 43: // Exp: MINUS Exp
#line 110 "./parser.y"
                                 {(yylhs.value.ptr)=mknode(1,yy::parser::token::UMINUS,yylineno,(yystack_[0].value.ptr));strcpy((yylhs.value.ptr)->type_id,"UMINUS");}
#line 863 "parser.tab.cc"
    break;

  case 44: // Exp: NOT Exp
#line 111 "./parser.y"
                      {(yylhs.value.ptr)=mknode(1,yy::parser::token::NOT,yylineno,(yystack_[0].value.ptr));strcpy((yylhs.value.ptr)->type_id,"NOT");}
#line 869 "parser.tab.cc"
    break;

  case 45: // Exp: DPLUS Exp
#line 112 "./parser.y"
                        {(yylhs.value.ptr)=mknode(1,yy::parser::token::DPLUS,yylineno,(yystack_[0].value.ptr));strcpy((yylhs.value.ptr)->type_id,"DPLUS");}
#line 875 "parser.tab.cc"
    break;

  case 46: // Exp: Exp DPLUS
#line 113 "./parser.y"
                         {(yylhs.value.ptr)=mknode(1,yy::parser::token::DPLUS,yylineno,(yystack_[1].value.ptr));strcpy((yylhs.value.ptr)->type_id,"DPLUS");}
#line 881 "parser.tab.cc"
    break;

  case 47: // Exp: ID LP Args RP
#line 114 "./parser.y"
                      {(yylhs.value.ptr)=mknode(1,yy::parser::token::FUNC_CALL,yylineno,(yystack_[1].value.ptr));strcpy((yylhs.value.ptr)->type_id,(yystack_[3].value.type_id));}
#line 887 "parser.tab.cc"
    break;

  case 48: // Exp: ID LP RP
#line 115 "./parser.y"
                      {(yylhs.value.ptr)=mknode(0,yy::parser::token::FUNC_CALL,yylineno);strcpy((yylhs.value.ptr)->type_id,(yystack_[2].value.type_id));}
#line 893 "parser.tab.cc"
    break;

  case 49: // Exp: ID
#line 116 "./parser.y"
                      {(yylhs.value.ptr)=mknode(0,yy::parser::token::ID,yylineno);strcpy((yylhs.value.ptr)->type_id,(yystack_[0].value.type_id));}
#line 899 "parser.tab.cc"
    break;

  case 50: // Exp: INT
#line 117 "./parser.y"
                      {(yylhs.value.ptr)=mknode(0,yy::parser::token::INT,yylineno);(yylhs.value.ptr)->type_int=(yystack_[0].value.type_int);(yylhs.value.ptr)->type=INT;}
#line 905 "parser.tab.cc"
    break;

  case 51: // Exp: FLOAT
#line 118 "./parser.y"
                      {(yylhs.value.ptr)=mknode(0,yy::parser::token::FLOAT,yylineno);(yylhs.value.ptr)->type_float=(yystack_[0].value.type_float);(yylhs.value.ptr)->type=FLOAT;}
#line 911 "parser.tab.cc"
    break;

  case 52: // Args: Exp COMMA Args
#line 120 "./parser.y"
                           {(yylhs.value.ptr)=mknode(2,yy::parser::token::ARGS,yylineno,(yystack_[2].value.ptr),(yystack_[0].value.ptr));}
#line 917 "parser.tab.cc"
    break;

  case 53: // Args: Exp
#line 121 "./parser.y"
                           {(yylhs.value.ptr)=mknode(1,yy::parser::token::ARGS,yylineno,(yystack_[0].value.ptr));}
#line 923 "parser.tab.cc"
    break;


#line 927 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
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


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
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
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -76;

  const signed char parser::yytable_ninf_ = -27;

  const short
  parser::yypact_[] =
  {
      49,    -6,   -76,    12,   -76,    49,    11,   -76,   -76,   -76,
      14,    23,    13,    30,    -1,   -76,    42,    36,   -76,   -76,
      42,    41,    40,   -76,   -76,    43,    42,    60,    36,   -76,
     -76,    51,   -76,    46,    47,    52,   -76,    61,   -76,    87,
      87,    87,    87,    63,    64,    87,   -76,    65,    60,    97,
     -76,   -76,    87,   -76,    42,    71,    76,   114,    76,    76,
      87,    87,   131,   -76,   -76,    87,   -76,   -76,    87,    87,
      87,    87,    87,    87,    87,   199,   -76,   -76,   148,    78,
     -76,   165,   182,   -76,   241,     0,     0,    76,    76,   216,
     236,   230,    87,   -76,    60,    60,   -76,    68,   -76,    60,
     -76
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     8,     0,     2,     0,     0,     7,     1,     4,
      11,     0,     9,     0,     0,     5,     0,     0,     6,    13,
       0,     0,    14,    11,    10,     0,     0,    18,     0,    16,
      12,     0,    28,    32,     0,    30,    50,    49,    51,     0,
       0,     0,     0,     0,     0,     0,    21,     0,    18,     0,
      27,    15,     0,    29,     0,     0,    45,     0,    43,    44,
       0,     0,     0,    17,    19,     0,    46,    20,     0,     0,
       0,     0,     0,     0,     0,    33,    31,    48,    53,     0,
      42,     0,     0,    22,    37,    38,    39,    40,    41,    34,
      35,    36,     0,    47,     0,     0,    52,    23,    25,     0,
      24
  };

  const signed char
  parser::yypgoto_[] =
  {
     -76,   -76,    84,   -76,    -3,    81,   -16,   -76,    67,   -76,
      86,    53,   -75,    72,   -76,    50,   -76,   -39,    15
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     3,     4,     5,     6,    11,    12,    13,    21,    22,
      46,    47,    48,    27,    28,    34,    35,    49,    79
  };

  const signed char
  parser::yytable_[] =
  {
      56,    57,    58,    59,    29,     2,    62,     7,    66,    19,
      33,    20,     8,    75,    26,    10,    78,    70,    71,    97,
      98,    81,    82,    14,   100,    26,    84,    16,    20,    85,
      86,    87,    88,    89,    90,    91,    15,    25,    33,   -26,
     -26,    17,     2,   -26,   -26,   -26,    23,   -26,   -26,    -3,
       1,    30,   -26,    78,    31,     2,    32,     2,   -26,   -26,
      53,   -26,   -26,    36,    37,    52,    54,    38,    39,    40,
      55,    17,    60,    61,    36,    37,    41,    63,    38,    39,
      40,    77,    42,    43,    66,    44,    45,    41,    93,     9,
      36,    37,    99,    42,    38,    39,    40,    24,    51,    18,
      50,    64,    65,    41,    76,    66,     0,    96,     0,    42,
      67,     0,    68,    69,    70,    71,    72,    73,    74,    65,
       0,     0,    66,     0,    80,     0,     0,     0,     0,    68,
      69,    70,    71,    72,    73,    74,    65,     0,     0,    66,
       0,     0,     0,     0,    83,     0,    68,    69,    70,    71,
      72,    73,    74,    65,     0,     0,    66,     0,     0,     0,
       0,     0,    92,    68,    69,    70,    71,    72,    73,    74,
      65,     0,     0,    66,     0,    94,     0,     0,     0,     0,
      68,    69,    70,    71,    72,    73,    74,    65,     0,     0,
      66,     0,    95,     0,     0,     0,     0,    68,    69,    70,
      71,    72,    73,    74,    65,     0,     0,    66,     0,     0,
       0,     0,     0,     0,    68,    69,    70,    71,    72,    73,
      74,    65,     0,     0,    66,     0,     0,     0,     0,     0,
       0,    68,    69,    70,    71,    65,    73,    74,    66,     0,
       0,    65,     0,     0,    66,    68,    69,    70,    71,    66,
      73,    68,    69,    70,    71,     0,    68,    69,    70,    71
  };

  const signed char
  parser::yycheck_[] =
  {
      39,    40,    41,    42,    20,     6,    45,    13,     8,    10,
      26,    14,     0,    52,    17,     4,    55,    17,    18,    94,
      95,    60,    61,     9,    99,    28,    65,    14,    31,    68,
      69,    70,    71,    72,    73,    74,    13,     1,    54,     3,
       4,    11,     6,     7,     8,     9,     4,    11,    12,     0,
       1,    10,    16,    92,    14,     6,    13,     6,    22,    23,
      13,    25,    26,     3,     4,    19,    14,     7,     8,     9,
       9,    11,     9,     9,     3,     4,    16,    12,     7,     8,
       9,    10,    22,    23,     8,    25,    26,    16,    10,     5,
       3,     4,    24,    22,     7,     8,     9,    16,    31,    13,
      28,    48,     5,    16,    54,     8,    -1,    92,    -1,    22,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,     5,
      -1,    -1,     8,    -1,    10,    -1,    -1,    -1,    -1,    15,
      16,    17,    18,    19,    20,    21,     5,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,     5,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
       5,    -1,    -1,     8,    -1,    10,    -1,    -1,    -1,    -1,
      15,    16,    17,    18,    19,    20,    21,     5,    -1,    -1,
       8,    -1,    10,    -1,    -1,    -1,    -1,    15,    16,    17,
      18,    19,    20,    21,     5,    -1,    -1,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    16,    17,    18,    19,    20,
      21,     5,    -1,    -1,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    15,    16,    17,    18,     5,    20,    21,     8,    -1,
      -1,     5,    -1,    -1,     8,    15,    16,    17,    18,     8,
      20,    15,    16,    17,    18,    -1,    15,    16,    17,    18
  };

  const signed char
  parser::yystos_[] =
  {
       0,     1,     6,    64,    65,    66,    67,    13,     0,    65,
       4,    68,    69,    70,     9,    13,    14,    11,    73,    10,
      67,    71,    72,     4,    68,     1,    67,    76,    77,    69,
      10,    14,    13,    69,    78,    79,     3,     4,     7,     8,
       9,    16,    22,    23,    25,    26,    73,    74,    75,    80,
      76,    71,    19,    13,    14,     9,    80,    80,    80,    80,
       9,     9,    80,    12,    74,     5,     8,    13,    15,    16,
      17,    18,    19,    20,    21,    80,    78,    10,    80,    81,
      10,    80,    80,    13,    80,    80,    80,    80,    80,    80,
      80,    80,    14,    10,    10,    10,    81,    75,    75,    24,
      75
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    63,    64,    65,    65,    66,    66,    66,    67,    68,
      68,    69,    70,    70,    71,    71,    72,    73,    74,    74,
      75,    75,    75,    75,    75,    75,    76,    76,    76,    77,
      78,    78,    79,    79,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    81,    81
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     3,     3,     2,     1,     1,
       3,     1,     4,     3,     1,     3,     2,     4,     0,     2,
       2,     1,     3,     5,     7,     5,     0,     2,     2,     3,
       1,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     4,     3,     1,
       1,     1,     3,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "INT", "ID", "RELOP",
  "TYPE", "FLOAT", "DPLUS", "LP", "RP", "LC", "RC", "SEMI", "COMMA",
  "PLUS", "MINUS", "STAR", "DIV", "ASSIGNOP", "AND", "OR", "NOT", "IF",
  "ELSE", "WHILE", "RETURN", "FOR", "SWITCH", "CASE", "COLON", "DEFAULT",
  "EXT_DEF_LIST", "EXT_VAR_DEF", "FUNC_DEF", "FUNC_DEC", "EXT_DEC_LIST",
  "PARAM_LIST", "PARAM_DEC", "VAR_DEF", "DEC_LIST", "DEF_LIST", "COMP_STM",
  "STM_LIST", "EXP_STMT", "IF_THEN", "IF_THEN_ELSE", "FUNC_CALL", "ARGS",
  "FUNCTION", "PARAM", "ARG", "CALL", "LABEL", "GOTO", "JLT", "JLE", "JGT",
  "JGE", "EQ", "NEQ", "UMINUS", "LOWER_THEN_ELSE", "$accept", "program",
  "ExtDefList", "ExtDef", "Specifier", "ExtDecList", "VarDec", "FuncDec",
  "VarList", "ParamDec", "CompSt", "StmList", "Stmt", "DefList", "Def",
  "DecList", "Dec", "Exp", "Args", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const signed char
  parser::yyrline_[] =
  {
       0,    51,    51,    53,    54,    56,    57,    58,    60,    62,
      63,    65,    67,    68,    71,    72,    74,    77,    79,    80,
      82,    83,    84,    85,    86,    87,    89,    90,    91,    93,
      95,    96,    98,    99,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   120,   121
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  parser::symbol_kind_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
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
      55,    56,    57,    58,    59,    60,    61,    62
    };
    // Last valid token kind.
    const int code_max = 317;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // yy
#line 1542 "parser.tab.cc"

#line 124 "./parser.y"

#include<stdarg.h>
void yyerror(const char* fmt, ...) {
        va_list ap;
        va_start(ap, fmt);
        fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
        vfprintf(stderr, fmt, ap);
        fprintf(stderr, ".\n");
}

int main(int argc, char *argv[]) {
	yyin = fopen(argv[1], "r");
	if (!yyin) exit(0);
	yylineno = 1;
	yy::yyparse();
	return 0;
}
