/* A Bison parser, made from parser.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	STRING	257
# define	NOMASK	258
# define	NIL	259
# define	BREAK	260
# define	ELSE	261
# define	CASE	262
# define	WHILE	263
# define	DEFAULT	264
# define	STATIC	265
# define	CONTINUE	266
# define	INT	267
# define	RLIMITS	268
# define	FLOAT	269
# define	FOR	270
# define	INHERIT	271
# define	VOID	272
# define	IF	273
# define	CATCH	274
# define	SWITCH	275
# define	VARARGS	276
# define	MAPPING	277
# define	PRIVATE	278
# define	DO	279
# define	RETURN	280
# define	ATOMIC	281
# define	MIXED	282
# define	OBJECT	283
# define	LARROW	284
# define	RARROW	285
# define	PLUS_PLUS	286
# define	MIN_MIN	287
# define	LSHIFT	288
# define	RSHIFT	289
# define	LE	290
# define	GE	291
# define	EQ	292
# define	NE	293
# define	LAND	294
# define	LOR	295
# define	PLUS_EQ	296
# define	MIN_EQ	297
# define	MULT_EQ	298
# define	DIV_EQ	299
# define	MOD_EQ	300
# define	LSHIFT_EQ	301
# define	RSHIFT_EQ	302
# define	AND_EQ	303
# define	XOR_EQ	304
# define	OR_EQ	305
# define	COLON_COLON	306
# define	DOT_DOT	307
# define	ELLIPSIS	308
# define	STRING_CONST	309
# define	IDENTIFIER	310
# define	INT_CONST	311
# define	FLOAT_CONST	312
# define	MARK	313
# define	HASH	314
# define	HASH_HASH	315
# define	INCL_CONST	316
# define	NR_TOKENS	317

#line 7 "parser.y"


# define INCLUDE_CTYPE
# include "comp.h"
# include "str.h"
# include "array.h"
# include "object.h"
# include "xfloat.h"
# include "interpret.h"
# include "macro.h"
# include "token.h"
# include "ppcontrol.h"
# include "node.h"
# include "compile.h"

# define yylex		pp_gettok
# define yyerror	c_error

int nerrors;			/* number of errors encountered so far */
static int ndeclarations;	/* number of declarations */
static int nstatements;		/* number of statements in current function */
static bool typechecking;	/* does the current function have it? */

static void  t_void	P((node*));
static bool  t_unary	P((node*, char*));
static node *uassign	P((int, node*, char*));
static node *cast	P((node*, node*));
static node *idx	P((node*, node*));
static node *range	P((node*, node*, node*));
static node *bini	P((int, node*, node*, char*));
static node *bina	P((int, node*, node*, char*));
static node *mult	P((int, node*, node*, char*));
static node *mdiv	P((int, node*, node*, char*));
static node *mod	P((int, node*, node*, char*));
static node *add	P((int, node*, node*, char*));
static node *sub	P((int, node*, node*, char*));
static node *umin	P((node*));
static node *lshift	P((int, node*, node*, char*));
static node *rshift	P((int, node*, node*, char*));
static node *rel	P((int, node*, node*, char*));
static node *eq		P((node*, node*));
static node *and	P((int, node*, node*, char*));
static node *xor	P((int, node*, node*, char*));
static node *or		P((int, node*, node*, char*));
static node *land	P((node*, node*));
static node *lor	P((node*, node*));
static node *quest	P((node*, node*, node*));
static node *assign	P((node*, node*));
static node *comma	P((node*, node*));


