#ifndef lint
static char const yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.28 2000/01/17 02:04:06 bde Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar = (YYEMPTY))
#define yyerrok (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
static int yygrowstack();
#define YYPREFIX "yy"
#line 3 "parse.y"
#include "parse.h"
#include "TextBuffer.h"
#include "nedit.h"
#include "rbTree.h"
#include "interpret.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <sys/param.h>

/* Macros to add error processing to AddOp and AddSym calls */
#define ADD_OP(op)                                                                                                                                                                                                                             \
	if (!AddOp(op, &ErrMsg))                                                                                                                                                                                                                   \
	return 1
#define ADD_SYM(sym)                                                                                                                                                                                                                           \
	if (!AddSym(sym, &ErrMsg))                                                                                                                                                                                                                 \
	return 1
#define ADD_IMMED(val)                                                                                                                                                                                                                         \
	if (!AddImmediate(val, &ErrMsg))                                                                                                                                                                                                           \
	return 1
#define ADD_BR_OFF(to)                                                                                                                                                                                                                         \
	if (!AddBranchOffset(to, &ErrMsg))                                                                                                                                                                                                         \
	return 1
#define SET_BR_OFF(from, to) ((from)->value) = ((Inst *)(to)) - ((Inst *)(from))

/* Max. length for a string constant (... there shouldn't be a maximum) */
#define MAX_STRING_CONST_LEN 5000

static int yyerror(char *s);
static int yylex(void);
int yyparse(void);
static int follow(char expect, int yes, int no);
static int follow2(char expect1, int yes1, char expect2, int yes2, int no);
static int follow_non_whitespace(char expect, int yes, int no);
static Symbol *matchesActionRoutine(char **inPtr);

static char *ErrMsg;
static char *InPtr;
extern Inst *LoopStack[];   /* addresses of break, cont stmts */
extern Inst **LoopStackPtr; /*  to fill at the end of a loop */

