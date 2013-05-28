/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "tree.y"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ast.h"
#include "table.h"

#define YYSTYPE ast_node
#define YYDEBUG 1

extern int yylex();
int yyerror(char *s);
extern char *yytext;

extern int lineNumber;
extern ast_node root;
extern int parseError;

extern char savedLiteralText[];
extern table symbol_table;

/* Line 371 of yacc.c  */
#line 90 "tree.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "tree.tab.h".  */
#ifndef YY_YY_TREE_TAB_H_INCLUDED
# define YY_YY_TREE_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     DOUBLE = 259,
     ID = 260,
     VOID = 261,
     IF = 262,
     ELSE = 263,
     WHILE = 264,
     DO = 265,
     FOR = 266,
     RETURN = 267,
     READ = 268,
     PRINT = 269,
     NUM = 270,
     FNUM = 271,
     STRING = 272,
     BADTOKEN = 273,
     OR = 274,
     AND = 275,
     ISEQUAL = 276,
     NOTEQUAL = 277,
     LEQ = 278,
     GEQ = 279,
     INCREMENT = 280,
     DECREMENT = 281,
     UMINUS = 282
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_TREE_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 183 "tree.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   637

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNRULES -- Number of states.  */
#define YYNSTATES  206

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   282

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,     2,     2,    34,     2,     2,
      41,    42,    32,    30,    38,    31,     2,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    37,
      28,    27,    29,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,    44,     2,     2,     2,     2,
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
      25,    26,    36
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    18,    20,
      22,    24,    28,    30,    34,    39,    46,    53,    55,    57,
      58,    60,    64,    67,    72,    77,    80,    81,    84,    85,
      87,    89,    91,    93,    95,    97,    99,   101,   103,   106,
     108,   111,   117,   125,   131,   139,   145,   151,   158,   165,
     175,   185,   195,   205,   215,   225,   235,   245,   247,   248,
     251,   255,   259,   262,   266,   270,   274,   278,   280,   282,
     287,   292,   296,   300,   304,   308,   312,   316,   320,   324,
     328,   332,   336,   340,   344,   347,   350,   352,   355,   358,
     362,   366,   368,   370,   372,   377,   379,   380,   384,   386
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      46,     0,    -1,    47,    -1,    48,    -1,    47,    48,    -1,
      49,    -1,    53,    -1,    50,    51,    37,    -1,     3,    -1,
       4,    -1,    52,    -1,    51,    38,    52,    -1,    76,    -1,
      76,    27,    70,    -1,    76,    39,    70,    40,    -1,    50,
      76,    41,    54,    42,    57,    -1,     6,    76,    41,    54,
      42,    57,    -1,    55,    -1,     6,    -1,    -1,    56,    -1,
      55,    38,    56,    -1,    50,    76,    -1,    50,    76,    39,
      40,    -1,    43,    58,    59,    44,    -1,    58,    49,    -1,
      -1,    59,    60,    -1,    -1,    61,    -1,    57,    -1,    62,
      -1,    63,    -1,    64,    -1,    65,    -1,    67,    -1,    68,
      -1,    69,    -1,    70,    37,    -1,    37,    -1,     1,    37,
      -1,     7,    41,    70,    42,    60,    -1,     7,    41,    70,
      42,    60,     8,    60,    -1,     7,    41,     1,    42,    60,
      -1,     7,    41,     1,    42,    60,     8,    60,    -1,     9,
      41,    70,    42,    60,    -1,     9,    41,     1,    42,    60,
      -1,    10,    60,     9,    41,    70,    42,    -1,    10,    60,
       9,    41,     1,    42,    -1,    11,    41,    66,    37,    66,
      37,    66,    42,    60,    -1,    11,    41,     1,    37,    66,
      37,    66,    42,    60,    -1,    11,    41,    66,    37,     1,
      37,    66,    42,    60,    -1,    11,    41,    66,    37,    66,
      37,     1,    42,    60,    -1,    11,    41,     1,    37,    66,
      37,     1,    42,    60,    -1,    11,    41,     1,    37,     1,
      37,    66,    42,    60,    -1,    11,    41,    66,    37,     1,
      37,     1,    42,    60,    -1,    11,    41,     1,    37,     1,
      37,     1,    42,    60,    -1,    70,    -1,    -1,    12,    37,
      -1,    12,    70,    37,    -1,    12,     1,    37,    -1,    13,
      71,    -1,    14,    70,    37,    -1,    14,    17,    37,    -1,
      14,     1,    37,    -1,    71,    27,    70,    -1,    72,    -1,
      76,    -1,    76,    39,    70,    40,    -1,    76,    39,     1,
      40,    -1,    70,    30,    70,    -1,    70,    31,    70,    -1,
      70,    32,    70,    -1,    70,    33,    70,    -1,    70,    34,
      70,    -1,    70,    28,    70,    -1,    70,    23,    70,    -1,
      70,    29,    70,    -1,    70,    24,    70,    -1,    70,    21,
      70,    -1,    70,    22,    70,    -1,    70,    20,    70,    -1,
      70,    19,    70,    -1,    35,    70,    -1,    31,    70,    -1,
      71,    -1,    25,    71,    -1,    26,    71,    -1,    41,    70,
      42,    -1,    41,     1,    42,    -1,    73,    -1,    15,    -1,
      16,    -1,    76,    41,    74,    42,    -1,    75,    -1,    -1,
      75,    38,    70,    -1,    70,    -1,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    37,    37,    44,    45,    54,    55,    58,    75,    77,
      81,    82,    95,    96,   101,   108,   127,   146,   150,   151,
     154,   160,   174,   181,   191,   206,   217,   220,   232,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   246,   247,
     248,   251,   256,   262,   263,   266,   272,   275,   284,   287,
     325,   326,   327,   328,   329,   330,   331,   335,   336,   339,
     340,   345,   348,   354,   358,   364,   367,   372,   375,   376,
     382,   385,   391,   397,   403,   409,   415,   422,   429,   436,
     443,   450,   457,   464,   471,   477,   482,   483,   488,   493,
     494,   495,   496,   502,   510,   517,   522,   525,   537,   541
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "DOUBLE", "ID", "VOID", "IF",
  "ELSE", "WHILE", "DO", "FOR", "RETURN", "READ", "PRINT", "NUM", "FNUM",
  "STRING", "BADTOKEN", "OR", "AND", "ISEQUAL", "NOTEQUAL", "LEQ", "GEQ",
  "INCREMENT", "DECREMENT", "'='", "'<'", "'>'", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'!'", "UMINUS", "';'", "','", "'['", "']'", "'('", "')'",
  "'{'", "'}'", "$accept", "program", "declarationList", "declaration",
  "varDeclaration", "varSpec", "varList", "varDecl", "funcDeclaration",
  "formalParams", "formalList", "formalParam", "compound", "localDec",
  "statementList", "statement", "exprStatement", "ifStatement",
  "whileStatement", "doWhileStatement", "forStatement", "forExpr",
  "returnStatement", "readStatement", "printStatement", "expr", "var",
  "rValue", "call", "args", "argList", "id", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    61,    60,    62,
      43,    45,    42,    47,    37,    33,   282,    59,    44,    91,
      93,    40,    41,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    49,    50,    50,
      51,    51,    52,    52,    52,    53,    53,    54,    54,    54,
      55,    55,    56,    56,    57,    58,    58,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    61,    61,
      61,    62,    62,    62,    62,    63,    63,    64,    64,    65,
      65,    65,    65,    65,    65,    65,    65,    66,    66,    67,
      67,    67,    68,    69,    69,    69,    70,    70,    71,    71,
      71,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    73,    74,    74,    75,    75,    76
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     1,     1,
       1,     3,     1,     3,     4,     6,     6,     1,     1,     0,
       1,     3,     2,     4,     4,     2,     0,     2,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     5,     7,     5,     7,     5,     5,     6,     6,     9,
       9,     9,     9,     9,     9,     9,     9,     1,     0,     2,
       3,     3,     2,     3,     3,     3,     3,     1,     1,     4,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     1,     2,     2,     3,
       3,     1,     1,     1,     4,     1,     0,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     8,     9,     0,     0,     2,     3,     5,     0,     6,
      99,     0,     1,     4,     0,    10,    12,    19,     7,     0,
       0,     0,    19,    18,     0,     0,    17,    20,    11,    12,
      92,    93,     0,     0,     0,     0,     0,    13,    86,    67,
      91,    68,     0,     0,    22,     0,     0,    87,    68,    88,
      85,    84,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    96,
      14,     0,     0,    26,    16,    21,    90,    89,    83,    82,
      80,    81,    77,    79,    76,    78,    71,    72,    73,    74,
      75,    66,     0,     0,    98,     0,    95,    15,    23,    28,
      70,    69,    94,     0,    25,     0,     0,    97,     0,     0,
       0,     0,     0,     0,     0,     0,    39,    24,    30,    27,
      29,    31,    32,    33,    34,    35,    36,    37,     0,    40,
       0,     0,     0,     0,     0,    59,     0,    62,     0,     0,
       0,    38,     0,     0,     0,     0,     0,     0,     0,    57,
      61,    60,    65,    64,    63,     0,     0,     0,     0,     0,
       0,     0,    43,    41,    46,    45,     0,     0,     0,     0,
       0,     0,     0,     0,    48,    47,     0,     0,     0,     0,
      44,    42,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    56,    54,
      53,    50,    55,    51,    52,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    24,    14,    15,     9,    25,
      26,    27,   118,    99,   106,   119,   120,   121,   122,   123,
     124,   148,   125,   126,   127,   128,    38,    39,    40,    95,
      96,    41
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -152
static const yytype_int16 yypact[] =
{
      74,  -152,  -152,    64,     5,    74,  -152,  -152,    64,  -152,
    -152,    38,  -152,  -152,   -25,  -152,    55,    94,  -152,    64,
     390,   390,    94,  -152,    64,    39,    65,  -152,  -152,   -16,
    -152,  -152,    64,    64,   390,   390,   314,   562,    75,  -152,
    -152,   -10,   461,    62,    67,    66,    56,  -152,    68,  -152,
    -152,  -152,    73,    42,   390,   390,   390,   390,   390,   390,
     390,   390,   390,   390,   390,   390,   390,   390,   332,   390,
    -152,    66,    77,  -152,  -152,  -152,  -152,  -152,   577,   591,
     603,   603,    24,    24,    24,    24,   -12,   -12,  -152,  -152,
    -152,   562,    79,   483,   562,    86,    70,  -152,  -152,    56,
    -152,  -152,  -152,   390,  -152,    64,   111,   562,    92,    89,
      90,   159,    91,   239,    64,   252,  -152,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,   505,  -152,
     345,   363,   124,   270,    97,  -152,   524,  -152,    98,   101,
     543,  -152,   102,   413,   103,   429,   106,   112,   113,   562,
    -152,  -152,  -152,  -152,  -152,   159,   159,   159,   159,   376,
     283,   301,   135,   143,  -152,  -152,   119,   445,   116,   125,
     128,   139,   159,   159,  -152,  -152,   162,   190,   208,   221,
    -152,  -152,   137,   138,   140,   141,   144,   147,   150,   156,
     159,   159,   159,   159,   159,   159,   159,   159,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -152,  -152,  -152,   176,   100,     2,  -152,   182,  -152,   185,
    -152,   164,   -41,  -152,  -152,  -105,  -152,  -152,  -152,  -152,
    -152,  -151,  -152,  -152,  -152,   -20,   -15,  -152,  -152,  -152,
    -152,     0
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -59
static const yytype_int16 yytable[] =
{
      37,    42,     8,    11,    74,    12,   132,     8,    16,   169,
     171,    20,    18,    19,    50,    51,    53,    47,    49,    29,
      64,    65,    66,    21,    44,   183,   185,   187,   189,    68,
      97,    69,    48,    48,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    93,    94,
     162,   163,   164,   165,    62,    63,    64,    65,    66,     1,
       2,    54,    55,    56,    57,    58,    59,   180,   181,    10,
      60,    61,    62,    63,    64,    65,    66,     1,     2,    17,
       3,    45,    20,   107,    77,   198,   199,   200,   201,   202,
     203,   204,   205,   136,    21,   140,    22,     1,     2,   137,
      23,   105,    67,    46,    71,    29,    72,    68,   103,    73,
     143,   145,   108,   149,    48,    76,    10,    98,   109,   100,
     110,   111,   112,   113,   114,   115,    30,    31,   102,   129,
     130,   131,   133,   146,   150,   152,    32,    33,   153,   167,
     149,   149,    34,   172,   155,   157,    35,   159,   116,   160,
     161,   173,    36,   176,    73,   117,   149,   149,   149,   149,
     108,   174,   177,   182,    10,   178,   109,    10,   110,   111,
     112,   113,   114,   115,    30,    31,   179,    30,    31,   190,
     191,    13,   192,   193,    32,    33,   194,    32,    33,   195,
      34,   184,   196,    34,    35,    10,   116,    35,   197,   104,
      36,    28,    73,    36,   -58,    30,    31,    43,     0,   186,
      75,     0,     0,    10,     0,    32,    33,     0,     0,     0,
       0,    34,   188,    30,    31,    35,    10,     0,     0,     0,
       0,    36,   -58,    32,    33,     0,    30,    31,     0,    34,
     134,     0,     0,    35,    10,     0,    32,    33,     0,    36,
     -58,     0,    34,   138,    30,    31,    35,    10,     0,     0,
       0,     0,    36,   -58,    32,    33,     0,    30,    31,   139,
      34,   147,     0,     0,    35,    10,   135,    32,    33,     0,
      36,     0,     0,    34,   168,    30,    31,    35,    10,     0,
       0,     0,     0,    36,     0,    32,    33,     0,    30,    31,
       0,    34,   170,     0,     0,    35,    10,   -58,    32,    33,
       0,    36,     0,     0,    34,    52,    30,    31,    35,    10,
     -58,     0,     0,     0,    36,     0,    32,    33,     0,    30,
      31,     0,    34,    92,     0,     0,    35,    10,   -58,    32,
      33,     0,    36,     0,     0,    34,   142,    30,    31,    35,
      10,     0,     0,     0,     0,    36,     0,    32,    33,     0,
      30,    31,     0,    34,   144,     0,     0,    35,    10,     0,
      32,    33,     0,    36,     0,     0,    34,   166,    30,    31,
      35,    10,     0,     0,     0,     0,    36,     0,    32,    33,
       0,    30,    31,     0,    34,    10,     0,     0,    35,     0,
       0,    32,    33,     0,    36,    30,    31,    34,     0,     0,
       0,    35,     0,     0,     0,    32,    33,    36,     0,     0,
       0,    34,     0,     0,     0,    35,     0,     0,     0,     0,
       0,    36,    54,    55,    56,    57,    58,    59,     0,     0,
       0,    60,    61,    62,    63,    64,    65,    66,    54,    55,
      56,    57,    58,    59,     0,   156,     0,    60,    61,    62,
      63,    64,    65,    66,    54,    55,    56,    57,    58,    59,
       0,   158,     0,    60,    61,    62,    63,    64,    65,    66,
      54,    55,    56,    57,    58,    59,     0,   175,     0,    60,
      61,    62,    63,    64,    65,    66,     0,     0,     0,     0,
       0,    70,    54,    55,    56,    57,    58,    59,     0,     0,
       0,    60,    61,    62,    63,    64,    65,    66,     0,     0,
       0,     0,     0,   101,    54,    55,    56,    57,    58,    59,
       0,     0,     0,    60,    61,    62,    63,    64,    65,    66,
       0,     0,   141,    54,    55,    56,    57,    58,    59,     0,
       0,     0,    60,    61,    62,    63,    64,    65,    66,     0,
       0,   151,    54,    55,    56,    57,    58,    59,     0,     0,
       0,    60,    61,    62,    63,    64,    65,    66,     0,     0,
     154,    54,    55,    56,    57,    58,    59,     0,     0,     0,
      60,    61,    62,    63,    64,    65,    66,    55,    56,    57,
      58,    59,     0,     0,     0,    60,    61,    62,    63,    64,
      65,    66,    56,    57,    58,    59,     0,     0,     0,    60,
      61,    62,    63,    64,    65,    66,    58,    59,     0,     0,
       0,    60,    61,    62,    63,    64,    65,    66
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-152)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      20,    21,     0,     3,    45,     0,   111,     5,     8,   160,
     161,    27,    37,    38,    34,    35,    36,    32,    33,    19,
      32,    33,    34,    39,    24,   176,   177,   178,   179,    39,
      71,    41,    32,    33,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
     155,   156,   157,   158,    30,    31,    32,    33,    34,     3,
       4,    19,    20,    21,    22,    23,    24,   172,   173,     5,
      28,    29,    30,    31,    32,    33,    34,     3,     4,    41,
       6,    42,    27,   103,    42,   190,   191,   192,   193,   194,
     195,   196,   197,   113,    39,   115,    41,     3,     4,   114,
       6,    99,    27,    38,    42,   105,    39,    39,    38,    43,
     130,   131,     1,   133,   114,    42,     5,    40,     7,    40,
       9,    10,    11,    12,    13,    14,    15,    16,    42,    37,
      41,    41,    41,     9,    37,    37,    25,    26,    37,   159,
     160,   161,    31,     8,    42,    42,    35,    41,    37,    37,
      37,     8,    41,    37,    43,    44,   176,   177,   178,   179,
       1,    42,    37,     1,     5,    37,     7,     5,     9,    10,
      11,    12,    13,    14,    15,    16,    37,    15,    16,    42,
      42,     5,    42,    42,    25,    26,    42,    25,    26,    42,
      31,     1,    42,    31,    35,     5,    37,    35,    42,    99,
      41,    19,    43,    41,    42,    15,    16,    22,    -1,     1,
      46,    -1,    -1,     5,    -1,    25,    26,    -1,    -1,    -1,
      -1,    31,     1,    15,    16,    35,     5,    -1,    -1,    -1,
      -1,    41,    42,    25,    26,    -1,    15,    16,    -1,    31,
       1,    -1,    -1,    35,     5,    -1,    25,    26,    -1,    41,
      42,    -1,    31,     1,    15,    16,    35,     5,    -1,    -1,
      -1,    -1,    41,    42,    25,    26,    -1,    15,    16,    17,
      31,     1,    -1,    -1,    35,     5,    37,    25,    26,    -1,
      41,    -1,    -1,    31,     1,    15,    16,    35,     5,    -1,
      -1,    -1,    -1,    41,    -1,    25,    26,    -1,    15,    16,
      -1,    31,     1,    -1,    -1,    35,     5,    37,    25,    26,
      -1,    41,    -1,    -1,    31,     1,    15,    16,    35,     5,
      37,    -1,    -1,    -1,    41,    -1,    25,    26,    -1,    15,
      16,    -1,    31,     1,    -1,    -1,    35,     5,    37,    25,
      26,    -1,    41,    -1,    -1,    31,     1,    15,    16,    35,
       5,    -1,    -1,    -1,    -1,    41,    -1,    25,    26,    -1,
      15,    16,    -1,    31,     1,    -1,    -1,    35,     5,    -1,
      25,    26,    -1,    41,    -1,    -1,    31,     1,    15,    16,
      35,     5,    -1,    -1,    -1,    -1,    41,    -1,    25,    26,
      -1,    15,    16,    -1,    31,     5,    -1,    -1,    35,    -1,
      -1,    25,    26,    -1,    41,    15,    16,    31,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    25,    26,    41,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      -1,    41,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    19,    20,
      21,    22,    23,    24,    -1,    42,    -1,    28,    29,    30,
      31,    32,    33,    34,    19,    20,    21,    22,    23,    24,
      -1,    42,    -1,    28,    29,    30,    31,    32,    33,    34,
      19,    20,    21,    22,    23,    24,    -1,    42,    -1,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    40,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    37,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    37,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
      37,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    21,    22,    23,    24,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    23,    24,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     6,    46,    47,    48,    49,    50,    53,
       5,    76,     0,    48,    51,    52,    76,    41,    37,    38,
      27,    39,    41,     6,    50,    54,    55,    56,    52,    76,
      15,    16,    25,    26,    31,    35,    41,    70,    71,    72,
      73,    76,    70,    54,    76,    42,    38,    71,    76,    71,
      70,    70,     1,    70,    19,    20,    21,    22,    23,    24,
      28,    29,    30,    31,    32,    33,    34,    27,    39,    41,
      40,    42,    39,    43,    57,    56,    42,    42,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,     1,    70,    70,    74,    75,    57,    40,    58,
      40,    40,    42,    38,    49,    50,    59,    70,     1,     7,
       9,    10,    11,    12,    13,    14,    37,    44,    57,    60,
      61,    62,    63,    64,    65,    67,    68,    69,    70,    37,
      41,    41,    60,    41,     1,    37,    70,    71,     1,    17,
      70,    37,     1,    70,     1,    70,     9,     1,    66,    70,
      37,    37,    37,    37,    37,    42,    42,    42,    42,    41,
      37,    37,    60,    60,    60,    60,     1,    70,     1,    66,
       1,    66,     8,     8,    42,    42,    37,    37,    37,    37,
      60,    60,     1,    66,     1,    66,     1,    66,     1,    66,
      42,    42,    42,    42,    42,    42,    42,    42,    60,    60,
      60,    60,    60,    60,    60,    60
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 37 "tree.y"
    {
  ast_node t = create_ast_node(ROOT, lineNumber);
  t->left_child = (yyvsp[(1) - (1)]);
  (yyval) = t;
  root = (yyval);}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 44 "tree.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 45 "tree.y"
    {
  ast_node t = (yyvsp[(1) - (2)]);
    while (t->right_sibling != NULL)
      t = t->right_sibling;
    t->right_sibling = (yyvsp[(2) - (2)]);
    (yyval) = (yyvsp[(1) - (2)]);
 }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 54 "tree.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 55 "tree.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 58 "tree.y"
    {
  ast_node t = (yyvsp[(1) - (3)]);
  t->left_child = (yyvsp[(2) - (3)]);
    ast_node vars = (yyvsp[(2) - (3)]);
  do {
	if (vars->node_type == OP_ASSIGN || vars->node_type == ARRAY) 	vars->left_child->type = (yyvsp[(1) - (3)])->type;
	else vars->type = (yyvsp[(1) - (3)])->type;
	
	vars = vars->right_sibling;
	}
  while (vars != NULL);
  

  (yyval) = t;
 }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 75 "tree.y"
    {(yyval) = create_ast_node(INT_TYPE, lineNumber);
	(yyval)->type = Int;}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 77 "tree.y"
    {(yyval) = create_ast_node(DOUBLE_TYPE, lineNumber);
	(yyval)->type = Double;}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 81 "tree.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 82 "tree.y"
    {
  ast_node t = (yyvsp[(1) - (3)]);
  if (t != NULL) {
    while (t->right_sibling != NULL)
      t = t->right_sibling;
    t->right_sibling = (yyvsp[(3) - (3)]);
    (yyval) = (yyvsp[(1) - (3)]);
  }
  else 
    (yyval) = NULL;
 }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 95 "tree.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 96 "tree.y"
    { 
  (yyval) = create_ast_node(OP_ASSIGN, lineNumber);
  (yyval)->left_child = (yyvsp[(1) - (3)]);
  (yyval)->left_child->right_sibling = (yyvsp[(3) - (3)]);
  }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 101 "tree.y"
    {
  (yyval) = create_ast_node(ARRAY, lineNumber);
  (yyval)->left_child = (yyvsp[(1) - (4)]);
  (yyval)->left_child->right_sibling = (yyvsp[(3) - (4)]);
  }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 108 "tree.y"
    {
  ast_node t = create_ast_node(FUNCDEC, lineNumber);
  t->type = (yyvsp[(1) - (6)])->type;
  ast_node current = (yyvsp[(1) - (6)]);
  t->left_child = current;
  current->right_sibling = (yyvsp[(2) - (6)]);
  current = (yyvsp[(2) - (6)]);
  
  if ((yyvsp[(4) - (6)]) != NULL){
    current->right_sibling = (yyvsp[(4) - (6)]);
    current = (yyvsp[(4) - (6)]);
    
    while (current->right_sibling != NULL) current=current->right_sibling;
    current->right_sibling = (yyvsp[(6) - (6)]);
  }
  else current->right_sibling = (yyvsp[(6) - (6)]);
  
  (yyval) = t;
 }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 127 "tree.y"
    {
  ast_node t = create_ast_node(FUNCDEC, lineNumber); 
  ast_node current = create_ast_node(VOID_TYPE, lineNumber); 
  t->left_child = current; 
  current->right_sibling = (yyvsp[(2) - (6)]); 
  current = (yyvsp[(2) - (6)]); 

  if ((yyvsp[(4) - (6)]) != NULL){
    current->right_sibling = (yyvsp[(4) - (6)]); 
    current = (yyvsp[(4) - (6)]); 

    while (current->right_sibling != NULL) current=current->right_sibling;
    current->right_sibling = (yyvsp[(6) - (6)]);
  }
  else current->right_sibling = (yyvsp[(6) - (6)]); 

  (yyval) = t; 
 }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 146 "tree.y"
    {
	ast_node a = create_ast_node(PARAMS, lineNumber);
	a->left_child= (yyvsp[(1) - (1)]);
	(yyval) = a;}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 150 "tree.y"
    {(yyval) = NULL;}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 151 "tree.y"
    {(yyval) = create_ast_node(PARAMS, lineNumber);}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 154 "tree.y"
    { 
	/*ast_node params = create_ast_node(PARAMS, lineNumber);
	params->left_child = $1;
	$$ = params;*/
	(yyval) = (yyvsp[(1) - (1)]);
	}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 160 "tree.y"
    {
  /*ast_node params = create_ast_node(PARAMS, lineNumber);*/
  ast_node t = (yyvsp[(1) - (3)]);
  if (t != NULL) {
    while (t->right_sibling != NULL)
      t = t->right_sibling;
    t->right_sibling = (yyvsp[(3) - (3)]);
    /*params->left_child = t;*/
    (yyval) = t;
  }
 }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 174 "tree.y"
    {
  /*  ast_node t = create_ast_node(PARAM, lineNumber);*/
  (yyval) = (yyvsp[(1) - (2)]);
  (yyval)->left_child = (yyvsp[(2) - (2)]);
  (yyval)->left_child->type = (yyval)->type;
  /*$$ = t;*/
 }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 181 "tree.y"
    { 
  ast_node t = (yyvsp[(1) - (4)]);
  ast_node array = create_ast_node(ARRAY, lineNumber);
  t->left_child = array;
  t->left_child->left_child = (yyvsp[(2) - (4)]);
  t->left_child->left_child->type = t->type;
  (yyval) = t;
 }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 191 "tree.y"
    {
  ast_node t = create_ast_node(CMPD, lineNumber);
  if ((yyvsp[(2) - (4)]) == NULL)
    t->left_child = (yyvsp[(3) - (4)]);
  else {
    t->left_child = (yyvsp[(2) - (4)]);
    ast_node current = (yyvsp[(2) - (4)]);
    while (current->right_sibling != NULL)
      current = current->right_sibling;
    current->right_sibling = (yyvsp[(3) - (4)]);
  }
  (yyval) = t;
 }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 206 "tree.y"
    {
  ast_node t = (yyvsp[(1) - (2)]);
  if (t != NULL) {
    while (t->right_sibling != NULL)
      t = t->right_sibling;
    t->right_sibling = (yyvsp[(2) - (2)]);
    (yyval) = (yyvsp[(1) - (2)]);
  }
  else
    (yyval) = (yyvsp[(2) - (2)]);
 }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 217 "tree.y"
    {(yyval) = NULL;}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 220 "tree.y"
    {
  ast_node t = (yyvsp[(1) - (2)]);
  if (t != NULL) {
    while (t->right_sibling != NULL)
      t = t->right_sibling;
    t->right_sibling = (yyvsp[(2) - (2)]);
    (yyval) = (yyvsp[(1) - (2)]);
  }
  else 
    (yyval) = (yyvsp[(2) - (2)]);
 }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 232 "tree.y"
    {(yyval) = NULL;}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 235 "tree.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 236 "tree.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 237 "tree.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 238 "tree.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 239 "tree.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 240 "tree.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 241 "tree.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 242 "tree.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 243 "tree.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 246 "tree.y"
    { (yyval) = (yyvsp[(1) - (2)]); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 247 "tree.y"
    { (yyval) = NULL; }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 248 "tree.y"
    { (yyval) = NULL; }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 251 "tree.y"
    {
  ast_node t = create_ast_node(IF_STMT, lineNumber);
  t->left_child = (yyvsp[(3) - (5)]);
  t->left_child->right_sibling = (yyvsp[(5) - (5)]);
  (yyval) = t; }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 256 "tree.y"
    {
  ast_node t = create_ast_node(IF_ELSE_STMT, lineNumber);
  t->left_child = (yyvsp[(3) - (7)]);
  t->left_child->right_sibling = (yyvsp[(5) - (7)]);
  t->left_child->right_sibling->right_sibling = (yyvsp[(7) - (7)]);
  (yyval) = t; }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 262 "tree.y"
    { (yyval) = NULL; }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 263 "tree.y"
    { (yyval) = NULL; }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 266 "tree.y"
    {
  ast_node t = create_ast_node(WHILE_STMT, lineNumber);
  t->left_child = (yyvsp[(3) - (5)]);
  t->left_child->right_sibling = (yyvsp[(5) - (5)]);
  (yyval) = t;
 }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 272 "tree.y"
    { (yyval) = NULL; }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 275 "tree.y"
    {
  ast_node t = create_ast_node(DO_WHILE_STMT, lineNumber);
  t->left_child = (yyvsp[(2) - (6)]);
  ast_node rightmost = t->left_child;
  while (rightmost->right_sibling != NULL)
    rightmost= rightmost->right_sibling;
  rightmost->right_sibling = (yyvsp[(5) - (6)]);
  (yyval) = t;
 }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 284 "tree.y"
    { (yyval) = NULL;}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 287 "tree.y"
    {
  ast_node t = create_ast_node(FOR_STMT, lineNumber);
  /*ast_node leftmost = $9;
  ast_node temp;
  if ($7 != NULL){
    leftmost = $7;
    leftmost->right_sibling = $9;
  }
  
  if ($5 != NULL){
    temp = leftmost;
    leftmost = $5;
    leftmost->right_sibling = temp;
  }
  
  if ($3 != NULL){
    temp = leftmost;
    leftmost = $3;
    leftmost->right_sibling = temp;
  }
  
  t->left_child = leftmost;
  */
  ast_node start = create_ast_node(FOR_STRT, lineNumber);
  ast_node cond  = create_ast_node(FOR_COND, lineNumber);
  ast_node update= create_ast_node(FOR_UPDT, lineNumber);
  
  start->left_child  = (yyvsp[(3) - (9)]);
  cond->left_child   = (yyvsp[(5) - (9)]);
  update->left_child = (yyvsp[(7) - (9)]);
  
  t->left_child = start;
  t->left_child->right_sibling = cond;
  t->left_child->right_sibling->right_sibling = update;
  t->left_child->right_sibling->right_sibling->right_sibling = (yyvsp[(9) - (9)]);
  
  (yyval) = t;
 }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 325 "tree.y"
    { (yyval) = NULL;}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 326 "tree.y"
    { (yyval) = NULL;}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 327 "tree.y"
    { (yyval) = NULL;}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 328 "tree.y"
    { (yyval) = NULL;}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 329 "tree.y"
    { (yyval) = NULL;}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 330 "tree.y"
    { (yyval) = NULL;}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 331 "tree.y"
    { (yyval) = NULL;}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 335 "tree.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 336 "tree.y"
    {(yyval) = NULL;}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 339 "tree.y"
    {(yyval) = create_ast_node(RETURN_STMT, lineNumber);}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 340 "tree.y"
    {
  (yyval) = create_ast_node(RETURN_STMT, lineNumber);
  (yyval)->left_child = (yyvsp[(2) - (3)]);
 }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 345 "tree.y"
    { (yyval) = NULL; }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 348 "tree.y"
    { 
  (yyval) = create_ast_node(READ_STMT, lineNumber);
  (yyval)->left_child = (yyvsp[(2) - (2)]);
 }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 354 "tree.y"
    { 
  (yyval) = create_ast_node(PRINT_STMT, lineNumber);
  (yyval)->left_child = (yyvsp[(2) - (3)]);
 }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 358 "tree.y"
    {
  (yyval) = create_ast_node(PRINT_STMT, lineNumber);
  ast_node t = create_ast_node(STRING_LIT, lineNumber);
  t->value.string = strdup(savedLiteralText);
  (yyval)->left_child = t;
 }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 364 "tree.y"
    {(yyval) = NULL;}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 367 "tree.y"
    {
  ast_node t = create_ast_node(OP_ASSIGN, lineNumber);
  t->left_child = (yyvsp[(1) - (3)]);
  t->left_child->right_sibling = (yyvsp[(3) - (3)]);
  (yyval) = t;}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 372 "tree.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 375 "tree.y"
    { (yyval) = (yyvsp[(1) - (1)]);  }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 376 "tree.y"
    {
  ast_node t = create_ast_node(ARRAY, lineNumber);
  t->left_child = (yyvsp[(1) - (4)]);
  t->left_child->right_sibling = (yyvsp[(3) - (4)]);
  (yyval) = t;
}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 382 "tree.y"
    { (yyval) = NULL;}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 385 "tree.y"
    {
  ast_node t = create_ast_node(OP_PLUS, lineNumber);
  t->left_child = (yyvsp[(1) - (3)]);
  t->left_child->right_sibling = (yyvsp[(3) - (3)]);
  (yyval) = t;
 }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 391 "tree.y"
    {
  ast_node t = create_ast_node(OP_MINUS, lineNumber);
  t->left_child = (yyvsp[(1) - (3)]);
  t->left_child->right_sibling = (yyvsp[(3) - (3)]);
  (yyval) = t;
  }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 397 "tree.y"
    {
  ast_node t = create_ast_node(OP_TIMES, lineNumber);
  t->left_child = (yyvsp[(1) - (3)]);
  t->left_child->right_sibling = (yyvsp[(3) - (3)]);
  (yyval) = t;
  }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 403 "tree.y"
    {
  ast_node t = create_ast_node(OP_DIVIDE, lineNumber);
  t->left_child = (yyvsp[(1) - (3)]);
  t->left_child->right_sibling = (yyvsp[(3) - (3)]);
  (yyval) = t;
  }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 409 "tree.y"
    {
  ast_node t = create_ast_node(OP_MOD, lineNumber);
  t->left_child = (yyvsp[(1) - (3)]);
  t->left_child->right_sibling = (yyvsp[(3) - (3)]);
  (yyval) = t;
  }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 415 "tree.y"
    {
  ast_node t = create_ast_node(OP_LT, lineNumber);
  t->left_child = (yyvsp[(1) - (3)]);
  t->left_child->right_sibling = (yyvsp[(3) - (3)]);
  t->type = Int;
  (yyval) = t;
  }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 422 "tree.y"
    {
  ast_node t = create_ast_node(OP_LEQ, lineNumber);
  t->left_child = (yyvsp[(1) - (3)]);
  t->left_child->right_sibling = (yyvsp[(3) - (3)]);
  t->type = Int;
  (yyval) = t;
  }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 429 "tree.y"
    {
  ast_node t = create_ast_node(OP_GT, lineNumber);
  t->left_child = (yyvsp[(1) - (3)]);
  t->left_child->right_sibling = (yyvsp[(3) - (3)]);
  t->type = Int;
  (yyval) = t;
  }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 436 "tree.y"
    {
  ast_node t = create_ast_node(OP_GEQ, lineNumber);
  t->left_child = (yyvsp[(1) - (3)]);
  t->left_child->right_sibling = (yyvsp[(3) - (3)]);
  t->type = Int;
  (yyval) = t;
  }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 443 "tree.y"
    {
  ast_node t = create_ast_node(OP_EQUALS, lineNumber);
  t->left_child = (yyvsp[(1) - (3)]);
  t->type = Int;
  t->left_child->right_sibling = (yyvsp[(3) - (3)]);
  (yyval) = t;
  }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 450 "tree.y"
    {
  ast_node t = create_ast_node(OP_NEQUALS, lineNumber);
  t->left_child = (yyvsp[(1) - (3)]);
  t->left_child->right_sibling = (yyvsp[(3) - (3)]);
  t->type = Int;
  (yyval) = t;
  }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 457 "tree.y"
    {
  ast_node t = create_ast_node(OP_AND, lineNumber);
  t->left_child = (yyvsp[(1) - (3)]);
  t->left_child->right_sibling = (yyvsp[(3) - (3)]);
  t->type = Int;
  (yyval) = t;
  }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 464 "tree.y"
    {
  ast_node t = create_ast_node(OP_OR, lineNumber);
  t->left_child = (yyvsp[(1) - (3)]);
  t->left_child->right_sibling = (yyvsp[(3) - (3)]);
  t->type = Int;
  (yyval) = t;
  }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 471 "tree.y"
    {
  ast_node t = create_ast_node(OP_NOT, lineNumber);
  t->left_child = (yyvsp[(2) - (2)]);
  t->type = Int;
  (yyval) = t;
  }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 477 "tree.y"
    {
  ast_node t = create_ast_node(OP_NEG, lineNumber);
  t->left_child = (yyvsp[(2) - (2)]);
  (yyval) = t;
  }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 482 "tree.y"
    { (yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 483 "tree.y"
    {
  ast_node t = create_ast_node(OP_INC, lineNumber);
  t->left_child = (yyvsp[(2) - (2)]);
  (yyval) = t;
  }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 488 "tree.y"
    {
  ast_node t = create_ast_node(OP_DEC, lineNumber);
  t->left_child = (yyvsp[(2) - (2)]);
  (yyval) = t;
  }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 493 "tree.y"
    {(yyval) = (yyvsp[(2) - (3)]);}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 494 "tree.y"
    { (yyval) = NULL;}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 495 "tree.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 496 "tree.y"
    {
  ast_node t = create_ast_node(INT_LITERAL, lineNumber);
  t->value.int_value = atoi(yytext);
  t->type = Int;
  (yyval) = t;
  }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 502 "tree.y"
    {
  ast_node t = create_ast_node(DOUBLE_LITERAL, lineNumber);
  t->value.double_value = atof(yytext);
  t->type = Double;
  (yyval) = t;
  }
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 510 "tree.y"
    {
  ast_node t = create_ast_node(CALL, lineNumber);
  t->left_child = (yyvsp[(1) - (4)]);
  t->left_child->right_sibling = (yyvsp[(3) - (4)]);
  (yyval) = t;
 }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 517 "tree.y"
    { 
	ast_node a = create_ast_node(ARGS, lineNumber);
	a->left_child = (yyvsp[(1) - (1)]);
	(yyval) = a;
	}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 522 "tree.y"
    { (yyval) = create_ast_node(ARGS, lineNumber) ; }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 525 "tree.y"
    {
  ast_node t = (yyvsp[(1) - (3)]);
  if (t != NULL) {
    while (t->right_sibling != NULL)
      t = t->right_sibling;
    t->right_sibling = (yyvsp[(3) - (3)]);
    (yyval) = (yyvsp[(1) - (3)]);
  }
  else
    (yyval) = NULL;
  
 }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 537 "tree.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 541 "tree.y"
    { 
  ast_node t = create_ast_node(IDENT, lineNumber);
  char* buffer;
  buffer = lookup(symbol_table, yytext);
  if (buffer != NULL)
    t->value.string = buffer;
  else 
    t->value.string =  add_id(symbol_table, yytext); 
  (yyval) = t;
 }
    break;


/* Line 1792 of yacc.c  */
#line 2582 "tree.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
		      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 552 "tree.y"


int yyerror(char *s){
  parseError = 1; 
  fprintf(stderr, "%s at line %d\n", s, lineNumber); 
  return 0; 
}  

