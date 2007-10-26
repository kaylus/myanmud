#ifndef BISON_Y_TAB_H
# define BISON_Y_TAB_H

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


extern YYSTYPE yylval;

#endif /* not BISON_Y_TAB_H */