#line 57 "parse.y"
typedef union {
	Symbol *sym;
	Inst *inst;
	int nArgs;
} YYSTYPE;
#line 76 "y.tab.c"
#define YYERRCODE 256
#define NUMBER 257
#define STRING 258
#define SYMBOL 259
#define DELETE 260
#define ARG_LOOKUP 261
#define IF 262
#define WHILE 263
#define ELSE 264
#define FOR 265
#define BREAK 266
#define CONTINUE 267
#define RETURN 268
#define IF_NO_ELSE 269
#define ADDEQ 270
#define SUBEQ 271
#define MULEQ 272
#define DIVEQ 273
#define MODEQ 274
#define ANDEQ 275
#define OREQ 276
#define CONCAT 277
#define OR 278
#define AND 279
#define GT 280
#define GE 281
#define LT 282
#define LE 283
#define EQ 284
#define NE 285
#define IN 286
#define UNARY_MINUS 287
#define NOT 288
#define INCR 289
#define DECR 290
#define POW 291
const short yylhs[] = {
    -1, 0, 0, 0,  0,  13, 13, 13, 12, 12, 14, 14, 14, 14, 14, 16, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 10, 3, 3,  3,
    1,  1, 1, 17, 17, 19, 19, 18, 18, 9,  20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 5,  4,  6,  2,  2,  7,  8, 11, 11,
};
const short yylen[] = {
    2, 2, 5, 4, 1, 5, 4, 1, 1, 2, 3, 6, 9, 6, 10, 0, 9, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 4, 2, 2, 2, 2, 1, 0, 1, 3,
    0, 1, 3, 1, 2, 1, 4, 1, 4, 1, 1, 1, 1, 4, 3,  4, 3, 1, 4, 3, 3, 3, 3, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 3, 1, 1, 1, 0, 1, 1, 1, 0, 2,
};
const short yydefred[] = {
    0,  4,  0,  0,  0, 0, 0, 93,  94, 0, 0, 0, 0, 0, 100, 101, 0, 0,   0,  0,  8,   0,  0, 0,  44, 46, 0, 58,  0, 0,  100, 100, 61, 62, 0, 0,  0,   0,   0, 0,   0, 100, 0, 0,   0, 0,   0,  0,   0, 0, 0,  0,
    0,  0,  0,  0,  0, 0, 9, 100, 0,  0, 0, 0, 0, 0, 0,   0,   0, 89,  91, 0,  0,   0,  0, 88, 90, 0,  0, 100, 0, 99, 98,  0,   0,  0,  0, 0,  0,   0,   0, 0,   0, 0,   0, 0,   0, 0,   0,  0,   0, 0, 0,  3,
    0,  0,  0,  49, 0, 0, 0, 0,   0,  0, 0, 0, 0, 0, 42,  0,   0, 100, 0,  67, 0,   65, 0, 0,  0,  0,  0, 0,   0, 0,  0,   0,   0,  0,  0, 0,  0,   0,   0, 0,   0, 0,   0, 2,   0, 0,   0,  100, 0, 0, 0,  0,
    64, 66, 69, 0,  0, 0, 0, 0,   50, 0, 0, 0, 0, 0, 0,   0,   0, 0,   38, 39, 100, 0,  7, 15, 0,  13, 0, 0,   0, 0,  0,   0,   0,  0,  0, 95, 100, 100, 0, 100, 0, 0,   0, 100, 0, 100, 12, 16,  0, 0, 14,
};
const short yydgoto[] = {
    2, 62, 65, 106, 16, 17, 192, 99, 100, 161, 18, 3, 19, 177, 178, 21, 193, 63, 28, 22, 43,
};
const short yysindex[] = {
    -242, 0,    0,   221, 6,   -243, -15, 0,   0,   32,   42,  603, -209, -204, 0,   0,   54,  58,  768,  1179, 0,   77,  22,  843, 0,    0,   843, 0,   38,  843, 0,   0,   0,   0,   8, 44,  843,  843, -150, -142, 843, 0,
    747,  1368, 0,   46,  0,   49,   369, 101, 843, 843,  843, 843, 843,  843,  843, 843, 0,   0,   843,  843,  -26, 843, 843, 82,  1368, 121, 121, 0,   0,   843, 975, -87, -87, 0,   0, 837, 121,  0,   1368, 0,    0,   843,
    843,  843,  843, 843, 843, 843,  843, 843, 843, 843,  843, 843, 843,  843,  843, 843, 843, 843, 843,  0,    328, -31, -27, 0,   104,  843, 843, 843, 843, 843, 843, 843, 121, -22, 0, 843, -21,  0,   -17,  0,    -35, 0,
    121,  65,   163, -9,  -9,  -9,   -9,  -9,  -9,  -9,   2,   2,   -87,  -87,  -87, -87, -7,  23,  1250, 39,   40,  0,   843, 843, 504,  0,   624, 843, 0,   292, 0,   0,   0,   0,   0, 110, 1368, 94,  0,    292,  843, 843,
    843,  843,  843, 843, 843, 843,  0,   0,   0,   -110, 0,   0,   504,  0,    843, 843, 843, 843, 843,  843,  843, 843, 665, 0,   0,    0,   55,  0,   464, 292, 292, 0,   121, 0,   0, 0,   292,  121, 0,
};
const short yyrindex[] = {
    700, 0,    0,    0,   -91, 0,   0,    0,    0,    0,    0,   0,   0,   0,   0,   0,   0,   0,    0,   155, 0,   0,   0,  0,   0,   0,  56, 0,   0,   116, 0,   0,   0,   0,   383, 128, 0,   0,   0,   0, 0, 0,
    0,   179,  10,   0,   108, 0,   0,    -18,  116,  0,    0,   0,   0,   0,   0,   0,   0,   0,    51,  47,  0,   -1,  51, 0,   -28, 1,  11, 0,   0,   56,  0,   419, 455, 0,   0,   0,   21,  0,   431, 0, 0, 0,
    0,   0,    0,    0,   0,   0,   0,    0,    0,    0,    0,   0,   0,   0,   51,  0,   0,   51,   51,  0,   0,   -91, 0,  0,   0,   75, 80, 117, 481, 503, 568, 611, 53,  0,   0,   0,   0,   0,   0,   0, 0, 0,
    63,  1342, 1337, 899, 934, 969, 1197, 1232, 1267, 1302, 827, 863, 491, 527, 563, 791, 0,   1377, 877, 0,   0,   0,   0,  127, 0,   0,  69, 18,  118, 0,   0,   0,   0,   391, 539, 0,   122, 0,   0,   0, 0, 0,
    0,   0,    0,    0,   0,   0,   0,    0,    0,    115,  0,   0,   81,  0,   613, 755, 815, 875,  932, 936, 940, 942, 0,  0,   0,   0,  0,  0,   0,   0,   0,   0,   73,  0,   0,   0,   0,   105, 0,
};
const short yygindex[] = {
    0, 444, -45, -16, 0, 0, 0, 0, 0, 0, 0, 1272, -42, 37, 26, -30, 0, 24, 0, 129, 1632,
};
#define YYTABLESIZE 1821
const short yytable[] = {
    56,  17,  96,  84,  98,  108, 104, 94,  92,  26,  93,  18, 95,  97,  1,   118, 27, 150, 119, 107, 43,  20,  119, 119, 156, 29,  48, 119, 96,  20,  23,  97,  149, 94,  92,  42,  93,  119, 95,  96,  52,  48,  30,  52,  94,  58,  26,  61,
    71,  95,  44,  43,  31,  10,  43,  46,  98,  21,  157, 53, 96,  84,  53,  19,  77, 94,  92,  23,  93,  43,  95,  152, 154, 6,   20, 109, 110, 111, 112, 113, 114, 115, 98,  119, 119, 22,  158, 59,  21,  83,  23,  21,  52,  98,  49,  51,
    199, 51,  50,  150, 51,  56,  96,  84,  163, 5,   21,  94, 92,  75,  93,  53,  95, 60,  98,  11,  22,  76,  45,  22,  164, 23,  48, 121, 23,  48,  17,  24,  29,  64,  58,  15,  159, 160, 22,  72,  18,  101, 68,  23,  102, 45,  47,  153,
    51,  151, 20,  83,  196, 45,  107, 179, 45,  180, 191, 1,  98,  96,  24,  29,  57, 24,  29,  60,  194, 68,  68,  45,  68,  68,  68, 68,  68,  68,  0,   68,  24,  29,  10,  47,  47,  47,  47,  47,  47,  47,  96,  68,  19,  54,  182, 183,
    184, 185, 186, 187, 188, 189, 6,   56,  96,  0,   181, 0,  97,  94,  92,  0,   93, 59,  95,  0,   0,   0,   0,   0,   20,  0,   0,  54,  54,  68,  58,  54,  0,   0,   0,   0,   0,   0,   5,   15,  0,   0,   202, 203, 0,   0,   54,  0,
    11,  206, 0,   81,  82,  85,  86,  87,  88,  89,  90,  91, 68,  0,   98,  148, 97, 0,   24,  25,  17,  17,  0,   17,  17,  17,  17, 17,  17,  17,  18,  18,  54,  18,  18,  18,  18,  18,  18,  18,  20,  20,  97,  20,  20,  20,  20,  20,
    20,  20,  17,  17,  0,   97,  0,   24,  25,  69,  70,  0,  18,  18,  15,  85,  86, 87,  88,  89,  90,  91,  20,  20,  10,  10,  97, 10,  10,  10,  10,  10,  10,  10,  19,  19,  0,   19,  19,  19,  19,  19,  19,  19,  6,   6,   0,   6,
    6,   6,   6,   6,   6,   6,   10,  10,  14,  85,  86,  87, 88,  89,  90,  91,  19, 19,  0,   0,   97,  0,   0,   0,   105, 5,   6,  6,   5,   5,   0,   5,   5,   5,   5,   5,   5,   5,   11,  11,  0,   11,  11,  15,  11,  11,  11,  11,
    0,   68,  68,  68,  0,   68,  12,  13,  0,   63,  5,   5,  0,   0,   0,   0,   0,  40,  0,   0,   11,  11,  68,  68,  68,  68,  68, 68,  68,  68,  68,  176, 68,  68,  68,  68,  63,  63,  0,   0,   63,  63,  63,  63,  63,  76,  63,  0,
    40,  0,   0,   40,  54,  54,  54,  0,   54,  55,  63,  85, 86,  87,  88,  89,  90, 91,  40,  0,   0,   147, 97,  0,   76,  76,  0,  76,  76,  76,  76,  76,  76,  87,  76,  54,  54,  54,  0,   55,  55,  0,   63,  55,  63,  0,   76,  0,
    4,   5,   57,  6,   7,   0,   8,   9,   10,  11,  55,  25, 87,  87,  103, 87,  87, 87,  87,  87,  87,  72,  87,  0,   117, 0,   0,  63,  120, 0,   12,  13,  76,  26,  87,  122, 0,   0,   0,   0,   0,   0,   25,  0,   55,  25,  0,   0,
    72,  72,  0,   72,  72,  72,  72,  72,  72,  73,  72,  0,  25,  0,   142, 76,  26, 145, 146, 26,  87,  41,  72,  4,   5,   0,   6,  7,   0,   8,   9,   10,  11,  0,   26,  0,   73,  73,  0,   73,  73,  73,  73,  73,  73,  74,  73,  0,
    0,   0,   27,  87,  41,  12,  13,  41,  72,  0,   73,  4,  5,   201, 6,   7,   0,  8,   9,   10,  11,  0,   41,  0,   74,  74,  0,  74,  74,  74,  74,  74,  74,  27,  74,  0,   27,  41,  0,   72,  0,   12,  13,  0,   73,  28,  74,  30,
    0,   0,   0,   27,  4,   5,   57,  6,   7,   0,   8,   9,  10,  11,  0,   0,   63, 63,  63,  40,  63,  0,   0,   0,   36,  0,   0,  73,  28,  0,   30,  28,  74,  30,  12,  13,  0,   63,  63,  63,  63,  63,  63,  63,  63,  63,  28,  63,
    30,  0,   63,  15,  76,  76,  76,  0,   76,  0,   0,   0,  0,   166, 0,   74,  55, 55,  55,  0,   55,  0,   0,   0,   0,   76,  76, 76,  76,  76,  76,  76,  76,  76,  0,   76,  76,  76,  100, 0,   87,  87,  87,  0,   87,  0,   0,   55,
    55,  55,  0,   4,   5,   0,   6,   7,   0,   8,   9,   10, 11,  87,  87,  87,  87, 87,  87,  87,  87,  87,  0,   87,  87,  87,  0,  0,   72,  72,  72,  0,   72,  12,  13,  0,   0,   79,  0,   0,   0,   0,   0,   4,   5,   31,  0,   0,
    0,   72,  72,  72,  72,  72,  72,  72,  72,  72,  0,   72, 72,  72,  0,   0,   73, 73,  73,  40,  73,  0,   195, 0,   36,  12,  13, 0,   31,  0,   0,   31,  0,   75,  0,   0,   0,   73,  73,  73,  73,  73,  73,  73,  73,  73,  31,  73,
    73,  73,  0,   0,   74,  74,  74,  100, 74,  32,  0,   0,  75,  75,  0,   75,  75, 75,  75,  75,  75,  70,  75,  0,   0,   74,  74, 74,  74,  74,  74,  74,  74,  74,  75,  74,  74,  74,  0,   0,   32,  0,   0,   32,  32,  33,  34,  0,
    35,  70,  0,   70,  70,  0,   70,  70,  70,  71,  32,  0,  0,   40,  125, 0,   0,  0,   36,  40,  75,  33,  70,  86,  36,  0,   0,  37,  38,  39,  167, 168, 169, 170, 171, 172, 173, 71,  0,   71,  71,  0,   71,  71,  71,  77,  0,   0,
    0,   174, 175, 75,  33,  86,  86,  33,  70,  86,  71,  0,  4,   5,   0,   6,   7,  0,   8,   9,   10,  11,  33,  0,   86,  77,  0,  77,  77,  0,   34,  77,  78,  0,   35,  0,   0,   0,   36,  70,  37,  0,   12,  13,  71,  0,   77,  100,
    100, 0,   100, 100, 0,   100, 100, 100, 100, 0,   86,  0,  78,  34,  78,  78,  34, 35,  78,  79,  35,  36,  0,   37,  36,  0,   37, 71,  0,   100, 100, 34,  77,  78,  0,   35,  0,   0,   0,   36,  0,   37,  0,   0,   32,  33,  34,  79,
    35,  79,  79,  0,   0,   79,  0,   40,  0,   0,   0,   0,  36,  0,   0,   77,  0,  0,   0,   78,  79,  0,   0,   0,   0,   0,   0,  37,  38,  39,  51,  52,  53,  54,  55,  56,  57,  0,   0,   0,   75,  75,  75,  0,   75,  0,   0,   0,
    0,   0,   78,  0,   0,   0,   79,  0,   0,   0,   0,   0,  123, 75,  75,  75,  75, 75,  75,  75,  75,  75,  0,   75,  75,  75,  0,  0,   70,  70,  70,  0,   70,  0,   0,   0,   0,   79,  32,  33,  34,  0,   35,  0,   32,  33,  34,  0,
    35,  70,  70,  70,  70,  70,  70,  70,  70,  70,  0,   70, 70,  70,  0,   0,   71, 71,  71,  0,   71,  37,  38,  39,  0,   0,   0,  37,  38,  39,  86,  86,  86,  0,   86,  0,   0,   71,  71,  71,  71,  71,  71,  71,  71,  71,  0,   71,
    71,  71,  0,   86,  77,  77,  77,  0,   77,  0,   0,   0,  0,   86,  86,  86,  0,  0,   0,   0,   0,   0,   0,   0,   0,   77,  77, 77,  77,  77,  77,  77,  77,  77,  0,   77,  77,  77,  0,   78,  78,  78,  0,   78,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   80,  0,   0,   0,   0,  78,  78,  78,  78,  78, 78,  78,  78,  78,  0,   78,  78,  78,  0,   79, 79,  79,  0,   79,  0,   32,  33,  34,  80,  35,  80,  80,  0,   0,   80,  81,  0,   0,   0,   0,   79,
    79,  79,  79,  79,  79,  79,  79,  79,  80,  79,  79,  79, 0,   0,   0,   37,  38, 39,  0,   0,   0,   0,   81,  0,   81,  81,  0,  0,   81,  82,  0,   0,   0,   0,   0,   0,   0,   0,   48,  96,  84,  0,   80,  81,  94,  92,  0,   93,
    0,   95,  0,   0,   0,   0,   67,  68,  0,   82,  0,   82, 82,  0,   0,   82,  92, 78,  0,   0,   0,   0,   0,   0,   0,   80,  0,  0,   0,   81,  82,  0,   0,   0,   0,   116, 0,   0,   0,   0,   0,   0,   0,   0,   92,  98,  92,  92,
    0,   0,   92,  83,  0,   0,   0,   126, 84,  0,   0,   0,  81,  0,   0,   0,   82, 92,  0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   0,   0,   83,  83,  0,   83,  83,  0,   0,   83,  84,  84,  0,   0,   84,  85,  0,   0,   0,   82,
    0,   155, 0,   92,  83,  0,   0,   0,   0,   84,  0,   0,  0,   96,  84,  0,   0,  0,   94,  92,  0,   93,  0,   95,  0,   85,  85, 0,   0,   85,  0,   165, 0,   0,   92,  0,   0,   0,   83,  0,   0,   0,   0,   84,  85,  0,   4,   5,
    0,   6,   7,   0,   8,   9,   10,  11,  190, 0,   0,   0,  0,   0,   80,  80,  80, 0,   80,  98,  0,   83,  0,   0,   197, 198, 84, 200, 12,  13,  85,  204, 0,   205, 0,   80,  80,  80,  80,  80,  80,  80,  80,  80,  0,   80,  80,  80,
    0,   81,  81,  81,  83,  81,  0,   0,   0,   0,   0,   0,  0,   0,   0,   0,   0,  0,   0,   0,   0,   0,   81,  81,  81,  81,  81, 81,  81,  81,  81,  0,   81,  81,  81,  0,   82,  82,  82,  0,   82,  82,  85,  86,  87,  88,  89,  90,
    91,  0,   0,   0,   0,   97,  0,   0,   0,   82,  82,  82, 82,  82,  82,  82,  82, 82,  0,   82,  82,  82,  0,   92,  92,  92,  0,  92,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   92,  92,  92,  92,
    92,  92,  92,  92,  92,  0,   92,  92,  92,  0,   83,  83, 83,  0,   83,  84,  84, 84,  0,   84,  0,   0,   0,   0,   0,   0,   0,  0,   0,   0,   0,   83,  83,  0,   0,   0,   84,  84,  0,   0,   0,   83,  83,  83,  0,   0,   84,  84,
    84,  0,   85,  85,  85,  0,   85,  0,   0,   0,   0,   0,  0,   0,   81,  82,  85, 86,  87,  88,  89,  90,  91,  85,  85,  0,   0,  97,  0,   66,  0,   0,   0,   85,  85,  85,  73,  74,  0,   0,   0,   0,   80,  0,   0,   0,   0,   0,
    0,   0,   66,  0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   80,  0,   80,  0,  0,   0,   0,   0,   0,   0,   0,   124, 0,   0,  0,   0,   80,  0,   0,   0,   0,   0,   127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
    140, 141, 0,   143, 144, 0,   0,   0,   0,   0,   0,   0,  0,   80,  80,  80,  80, 80,  80,  80,  0,   0,   0,   0,   0,   0,   0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   162, 66,  0,   0,   0,   80,  0,   0,  0,   0,   0,   0,   0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   80,  80,  80,  80,  80,  80,  80,  80,
};
const short yycheck[] = {
    91,  0,   37,  38,  91,  50,  48,  42,  43,  40,  45,  0,   47,  41,  256, 41,  259, 44,  44,  49,  10,  0,   44,  44,  41,  40,  44,  44,  37,  3,   61,  59,  59,  42,  43,  11,  45,  44,  47,  37,  41,  59,  10,  44,  42,  19,  40,
    23,  40,  47,  259, 41,  10,  0,   44,  259, 91,  10,  93,  41,  37,  38,  44,  0,   40,  42,  43,  61,  45,  59,  47,  93,  93,  0,   48,  51,  52,  53,  54,  55,  56,  57,  91,  44,  44,  10,  93,  10,  41,  124, 10,  44,  93,  91,
    40,  44,  41,  41,  40,  44,  44,  91,  37,  38,  149, 0,   59,  42,  43,  259, 45,  93,  47,  91,  91,  0,   41,  259, 10,  44,  150, 41,  41,  41,  44,  44,  125, 10,  10,  91,  104, 10,  93,  93,  59,  91,  125, 91,  10,  59,  91,
    12,  13,  119, 93,  41,  125, 124, 190, 41,  180, 41,  44,  59,  264, 0,   91,  41,  41,  41,  91,  44,  44,  41,  180, 37,  38,  59,  40,  41,  42,  43,  44,  45,  -1,  47,  59,  59,  125, 270, 271, 272, 273, 274, 275, 276, 59,  59,
    125, 10,  166, 167, 168, 169, 170, 171, 172, 173, 125, 91,  37,  -1,  165, -1,  291, 42,  43,  -1,  45,  91,  47,  -1,  -1,  -1,  -1,  -1,  190, -1,  -1,  40,  41,  93,  196, 44,  -1,  -1,  -1,  -1,  -1,  -1,  125, 10,  -1,  -1,  197,
    198, -1,  -1,  59,  -1,  125, 204, -1,  278, 279, 280, 281, 282, 283, 284, 285, 286, 124, -1,  91,  286, 291, -1,  289, 290, 259, 260, -1,  262, 263, 264, 265, 266, 267, 268, 259, 260, 93,  262, 263, 264, 265, 266, 267, 268, 259, 260,
    291, 262, 263, 264, 265, 266, 267, 268, 289, 290, -1,  291, -1,  289, 290, 289, 290, -1,  289, 290, 10,  280, 281, 282, 283, 284, 285, 286, 289, 290, 259, 260, 291, 262, 263, 264, 265, 266, 267, 268, 259, 260, -1,  262, 263, 264, 265,
    266, 267, 268, 259, 260, -1,  262, 263, 264, 265, 266, 267, 268, 289, 290, 123, 280, 281, 282, 283, 284, 285, 286, 289, 290, -1,  -1,  291, -1,  -1,  -1,  259, 260, 289, 290, 259, 260, -1,  262, 263, 264, 265, 266, 267, 268, 259, 260,
    -1,  262, 263, 10,  265, 266, 267, 268, -1,  257, 258, 259, -1,  261, 289, 290, -1,  10,  289, 290, -1,  -1,  -1,  -1,  -1,  10,  -1,  -1,  289, 290, 278, 279, 280, 281, 282, 283, 284, 285, 286, 123, 288, 289, 290, 291, 37,  38,  -1,
    -1,  41,  42,  43,  44,  45,  10,  47,  -1,  41,  -1,  -1,  44,  257, 258, 259, -1,  261, 10,  59,  280, 281, 282, 283, 284, 285, 286, 59,  -1,  -1,  125, 291, -1,  37,  38,  -1,  40,  41,  42,  43,  44,  45,  10,  47,  288, 289, 290,
    -1,  40,  41,  -1,  91,  44,  93,  -1,  59,  -1,  259, 260, 91,  262, 263, -1,  265, 266, 267, 268, 59,  10,  37,  38,  125, 40,  41,  42,  43,  44,  45,  10,  47,  -1,  60,  -1,  -1,  124, 64,  -1,  289, 290, 93,  10,  59,  71,  -1,
    -1,  -1,  -1,  -1,  -1,  41,  -1,  93,  44,  -1,  -1,  37,  38,  -1,  40,  41,  42,  43,  44,  45,  10,  47,  -1,  59,  -1,  98,  124, 41,  101, 102, 44,  93,  10,  59,  259, 260, -1,  262, 263, -1,  265, 266, 267, 268, -1,  59,  -1,
    37,  38,  -1,  40,  41,  42,  43,  44,  45,  10,  47,  -1,  -1,  -1,  10,  124, 41,  289, 290, 44,  93,  -1,  59,  259, 260, 125, 262, 263, -1,  265, 266, 267, 268, -1,  59,  -1,  37,  38,  -1,  40,  41,  42,  43,  44,  45,  41,  47,
    -1,  44,  10,  -1,  124, -1,  289, 290, -1,  93,  10,  59,  10,  -1,  -1,  -1,  59,  259, 260, 91,  262, 263, -1,  265, 266, 267, 268, -1,  -1,  257, 258, 259, 40,  261, -1,  -1,  -1,  45,  -1,  -1,  124, 41,  -1,  41,  44,  93,  44,
    289, 290, -1,  278, 279, 280, 281, 282, 283, 284, 285, 286, 59,  288, 59,  -1,  291, 10,  257, 258, 259, -1,  261, -1,  -1,  -1,  -1,  61,  -1,  124, 257, 258, 259, -1,  261, -1,  -1,  -1,  -1,  278, 279, 280, 281, 282, 283, 284, 285,
    286, -1,  288, 289, 290, 10,  -1,  257, 258, 259, -1,  261, -1,  -1,  288, 289, 290, -1,  259, 260, -1,  262, 263, -1,  265, 266, 267, 268, 278, 279, 280, 281, 282, 283, 284, 285, 286, -1,  288, 289, 290, -1,  -1,  257, 258, 259, -1,
    261, 289, 290, -1,  -1,  10,  -1,  -1,  -1,  -1,  -1,  259, 260, 10,  -1,  -1,  -1,  278, 279, 280, 281, 282, 283, 284, 285, 286, -1,  288, 289, 290, -1,  -1,  257, 258, 259, 40,  261, -1,  125, -1,  45,  289, 290, -1,  41,  -1,  -1,
    44,  -1,  10,  -1,  -1,  -1,  278, 279, 280, 281, 282, 283, 284, 285, 286, 59,  288, 289, 290, -1,  -1,  257, 258, 259, 123, 261, 10,  -1,  -1,  37,  38,  -1,  40,  41,  42,  43,  44,  45,  10,  47,  -1,  -1,  278, 279, 280, 281, 282,
    283, 284, 285, 286, 59,  288, 289, 290, -1,  -1,  41,  -1,  -1,  44,  257, 258, 259, -1,  261, 38,  -1,  40,  41,  -1,  43,  44,  45,  10,  59,  -1,  -1,  40,  41,  -1,  -1,  -1,  45,  40,  93,  10,  59,  10,  45,  -1,  -1,  288, 289,
    290, 270, 271, 272, 273, 274, 275, 276, 38,  -1,  40,  41,  -1,  43,  44,  45,  10,  -1,  -1,  -1,  289, 290, 124, 41,  40,  41,  44,  93,  44,  59,  -1,  259, 260, -1,  262, 263, -1,  265, 266, 267, 268, 59,  -1,  59,  38,  -1,  40,
    41,  -1,  10,  44,  10,  -1,  10,  -1,  -1,  -1,  10,  124, 10,  -1,  289, 290, 93,  -1,  59,  259, 260, -1,  262, 263, -1,  265, 266, 267, 268, -1,  93,  -1,  38,  41,  40,  41,  44,  41,  44,  10,  44,  41,  -1,  41,  44,  -1,  44,
    124, -1,  289, 290, 59,  93,  59,  -1,  59,  -1,  -1,  -1,  59,  -1,  59,  -1,  -1,  257, 258, 259, 38,  261, 40,  41,  -1,  -1,  44,  -1,  40,  -1,  -1,  -1,  -1,  45,  -1,  -1,  124, -1,  -1,  -1,  93,  59,  -1,  -1,  -1,  -1,  -1,
    -1,  288, 289, 290, 270, 271, 272, 273, 274, 275, 276, -1,  -1,  -1,  257, 258, 259, -1,  261, -1,  -1,  -1,  -1,  -1,  124, -1,  -1,  -1,  93,  -1,  -1,  -1,  -1,  -1,  93,  278, 279, 280, 281, 282, 283, 284, 285, 286, -1,  288, 289,
    290, -1,  -1,  257, 258, 259, -1,  261, -1,  -1,  -1,  -1,  124, 257, 258, 259, -1,  261, -1,  257, 258, 259, -1,  261, 278, 279, 280, 281, 282, 283, 284, 285, 286, -1,  288, 289, 290, -1,  -1,  257, 258, 259, -1,  261, 288, 289, 290,
    -1,  -1,  -1,  288, 289, 290, 257, 258, 259, -1,  261, -1,  -1,  278, 279, 280, 281, 282, 283, 284, 285, 286, -1,  288, 289, 290, -1,  278, 257, 258, 259, -1,  261, -1,  -1,  -1,  -1,  288, 289, 290, -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1,  -1,  278, 279, 280, 281, 282, 283, 284, 285, 286, -1,  288, 289, 290, -1,  257, 258, 259, -1,  261, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  10,  -1,  -1,  -1,  -1,  278, 279, 280, 281, 282, 283, 284, 285, 286, -1,
    288, 289, 290, -1,  257, 258, 259, -1,  261, -1,  257, 258, 259, 38,  261, 40,  41,  -1,  -1,  44,  10,  -1,  -1,  -1,  -1,  278, 279, 280, 281, 282, 283, 284, 285, 286, 59,  288, 289, 290, -1,  -1,  -1,  288, 289, 290, -1,  -1,  -1,
    -1,  38,  -1,  40,  41,  -1,  -1,  44,  10,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  14,  37,  38,  -1,  93,  59,  42,  43,  -1,  45,  -1,  47,  -1,  -1,  -1,  -1,  30,  31,  -1,  38,  -1,  40,  41,  -1,  -1,  44,  10,  41,  -1,  -1,
    -1,  -1,  -1,  -1,  -1,  124, -1,  -1,  -1,  93,  59,  -1,  -1,  -1,  -1,  59,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  38,  91,  40,  41,  -1,  -1,  44,  10,  -1,  -1,  -1,  79,  10,  -1,  -1,  -1,  124, -1,  -1,  -1,  93,  59,  -1,
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  124, 38,  -1,  40,  41,  -1,  -1,  44,  40,  41,  -1,  -1,  44,  10,  -1,  -1,  -1,  124, -1,  121, -1,  93,  59,  -1,  -1,  -1,  -1,  59,  -1,  -1,  -1,  37,  38,  -1,  -1,  -1,
    42,  43,  -1,  45,  -1,  47,  -1,  40,  41,  -1,  -1,  44,  -1,  151, -1,  -1,  124, -1,  -1,  -1,  93,  -1,  -1,  -1,  -1,  93,  59,  -1,  259, 260, -1,  262, 263, -1,  265, 266, 267, 268, 176, -1,  -1,  -1,  -1,  -1,  257, 258, 259,
    -1,  261, 91,  -1,  124, -1,  -1,  192, 193, 124, 195, 289, 290, 93,  199, -1,  201, -1,  278, 279, 280, 281, 282, 283, 284, 285, 286, -1,  288, 289, 290, -1,  257, 258, 259, 124, 261, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1,  -1,  -1,  -1,  -1,  -1,  278, 279, 280, 281, 282, 283, 284, 285, 286, -1,  288, 289, 290, -1,  257, 258, 259, -1,  261, 279, 280, 281, 282, 283, 284, 285, 286, -1,  -1,  -1,  -1,  291, -1,  -1,  -1,  278, 279, 280, 281, 282, 283,
    284, 285, 286, -1,  288, 289, 290, -1,  257, 258, 259, -1,  261, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  278, 279, 280, 281, 282, 283, 284, 285, 286, -1,  288, 289, 290, -1,  257, 258, 259, -1,
    261, 257, 258, 259, -1,  261, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  278, 279, -1,  -1,  -1,  278, 279, -1,  -1,  -1,  288, 289, 290, -1,  -1,  288, 289, 290, -1,  257, 258, 259, -1,  261, -1,  -1,  -1,  -1,  -1,  -1,
    -1,  278, 279, 280, 281, 282, 283, 284, 285, 286, 278, 279, -1,  -1,  291, -1,  29,  -1,  -1,  -1,  288, 289, 290, 36,  37,  -1,  -1,  -1,  -1,  42,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  50,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1,  61,  -1,  63,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  72,  -1,  -1,  -1,  -1,  77,  -1,  -1,  -1,  -1,  -1,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  -1,  99,  100, -1,  -1,  -1,  -1,  -1,  -1,
    -1,  -1,  109, 110, 111, 112, 113, 114, 115, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  148, 149, -1,  -1,  -1,  153,
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  182, 183, 184, 185, 186, 187, 188, 189,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 291
#if YYDEBUG
const char *const yyname[] = {
    "end-of-file", 0,        0,    0,     0,        0,        0,        0,        0,            0,     "'\\n'", 0,             0,     0,       0,          0,        0,            0,       0,       0,       0,       0,       0,
    0,             0,        0,    0,     0,        0,        0,        0,        0,            0,     0,       0,             0,     0,       "'%'",      "'&'",    0,            "'('",   "')'",   "'*'",   "'+'",   "','",   "'-'",
    0,             "'/'",    0,    0,     0,        0,        0,        0,        0,            0,     0,       0,             0,     "';'",   0,          "'='",    0,            0,       0,       0,       0,       0,       0,
    0,             0,        0,    0,     0,        0,        0,        0,        0,            0,     0,       0,             0,     0,       0,          0,        0,            0,       0,       0,       0,       0,       "'['",
    0,             "']'",    0,    0,     0,        0,        0,        0,        0,            0,     0,       0,             0,     0,       0,          0,        0,            0,       0,       0,       0,       0,       0,
    0,             0,        0,    0,     0,        0,        0,        0,        "'{'",        "'|'", "'}'",   0,             0,     0,       0,          0,        0,            0,       0,       0,       0,       0,       0,
    0,             0,        0,    0,     0,        0,        0,        0,        0,            0,     0,       0,             0,     0,       0,          0,        0,            0,       0,       0,       0,       0,       0,
    0,             0,        0,    0,     0,        0,        0,        0,        0,            0,     0,       0,             0,     0,       0,          0,        0,            0,       0,       0,       0,       0,       0,
    0,             0,        0,    0,     0,        0,        0,        0,        0,            0,     0,       0,             0,     0,       0,          0,        0,            0,       0,       0,       0,       0,       0,
    0,             0,        0,    0,     0,        0,        0,        0,        0,            0,     0,       0,             0,     0,       0,          0,        0,            0,       0,       0,       0,       0,       0,
    0,             0,        0,    0,     0,        0,        0,        0,        0,            0,     0,       0,             0,     0,       0,          0,        0,            0,       0,       0,       0,       0,       0,
    0,             0,        0,    0,     "NUMBER", "STRING", "SYMBOL", "DELETE", "ARG_LOOKUP", "IF",  "WHILE", "ELSE",        "FOR", "BREAK", "CONTINUE", "RETURN", "IF_NO_ELSE", "ADDEQ", "SUBEQ", "MULEQ", "DIVEQ", "MODEQ", "ANDEQ",
    "OREQ",        "CONCAT", "OR", "AND", "GT",     "GE",     "LT",     "LE",     "EQ",         "NE",  "IN",    "UNARY_MINUS", "NOT", "INCR",  "DECR",     "POW",
};
const char *const yyrule[] = {
    "$accept : program",                                      "program : blank stmts",                             "program : blank '{' blank stmts '}'",                             "program : blank '{' blank '}'",
    "program : error",                                        "block : '{' blank stmts '}' blank",                 "block : '{' blank '}' blank",                                     "block : stmt",
    "stmts : stmt",                                           "stmts : stmts stmt",                                "stmt : simpstmt '\\n' blank",                                     "stmt : IF '(' cond ')' blank block",
    "stmt : IF '(' cond ')' blank block else blank block",    "stmt : while '(' cond ')' blank block",             "stmt : for '(' comastmts ';' cond ';' comastmts ')' blank block", "$$1 :",
    "stmt : for '(' SYMBOL IN arrayexpr ')' $$1 blank block", "stmt : BREAK '\\n' blank",                          "stmt : CONTINUE '\\n' blank",                                     "stmt : RETURN expr '\\n' blank",
    "stmt : RETURN '\\n' blank",                              "simpstmt : SYMBOL '=' expr",                        "simpstmt : evalsym ADDEQ expr",                                   "simpstmt : evalsym SUBEQ expr",
    "simpstmt : evalsym MULEQ expr",                          "simpstmt : evalsym DIVEQ expr",                     "simpstmt : evalsym MODEQ expr",                                   "simpstmt : evalsym ANDEQ expr",
    "simpstmt : evalsym OREQ expr",                           "simpstmt : DELETE arraylv '[' arglist ']'",         "simpstmt : initarraylv '[' arglist ']' '=' expr",                 "simpstmt : initarraylv '[' arglist ']' ADDEQ expr",
    "simpstmt : initarraylv '[' arglist ']' SUBEQ expr",      "simpstmt : initarraylv '[' arglist ']' MULEQ expr", "simpstmt : initarraylv '[' arglist ']' DIVEQ expr",               "simpstmt : initarraylv '[' arglist ']' MODEQ expr",
    "simpstmt : initarraylv '[' arglist ']' ANDEQ expr",      "simpstmt : initarraylv '[' arglist ']' OREQ expr",  "simpstmt : initarraylv '[' arglist ']' INCR",                     "simpstmt : initarraylv '[' arglist ']' DECR",
    "simpstmt : INCR initarraylv '[' arglist ']'",            "simpstmt : DECR initarraylv '[' arglist ']'",       "simpstmt : SYMBOL '(' arglist ')'",                               "simpstmt : INCR SYMBOL",
    "simpstmt : SYMBOL INCR",                                 "simpstmt : DECR SYMBOL",                            "simpstmt : SYMBOL DECR",                                          "evalsym : SYMBOL",
    "comastmts :",                                            "comastmts : simpstmt",                              "comastmts : comastmts ',' simpstmt",                              "arglist :",
    "arglist : expr",                                         "arglist : arglist ',' expr",                        "expr : numexpr",                                                  "expr : expr numexpr",
    "initarraylv : SYMBOL",                                   "initarraylv : initarraylv '[' arglist ']'",         "arraylv : SYMBOL",                                                "arraylv : arraylv '[' arglist ']'",
    "arrayexpr : numexpr",                                    "numexpr : NUMBER",                                  "numexpr : STRING",                                                "numexpr : SYMBOL",
    "numexpr : SYMBOL '(' arglist ')'",                       "numexpr : '(' expr ')'",                            "numexpr : ARG_LOOKUP '[' numexpr ']'",                            "numexpr : ARG_LOOKUP '[' ']'",
    "numexpr : ARG_LOOKUP",                                   "numexpr : numexpr '[' arglist ']'",                 "numexpr : numexpr '+' numexpr",                                   "numexpr : numexpr '-' numexpr",
    "numexpr : numexpr '*' numexpr",                          "numexpr : numexpr '/' numexpr",                     "numexpr : numexpr '%' numexpr",                                   "numexpr : numexpr POW numexpr",
    "numexpr : '-' numexpr",                                  "numexpr : numexpr GT numexpr",                      "numexpr : numexpr GE numexpr",                                    "numexpr : numexpr LT numexpr",
    "numexpr : numexpr LE numexpr",                           "numexpr : numexpr EQ numexpr",                      "numexpr : numexpr NE numexpr",                                    "numexpr : numexpr '&' numexpr",
    "numexpr : numexpr '|' numexpr",                          "numexpr : numexpr and numexpr",                     "numexpr : numexpr or numexpr",                                    "numexpr : NOT numexpr",
    "numexpr : INCR SYMBOL",                                  "numexpr : SYMBOL INCR",                             "numexpr : DECR SYMBOL",                                           "numexpr : SYMBOL DECR",
    "numexpr : numexpr IN numexpr",                           "while : WHILE",                                     "for : FOR",                                                       "else : ELSE",
    "cond :",                                                 "cond : numexpr",                                    "and : AND",                                                       "or : OR",
    "blank :",                                                "blank : blank '\\n'",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 443 "parse.y"
/* User Subroutines Section */

/*
** Parse a null terminated string and create a program from it (this is the
** parser entry point).  The program created by this routine can be
** executed using ExecuteProgram.  Returns program on success, or nullptr
** on failure.  If the command failed, the error message is returned
** as a pointer to a static string in msg, and the length of the string up
** to where parsing failed in stoppedAt.
*/
Program *ParseMacro(char *expr, char **msg, char **stoppedAt) {
	Program *prog;

	BeginCreatingProgram();

	/* call yyparse to parse the string and check for success.  If the parse
	   failed, return the error message and string index (the grammar aborts
	   parsing at the first error) */
	InPtr = expr;
	if (yyparse()) {
		*msg = ErrMsg;
		*stoppedAt = InPtr;
		FreeProgram(FinishCreatingProgram());
		return nullptr;
	}

	/* get the newly created program */
	prog = FinishCreatingProgram();

	/* parse succeeded */
	*msg = "";
	*stoppedAt = InPtr;
	return prog;
}

static int yylex(void) {
	int i, len;
	Symbol *s;
	static DataValue value = {NO_TAG, {0}};
	static char escape[] = "\\\"ntbrfave";
	static char replace[] = "\\\"\n\t\b\r\f\a\v\x1B"; /* ASCII escape */

	/* skip whitespace, backslash-newline combinations, and comments, which are
	   all considered whitespace */
	for (;;) {
		if (*InPtr == '\\' && *(InPtr + 1) == '\n')
			InPtr += 2;
		else if (*InPtr == ' ' || *InPtr == '\t')
			InPtr++;
		else if (*InPtr == '#')
			while (*InPtr != '\n' && *InPtr != '\0') {
				/* Comments stop at escaped newlines */
				if (*InPtr == '\\' && *(InPtr + 1) == '\n') {
					InPtr += 2;
					break;
				}
				InPtr++;
			}
		else
			break;
	}

	/* return end of input at the end of the string */
	if (*InPtr == '\0') {
		return 0;
	}

	/* process number tokens */
	if (isdigit((unsigned char)*InPtr)) { /* number */
		char name[28];
		sscanf(InPtr, "%d%n", &value.val.n, &len);
		sprintf(name, "const %d", value.val.n);
		InPtr += len;
		value.tag = INT_TAG;
		if ((yylval.sym = LookupSymbol(name)) == nullptr)
			yylval.sym = InstallSymbol(name, CONST_SYM, value);
		return NUMBER;
	}

	/* process symbol tokens.  "define" is a special case not handled
	   by this parser, considered end of input.  Another special case
	   is action routine names which are allowed to contain '-' despite
	   the ambiguity, handled in matchesActionRoutine. */
	if (isalpha((unsigned char)*InPtr) || *InPtr == '$') {
		if ((s = matchesActionRoutine(&InPtr)) == nullptr) {
			char symName[MAX_SYM_LEN + 1], *p = symName;
			*p++ = *InPtr++;
			while (isalnum((unsigned char)*InPtr) || *InPtr == '_') {
				if (p >= symName + MAX_SYM_LEN)
					InPtr++;
				else
					*p++ = *InPtr++;
			}
			*p = '\0';
			if (!strcmp(symName, "while"))
				return WHILE;
			if (!strcmp(symName, "if"))
				return IF;
			if (!strcmp(symName, "else"))
				return ELSE;
			if (!strcmp(symName, "for"))
				return FOR;
			if (!strcmp(symName, "break"))
				return BREAK;
			if (!strcmp(symName, "continue"))
				return CONTINUE;
			if (!strcmp(symName, "return"))
				return RETURN;
			if (!strcmp(symName, "in"))
				return IN;
			if (!strcmp(symName, "$args"))
				return ARG_LOOKUP;
			if (!strcmp(symName, "delete") && follow_non_whitespace('(', SYMBOL, DELETE) == DELETE)
				return DELETE;
			if (!strcmp(symName, "define")) {
				InPtr -= 6;
				return 0;
			}
			if ((s = LookupSymbol(symName)) == nullptr) {
				s = InstallSymbol(symName, symName[0] == '$' ? (((symName[1] > '0' && symName[1] <= '9') && symName[2] == 0) ? ARG_SYM : GLOBAL_SYM) : LOCAL_SYM, value);
				s->value.tag = NO_TAG;
			}
		}
		yylval.sym = s;
		return SYMBOL;
	}

	/* Process quoted strings with embedded escape sequences:
	     For backslashes we recognise hexadecimal values with initial 'x' such
	   as "\x1B"; octal value (upto 3 oct digits with a possible leading zero)
	   such as "\33", "\033" or "\0033", and the C escapes: \", \', \n, \t, \b,
	   \r, \f, \a, \v, and the added \e for the escape character, as for REs.
	     Disallow hex/octal zero values (NUL): instead ignore the introductory
	   backslash, eg "\x0xyz" becomes "x0xyz" and "\0000hello" becomes
	   "0000hello". */

	if (*InPtr == '\"') {
		char string[MAX_STRING_CONST_LEN], *p = string;
		char *backslash;
		InPtr++;
		while (*InPtr != '\0' && *InPtr != '\"' && *InPtr != '\n') {
			if (p >= string + MAX_STRING_CONST_LEN) {
				InPtr++;
				continue;
			}
			if (*InPtr == '\\') {
				backslash = InPtr;
				InPtr++;
				if (*InPtr == '\n') {
					InPtr++;
					continue;
				}
				if (*InPtr == 'x') {
					/* a hex introducer */
					int hexValue = 0;
					const char *hexDigits = "0123456789abcdef";
					const char *hexD;
					InPtr++;
					if (*InPtr == '\0' || (hexD = strchr(hexDigits, tolower(*InPtr))) == nullptr) {
						*p++ = 'x';
					} else {
						hexValue = hexD - hexDigits;
						InPtr++;
						/* now do we have another digit? only accept one more */
						if (*InPtr != '\0' && (hexD = strchr(hexDigits, tolower(*InPtr))) != nullptr) {
							hexValue = hexD - hexDigits + (hexValue << 4);
							InPtr++;
						}
						if (hexValue != 0) {
							*p++ = (char)hexValue;
						} else {
							InPtr = backslash + 1; /* just skip the backslash */
						}
					}
					continue;
				}
				/* the RE documentation requires \0 as the octal introducer;
				   here you can start with any octal digit, but you are only
				   allowed up to three (or four if the first is '0'). */
				if ('0' <= *InPtr && *InPtr <= '7') {
					if (*InPtr == '0') {
						InPtr++; /* octal introducer: don't count this digit */
					}
					if ('0' <= *InPtr && *InPtr <= '7') {
						/* treat as octal - first digit */
						char octD = *InPtr++;
						int octValue = octD - '0';
						if ('0' <= *InPtr && *InPtr <= '7') {
							/* second digit */
							octD = *InPtr++;
							octValue = (octValue << 3) + octD - '0';
							/* now do we have another digit? can we add it?
							   if value is going to be too big for char (greater
							   than 0377), stop converting now before adding the
							   third digit */
							if ('0' <= *InPtr && *InPtr <= '7' && octValue <= 037) {
								/* third digit is acceptable */
								octD = *InPtr++;
								octValue = (octValue << 3) + octD - '0';
							}
						}
						if (octValue != 0) {
							*p++ = (char)octValue;
						} else {
							InPtr = backslash + 1; /* just skip the backslash */
						}
					} else {                   /* \0 followed by non-digits: go back to 0 */
						InPtr = backslash + 1; /* just skip the backslash */
					}
					continue;
				}
				for (i = 0; escape[i] != '\0'; i++) {
					if (escape[i] == *InPtr) {
						*p++ = replace[i];
						InPtr++;
						break;
					}
				}
				/* if we get here, we didn't recognise the character after
				   the backslash: just copy it next time round the loop */
			} else {
				*p++ = *InPtr++;
			}
		}
		*p = '\0';
		InPtr++;
		yylval.sym = InstallStringConstSymbol(string);
		return STRING;
	}

	/* process remaining two character tokens or return single char as token */
	switch (*InPtr++) {
	case '>':
		return follow('=', GE, GT);
	case '<':
		return follow('=', LE, LT);
	case '=':
		return follow('=', EQ, '=');
	case '!':
		return follow('=', NE, NOT);
	case '+':
		return follow2('+', INCR, '=', ADDEQ, '+');
	case '-':
		return follow2('-', DECR, '=', SUBEQ, '-');
	case '|':
		return follow2('|', OR, '=', OREQ, '|');
	case '&':
		return follow2('&', AND, '=', ANDEQ, '&');
	case '*':
		return follow2('*', POW, '=', MULEQ, '*');
	case '/':
		return follow('=', DIVEQ, '/');
	case '%':
		return follow('=', MODEQ, '%');
	case '^':
		return POW;
	default:
		return *(InPtr - 1);
	}
}

/*
** look ahead for >=, etc.
*/
static int follow(char expect, int yes, int no) {
	if (*InPtr++ == expect)
		return yes;
	InPtr--;
	return no;
}
static int follow2(char expect1, int yes1, char expect2, int yes2, int no) {
	char next = *InPtr++;
	if (next == expect1)
		return yes1;
	if (next == expect2)
		return yes2;
	InPtr--;
	return no;
}

static int follow_non_whitespace(char expect, int yes, int no) {
	char *localInPtr = InPtr;

	while (1) {
		if (*localInPtr == ' ' || *localInPtr == '\t') {
			++localInPtr;
		} else if (*localInPtr == '\\' && *(localInPtr + 1) == '\n') {
			localInPtr += 2;
		} else if (*localInPtr == expect) {
			return (yes);
		} else {
			return (no);
		}
	}
}

/*
** Look (way) ahead for hyphenated routine names which begin at inPtr.  A
** hyphenated name is allowed if it is pre-defined in the global symbol
** table.  If a matching name exists, returns the symbol, and update "inPtr".
**
** I know this is horrible language design, but existing nedit action routine
** names contain hyphens.  Handling them here in the lexical analysis process
** is much easier than trying to deal with it in the parser itself.  (sorry)
*/
static Symbol *matchesActionRoutine(char **inPtr) {
	char *c, *symPtr;
	int hasDash = False;
	char symbolName[MAX_SYM_LEN + 1];
	Symbol *s;

	symPtr = symbolName;
	for (c = *inPtr; isalnum((unsigned char)*c) || *c == '_' || (*c == '-' && isalnum((unsigned char)(*(c + 1)))); c++) {
		if (*c == '-')
			hasDash = True;
		*symPtr++ = *c;
	}
	if (!hasDash)
		return nullptr;
	*symPtr = '\0';
	s = LookupSymbol(symbolName);
	if (s != nullptr)
		*inPtr = c;
	return s;
}

/*
** Called by yacc to report errors (just stores for returning when
** parsing is aborted.  The error token action is to immediate abort
** parsing, so this message is immediately reported to the caller
** of ParseExpr)
*/
static int yyerror(char *s) {
	ErrMsg = s;
	return 0;
}
#line 1079 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack() {
	int newsize, i;
	short *newss;
	YYSTYPE *newvs;

	if ((newsize = yystacksize) == 0)
		newsize = YYINITSTACKSIZE;
	else if (newsize >= YYMAXDEPTH)
		return -1;
	else if ((newsize *= 2) > YYMAXDEPTH)
		newsize = YYMAXDEPTH;
	i = yyssp - yyss;
	newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) : (short *)malloc(newsize * sizeof *newss);
	if (newss == nullptr)
		return -1;
	yyss = newss;
	yyssp = newss + i;
	newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) : (YYSTYPE *)malloc(newsize * sizeof *newvs);
	if (newvs == nullptr)
		return -1;
	yyvs = newvs;
	yyvsp = newvs + i;
	yystacksize = newsize;
	yysslim = yyss + newsize - 1;
	return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else /* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* ANSI-C/C++ */