#line 74 "parser.y"
#ifndef YYSTYPE
typedef union {
    Int number;			/* lex input */
    xfloat real;		/* lex input */
    unsigned short type;	/* internal */
    struct _node_ *node;	/* internal */
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		333
#define	YYFLAG		-32768
#define	YYNTBASE	87

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 317 ? yytranslate[x] : 159)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    76,     2,     2,     2,    79,    82,     2,
      66,    67,    69,    65,    68,    75,     2,    78,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    70,    64,
      80,    86,    81,    85,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    73,     2,    74,    83,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    71,    84,    72,    77,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     5,     8,    14,    16,    18,    19,
      21,    23,    25,    29,    33,    35,    40,    41,    47,    48,
      56,    61,    62,    64,    66,    69,    71,    75,    78,    80,
      83,    85,    87,    89,    92,    94,    97,    99,   101,   102,
     104,   106,   108,   110,   112,   114,   116,   118,   120,   123,
     125,   127,   129,   130,   133,   136,   142,   144,   146,   148,
     152,   153,   156,   158,   160,   163,   166,   168,   174,   182,
     183,   192,   193,   200,   201,   212,   213,   222,   223,   224,
     230,   231,   238,   239,   245,   246,   254,   255,   260,   263,
     266,   270,   272,   273,   278,   279,   282,   284,   287,   291,
     293,   295,   297,   299,   305,   311,   313,   317,   322,   327,
     334,   338,   344,   346,   351,   358,   360,   363,   366,   368,
     371,   374,   377,   380,   383,   386,   388,   394,   396,   400,
     404,   408,   410,   414,   418,   420,   424,   428,   430,   434,
     438,   442,   446,   448,   452,   456,   458,   462,   464,   468,
     470,   474,   476,   480,   482,   486,   488,   494,   496,   500,
     504,   508,   512,   516,   520,   524,   528,   532,   536,   540,
     542,   546,   547,   549,   551,   553,   555,   559,   560,   562,
     565,   566,   568,   571,   575,   577,   581,   582,   584
};
static const short yyrhs[] =
{
      -1,    88,    89,     0,     0,    89,    90,     0,   107,    17,
      91,    93,    64,     0,    95,     0,    96,     0,     0,    92,
       0,    56,     0,    94,     0,    93,    65,    94,     0,    66,
      93,    67,     0,    55,     0,   104,   109,   114,    64,     0,
       0,   104,   109,   112,    97,   128,     0,     0,   104,    92,
      66,   100,    67,    98,   128,     0,   104,   109,   114,    64,
       0,     0,    18,     0,   101,     0,   101,    54,     0,   102,
       0,   101,    68,   102,     0,    22,   103,     0,   103,     0,
     109,   111,     0,    92,     0,   107,     0,   108,     0,   106,
     105,     0,   106,     0,   105,   106,     0,    24,     0,   108,
       0,     0,    24,     0,    11,     0,    27,     0,     4,     0,
      22,     0,    13,     0,    15,     0,     3,     0,    29,     0,
      29,    93,     0,    23,     0,    28,     0,    18,     0,     0,
     110,    69,     0,   110,    92,     0,   110,    92,    66,   100,
      67,     0,   111,     0,   112,     0,   113,     0,   114,    68,
     113,     0,     0,   115,   116,     0,    99,     0,   117,     0,
       1,    64,     0,   149,    64,     0,   128,     0,    19,    66,
     151,    67,   117,     0,    19,    66,   151,    67,   117,     7,
     117,     0,     0,    25,   118,   117,     9,    66,   151,    67,
      64,     0,     0,     9,    66,   151,    67,   119,   117,     0,
       0,    16,    66,   150,    64,   152,    64,   150,    67,   120,
     117,     0,     0,    14,    66,   151,    64,   151,    67,   121,
     128,     0,     0,     0,    20,   122,   128,   123,   130,     0,
       0,    21,    66,   151,    67,   124,   128,     0,     0,     8,
     148,    70,   125,   117,     0,     0,     8,   148,    53,   148,
      70,   126,   117,     0,     0,    10,    70,   127,   117,     0,
       6,    64,     0,    12,    64,     0,    26,   152,    64,     0,
      64,     0,     0,    71,   129,   115,    72,     0,     0,    70,
     117,     0,    92,     0,    52,    92,     0,    92,    52,    92,
       0,    57,     0,    58,     0,     5,     0,    94,     0,    66,
      71,   155,    72,    67,     0,    66,    73,   158,    74,    67,
       0,    92,     0,    66,   149,    67,     0,   131,    66,   154,
      67,     0,    20,    66,   149,    67,     0,   133,    31,    92,
      66,   154,    67,     0,   133,    30,    94,     0,   133,    30,
      66,    93,    67,     0,   132,     0,   133,    73,   151,    74,
       0,   133,    73,   152,    53,   152,    74,     0,   133,     0,
     134,    32,     0,   134,    33,     0,   134,     0,    32,   136,
       0,    33,   136,     0,    75,   136,     0,    65,   136,     0,
      76,   136,     0,    77,   136,     0,   135,     0,    66,   109,
     110,    67,   136,     0,   136,     0,   137,    69,   136,     0,
     137,    78,   136,     0,   137,    79,   136,     0,   137,     0,
     138,    65,   137,     0,   138,    75,   137,     0,   138,     0,
     139,    34,   138,     0,   139,    35,   138,     0,   139,     0,
     140,    80,   139,     0,   140,    81,   139,     0,   140,    36,
     139,     0,   140,    37,   139,     0,   140,     0,   141,    38,
     140,     0,   141,    39,   140,     0,   141,     0,   142,    82,
     141,     0,   142,     0,   143,    83,   142,     0,   143,     0,
     144,    84,   143,     0,   144,     0,   145,    40,   144,     0,
     145,     0,   146,    41,   145,     0,   146,     0,   146,    85,
     149,    70,   147,     0,   147,     0,   147,    86,   148,     0,
     147,    42,   148,     0,   147,    43,   148,     0,   147,    44,
     148,     0,   147,    45,   148,     0,   147,    46,   148,     0,
     147,    47,   148,     0,   147,    48,   148,     0,   147,    49,
     148,     0,   147,    50,   148,     0,   147,    51,   148,     0,
     148,     0,   149,    68,   148,     0,     0,   149,     0,   149,
       0,   150,     0,   148,     0,   153,    68,   148,     0,     0,
     153,     0,   153,    54,     0,     0,   153,     0,   153,    68,
       0,   148,    70,   148,     0,   156,     0,   157,    68,   156,
       0,     0,   157,     0,   157,    68,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   112,   112,   125,   126,   135,   148,   150,   155,   157,
     161,   166,   167,   169,   174,   179,   184,   184,   195,   195,
     211,   216,   218,   219,   220,   228,   229,   234,   239,   243,
     249,   256,   257,   258,   263,   264,   269,   271,   275,   277,
     282,   284,   286,   288,   293,   294,   295,   297,   299,   301,
     303,   304,   308,   310,   320,   328,   333,   334,   338,   339,
     344,   346,   351,   358,   362,   372,   374,   375,   378,   380,
     380,   383,   383,   386,   386,   389,   389,   407,   407,   407,
     412,   412,   416,   416,   426,   426,   436,   436,   446,   450,
     454,   456,   460,   460,   472,   474,   479,   480,   482,   487,
     489,   491,   492,   493,   495,   497,   514,   516,   518,   520,
     525,   527,   532,   533,   535,   540,   541,   543,   548,   549,
     551,   553,   555,   557,   562,   579,   580,   588,   589,   591,
     593,   598,   599,   601,   606,   607,   609,   614,   615,   617,
     619,   621,   626,   627,   629,   634,   635,   640,   641,   646,
     647,   652,   653,   658,   659,   664,   665,   670,   671,   673,
     675,   677,   679,   681,   683,   685,   687,   689,   691,   696,
     697,   702,   704,   708,   713,   718,   719,   727,   729,   730,
     742,   744,   745,   750,   759,   760,   765,   767,   768
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "STRING", "NOMASK", "NIL", "BREAK", "ELSE", 
  "CASE", "WHILE", "DEFAULT", "STATIC", "CONTINUE", "INT", "RLIMITS", 
  "FLOAT", "FOR", "INHERIT", "VOID", "IF", "CATCH", "SWITCH", "VARARGS", 
  "MAPPING", "PRIVATE", "DO", "RETURN", "ATOMIC", "MIXED", "OBJECT", 
  "LARROW", "RARROW", "PLUS_PLUS", "MIN_MIN", "LSHIFT", "RSHIFT", "LE", 
  "GE", "EQ", "NE", "LAND", "LOR", "PLUS_EQ", "MIN_EQ", "MULT_EQ", 
  "DIV_EQ", "MOD_EQ", "LSHIFT_EQ", "RSHIFT_EQ", "AND_EQ", "XOR_EQ", 
  "OR_EQ", "COLON_COLON", "DOT_DOT", "ELLIPSIS", "STRING_CONST", 
  "IDENTIFIER", "INT_CONST", "FLOAT_CONST", "MARK", "HASH", "HASH_HASH", 
  "INCL_CONST", "NR_TOKENS", "';'", "'+'", "'('", "')'", "','", "'*'", 
  "':'", "'{'", "'}'", "'['", "']'", "'-'", "'!'", "'~'", "'/'", "'%'", 
  "'<'", "'>'", "'&'", "'^'", "'|'", "'?'", "'='", "program", "@1", 
  "top_level_declarations", "top_level_declaration", "opt_inherit_label", 
  "ident", "composite_string", "string", "data_declaration", 
  "function_declaration", "@2", "@3", "local_data_declaration", 
  "formals_declaration", "formal_declaration_list", 
  "varargs_formal_declaration", "formal_declaration", 
  "class_specifier_list", "class_specifier_list2", "class_specifier", 
  "opt_private", "non_private", "type_specifier", "star_list", 
  "data_dcltr", "function_dcltr", "dcltr", "list_dcltr", 
  "dcltr_or_stmt_list", "dcltr_or_stmt", "stmt", "@4", "@5", "@6", "@7", 
  "@8", "@9", "@10", "@11", "@12", "@13", "compound_stmt", "@14", 
  "opt_caught_stmt", "function_name", "primary_p1_exp", "primary_p2_exp", 
  "postfix_exp", "prefix_exp", "cast_exp", "mult_oper_exp", 
  "add_oper_exp", "shift_oper_exp", "rel_oper_exp", "equ_oper_exp", 
  "bitand_oper_exp", "bitxor_oper_exp", "bitor_oper_exp", "and_oper_exp", 
  "or_oper_exp", "cond_exp", "exp", "list_exp", "opt_list_exp", 
  "f_list_exp", "f_opt_list_exp", "arg_list", "opt_arg_list", 
  "opt_arg_list_comma", "assoc_exp", "assoc_arg_list", 
  "opt_assoc_arg_list_comma", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    88,    87,    89,    89,    90,    90,    90,    91,    91,
      92,    93,    93,    93,    94,    95,    97,    96,    98,    96,
      99,   100,   100,   100,   100,   101,   101,   102,   102,   103,
     103,   104,   104,   104,   105,   105,   106,   106,   107,   107,
     108,   108,   108,   108,   109,   109,   109,   109,   109,   109,
     109,   109,   110,   110,   111,   112,   113,   113,   114,   114,
     115,   115,   116,   116,   116,   117,   117,   117,   117,   118,
     117,   119,   117,   120,   117,   121,   117,   122,   123,   117,
     124,   117,   125,   117,   126,   117,   127,   117,   117,   117,
     117,   117,   129,   128,   130,   130,   131,   131,   131,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   133,   133,   133,   134,   134,   134,   135,   135,
     135,   135,   135,   135,   135,   136,   136,   137,   137,   137,
     137,   138,   138,   138,   139,   139,   139,   140,   140,   140,
     140,   140,   141,   141,   141,   142,   142,   143,   143,   144,
     144,   145,   145,   146,   146,   147,   147,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   149,
     149,   150,   150,   151,   152,   153,   153,   154,   154,   154,
     155,   155,   155,   156,   157,   157,   158,   158,   158
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     0,     2,     5,     1,     1,     0,     1,
       1,     1,     3,     3,     1,     4,     0,     5,     0,     7,
       4,     0,     1,     1,     2,     1,     3,     2,     1,     2,
       1,     1,     1,     2,     1,     2,     1,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     0,     2,     2,     5,     1,     1,     1,     3,
       0,     2,     1,     1,     2,     2,     1,     5,     7,     0,
       8,     0,     6,     0,    10,     0,     8,     0,     0,     5,
       0,     6,     0,     5,     0,     7,     0,     4,     2,     2,
       3,     1,     0,     4,     0,     2,     1,     2,     3,     1,
       1,     1,     1,     5,     5,     1,     3,     4,     4,     6,
       3,     5,     1,     4,     6,     1,     2,     2,     1,     2,
       2,     2,     2,     2,     2,     1,     5,     1,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     5,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     0,     1,     1,     1,     1,     3,     0,     1,     2,
       0,     1,     2,     3,     1,     3,     0,     1,     2
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     3,    38,    42,    40,    43,    39,    41,     4,     6,
       7,     0,     0,    31,    32,    46,    44,    45,    51,    49,
      50,    47,    10,     0,    52,    36,    33,    34,    37,     8,
      14,     0,    48,    11,    21,     0,    56,    57,    58,     0,
      35,     0,     9,     0,     0,    51,     0,    30,     0,    23,
      25,    28,    52,    53,    54,     0,    15,    52,     0,    13,
      12,    27,    18,    24,     0,     0,    29,    21,    92,    17,
      57,    59,     5,     0,    26,    54,     0,    60,    19,    55,
       0,     0,   101,     0,     0,     0,     0,     0,     0,     0,
       0,    77,     0,    69,   171,     0,     0,     0,    99,   100,
      91,     0,     0,    93,     0,     0,     0,   105,   102,    62,
       0,    31,    61,    63,    66,     0,   112,   115,   118,   125,
     127,   131,   134,   137,   142,   145,   147,   149,   151,   153,
     155,   157,   169,     0,    64,    88,     0,     0,     0,    86,
      89,     0,   171,     0,     0,     0,     0,     0,   172,   174,
       0,   119,   120,    97,   122,   180,   186,    52,     0,   121,
     123,   124,     0,    52,   177,     0,     0,   171,   116,   117,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      65,     0,     0,    82,   173,     0,     0,     0,     0,     0,
       0,    78,     0,     0,    90,   175,   181,     0,     0,   184,
     187,     0,     0,   106,    98,     0,   178,     0,     0,   110,
       0,   172,     0,     0,   128,   129,   130,   132,   133,   135,
     136,   140,   141,   138,   139,   143,   144,   146,   148,   150,
     152,   154,     0,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   158,   170,     0,     0,    71,    87,     0,
     171,     0,   108,    94,    80,     0,   182,     0,     0,   188,
       0,     0,    20,   179,     0,   107,     0,   177,   113,   171,
       0,    84,    83,     0,     0,     0,    67,     0,    79,     0,
       0,   176,   103,   183,   185,   104,   126,   111,     0,     0,
     156,     0,    72,    75,   171,     0,    95,    81,     0,   109,
     114,    85,     0,     0,    68,     0,    76,    73,    70,     0,
      74,     0,     0,     0
};

static const short yydefgoto[] =
{
     331,     1,     2,     8,    41,   107,    32,   108,     9,    10,
      55,    73,   109,    48,    49,    50,    51,    11,    26,    12,
      13,    14,    52,    35,    36,    70,    38,    39,    80,   112,
     113,   147,   293,   329,   322,   145,   273,   299,   266,   311,
     206,   114,    77,   298,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   149,   205,   150,   226,   227,   217,   219,
     220,   221
};

