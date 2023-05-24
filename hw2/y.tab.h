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
    BOOL = 274,                    /* BOOL  */
    BREAK = 275,                   /* BREAK  */
    CHAR = 276,                    /* CHAR  */
    CASE = 277,                    /* CASE  */
    CLASS = 278,                   /* CLASS  */
    CONTINUE = 279,                /* CONTINUE  */
    DECLARE = 280,                 /* DECLARE  */
    DO = 281,                      /* DO  */
    IF = 282,                      /* IF  */
    EXIT = 283,                    /* EXIT  */
    FLOAT = 284,                   /* FLOAT  */
    FOR = 285,                     /* FOR  */
    FUNCTION = 286,                /* FUNCTION  */
    INT = 287,                     /* INT  */
    LOOP = 288,                    /* LOOP  */
    PRINT = 289,                   /* PRINT  */
    PRINTLN = 290,                 /* PRINTLN  */
    RETURN = 291,                  /* RETURN  */
    STRING = 292,                  /* STRING  */
    VAR = 293,                     /* VAR  */
    REAL = 294,                    /* REAL  */
    ARRAY = 295,                   /* ARRAY  */
    OF = 296,                      /* OF  */
    END = 297,                     /* END  */
    PROCEDURE = 298,               /* PROCEDURE  */
    CONST = 299,                   /* CONST  */
    CBEGIN = 300,                  /* CBEGIN  */
    PUT = 301,                     /* PUT  */
    GET = 302,                     /* GET  */
    RESULT = 303,                  /* RESULT  */
    WHEN = 304,                    /* WHEN  */
    SKIP = 305,                    /* SKIP  */
    THEN = 306,                    /* THEN  */
    DEFAULT = 307,                 /* DEFAULT  */
    DECREASING = 308,              /* DECREASING  */
    TRUE = 309,                    /* TRUE  */
    FALSE = 310,                   /* FALSE  */
    string = 311,                  /* string  */
    id = 312,                      /* id  */
    integer = 313,                 /* integer  */
    real = 314                     /* real  */
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
#define BOOL 274
#define BREAK 275
#define CHAR 276
#define CASE 277
#define CLASS 278
#define CONTINUE 279
#define DECLARE 280
#define DO 281
#define IF 282
#define EXIT 283
#define FLOAT 284
#define FOR 285
#define FUNCTION 286
#define INT 287
#define LOOP 288
#define PRINT 289
#define PRINTLN 290
#define RETURN 291
#define STRING 292
#define VAR 293
#define REAL 294
#define ARRAY 295
#define OF 296
#define END 297
#define PROCEDURE 298
#define CONST 299
#define CBEGIN 300
#define PUT 301
#define GET 302
#define RESULT 303
#define WHEN 304
#define SKIP 305
#define THEN 306
#define DEFAULT 307
#define DECREASING 308
#define TRUE 309
#define FALSE 310
#define string 311
#define id 312
#define integer 313
#define real 314

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 12 "hw2.y"

    Hash*          symbol;
    int                      ivalue;
    char*                    str;
    float                    fvalue;
    _Bool                    bvalue;
    //identifier_type*           identifier;
    //value_type identifier_value_type;

#line 195 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