#else  /* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif /* ANSI-C/C++ */
#endif /* ! YYPARSE_PARAM */

int yyparse(YYPARSE_PARAM_ARG) YYPARSE_PARAM_DECL {
	register int yym, yyn, yystate;
#if YYDEBUG
	register const char *yys;

	if ((yys = getenv("YYDEBUG"))) {
		yyn = *yys;
		if (yyn >= '0' && yyn <= '9')
			yydebug = yyn - '0';
	}
#endif

	yynerrs = 0;
	yyerrflag = 0;
	yychar = (-1);

	if (yyss == nullptr && yygrowstack())
		goto yyoverflow;
	yyssp = yyss;
	yyvsp = yyvs;
	*yyssp = yystate = 0;

yyloop:
	if ((yyn = yydefred[yystate]))
		goto yyreduce;
	if (yychar < 0) {
		if ((yychar = yylex()) < 0)
			yychar = 0;
#if YYDEBUG
		if (yydebug) {
			yys = 0;
			if (yychar <= YYMAXTOKEN)
				yys = yyname[yychar];
			if (!yys)
				yys = "illegal-symbol";
			printf("%sdebug: state %d, reading %d (%s)\n", YYPREFIX, yystate, yychar, yys);
		}
#endif
	}
	if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 && yyn <= YYTABLESIZE && yycheck[yyn] == yychar) {
#if YYDEBUG
		if (yydebug)
			printf("%sdebug: state %d, shifting to state %d\n", YYPREFIX, yystate, yytable[yyn]);
#endif
		if (yyssp >= yysslim && yygrowstack()) {
			goto yyoverflow;
		}
		*++yyssp = yystate = yytable[yyn];
		*++yyvsp = yylval;
		yychar = (-1);
		if (yyerrflag > 0)
			--yyerrflag;
		goto yyloop;
	}
	if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 && yyn <= YYTABLESIZE && yycheck[yyn] == yychar) {
		yyn = yytable[yyn];
		goto yyreduce;
	}
	if (yyerrflag)
		goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
	goto yynewerror;