static const short yypact[] =
{
  -32768,-32768,   133,-32768,-32768,-32768,    20,-32768,-32768,-32768,
  -32768,   417,    48,    49,    56,-32768,-32768,-32768,-32768,-32768,
  -32768,     3,-32768,   -20,-32768,-32768,    48,-32768,-32768,    51,
  -32768,     3,    16,-32768,   125,   -39,-32768,    13,-32768,    40,
  -32768,     3,-32768,   -26,    42,    62,   417,-32768,    72,     0,
  -32768,-32768,-32768,-32768,    76,    94,-32768,-32768,    86,-32768,
  -32768,-32768,-32768,-32768,   377,   -39,-32768,   125,-32768,-32768,
  -32768,-32768,-32768,    94,-32768,-32768,   102,-32768,-32768,-32768,
     214,   109,-32768,   116,   263,   121,   112,   128,   132,   136,
     140,   147,   148,-32768,   263,   263,   263,    51,-32768,-32768,
  -32768,   263,   279,-32768,   263,   263,   263,    30,-32768,-32768,
     373,-32768,-32768,-32768,-32768,   150,-32768,    -2,   139,-32768,
  -32768,    80,   -32,   144,   -17,   145,   149,   162,   164,   219,
     -30,   207,-32768,    41,-32768,-32768,   147,   -13,   263,-32768,
  -32768,   263,   263,   263,   263,    94,   263,   352,   192,-32768,
     197,-32768,-32768,-32768,-32768,   263,   263,-32768,   118,-32768,
  -32768,-32768,    51,-32768,   263,    33,    51,   263,-32768,-32768,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
  -32768,   263,   263,-32768,   192,   195,   352,   199,   200,   198,
     123,-32768,   206,   265,-32768,-32768,   208,   203,   211,-32768,
     209,   213,    65,-32768,-32768,    67,    25,   221,     3,-32768,
     232,   -53,   226,   248,-32768,-32768,-32768,    80,    80,   -32,
     -32,   144,   144,   144,   144,   -17,   -17,   145,   149,   162,
     164,   219,    19,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,   233,   352,-32768,-32768,   263,
     263,   352,-32768,   234,-32768,   239,   263,   242,   263,   263,
     243,   263,-32768,-32768,   263,-32768,   101,   263,-32768,   263,
     263,-32768,-32768,   352,   246,   250,   299,   352,-32768,    94,
     263,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   249,   251,
  -32768,   352,-32768,-32768,   263,   352,-32768,-32768,   255,-32768,
  -32768,-32768,    94,   256,-32768,   253,-32768,-32768,-32768,   352,
  -32768,   324,   326,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,-32768,    27,   -27,   -19,-32768,-32768,
  -32768,-32768,-32768,   260,-32768,   266,   286,   261,-32768,    74,
     262,   115,    -4,   -36,   281,   319,   289,   184,-32768,-32768,
    -141,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   -55,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   -69,
      21,    28,   -16,    29,   165,   167,   168,   163,   172,-32768,
      73,   -79,   -93,  -139,  -133,  -144,   210,    82,-32768,    88,
  -32768,-32768
};


#define	YYLAST		473


static const short yytable[] =
{
      69,   148,    33,   208,    43,   137,   213,    24,   207,   158,
     209,   187,    33,   212,    58,   201,    65,    22,    78,   177,
     178,  -173,    33,   233,   -36,    60,   151,   152,   165,   166,
      53,   -36,   154,   173,   232,   159,   160,   161,    23,    44,
     202,    59,   -36,   174,   -36,   204,    34,   -36,   204,   148,
     204,   210,     3,   204,    63,   188,    42,   203,    30,     4,
     -37,    47,    54,   179,   180,   268,    29,   -37,    64,    31,
       5,   167,    25,    47,   231,     7,   215,   218,   -37,   283,
     -37,    44,   162,   -37,   -16,   215,    27,   201,    30,   290,
     211,    47,    75,   284,    47,   252,   -96,    30,   157,   228,
      40,   234,   235,   236,    56,   200,   163,    22,    57,   201,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   222,   264,   265,   153,   292,   295,    28,    15,   -22,
     296,   282,   281,    -2,    53,    57,   294,     3,    16,    62,
      17,    28,    67,    45,     4,   309,   229,    46,    19,   170,
      72,    44,   312,    20,    21,     5,   316,     6,   171,   172,
       7,   241,   242,   243,   244,    68,    44,   318,   307,    79,
     321,   168,   169,   134,   324,   323,   204,   148,   175,   176,
     135,    22,   139,   181,   182,   223,   201,   138,   330,   224,
     272,   201,   140,   230,   237,   238,   148,   301,   141,   303,
     218,   286,   142,   239,   240,   301,   143,   204,   215,    33,
     245,   246,   306,   144,   146,    81,   164,   -38,     3,    82,
      83,   148,    84,    85,    86,     4,    87,   -38,    88,   -38,
      89,   183,   -38,    90,    91,    92,     5,   -38,     6,    93,
      94,     7,   -38,   -38,   317,   184,    95,    96,   185,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   186,
     201,   214,   267,   269,   270,   271,    97,   326,    82,    30,
      22,    98,    99,   274,   275,   277,   276,   279,   100,   101,
     102,   278,    15,   136,    82,    68,   103,   280,   285,   104,
     105,   106,    16,   199,    17,    95,    96,    18,   287,   136,
     288,   289,    19,   291,   297,   300,   315,    20,    21,   302,
     305,    95,    96,   313,   314,    97,   319,   328,    30,    22,
      98,    99,   325,   327,   332,   320,   333,    76,   101,   102,
      74,    97,    61,    66,    30,    22,    98,    99,   104,   105,
     106,   110,   111,    37,   101,   102,    71,   225,   247,   250,
     155,   248,   156,   249,   104,   105,   106,    82,    83,   251,
      84,    85,    86,   310,    87,   216,    88,   304,    89,   308,
       0,    90,    91,    92,     0,     0,    15,    93,    94,     0,
      15,     0,     0,     0,    95,    96,    16,     0,    17,     0,
      16,    18,    17,     0,     0,    18,    19,     0,     0,    46,
      19,    20,    21,     0,    97,    20,    21,    30,    22,    98,
      99,     0,     0,     0,     0,     0,   100,   101,   102,     0,
      15,     0,     0,    68,     0,     0,     0,   104,   105,   106,
      16,     0,    17,    22,     0,    18,     0,     0,     0,     0,
      19,     0,     0,     0,     0,    20,    21,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22
};

