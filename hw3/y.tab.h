/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    DE = 258,                      /* DE  */
    ME = 259,                      /* ME  */
    SE = 260,                      /* SE  */
    AE = 261,                      /* AE  */
    NE = 262,                      /* NE  */
    EQ = 263,                      /* EQ  */
    GE = 264,                      /* GE  */
    LE = 265,                      /* LE  */
    ASSIGN = 266,                  /* ASSIGN  */
    AND = 267,                     /* AND  */
    OR = 268,                      /* OR  */
    NOT = 269,                     /* NOT  */
    MOD = 270,                     /* MOD  */
    UMINUS = 271,                  /* UMINUS  */
    LOWER_THAN_ELSE = 272,         /* LOWER_THAN_ELSE  */
    ELSE = 273,                    /* ELSE  */
    BREAK = 274,                   /* BREAK  */
    CHAR = 275,                    /* CHAR  */
    CASE = 276,                    /* CASE  */
    CLASS = 277,                   /* CLASS  */
    CONTINUE = 278,                /* CONTINUE  */
    DECLARE = 279,                 /* DECLARE  */
    DO = 280,                      /* DO  */
    IF = 281,                      /* IF  */
    EXIT = 282,                    /* EXIT  */
    FOR = 283,                     /* FOR  */
    FUNCTION = 284,                /* FUNCTION  */
    LOOP = 285,                    /* LOOP  */
    PRINT = 286,                   /* PRINT  */
    PRINTLN = 287,                 /* PRINTLN  */
    RETURN = 288,                  /* RETURN  */
    VAR = 289,                     /* VAR  */
    REAL = 290,                    /* REAL  */
    ARRAY = 291,                   /* ARRAY  */
    OF = 292,                      /* OF  */
    END = 293,                     /* END  */
    PROCEDURE = 294,               /* PROCEDURE  */
    CONST = 295,                   /* CONST  */
    CBEGIN = 296,                  /* CBEGIN  */
    PUT = 297,                     /* PUT  */
    GET = 298,                     /* GET  */
    RESULT = 299,                  /* RESULT  */
    WHEN = 300,                    /* WHEN  */
    SKIP = 301,                    /* SKIP  */
    THEN = 302,                    /* THEN  */
    DEFAULT = 303,                 /* DEFAULT  */
    DECREASING = 304,              /* DECREASING  */
    IN = 305,                      /* IN  */
    TRUE = 306,                    /* TRUE  */
    FALSE = 307,                   /* FALSE  */
    str = 308,                     /* str  */
    id = 309,                      /* id  */
    integer = 310,                 /* integer  */
    real = 311,                    /* real  */
    KW_STRING = 312,               /* KW_STRING  */
    INT = 313,                     /* INT  */
    FLOAT = 314,                   /* FLOAT  */
    BOOL = 315                     /* BOOL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define DE 258
#define ME 259
#define SE 260
#define AE 261
#define NE 262
#define EQ 263
#define GE 264
#define LE 265
#define ASSIGN 266
#define AND 267
#define OR 268
#define NOT 269
#define MOD 270
#define UMINUS 271
#define LOWER_THAN_ELSE 272
#define ELSE 273
#define BREAK 274
#define CHAR 275
#define CASE 276
#define CLASS 277
#define CONTINUE 278
#define DECLARE 279
#define DO 280
#define IF 281
#define EXIT 282
#define FOR 283
#define FUNCTION 284
#define LOOP 285
#define PRINT 286
#define PRINTLN 287
#define RETURN 288
#define VAR 289
#define REAL 290
#define ARRAY 291
#define OF 292
#define END 293
#define PROCEDURE 294
#define CONST 295
#define CBEGIN 296
#define PUT 297
#define GET 298
#define RESULT 299
#define WHEN 300
#define SKIP 301
#define THEN 302
#define DEFAULT 303
#define DECREASING 304
#define IN 305
#define TRUE 306
#define FALSE 307
#define str 308
#define id 309
#define integer 310
#define real 311
#define KW_STRING 312
#define INT 313
#define FLOAT 314
#define BOOL 315

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 408 "hw3.y"

    Token                    token;

#line 191 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