#endif
yynewerror:
	yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
	goto yyerrlab;
#endif
yyerrlab:
	++yynerrs;
yyinrecovery:
	if (yyerrflag < 3) {
		yyerrflag = 3;
		for (;;) {
			if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 && yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE) {
#if YYDEBUG
				if (yydebug)
					printf("%sdebug: state %d, error recovery shifting\
 to state %d\n",
					       YYPREFIX, *yyssp, yytable[yyn]);
#endif
				if (yyssp >= yysslim && yygrowstack()) {
					goto yyoverflow;
				}
				*++yyssp = yystate = yytable[yyn];
				*++yyvsp = yylval;
				goto yyloop;
			} else {
#if YYDEBUG
				if (yydebug)
					printf("%sdebug: error recovery discarding state %d\n", YYPREFIX, *yyssp);
#endif
				if (yyssp <= yyss)
					goto yyabort;
				--yyssp;
				--yyvsp;
			}
		}
	} else {
		if (yychar == 0)
			goto yyabort;
#if YYDEBUG
		if (yydebug) {
			yys = 0;
			if (yychar <= YYMAXTOKEN)
				yys = yyname[yychar];
			if (!yys)
				yys = "illegal-symbol";
			printf("%sdebug: state %d, error recovery discards token %d (%s)\n", YYPREFIX, yystate, yychar, yys);
		}
#endif
		yychar = (-1);
		goto yyloop;
	}