static const short yycheck[] =
{
      55,    94,    21,   142,    31,    84,   147,    11,   141,   102,
     143,    41,    31,   146,    41,    68,    52,    56,    73,    36,
      37,    74,    41,   167,     4,    44,    95,    96,    30,    31,
      69,    11,   101,    65,   167,   104,   105,   106,    11,    65,
      53,    67,    22,    75,    24,   138,    66,    27,   141,   142,
     143,   144,     4,   146,    54,    85,    29,    70,    55,    11,
       4,    34,    35,    80,    81,   206,    17,    11,    68,    66,
      22,    73,    24,    46,   167,    27,   155,   156,    22,    54,
      24,    65,    52,    27,    71,   164,    12,    68,    55,    70,
     145,    64,    65,    68,    67,   188,    66,    55,   102,    66,
      26,   170,   171,   172,    64,    64,   110,    56,    68,    68,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   157,   201,   202,    97,   266,   270,    12,     3,    67,
     271,    64,    67,     0,    69,    68,   269,     4,    13,    67,
      15,    26,    66,    18,    11,   289,   165,    22,    23,    69,
      64,    65,   293,    28,    29,    22,   297,    24,    78,    79,
      27,   177,   178,   179,   180,    71,    65,   300,    67,    67,
     311,    32,    33,    64,   315,   314,   269,   270,    34,    35,
      64,    56,    70,    38,    39,    67,    68,    66,   329,   162,
      67,    68,    64,   166,   173,   174,   289,   276,    66,   278,
     279,   228,    66,   175,   176,   284,    66,   300,   287,   228,
     181,   182,   281,    66,    66,     1,    66,     3,     4,     5,
       6,   314,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    82,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   299,    83,    32,    33,    84,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    40,
      68,    64,    67,    64,    64,    67,    52,   322,     5,    55,
      56,    57,    58,    67,     9,    72,    68,    68,    64,    65,
      66,    70,     3,    20,     5,    71,    72,    74,    67,    75,
      76,    77,    13,    86,    15,    32,    33,    18,    66,    20,
      74,    53,    23,    70,    70,    66,     7,    28,    29,    67,
      67,    32,    33,    67,    64,    52,    67,    64,    55,    56,
      57,    58,    67,    67,     0,    74,     0,    67,    65,    66,
      64,    52,    46,    52,    55,    56,    57,    58,    75,    76,
      77,    80,    80,    24,    65,    66,    57,   163,   183,   186,
      71,   184,    73,   185,    75,    76,    77,     5,     6,   187,
       8,     9,    10,   290,    12,   155,    14,   279,    16,   287,
      -1,    19,    20,    21,    -1,    -1,     3,    25,    26,    -1,
       3,    -1,    -1,    -1,    32,    33,    13,    -1,    15,    -1,
      13,    18,    15,    -1,    -1,    18,    23,    -1,    -1,    22,
      23,    28,    29,    -1,    52,    28,    29,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    -1,
       3,    -1,    -1,    71,    -1,    -1,    -1,    75,    76,    77,
      13,    -1,    15,    56,    -1,    18,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


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
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   include <string.h>
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 316 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 112 "parser.y"
{
		  nerrors = 0;
		  ndeclarations = 0;
		}
    break;
case 2:
#line 117 "parser.y"
{
		  if (nerrors > 0) {
		      YYABORT;
		  }
		}
    break;
case 4:
#line 127 "parser.y"
{
		  if (nerrors > 0) {
		      YYABORT;
		  }
		}
    break;
case 5:
#line 136 "parser.y"
{
		  if (ndeclarations > 0) {
		      c_error("inherit must precede all declarations");
		  } else if (nerrors > 0 ||
			     !c_inherit(yyvsp[-1].node->l.string->text, yyvsp[-2].node, yyvsp[-4].type != 0)) {
		      /*
		       * The object to be inherited may have been compiled;
		       * abort this compilation and possibly restart later.
		       */
		      YYABORT;
		  }
		}
    break;
case 6:
#line 149 "parser.y"
{ ndeclarations++; }
    break;
case 7:
#line 151 "parser.y"
{ ndeclarations++; }
    break;
case 8:
#line 156 "parser.y"
{ yyval.node = (node *) NULL; }
    break;
case 10:
#line 162 "parser.y"
{ yyval.node = node_str(str_new(yytext, (long) yyleng)); }
    break;
case 12:
#line 168 "parser.y"
{ yyval.node = node_str(str_add(yyvsp[-2].node->l.string, yyvsp[0].node->l.string)); }
    break;
case 13:
#line 170 "parser.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 14:
#line 175 "parser.y"
{ yyval.node = node_str(str_new(yytext, (long) yyleng)); }
    break;
case 15:
#line 180 "parser.y"
{ c_global(yyvsp[-3].type, yyvsp[-2].node, yyvsp[-1].node); }
    break;
case 16:
#line 185 "parser.y"
{ 
		  typechecking = TRUE;
		  c_function(yyvsp[-2].type, yyvsp[-1].node, yyvsp[0].node);
		}
    break;
case 17:
#line 190 "parser.y"
{
		  if (nerrors == 0) {
		      c_funcbody(yyvsp[0].node);
		  }
		}
    break;
case 18:
#line 196 "parser.y"
{
		  typechecking = c_typechecking();
		  c_function(yyvsp[-4].type, node_type((typechecking) ? T_VOID : T_NIL,
					   (string *) NULL),
			     node_bin(N_FUNC, 0, yyvsp[-3].node, yyvsp[-1].node));
		}
    break;
case 19:
#line 203 "parser.y"
{
		  if (nerrors == 0) {
		      c_funcbody(yyvsp[0].node);
		  }
		}
    break;
case 20:
#line 212 "parser.y"
{ c_local(yyvsp[-3].type, yyvsp[-2].node, yyvsp[-1].node); }
    break;
case 21:
#line 217 "parser.y"
{ yyval.node = (node *) NULL; }
    break;
case 22:
#line 218 "parser.y"
{ yyval.node = (node *) NULL; }
    break;
case 24:
#line 221 "parser.y"
{
		  yyval.node = yyvsp[-1].node;
		  yyval.node->flags |= F_ELLIPSIS;
		}
    break;
case 26:
#line 230 "parser.y"
{ yyval.node = node_bin(N_PAIR, 0, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 27:
#line 235 "parser.y"
{
		  yyval.node = yyvsp[0].node;
		  yyval.node->flags |= F_VARARGS;
		}
    break;
case 29:
#line 244 "parser.y"
{
		  yyval.node = yyvsp[0].node;
		  yyval.node->mod |= yyvsp[-1].node->mod;
		  yyval.node->class = yyvsp[-1].node->class;
		}
    break;
case 30:
#line 249 "parser.y"
{
		  yyval.node = yyvsp[0].node;
		  yyval.node->mod = T_NIL;	/* only if typechecking, though */
		}
    break;
case 33:
#line 259 "parser.y"
{ yyval.type = yyvsp[-1].type | yyvsp[0].type; }
    break;
case 35:
#line 265 "parser.y"
{ yyval.type = yyvsp[-1].type | yyvsp[0].type; }
    break;
case 36:
#line 270 "parser.y"
{ yyval.type = C_STATIC | C_PRIVATE; }
    break;
case 38:
#line 276 "parser.y"
{ yyval.type = 0; }
    break;
case 39:
#line 278 "parser.y"
{ yyval.type = C_STATIC | C_PRIVATE; }
    break;
case 40:
#line 283 "parser.y"
{ yyval.type = C_STATIC; }
    break;
case 41:
#line 285 "parser.y"
{ yyval.type = C_ATOMIC; }
    break;
case 42:
#line 287 "parser.y"
{ yyval.type = C_NOMASK; }
    break;
case 43:
#line 289 "parser.y"
{ yyval.type = C_VARARGS; }
    break;
case 44:
#line 293 "parser.y"
{ yyval.node = node_type(T_INT, (string *) NULL); }
    break;
case 45:
#line 294 "parser.y"
{ yyval.node = node_type(T_FLOAT, (string *) NULL); }
    break;
case 46:
#line 296 "parser.y"
{ yyval.node = node_type(T_STRING, (string *) NULL); }
    break;
case 47:
#line 298 "parser.y"
{ yyval.node = node_type(T_OBJECT, (string *) NULL); }
    break;
case 48:
#line 300 "parser.y"
{ yyval.node = node_type(T_CLASS, c_objecttype(yyvsp[0].node)); }
    break;
case 49:
#line 302 "parser.y"
{ yyval.node = node_type(T_MAPPING, (string *) NULL); }
    break;
case 50:
#line 303 "parser.y"
{ yyval.node = node_type(T_MIXED, (string *) NULL); }
    break;
case 51:
#line 304 "parser.y"
{ yyval.node = node_type(T_VOID, (string *) NULL); }
    break;
case 52:
#line 309 "parser.y"
{ yyval.type = 0; }
    break;
case 53:
#line 311 "parser.y"
{
		  yyval.type = yyvsp[-1].type + 1;
		  if (yyval.type == 1 << (8 - REFSHIFT)) {
		      c_error("too deep indirection");
		  }
		}
    break;
case 54:
#line 321 "parser.y"
{
		  yyval.node = yyvsp[0].node;
		  yyval.node->mod = (yyvsp[-1].type << REFSHIFT) & T_REF;
		}
    break;
case 55:
#line 329 "parser.y"
{ yyval.node = node_bin(N_FUNC, (yyvsp[-4].type << REFSHIFT) & T_REF, yyvsp[-3].node, yyvsp[-1].node); }
    break;
case 59:
#line 340 "parser.y"
{ yyval.node = node_bin(N_PAIR, 0, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 60:
#line 345 "parser.y"
{ yyval.node = (node *) NULL; }
    break;
case 61:
#line 347 "parser.y"
{ yyval.node = c_concat(yyvsp[-1].node, yyvsp[0].node); }
    break;
case 62:
#line 352 "parser.y"
{
		  if (nstatements > 0) {
		      c_error("declaration after statement");
		  }
		  yyval.node = (node *) NULL;
		}
    break;
case 63:
#line 358 "parser.y"
{
		  nstatements++;
		  yyval.node = yyvsp[0].node;
		}
    break;
case 64:
#line 363 "parser.y"
{
		  if (nerrors >= MAX_ERRORS) {
		      YYABORT;
		  }
		  yyval.node = (node *) NULL;
		}
    break;
case 65:
#line 373 "parser.y"
{ yyval.node = c_exp_stmt(yyvsp[-1].node); }
    break;
case 67:
#line 376 "parser.y"
{ yyval.node = c_if(yyvsp[-2].node, yyvsp[0].node, (node *) NULL); }
    break;
case 68:
#line 379 "parser.y"
{ yyval.node = c_if(yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 69:
#line 380 "parser.y"
{ c_loop(); }
    break;
case 70:
#line 382 "parser.y"
{ yyval.node = c_do(yyvsp[-2].node, yyvsp[-5].node); }
    break;
case 71:
#line 384 "parser.y"
{ c_loop(); }
    break;
case 72:
#line 385 "parser.y"
{ yyval.node = c_while(yyvsp[-3].node, yyvsp[0].node); }
    break;
case 73:
#line 387 "parser.y"
{ c_loop(); }
    break;
case 74:
#line 388 "parser.y"
{ yyval.node = c_for(c_exp_stmt(yyvsp[-7].node), yyvsp[-5].node, c_exp_stmt(yyvsp[-3].node), yyvsp[0].node); }
    break;
case 75:
#line 390 "parser.y"
{
		  if (typechecking) {
		      char tnbuf[17];

		      if (yyvsp[-3].node->mod != T_INT && yyvsp[-3].node->mod != T_MIXED) {
			  c_error("bad type for stack rlimit (%s)",
				  i_typename(tnbuf, yyvsp[-3].node->mod));
		      }
		      if (yyvsp[-1].node->mod != T_INT && yyvsp[-1].node->mod != T_MIXED) {
			  c_error("bad type for ticks rlimit (%s)",
				  i_typename(tnbuf, yyvsp[-1].node->mod));
		      }
		  }
		  c_startrlimits();
		}
    break;
case 76:
#line 406 "parser.y"
{ yyval.node = c_endrlimits(yyvsp[-5].node, yyvsp[-3].node, yyvsp[0].node); }
    break;
case 77:
#line 407 "parser.y"
{ c_startcatch(); }
    break;
case 78:
#line 409 "parser.y"
{ c_endcatch(); }
    break;
case 79:
#line 411 "parser.y"
{ yyval.node = c_donecatch(yyvsp[-2].node, yyvsp[0].node); }
    break;
case 80:
#line 413 "parser.y"
{ c_startswitch(yyvsp[-1].node, typechecking); }
    break;
case 81:
#line 415 "parser.y"
{ yyval.node = c_endswitch(yyvsp[-3].node, yyvsp[0].node); }
    break;
case 82:
#line 417 "parser.y"
{ yyvsp[-1].node = c_case(yyvsp[-1].node, (node *) NULL); }
    break;
case 83:
#line 418 "parser.y"
{
		  yyval.node = yyvsp[-3].node;
		  if (yyval.node != (node *) NULL) {
		      yyval.node->l.left = yyvsp[0].node;
		  } else {
		      yyval.node = yyvsp[0].node;
		  }
		}
    break;
case 84:
#line 427 "parser.y"
{ yyvsp[-3].node = c_case(yyvsp[-3].node, yyvsp[-1].node); }
    break;
case 85:
#line 428 "parser.y"
{
		  yyval.node = yyvsp[-5].node;
		  if (yyval.node != (node *) NULL) {
		      yyval.node->l.left = yyvsp[0].node;
		  } else {
		      yyval.node = yyvsp[0].node;
		  }
		}
    break;
case 86:
#line 437 "parser.y"
{ yyvsp[0].node = c_default(); }
    break;
case 87:
#line 438 "parser.y"
{
		  yyval.node = yyvsp[-2].node;
		  if (yyval.node != (node *) NULL) {
		      yyval.node->l.left = yyvsp[0].node;
		  } else {
		      yyval.node = yyvsp[0].node;
		  }
		}
    break;
case 88:
#line 447 "parser.y"
{
		  yyval.node = c_break();
		}
    break;
case 89:
#line 451 "parser.y"
{
		  yyval.node = c_continue();
		}
    break;
case 90:
#line 455 "parser.y"
{ yyval.node = c_return(yyvsp[-1].node, typechecking); }
    break;
case 91:
#line 456 "parser.y"
{ yyval.node = (node *) NULL; }
    break;
case 92:
#line 460 "parser.y"
{
		  nstatements = 0;
		  c_startcompound();
		}
    break;
case 93:
#line 465 "parser.y"
{
		  nstatements = 1;	/* any non-zero value will do */
		  yyval.node = c_endcompound(yyvsp[-1].node);
		}
    break;
case 94:
#line 473 "parser.y"
{ yyval.node = (node *) NULL; }
    break;
case 95:
#line 475 "parser.y"
{ yyval.node = yyvsp[0].node; }
    break;
case 96:
#line 479 "parser.y"
{ yyval.node = c_flookup(yyvsp[0].node, typechecking); }
    break;
case 97:
#line 481 "parser.y"
{ yyval.node = c_iflookup(yyvsp[0].node, (node *) NULL); }
    break;
case 98:
#line 483 "parser.y"
{ yyval.node = c_iflookup(yyvsp[0].node, yyvsp[-2].node); }
    break;
case 99:
#line 488 "parser.y"
{ yyval.node = node_int(yyvsp[0].number); }
    break;
case 100:
#line 490 "parser.y"
{ yyval.node = node_float(&yyvsp[0].real); }
    break;
case 101:
#line 491 "parser.y"
{ yyval.node = node_nil(); }
    break;
case 103:
#line 494 "parser.y"
{ yyval.node = c_aggregate(yyvsp[-2].node, T_MIXED | (1 << REFSHIFT)); }
    break;
case 104:
#line 496 "parser.y"
{ yyval.node = c_aggregate(yyvsp[-2].node, T_MAPPING); }
    break;
case 105:
#line 497 "parser.y"
{
		  yyval.node = c_variable(yyvsp[0].node);
		  if (typechecking) {
		      if (yyval.node->type == N_GLOBAL && yyval.node->mod != T_MIXED &&
			  !conf_typechecking()) {
			  /*
			   * global vars might be modified by untypechecked
			   * functions...
			   */
			  yyval.node = node_mon(N_CAST, yyval.node->mod, yyval.node);
			  yyval.node->class = yyval.node->l.left->class;
		      }
		  } else {
		      /* the variable could be anything */
		      yyval.node->mod = T_MIXED;
		  }
		}
    break;
case 106:
#line 515 "parser.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 107:
#line 517 "parser.y"
{ yyval.node = c_checkcall(c_funcall(yyvsp[-3].node, yyvsp[-1].node), typechecking); }
    break;
case 108:
#line 519 "parser.y"
{ yyval.node = node_mon(N_CATCH, T_STRING, yyvsp[-1].node); }
    break;
case 109:
#line 521 "parser.y"
{
		  t_void(yyvsp[-5].node);
		  yyval.node = c_checkcall(c_arrow(yyvsp[-5].node, yyvsp[-3].node, yyvsp[-1].node), typechecking);
		}
    break;
case 110:
#line 526 "parser.y"
{ yyval.node = c_instanceof(yyvsp[-2].node, yyvsp[0].node); }
    break;
case 111:
#line 528 "parser.y"
{ yyval.node = c_instanceof(yyvsp[-4].node, yyvsp[-1].node); }
    break;
case 113:
#line 534 "parser.y"
{ yyval.node = idx(yyvsp[-3].node, yyvsp[-1].node); }
    break;
case 114:
#line 536 "parser.y"
{ yyval.node = range(yyvsp[-5].node, yyvsp[-3].node, yyvsp[-1].node); }
    break;
case 116:
#line 542 "parser.y"
{ yyval.node = uassign(N_PLUS_PLUS, yyvsp[-1].node, "++"); }
    break;
case 117:
#line 544 "parser.y"
{ yyval.node = uassign(N_MIN_MIN, yyvsp[-1].node, "--"); }
    break;
case 119:
#line 550 "parser.y"
{ yyval.node = uassign(N_ADD_EQ_1, yyvsp[0].node, "++"); }
    break;
case 120:
#line 552 "parser.y"
{ yyval.node = uassign(N_SUB_EQ_1, yyvsp[0].node, "--"); }
    break;
case 121:
#line 554 "parser.y"
{ yyval.node = umin(yyvsp[0].node); }
    break;
case 122:
#line 556 "parser.y"
{ yyval.node = yyvsp[0].node; }
    break;
case 123:
#line 558 "parser.y"
{
		  t_void(yyvsp[0].node);
		  yyval.node = c_not(yyvsp[0].node);
		}
    break;
case 124:
#line 563 "parser.y"
{
		  yyval.node = yyvsp[0].node;
		  t_void(yyval.node);
		  if (typechecking && yyval.node->mod != T_INT && yyval.node->mod != T_MIXED) {
		      char tnbuf[17];

		      c_error("bad argument type for ~ (%s)",
			      i_typename(tnbuf, yyval.node->mod));
		      yyval.node->mod = T_MIXED;
		  } else {
		      yyval.node = xor(N_XOR, yyval.node, node_int((Int) -1), "^");
		  }
		}
    break;
case 126:
#line 581 "parser.y"
{
		  yyvsp[-3].node->mod |= (yyvsp[-2].type << REFSHIFT) & T_REF;
		  yyval.node = cast(yyvsp[0].node, yyvsp[-3].node);
		}
    break;
case 128:
#line 590 "parser.y"
{ yyval.node = mult(N_MULT, yyvsp[-2].node, yyvsp[0].node, "*"); }
    break;
case 129:
#line 592 "parser.y"
{ yyval.node = mdiv(N_DIV, yyvsp[-2].node, yyvsp[0].node, "/"); }
    break;
case 130:
#line 594 "parser.y"
{ yyval.node = mod(N_MOD, yyvsp[-2].node, yyvsp[0].node, "%"); }
    break;
case 132:
#line 600 "parser.y"
{ yyval.node = add(N_ADD, yyvsp[-2].node, yyvsp[0].node, "+"); }
    break;
case 133:
#line 602 "parser.y"
{ yyval.node = sub(N_SUB, yyvsp[-2].node, yyvsp[0].node, "-"); }
    break;
case 135:
#line 608 "parser.y"
{ yyval.node = lshift(N_LSHIFT, yyvsp[-2].node, yyvsp[0].node, "<<"); }
    break;
case 136:
#line 610 "parser.y"
{ yyval.node = rshift(N_RSHIFT, yyvsp[-2].node, yyvsp[0].node, ">>"); }
    break;
case 138:
#line 616 "parser.y"
{ yyval.node = rel(N_LT, yyval.node, yyvsp[0].node, "<"); }
    break;
case 139:
#line 618 "parser.y"
{ yyval.node = rel(N_GT, yyval.node, yyvsp[0].node, ">"); }
    break;
case 140:
#line 620 "parser.y"
{ yyval.node = rel(N_LE, yyval.node, yyvsp[0].node, "<="); }
    break;
case 141:
#line 622 "parser.y"
{ yyval.node = rel(N_GE, yyval.node, yyvsp[0].node, ">="); }
    break;
case 143:
#line 628 "parser.y"
{ yyval.node = eq(yyvsp[-2].node, yyvsp[0].node); }
    break;
case 144:
#line 630 "parser.y"
{ yyval.node = c_not(eq(yyvsp[-2].node, yyvsp[0].node)); }
    break;
case 146:
#line 636 "parser.y"
{ yyval.node = and(N_AND, yyvsp[-2].node, yyvsp[0].node, "&"); }
    break;
case 148:
#line 642 "parser.y"
{ yyval.node = xor(N_XOR, yyvsp[-2].node, yyvsp[0].node, "^"); }
    break;
case 150:
#line 648 "parser.y"
{ yyval.node = or(N_OR, yyvsp[-2].node, yyvsp[0].node, "|"); }
    break;
case 152:
#line 654 "parser.y"
{ yyval.node = land(yyvsp[-2].node, yyvsp[0].node); }
    break;
case 154:
#line 660 "parser.y"
{ yyval.node = lor(yyvsp[-2].node, yyvsp[0].node); }
    break;
case 156:
#line 666 "parser.y"
{ yyval.node = quest(yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 158:
#line 672 "parser.y"
{ yyval.node = assign(c_lvalue(yyvsp[-2].node, "assignment"), yyvsp[0].node); }
    break;
case 159:
#line 674 "parser.y"
{ yyval.node = add(N_ADD_EQ, c_lvalue(yyvsp[-2].node, "+="), yyvsp[0].node, "+="); }
    break;
case 160:
#line 676 "parser.y"
{ yyval.node = sub(N_SUB_EQ, c_lvalue(yyvsp[-2].node, "-="), yyvsp[0].node, "-="); }
    break;
case 161:
#line 678 "parser.y"
{ yyval.node = mult(N_MULT_EQ, c_lvalue(yyvsp[-2].node, "*="), yyvsp[0].node, "*="); }
    break;
case 162:
#line 680 "parser.y"
{ yyval.node = mdiv(N_DIV_EQ, c_lvalue(yyvsp[-2].node, "/="), yyvsp[0].node, "/="); }
    break;
case 163:
#line 682 "parser.y"
{ yyval.node = mod(N_MOD_EQ, c_lvalue(yyvsp[-2].node, "%="), yyvsp[0].node, "%="); }
    break;
case 164:
#line 684 "parser.y"
{ yyval.node = lshift(N_LSHIFT_EQ, c_lvalue(yyvsp[-2].node, "<<="), yyvsp[0].node, "<<="); }
    break;
case 165:
#line 686 "parser.y"
{ yyval.node = rshift(N_RSHIFT_EQ, c_lvalue(yyvsp[-2].node, ">>="), yyvsp[0].node, ">>="); }
    break;
case 166:
#line 688 "parser.y"
{ yyval.node = and(N_AND_EQ, c_lvalue(yyvsp[-2].node, "&="), yyvsp[0].node, "&="); }
    break;
case 167:
#line 690 "parser.y"
{ yyval.node = xor(N_XOR_EQ, c_lvalue(yyvsp[-2].node, "^="), yyvsp[0].node, "^="); }
    break;
case 168:
#line 692 "parser.y"
{ yyval.node = or(N_OR_EQ, c_lvalue(yyvsp[-2].node, "|="), yyvsp[0].node, "|="); }
    break;
case 170:
#line 698 "parser.y"
{ yyval.node = comma(yyvsp[-2].node, yyvsp[0].node); }
    break;
case 171:
#line 703 "parser.y"
{ yyval.node = (node *) NULL; }
    break;
case 173:
#line 709 "parser.y"
{ t_void(yyval.node = yyvsp[0].node); }
    break;
case 174:
#line 714 "parser.y"
{ t_void(yyval.node = yyvsp[0].node); }
    break;
case 175:
#line 718 "parser.y"
{ t_void(yyval.node = yyvsp[0].node); }
    break;
case 176:
#line 720 "parser.y"
{
		  t_void(yyvsp[0].node);
		  yyval.node = node_bin(N_PAIR, 0, yyvsp[-2].node, yyvsp[0].node);
		}
    break;
case 177:
#line 728 "parser.y"
{ yyval.node = (node *) NULL; }
    break;
case 179:
#line 731 "parser.y"
{
		  yyval.node = yyvsp[-1].node;
		  if (yyval.node->type == N_PAIR) {
		      yyval.node->r.right = node_mon(N_SPREAD, -1, yyval.node->r.right);
		  } else {
		      yyval.node = node_mon(N_SPREAD, -1, yyval.node);
		  }
		}
    break;
case 180:
#line 743 "parser.y"
{ yyval.node = (node *) NULL; }
    break;
case 182:
#line 746 "parser.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 183:
#line 751 "parser.y"
{
		  t_void(yyvsp[-2].node);
		  t_void(yyvsp[0].node);
		  yyval.node = node_bin(N_COMMA, 0, yyvsp[-2].node, yyvsp[0].node);
		}
    break;
case 185:
#line 761 "parser.y"
{ yyval.node = node_bin(N_PAIR, 0, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 186:
#line 766 "parser.y"
{ yyval.node = (node *) NULL; }
    break;
case 188:
#line 769 "parser.y"
{ yyval.node = yyvsp[-1].node; }
    break;
}

#line 706 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 772 "parser.y"


/*
 * NAME:	t_void()
 * DESCRIPTION:	if the argument is of type void, an error will result
 */
static void t_void(n)
register node *n;
{
    if (n != (node *) NULL && n->mod == T_VOID) {
	c_error("void value not ignored");
	n->mod = T_MIXED;
    }
}

/*
 * NAME:	t_unary()
 * DESCRIPTION:	typecheck the argument of a unary operator
 */
static bool t_unary(n, name)
register node *n;
char *name;
{
    char tnbuf[17];

    t_void(n);
    if (typechecking && !T_ARITHMETIC(n->mod) && n->mod != T_MIXED) {
	c_error("bad argument type for %s (%s)", name,
		i_typename(tnbuf, n->mod));
	n->mod = T_MIXED;
	return FALSE;
    }
    return TRUE;
}

/*
 * NAME:	uassign()
 * DESCRIPTION:	handle a unary assignment operator
 */
static node *uassign(op, n, name)
int op;
register node *n;
char *name;
{
    t_unary(n, name);
    return node_mon((n->mod == T_INT) ? op + 1 : op, n->mod, c_lvalue(n, name));
}

/*
 * NAME:	cast()
 * DESCRIPTION:	cast an expression to a type
 */
static node *cast(n, type)
register node *n, *type;
{
    xfloat flt;
    Int i;
    char *p, buffer[18];

    if (type->mod != n->mod) {
	switch (type->mod) {
	case T_INT:
	    switch (n->type) {
	    case N_FLOAT:
		/* cast float constant to int */
		NFLT_GET(n, flt);
		return node_int(flt_ftoi(&flt));

	    case N_STR:
		/* cast string to int */
		p = n->l.string->text;
		i = strtoint(&p);
		if (p == n->l.string->text + n->l.string->len) {
		    return node_int(i);
		} else {
		    c_error("cast of invalid string constant");
		    n->mod = T_MIXED;
		}
		break;

	    case N_TOFLOAT:
	    case N_TOSTRING:
		if (n->l.left->type == N_INT) {
		    /* (int) (float) i, (int) (string) i */
		    return n->l.left;
		}
		/* fall through */
	    default:
		if (n->mod == T_FLOAT || n->mod == T_STRING ||
		    n->mod == T_MIXED) {
		    return node_mon(N_TOINT, T_INT, n);
		}
		break;
	    }
	    break;

	case T_FLOAT:
	    switch (n->type) {
	    case N_INT:
		/* cast int constant to float */
		flt_itof(n->l.number, &flt);
		return node_float(&flt);

	    case N_STR:
		/* cast string to float */
		p = n->l.string->text;
		if (flt_atof(&p, &flt) &&
		    p == n->l.string->text + n->l.string->len) {
		    return node_float(&flt);
		} else {
		    yyerror("cast of invalid string constant");
		    n->mod = T_MIXED;
		}
		break;

	    case N_TOSTRING:
		if (n->l.left->mod == T_INT) {
		    return node_mon(N_TOFLOAT, T_FLOAT, n->l.left);
		}
		/* fall through */
	    default:
		if (n->mod == T_INT || n->mod == T_STRING || n->mod == T_MIXED)
		{
		    return node_mon(N_TOFLOAT, T_FLOAT, n);
		}
		break;
	    }
	    break;

	case T_STRING:
	    switch (n->type) {
	    case N_INT:
		/* cast int constant to string */
		sprintf(buffer, "%ld", (long) n->l.number);
		return node_str(str_new(buffer, (long) strlen(buffer)));

	    case N_FLOAT:
		/* cast float constant to string */
		NFLT_GET(n, flt);
		flt_ftoa(&flt, buffer);
		return node_str(str_new(buffer, (long) strlen(buffer)));

	    default:
		if (n->mod == T_INT || n->mod == T_FLOAT || n->mod == T_MIXED) {
		    return node_mon(N_TOSTRING, T_STRING, n);
		}
		break;
	    }
	    break;
	}

	if (type->mod == T_MIXED || (type->mod & T_TYPE) == T_VOID) {
	    /* (mixed), (void), (void *) */
	    c_error("cannot cast to %s", i_typename(buffer, type->mod));
	    n->mod = T_MIXED;
	} else if ((type->mod & T_REF) < (n->mod & T_REF)) {
	    /* (mixed *) of (mixed **) */
	    c_error("illegal cast of array type (%s)",
		    i_typename(buffer, n->mod));
	} else if ((n->mod & T_TYPE) != T_MIXED &&
		   ((type->mod & T_TYPE) != T_CLASS ||
		    ((n->mod & T_TYPE) != T_OBJECT &&
		     (n->mod & T_TYPE) != T_CLASS) ||
		    (type->mod & T_REF) != (n->mod & T_REF))) {
	    /* can only cast from mixed, or object/class to class */
	    c_error("cast of invalid type (%s)", i_typename(buffer, n->mod));
	} else {
	    if ((type->mod & T_REF) == 0 || (n->mod & T_REF) == 0) {
		/* runtime cast */
		n = node_mon(N_CAST, type->mod, n);
	    } else {
		n->mod = type->mod;
	    }
	    n->class = type->class;
	}
    } else if (type->mod == T_CLASS && str_cmp(type->class, n->class) != 0) {
	/*
	 * cast to different object class
	 */
	n = node_mon(N_CAST, type->mod, n);
	n->class = type->class;
    }
    return n;
}

/*
 * NAME:	idx()
 * DESCRIPTION:	handle the [ ] operator
 */
static node *idx(n1, n2)
register node *n1, *n2;
{
    char tnbuf[17];
    register unsigned short type;

    if (n1->type == N_STR && n2->type == N_INT) {
	/* str [ int ] */
	if (n2->l.number < 0 || n2->l.number >= (Int) n1->l.string->len) {
	    c_error("string index out of range");
	} else {
	    n2->l.number =
		    UCHAR(n1->l.string->text[str_index(n1->l.string,
						       (long) n2->l.number)]);
	}
	return n2;
    }

    if ((n1->mod & T_REF) != 0) {
	/*
	 * array
	 */
	if (typechecking) {
	    type = n1->mod - (1 << REFSHIFT);
	    if (n2->mod != T_INT && n2->mod != T_MIXED) {
		c_error("bad index type (%s)", i_typename(tnbuf, n2->mod));
	    }
	    if (type != T_MIXED) {
		/* you can't trust these arrays */
		n2 = node_mon(N_CAST, type, node_bin(N_INDEX, type, n1, n2));
		n2->class = n1->class;
		return n2;
	    }
	}
	type = T_MIXED;
    } else if (n1->mod == T_STRING) {
	/*
	 * string
	 */
	if (typechecking && n2->mod != T_INT && n2->mod != T_MIXED) {
	    c_error("bad index type (%s)", i_typename(tnbuf, n2->mod));
	}
	type = T_INT;
    } else {
	if (typechecking && n1->mod != T_MAPPING && n1->mod != T_MIXED) {
	    c_error("bad indexed type (%s)", i_typename(tnbuf, n1->mod));
	}
	type = T_MIXED;
    }
    return node_bin(N_INDEX, type, n1, n2);
}

/*
 * NAME:	range()
 * DESCRIPTION:	handle the [ .. ] operator
 */
static node *range(n1, n2, n3)
register node *n1, *n2, *n3;
{
    if (n1->type == N_STR && (n2 == (node *) NULL || n2->type == N_INT) &&
	(n3 == (node *) NULL || n3->type == N_INT)) {
	Int from, to;

	/* str [ int .. int ] */
	from = (n2 == (node *) NULL) ? 0 : n2->l.number;
	to = (n3 == (node *) NULL) ? n1->l.string->len - 1 : n3->l.number;
	if (from < 0 || from > to + 1 || to >= n1->l.string->len) {
	    c_error("invalid string range");
	} else {
	    return node_str(str_range(n1->l.string, (long) from, (long) to));
	}
    }

    if (typechecking && n1->mod != T_MAPPING && n1->mod != T_MIXED) {
	char tnbuf[17];

	/* indices */
	if (n2 != (node *) NULL && n2->mod != T_INT && n2->mod != T_MIXED) {
	    c_error("bad index type (%s)", i_typename(tnbuf, n2->mod));
	}
	if (n3 != (node *) NULL && n3->mod != T_INT && n3->mod != T_MIXED) {
	    c_error("bad index type (%s)", i_typename(tnbuf, n3->mod));
	}
	/* range */
	if ((n1->mod & T_REF) == 0 && n1->mod != T_STRING) {
	    c_error("bad indexed type (%s)", i_typename(tnbuf, n1->mod));
	}
    }

    return node_bin(N_RANGE, n1->mod, n1, node_bin(N_PAIR, 0, n2, n3));
}

/*
 * NAME:	bini()
 * DESCRIPTION:	handle a binary int operator
 */
static node *bini(op, n1, n2, name)
int op;
register node *n1, *n2;
char *name;
{
    char tnbuf1[17], tnbuf2[17];

    t_void(n1);
    t_void(n2);

    if (typechecking &&
	((n1->mod != T_INT && n1->mod != T_MIXED) ||
	 (n2->mod != T_INT && n2->mod != T_MIXED))) {
	c_error("bad argument types for %s (%s, %s)", name,
		i_typename(tnbuf1, n1->mod), i_typename(tnbuf2, n2->mod));
    }
    if (n1->mod == T_INT && n2->mod == T_INT) {
	op++;
    }
    return node_bin(op, T_INT, n1, n2);
}

/*
 * NAME:	bina()
 * DESCRIPTION:	handle a binary arithmetic operator
 */
static node *bina(op, n1, n2, name)
int op;
register node *n1, *n2;
char *name;
{
    char tnbuf1[17], tnbuf2[17];
    register unsigned short type;

    t_void(n1);
    t_void(n2);

    type = T_MIXED;
    if (typechecking &&
	((n1->mod != n2->mod && n1->mod != T_MIXED && n2->mod != T_MIXED) ||
	 (!T_ARITHMETIC(n1->mod) && n1->mod != T_MIXED) ||
	 (!T_ARITHMETIC(n2->mod) && n2->mod != T_MIXED))) {
	c_error("bad argument types for %s (%s, %s)", name,
		i_typename(tnbuf1, n1->mod), i_typename(tnbuf2, n2->mod));
    } else if (n1->mod == T_INT || n2->mod == T_INT) {
	if (n1->mod == T_INT && n2->mod == T_INT) {
	    op++;
	}
	type = T_INT;
    } else if (n1->mod == T_FLOAT || n2->mod == T_FLOAT) {
	type = T_FLOAT;
    }

    return node_bin(op, type, n1, n2);
}

/*
 * NAME:	mult()
 * DESCRIPTION:	handle the * *= operators
 */
static node *mult(op, n1, n2, name)
int op;
register node *n1, *n2;
char *name;
{
    xfloat f1, f2;

    if (n1->type == N_INT && n2->type == N_INT) {
	/* i * i */
	n1->l.number *= n2->l.number;
	return n1;
    }
    if (n1->type == N_FLOAT && n2->type == N_FLOAT) {
	NFLT_GET(n1, f1);
	NFLT_GET(n2, f2);
	flt_mult(&f1, &f2);
	NFLT_PUT(n1, f1);
	return n1;
    }
    return bina(op, n1, n2, name);
}

/*
 * NAME:	mdiv()
 * DESCRIPTION:	handle the / /= operators
 */
static node *mdiv(op, n1, n2, name)
int op;
register node *n1, *n2;
char *name;
{
    xfloat f1, f2;

    if (n1->type == N_INT && n2->type == N_INT) {
	register Int i, d;

	/* i / i */
	i = n1->l.number;
	d = n2->l.number;
	if (d == 0) {
	    /* i / 0 */
	    c_error("division by zero");
	    return n1;
	}
	if ((d | i) < 0) {
	    Int r;

            r = ((Uint) ((i < 0) ? -i : i)) / ((Uint) ((d < 0) ? -d : d));
            n1->l.number = ((i ^ d) < 0) ? -r : r;
	} else {
	    n1->l.number = ((Uint) i) / ((Uint) d);
	}
	return n1;
    } else if (n1->type == N_FLOAT && n2->type == N_FLOAT) {
	/* f / f */
	if (NFLT_ISZERO(n2)) {
	    /* f / 0.0 */
	    c_error("division by zero");
	    return n1;
	}
	NFLT_GET(n1, f1);
	NFLT_GET(n2, f2);
	flt_div(&f1, &f2);
	NFLT_PUT(n1, f1);
	return n1;
    }

    return bina(op, n1, n2, name);
}

/*
 * NAME:	mod()
 * DESCRIPTION:	handle the % %= operators
 */
static node *mod(op, n1, n2, name)
int op;
register node *n1, *n2;
char *name;
{
    if (n1->type == N_INT && n2->type == N_INT) {
	register Int i, d;

	/* i % i */
	i = n1->l.number;
	d = n2->l.number;
	if (d == 0) {
	    /* i % 0 */
	    c_error("modulus by zero");
	    return n1;
	}
	if (d < 0) {
	    d = -d;
	}
	if (i < 0) {
            n1->l.number = - (Int) (((Uint) -i) % ((Uint) d));
	} else {
	    n1->l.number = ((Uint) i) % ((Uint) d);
	}
	return n1;
    }

    return bini(op, n1, n2, name);
}

/*
 * NAME:	add()
 * DESCRIPTION:	handle the + += operators, possibly rearranging the order
 *		of the expression
 */
static node *add(op, n1, n2, name)
int op;
register node *n1, *n2;
char *name;
{
    char tnbuf1[17], tnbuf2[17];
    xfloat f1, f2;
    register unsigned short type;

    t_void(n1);
    t_void(n2);

    if (n1->mod == T_STRING) {
	if (n2->mod == T_INT || n2->mod == T_FLOAT ||
	    (n2->mod == T_MIXED && typechecking)) {
	    n2 = cast(n2, node_type(T_STRING, (string *) NULL));
	}
    } else if (n2->mod == T_STRING && op == N_ADD) {
	if (n1->mod == T_INT || n1->mod == T_FLOAT ||
	    (n1->mod == T_MIXED && typechecking)) {
	    n1 = cast(n1, node_type(T_STRING, (string *) NULL));
	}
    }

    if (n1->type == N_INT && n2->type == N_INT) {
	/* i + i */
	n1->l.number += n2->l.number;
	return n1;
    }
    if (n1->type == N_FLOAT && n2->type == N_FLOAT) {
	/* f + f */
	NFLT_GET(n1, f1);
	NFLT_GET(n2, f2);
	flt_add(&f1, &f2);
	NFLT_PUT(n1, f1);
	return n1;
    }
    if (n1->type == N_STR && n2->type == N_STR) {
	/* s + s */
	return node_str(str_add(n1->l.string, n2->l.string));
    }

    type = c_tmatch(n1->mod, n2->mod);
    if (type == T_NIL || type == T_OBJECT || type == T_CLASS) {
	type = T_MIXED;
	if (typechecking) {
	    c_error("bad argument types for %s (%s, %s)", name,
		    i_typename(tnbuf1, n1->mod), i_typename(tnbuf2, n2->mod));
	}
    } else if (type == T_INT) {
	op++;
    } else if (op == N_ADD_EQ) {
	if (n1->mod == T_INT) {
	    n2 = node_mon(N_CAST, T_INT, n2);
	    type = T_INT;
	    op++;
	} else if (n1->mod == T_FLOAT && n2->mod != T_FLOAT) {
	    n2 = node_mon(N_CAST, T_FLOAT, n2);
	    type = T_FLOAT;
	}
    }
    return node_bin(op, type, n1, n2);
}

/*
 * NAME:	sub()
 * DESCRIPTION:	handle the - -= operators
 */
static node *sub(op, n1, n2, name)
int op;
register node *n1, *n2;
char *name;
{
    char tnbuf1[17], tnbuf2[17];
    xfloat f1, f2;
    register unsigned short type;

    t_void(n1);
    t_void(n2);

    if (n1->type == N_INT && n2->type == N_INT) {
	/* i - i */
	n1->l.number -= n2->l.number;
	return n1;
    }
    if (n1->type == N_FLOAT && n2->type == N_FLOAT) {
	/* f - f */
	NFLT_GET(n1, f1);
	NFLT_GET(n2, f2);
	flt_sub(&f1, &f2);
	NFLT_PUT(n1, f1);
	return n1;
    }

    type = c_tmatch(n1->mod, n2->mod);
    if (type == T_NIL || type == T_STRING || type == T_OBJECT ||
	type == T_CLASS || type == T_MAPPING) {
	if ((type=n1->mod) != T_MAPPING ||
	    (n2->mod != T_MIXED && (n2->mod & T_REF) == 0)) {
	    type = T_MIXED;
	    if (typechecking) {
		c_error("bad argument types for %s (%s, %s)", name,
			i_typename(tnbuf1, n1->mod),
			i_typename(tnbuf2, n2->mod));
	    }
	}
    } else if (type == T_INT) {
	op++;
    } else if (type == T_MIXED) {
	type = (n1->mod == T_MIXED) ? n2->mod : n1->mod;
    } else if (n1->mod == T_MIXED && (n2->mod & T_REF)) {
	type = T_MIXED;
    }
    return node_bin(op, type, n1, n2);
}

/*
 * NAME:	umin()
 * DESCRIPTION:	handle unary minus
 */
static node *umin(n)
register node *n;
{
    xfloat flt;

    if (t_unary(n, "unary -")) {
	if (n->mod == T_FLOAT) {
	    FLT_ZERO(flt.high, flt.low);
	    n = sub(N_SUB, node_float(&flt), n, "-");
	} else {
	    n = sub(N_SUB, node_int((Int) 0), n, "-");
	}
    }
    return n;
}

/*
 * NAME:	lshift()
 * DESCRIPTION:	handle the << <<= operators
 */
static node *lshift(op, n1, n2, name)
int op;
register node *n1, *n2;
char *name;
{
    if (n2->type == N_INT) {
	if (n2->l.number < 0) {
	    c_error("negative left shift");
	    n2->l.number = 0;
	}
	if (n1->type == N_INT) {
	    /* i << i */
	    n1->l.number = (n2->l.number < 32) ?
			    (Uint) n1->l.number << n2->l.number : 0;
	    return n1;
	}
    }

    return bini(op, n1, n2, name);
}

/*
 * NAME:	rshift()
 * DESCRIPTION:	handle the >> >>= operators
 */
static node *rshift(op, n1, n2, name)
int op;
register node *n1, *n2;
char *name;
{
    if (n2->type == N_INT) {
	if (n2->l.number < 0) {
	    c_error("negative right shift");
	    n2->l.number = 0;
	}
	if (n1->type == N_INT) {
	    /* i >> i */
	    n1->l.number = (n2->l.number < 32) ?
			    (Uint) n1->l.number >> n2->l.number : 0;
	    return n1;
	}
    }

    return bini(op, n1, n2, name);
}

/*
 * NAME:	rel()
 * DESCRIPTION:	handle the < > <= >= operators
 */
static node *rel(op, n1, n2, name)
int op;
register node *n1, *n2;
char *name;
{
    char tnbuf1[17], tnbuf2[17];

    t_void(n1);
    t_void(n2);

    if (n1->type == N_INT && n2->type == N_INT) {
	/* i . i */
	switch (op) {
	case N_GE:
	    n1->l.number = (n1->l.number >= n2->l.number);
	    break;

	case N_GT:
	    n1->l.number = (n1->l.number > n2->l.number);
	    break;

	case N_LE:
	    n1->l.number = (n1->l.number <= n2->l.number);
	    break;

	case N_LT:
	    n1->l.number = (n1->l.number < n2->l.number);
	    break;
	}
	return n1;
    }
    if (n1->type == N_FLOAT && n2->type == N_FLOAT) {
	xfloat f1, f2;

	/* f . f */
	NFLT_GET(n1, f1);
	NFLT_GET(n2, f2);

	switch (op) {
	case N_GE:
	    return node_int((Int) (flt_cmp(&f1, &f2) >= 0));

	case N_GT:
	    return node_int((Int) (flt_cmp(&f1, &f2) > 0));

	case N_LE:
	    return node_int((Int) (flt_cmp(&f1, &f2) <= 0));

	case N_LT:
	    return node_int((Int) (flt_cmp(&f1, &f2) < 0));
	}
	return n1;
    }
    if (n1->type == N_STR && n2->type == N_STR) {
	/* s . s */
	switch (op) {
	case N_GE:
	    return node_int((Int) (str_cmp(n1->l.string, n2->l.string) >= 0));

	case N_GT:
	    return node_int((Int) (str_cmp(n1->l.string, n2->l.string) > 0));

	case N_LE:
	    return node_int((Int) (str_cmp(n1->l.string, n2->l.string) <= 0));

	case N_LT:
	    return node_int((Int) (str_cmp(n1->l.string, n2->l.string) < 0));
	}
    }

    if (typechecking &&
	((n1->mod != n2->mod && n1->mod != T_MIXED && n2->mod != T_MIXED) ||
	 (!T_ARITHSTR(n1->mod) && n1->mod != T_MIXED) ||
	 (!T_ARITHSTR(n2->mod) && n2->mod != T_MIXED))) {
	c_error("bad argument types for %s (%s, %s)", name,
		i_typename(tnbuf1, n1->mod), i_typename(tnbuf2, n2->mod));
    } else if (n1->mod == T_INT && n2->mod == T_INT) {
	op++;
    }
    return node_bin(op, T_INT, n1, n2);
}

/*
 * NAME:	eq()
 * DESCRIPTION:	handle the == operator
 */
static node *eq(n1, n2)
register node *n1, *n2;
{
    char tnbuf1[17], tnbuf2[17];
    xfloat f1, f2;
    int op;

    t_void(n1);
    t_void(n2);

    switch (n1->type) {
    case N_INT:
	if (n2->type == N_INT) {
	    /* i == i */
	    n1->l.number = (n1->l.number == n2->l.number);
	    return n1;
	}
	if (nil_node == N_INT && n1->l.number == 0 && n2->type == N_STR) {
	    /* nil == str */
	    return node_int((Int) FALSE);
	}
	break;

    case N_FLOAT:
	if (n2->type == N_FLOAT) {
	    /* f == f */
	    NFLT_GET(n1, f1);
	    NFLT_GET(n2, f2);
	    return node_int((Int) (flt_cmp(&f1, &f2) == 0));
	}
	break;

    case N_STR:
	if (n2->type == N_STR) {
	    /* s == s */
	    return node_int((Int) (str_cmp(n1->l.string, n2->l.string) == 0));
	}
	if (n2->type == nil_node && n2->l.number == 0) {
	    /* s == nil */
	    return node_int((Int) FALSE);
	}
	break;

    case N_NIL:
	if (n2->type == N_NIL) {
	    /* nil == nil */
	    return node_int((Int) TRUE);
	}
	if (n2->type == N_STR) {
	    /* nil == str */
	    return node_int((Int) FALSE);
	}
	break;
    }

    op = N_EQ;
    if (n1->mod != n2->mod && n1->mod != T_MIXED && n2->mod != T_MIXED &&
	(!c_nil(n1) || !T_POINTER(n2->mod)) &&
	(!c_nil(n2) || !T_POINTER(n1->mod))) {
	if (typechecking) {
	    c_error("incompatible types for equality (%s, %s)",
		    i_typename(tnbuf1, n1->mod), i_typename(tnbuf2, n2->mod));
	}
    } else if (n1->mod == T_INT && n2->mod == T_INT) {
	op++;
    }
    return node_bin(op, T_INT, n1, n2);
}

/*
 * NAME:	and()
 * DESCRIPTION:	handle the & &= operators
 */
static node *and(op, n1, n2, name)
int op;
register node *n1, *n2;
char *name;
{
    register unsigned short type;

    if (n1->type == N_INT && n2->type == N_INT) {
	/* i & i */
	n1->l.number &= n2->l.number;
	return n1;
    }
    if ((((type=n1->mod) == T_MIXED || type == T_MAPPING) &&
	 ((n2->mod & T_REF) != 0 || n2->mod == T_MIXED)) ||
	((type=c_tmatch(n1->mod, n2->mod)) & T_REF) != T_NIL) {
	/*
	 * possibly array & array or mapping & array
	 */
	return node_bin(op, type, n1, n2);
    }
    return bini(op, n1, n2, name);
}

/*
 * NAME:	xor()
 * DESCRIPTION:	handle the ^ ^= operators
 */
static node *xor(op, n1, n2, name)
int op;
register node *n1, *n2;
char *name;
{
    register unsigned short type;

    if (n1->type == N_INT && n2->type == N_INT) {
	/* i ^ i */
	n1->l.number ^= n2->l.number;
	return n1;
    }
    if (((type=n1->mod) == T_MIXED && n2->mod == T_MIXED) ||
	((type=c_tmatch(n1->mod, n2->mod)) & T_REF) != T_NIL) {
	/*
	 * possibly array ^ array
	 */
	return node_bin(op, type, n1, n2);
    }
    return bini(op, n1, n2, name);
}

/*
 * NAME:	or()
 * DESCRIPTION:	handle the | |= operators
 */
static node *or(op, n1, n2, name)
int op;
register node *n1, *n2;
char *name;
{
    register unsigned short type;

    if (n1->type == N_INT && n2->type == N_INT) {
	/* i | i */
	n1->l.number |= n2->l.number;
	return n1;
    }
    if (((type=n1->mod) == T_MIXED && n2->mod == T_MIXED) ||
	((type=c_tmatch(n1->mod, n2->mod)) & T_REF) != T_NIL) {
	/*
	 * possibly array | array
	 */
	return node_bin(op, type, n1, n2);
    }
    return bini(op, n1, n2, name);
}

/*
 * NAME:	land()
 * DESCRIPTION:	handle the && operator
 */
static node *land(n1, n2)
register node *n1, *n2;
{
    t_void(n1);
    t_void(n2);

    if ((n1->flags & F_CONST) && (n2->flags & F_CONST)) {
	n1 = c_tst(n1);
	n2 = c_tst(n2);
	n1->l.number &= n2->l.number;
	return n1;
    }

    return node_bin(N_LAND, T_INT, n1, n2);
}

/*
 * NAME:	lor()
 * DESCRIPTION:	handle the || operator
 */
static node *lor(n1, n2)
register node *n1, *n2;
{
    t_void(n1);
    t_void(n2);

    if ((n1->flags & F_CONST) && (n2->flags & F_CONST)) {
	n1 = c_tst(n1);
	n2 = c_tst(n2);
	n1->l.number |= n2->l.number;
	return n1;
    }

    return node_bin(N_LOR, T_INT, n1, n2);
}

/*
 * NAME:	quest()
 * DESCRIPTION:	handle the ? : operator
 */
static node *quest(n1, n2, n3)
register node *n1, *n2, *n3;
{
    register unsigned short type;

    t_void(n1);

    if ((n2->flags & F_CONST) && n3->type == n2->type) {
	switch (n1->type) {
	case N_INT:
	    return (n1->l.number == 0) ? n3 : n2;

	case N_FLOAT:
	    return (NFLT_ISZERO(n1)) ? n3 : n2;

	case N_STR:
	    return n2;

	case N_NIL:
	    return n3;
	}
    }

    type = T_MIXED;
    if (c_nil(n2) && T_POINTER(n3->mod)) {
	/*
	 * expr ? nil : expr
	 */
	type = n3->mod;
    } else if (c_nil(n3) && T_POINTER(n2->mod)) {
	/*
	 * expr ? expr : nil;
	 */
	type = n2->mod;
    } else if (typechecking) {
	/*
	 * typechecked
	 */
	if (n2->mod == T_VOID || n3->mod == T_VOID) {
	    /* result can never be used */
	    type = T_VOID;
	} else {
	    type = c_tmatch(n2->mod, n3->mod);
	    if (type == T_NIL) {
		/* no typechecking here, just let the result be mixed */
		type = T_MIXED;
	    }
	}
    }

    n1 = node_bin(N_QUEST, type, n1, node_bin(N_PAIR, 0, n2, n3));
    if ((type & T_TYPE) == T_CLASS && str_cmp(n2->class, n3->class) == 0) {
	n1->class = n2->class;
    }
    return n1;
}

/*
 * NAME:	assign()
 * DESCRIPTION:	handle the assignment operator
 */
static node *assign(n1, n2)
register node *n1, *n2;
{
    char tnbuf1[17], tnbuf2[17];

    if (typechecking && (!c_nil(n2) || !T_POINTER(n1->mod))) {
	/*
	 * typechecked
	 */
	if (c_tmatch(n1->mod, n2->mod) == T_NIL) {
	    c_error("incompatible types for = (%s, %s)",
		    i_typename(tnbuf1, n1->mod), i_typename(tnbuf2, n2->mod));
	} else if ((n1->mod != T_MIXED && n2->mod == T_MIXED) ||
		   (n1->mod == T_CLASS &&
		    (n2->mod != T_CLASS || str_cmp(n1->class, n2->class) != 0)))
	{
	    n2 = node_mon(N_CAST, n1->mod, n2);
	    n2->class = n1->class;
	}
    }

    n2 = node_bin(N_ASSIGN, n1->mod, n1, n2);
    n2->class = n1->class;
    return n2;
}

/*
 * NAME:	comma()
 * DESCRIPTION:	handle the comma operator, rearranging the order of the
 *		expression if needed
 */
static node *comma(n1, n2)
register node *n1, *n2;
{
    if (n2->type == N_COMMA) {
	/* a, (b, c) --> (a, b), c */
	n2->l.left = comma(n1, n2->l.left);
	return n2;
    } else {
	n1 = node_bin(N_COMMA, n2->mod, n1, n2);
	n1->class = n2->class;
	return n1;
    }
}