yyreduce:
#if YYDEBUG
	if (yydebug)
		printf("%sdebug: state %d, reducing by rule %d (%s)\n", YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
	yym = yylen[yyn];
	yyval = yyvsp[1 - yym];
	switch (yyn) {
	case 1:
#line 91 "parse.y"
	{
		ADD_OP(OP_RETURN_NO_VAL);
		return 0;
	} break;
	case 2:
#line 94 "parse.y"
	{
		ADD_OP(OP_RETURN_NO_VAL);
		return 0;
	} break;
	case 3:
#line 97 "parse.y"
	{
		ADD_OP(OP_RETURN_NO_VAL);
		return 0;
	} break;
	case 4:
#line 100 "parse.y"
	{
		return 1;
	} break;
	case 11:
#line 112 "parse.y"
	{
		SET_BR_OFF(yyvsp[-3].inst, GetPC());
	} break;
	case 12:
#line 115 "parse.y"
	{
		SET_BR_OFF(yyvsp[-6].inst, (yyvsp[-2].inst + 1));
		SET_BR_OFF(yyvsp[-2].inst, GetPC());
	} break;
	case 13:
#line 118 "parse.y"
	{
		ADD_OP(OP_BRANCH);
		ADD_BR_OFF(yyvsp[-5].inst);
		SET_BR_OFF(yyvsp[-3].inst, GetPC());
		FillLoopAddrs(GetPC(), yyvsp[-5].inst);
	} break;
	case 14:
#line 122 "parse.y"
	{
		FillLoopAddrs(GetPC() + 2 + (yyvsp[-3].inst - (yyvsp[-5].inst + 1)), GetPC());
		SwapCode(yyvsp[-5].inst + 1, yyvsp[-3].inst, GetPC());
		ADD_OP(OP_BRANCH);
		ADD_BR_OFF(yyvsp[-7].inst);
		SET_BR_OFF(yyvsp[-5].inst, GetPC());
	} break;
	case 15:
#line 127 "parse.y"
	{
		Symbol *iterSym = InstallIteratorSymbol();
		ADD_OP(OP_BEGIN_ARRAY_ITER);
		ADD_SYM(iterSym);
		ADD_OP(OP_ARRAY_ITER);
		ADD_SYM(yyvsp[-3].sym);
		ADD_SYM(iterSym);
		ADD_BR_OFF(0);
	} break;
	case 16:
#line 132 "parse.y"
	{
		ADD_OP(OP_BRANCH);
		ADD_BR_OFF(yyvsp[-4].inst + 2);
		SET_BR_OFF(yyvsp[-4].inst + 5, GetPC());
		FillLoopAddrs(GetPC(), yyvsp[-4].inst + 2);
	} break;
	case 17:
#line 137 "parse.y"
	{
		ADD_OP(OP_BRANCH);
		ADD_BR_OFF(0);
		if (AddBreakAddr(GetPC() - 1)) {
			yyerror("break outside loop");
			YYERROR;
		}
	} break;
	case 18:
#line 143 "parse.y"
	{
		ADD_OP(OP_BRANCH);
		ADD_BR_OFF(0);
		if (AddContinueAddr(GetPC() - 1)) {
			yyerror("continue outside loop");
			YYERROR;
		}
	} break;
	case 19:
#line 149 "parse.y"
	{
		ADD_OP(OP_RETURN);
	} break;
	case 20:
#line 152 "parse.y"
	{
		ADD_OP(OP_RETURN_NO_VAL);
	} break;
	case 21:
#line 156 "parse.y"
	{
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[-2].sym);
	} break;
	case 22:
#line 159 "parse.y"
	{
		ADD_OP(OP_ADD);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[-2].sym);
	} break;
	case 23:
#line 162 "parse.y"
	{
		ADD_OP(OP_SUB);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[-2].sym);
	} break;
	case 24:
#line 165 "parse.y"
	{
		ADD_OP(OP_MUL);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[-2].sym);
	} break;
	case 25:
#line 168 "parse.y"
	{
		ADD_OP(OP_DIV);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[-2].sym);
	} break;
	case 26:
#line 171 "parse.y"
	{
		ADD_OP(OP_MOD);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[-2].sym);
	} break;
	case 27:
#line 174 "parse.y"
	{
		ADD_OP(OP_BIT_AND);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[-2].sym);
	} break;
	case 28:
#line 177 "parse.y"
	{
		ADD_OP(OP_BIT_OR);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[-2].sym);
	} break;
	case 29:
#line 180 "parse.y"
	{
		ADD_OP(OP_ARRAY_DELETE);
		ADD_IMMED(yyvsp[-1].nArgs);
	} break;
	case 30:
#line 183 "parse.y"
	{
		ADD_OP(OP_ARRAY_ASSIGN);
		ADD_IMMED(yyvsp[-3].nArgs);
	} break;
	case 31:
#line 186 "parse.y"
	{
		ADD_OP(OP_ARRAY_REF_ASSIGN_SETUP);
		ADD_IMMED(1);
		ADD_IMMED(yyvsp[-3].nArgs);
		ADD_OP(OP_ADD);
		ADD_OP(OP_ARRAY_ASSIGN);
		ADD_IMMED(yyvsp[-3].nArgs);
	} break;
	case 32:
#line 191 "parse.y"
	{
		ADD_OP(OP_ARRAY_REF_ASSIGN_SETUP);
		ADD_IMMED(1);
		ADD_IMMED(yyvsp[-3].nArgs);
		ADD_OP(OP_SUB);
		ADD_OP(OP_ARRAY_ASSIGN);
		ADD_IMMED(yyvsp[-3].nArgs);
	} break;
	case 33:
#line 196 "parse.y"
	{
		ADD_OP(OP_ARRAY_REF_ASSIGN_SETUP);
		ADD_IMMED(1);
		ADD_IMMED(yyvsp[-3].nArgs);
		ADD_OP(OP_MUL);
		ADD_OP(OP_ARRAY_ASSIGN);
		ADD_IMMED(yyvsp[-3].nArgs);
	} break;
	case 34:
#line 201 "parse.y"
	{
		ADD_OP(OP_ARRAY_REF_ASSIGN_SETUP);
		ADD_IMMED(1);
		ADD_IMMED(yyvsp[-3].nArgs);
		ADD_OP(OP_DIV);
		ADD_OP(OP_ARRAY_ASSIGN);
		ADD_IMMED(yyvsp[-3].nArgs);
	} break;
	case 35:
#line 206 "parse.y"
	{
		ADD_OP(OP_ARRAY_REF_ASSIGN_SETUP);
		ADD_IMMED(1);
		ADD_IMMED(yyvsp[-3].nArgs);
		ADD_OP(OP_MOD);
		ADD_OP(OP_ARRAY_ASSIGN);
		ADD_IMMED(yyvsp[-3].nArgs);
	} break;
	case 36:
#line 211 "parse.y"
	{
		ADD_OP(OP_ARRAY_REF_ASSIGN_SETUP);
		ADD_IMMED(1);
		ADD_IMMED(yyvsp[-3].nArgs);
		ADD_OP(OP_BIT_AND);
		ADD_OP(OP_ARRAY_ASSIGN);
		ADD_IMMED(yyvsp[-3].nArgs);
	} break;
	case 37:
#line 216 "parse.y"
	{
		ADD_OP(OP_ARRAY_REF_ASSIGN_SETUP);
		ADD_IMMED(1);
		ADD_IMMED(yyvsp[-3].nArgs);
		ADD_OP(OP_BIT_OR);
		ADD_OP(OP_ARRAY_ASSIGN);
		ADD_IMMED(yyvsp[-3].nArgs);
	} break;
	case 38:
#line 221 "parse.y"
	{
		ADD_OP(OP_ARRAY_REF_ASSIGN_SETUP);
		ADD_IMMED(0);
		ADD_IMMED(yyvsp[-2].nArgs);
		ADD_OP(OP_INCR);
		ADD_OP(OP_ARRAY_ASSIGN);
		ADD_IMMED(yyvsp[-2].nArgs);
	} break;
	case 39:
#line 226 "parse.y"
	{
		ADD_OP(OP_ARRAY_REF_ASSIGN_SETUP);
		ADD_IMMED(0);
		ADD_IMMED(yyvsp[-2].nArgs);
		ADD_OP(OP_DECR);
		ADD_OP(OP_ARRAY_ASSIGN);
		ADD_IMMED(yyvsp[-2].nArgs);
	} break;
	case 40:
#line 231 "parse.y"
	{
		ADD_OP(OP_ARRAY_REF_ASSIGN_SETUP);
		ADD_IMMED(0);
		ADD_IMMED(yyvsp[-1].nArgs);
		ADD_OP(OP_INCR);
		ADD_OP(OP_ARRAY_ASSIGN);
		ADD_IMMED(yyvsp[-1].nArgs);
	} break;
	case 41:
#line 236 "parse.y"
	{
		ADD_OP(OP_ARRAY_REF_ASSIGN_SETUP);
		ADD_IMMED(0);
		ADD_IMMED(yyvsp[-1].nArgs);
		ADD_OP(OP_DECR);
		ADD_OP(OP_ARRAY_ASSIGN);
		ADD_IMMED(yyvsp[-1].nArgs);
	} break;
	case 42:
#line 241 "parse.y"
	{
		ADD_OP(OP_SUBR_CALL);
		ADD_SYM(PromoteToGlobal(yyvsp[-3].sym));
		ADD_IMMED(yyvsp[-1].nArgs);
	} break;
	case 43:
#line 245 "parse.y"
	{
		ADD_OP(OP_PUSH_SYM);
		ADD_SYM(yyvsp[0].sym);
		ADD_OP(OP_INCR);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[0].sym);
	} break;
	case 44:
#line 249 "parse.y"
	{
		ADD_OP(OP_PUSH_SYM);
		ADD_SYM(yyvsp[-1].sym);
		ADD_OP(OP_INCR);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[-1].sym);
	} break;
	case 45:
#line 253 "parse.y"
	{
		ADD_OP(OP_PUSH_SYM);
		ADD_SYM(yyvsp[0].sym);
		ADD_OP(OP_DECR);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[0].sym);
	} break;
	case 46:
#line 257 "parse.y"
	{
		ADD_OP(OP_PUSH_SYM);
		ADD_SYM(yyvsp[-1].sym);
		ADD_OP(OP_DECR);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[-1].sym);
	} break;
	case 47:
#line 262 "parse.y"
	{
		yyval.sym = yyvsp[0].sym;
		ADD_OP(OP_PUSH_SYM);
		ADD_SYM(yyvsp[0].sym);
	} break;
	case 48:
#line 266 "parse.y"
	{
		yyval.inst = GetPC();
	} break;
	case 49:
#line 269 "parse.y"
	{
		yyval.inst = GetPC();
	} break;
	case 50:
#line 272 "parse.y"
	{
		yyval.inst = GetPC();
	} break;
	case 51:
#line 276 "parse.y"
	{
		yyval.nArgs = 0;
	} break;
	case 52:
#line 279 "parse.y"
	{
		yyval.nArgs = 1;
	} break;
	case 53:
#line 282 "parse.y"
	{
		yyval.nArgs = yyvsp[-2].nArgs + 1;
	} break;
	case 55:
#line 287 "parse.y"
	{
		ADD_OP(OP_CONCAT);
	} break;
	case 56:
#line 291 "parse.y"
	{
		ADD_OP(OP_PUSH_ARRAY_SYM);
		ADD_SYM(yyvsp[0].sym);
		ADD_IMMED(1);
	} break;
	case 57:
#line 294 "parse.y"
	{
		ADD_OP(OP_ARRAY_REF);
		ADD_IMMED(yyvsp[-1].nArgs);
	} break;
	case 58:
#line 298 "parse.y"
	{
		ADD_OP(OP_PUSH_ARRAY_SYM);
		ADD_SYM(yyvsp[0].sym);
		ADD_IMMED(0);
	} break;
	case 59:
#line 301 "parse.y"
	{
		ADD_OP(OP_ARRAY_REF);
		ADD_IMMED(yyvsp[-1].nArgs);
	} break;
	case 60:
#line 305 "parse.y"
	{
		yyval.inst = GetPC();
	} break;
	case 61:
#line 309 "parse.y"
	{
		ADD_OP(OP_PUSH_SYM);
		ADD_SYM(yyvsp[0].sym);
	} break;
	case 62:
#line 312 "parse.y"
	{
		ADD_OP(OP_PUSH_SYM);
		ADD_SYM(yyvsp[0].sym);
	} break;
	case 63:
#line 315 "parse.y"
	{
		ADD_OP(OP_PUSH_SYM);
		ADD_SYM(yyvsp[0].sym);
	} break;
	case 64:
#line 318 "parse.y"
	{
		ADD_OP(OP_SUBR_CALL);
		ADD_SYM(PromoteToGlobal(yyvsp[-3].sym));
		ADD_IMMED(yyvsp[-1].nArgs);
		ADD_OP(OP_FETCH_RET_VAL);
	} break;
	case 66:
#line 324 "parse.y"
	{
		ADD_OP(OP_PUSH_ARG);
	} break;
	case 67:
#line 327 "parse.y"
	{
		ADD_OP(OP_PUSH_ARG_COUNT);
	} break;
	case 68:
#line 330 "parse.y"
	{
		ADD_OP(OP_PUSH_ARG_ARRAY);
	} break;
	case 69:
#line 333 "parse.y"
	{
		ADD_OP(OP_ARRAY_REF);
		ADD_IMMED(yyvsp[-1].nArgs);
	} break;
	case 70:
#line 336 "parse.y"
	{
		ADD_OP(OP_ADD);
	} break;
	case 71:
#line 339 "parse.y"
	{
		ADD_OP(OP_SUB);
	} break;
	case 72:
#line 342 "parse.y"
	{
		ADD_OP(OP_MUL);
	} break;
	case 73:
#line 345 "parse.y"
	{
		ADD_OP(OP_DIV);
	} break;
	case 74:
#line 348 "parse.y"
	{
		ADD_OP(OP_MOD);
	} break;
	case 75:
#line 351 "parse.y"
	{
		ADD_OP(OP_POWER);
	} break;
	case 76:
#line 354 "parse.y"
	{
		ADD_OP(OP_NEGATE);
	} break;
	case 77:
#line 357 "parse.y"
	{
		ADD_OP(OP_GT);
	} break;
	case 78:
#line 360 "parse.y"
	{
		ADD_OP(OP_GE);
	} break;
	case 79:
#line 363 "parse.y"
	{
		ADD_OP(OP_LT);
	} break;
	case 80:
#line 366 "parse.y"
	{
		ADD_OP(OP_LE);
	} break;
	case 81:
#line 369 "parse.y"
	{
		ADD_OP(OP_EQ);
	} break;
	case 82:
#line 372 "parse.y"
	{
		ADD_OP(OP_NE);
	} break;
	case 83:
#line 375 "parse.y"
	{
		ADD_OP(OP_BIT_AND);
	} break;
	case 84:
#line 378 "parse.y"
	{
		ADD_OP(OP_BIT_OR);
	} break;
	case 85:
#line 381 "parse.y"
	{
		ADD_OP(OP_AND);
		SET_BR_OFF(yyvsp[-1].inst, GetPC());
	} break;
	case 86:
#line 384 "parse.y"
	{
		ADD_OP(OP_OR);
		SET_BR_OFF(yyvsp[-1].inst, GetPC());
	} break;
	case 87:
#line 387 "parse.y"
	{
		ADD_OP(OP_NOT);
	} break;
	case 88:
#line 390 "parse.y"
	{
		ADD_OP(OP_PUSH_SYM);
		ADD_SYM(yyvsp[0].sym);
		ADD_OP(OP_INCR);
		ADD_OP(OP_DUP);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[0].sym);
	} break;
	case 89:
#line 394 "parse.y"
	{
		ADD_OP(OP_PUSH_SYM);
		ADD_SYM(yyvsp[-1].sym);
		ADD_OP(OP_DUP);
		ADD_OP(OP_INCR);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[-1].sym);
	} break;
	case 90:
#line 398 "parse.y"
	{
		ADD_OP(OP_PUSH_SYM);
		ADD_SYM(yyvsp[0].sym);
		ADD_OP(OP_DECR);
		ADD_OP(OP_DUP);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[0].sym);
	} break;
	case 91:
#line 402 "parse.y"
	{
		ADD_OP(OP_PUSH_SYM);
		ADD_SYM(yyvsp[-1].sym);
		ADD_OP(OP_DUP);
		ADD_OP(OP_DECR);
		ADD_OP(OP_ASSIGN);
		ADD_SYM(yyvsp[-1].sym);
	} break;
	case 92:
#line 406 "parse.y"
	{
		ADD_OP(OP_IN_ARRAY);
	} break;
	case 93:
#line 410 "parse.y"
	{
		yyval.inst = GetPC();
		StartLoopAddrList();
	} break;
	case 94:
#line 414 "parse.y"
	{
		StartLoopAddrList();
		yyval.inst = GetPC();
	} break;
	case 95:
#line 418 "parse.y"
	{
		ADD_OP(OP_BRANCH);
		yyval.inst = GetPC();
		ADD_BR_OFF(0);
	} break;
	case 96:
#line 422 "parse.y"
	{
		ADD_OP(OP_BRANCH_NEVER);
		yyval.inst = GetPC();
		ADD_BR_OFF(0);
	} break;
	case 97:
#line 425 "parse.y"
	{
		ADD_OP(OP_BRANCH_FALSE);
		yyval.inst = GetPC();
		ADD_BR_OFF(0);
	} break;
	case 98:
#line 429 "parse.y"
	{
		ADD_OP(OP_DUP);
		ADD_OP(OP_BRANCH_FALSE);
		yyval.inst = GetPC();
		ADD_BR_OFF(0);
	} break;
	case 99:
#line 434 "parse.y"
	{
		ADD_OP(OP_DUP);
		ADD_OP(OP_BRANCH_TRUE);
		yyval.inst = GetPC();
		ADD_BR_OFF(0);
	} break;
#line 1868 "y.tab.c"
	}
	yyssp -= yym;
	yystate = *yyssp;
	yyvsp -= yym;
	yym = yylhs[yyn];
	if (yystate == 0 && yym == 0) {
#if YYDEBUG
		if (yydebug)
			printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n",
			       YYPREFIX, YYFINAL);
#endif
		yystate = YYFINAL;
		*++yyssp = YYFINAL;
		*++yyvsp = yyval;
		if (yychar < 0) {
			if ((yychar = yylex()) < 0)
				yychar = 0;
#if YYDEBUG
			if (yydebug) {
				yys = 0;
				if (yychar <= YYMAXTOKEN)
					yys = yyname[yychar];
				if (!yys)
					yys = "illegal-symbol";
				printf("%sdebug: state %d, reading %d (%s)\n", YYPREFIX, YYFINAL, yychar, yys);
			}
#endif
		}
		if (yychar == 0)
			goto yyaccept;
		goto yyloop;
	}
	if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 && yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
		yystate = yytable[yyn];
	else
		yystate = yydgoto[yym];
#if YYDEBUG
	if (yydebug)
		printf("%sdebug: after reduction, shifting from state %d \
to state %d\n",
		       YYPREFIX, *yyssp, yystate);
#endif
	if (yyssp >= yysslim && yygrowstack()) {
		goto yyoverflow;
	}
	*++yyssp = yystate;
	*++yyvsp = yyval;
	goto yyloop;
yyoverflow:
	yyerror("yacc stack overflow");
yyabort:
	return (1);
yyaccept:
	return (0);
}
