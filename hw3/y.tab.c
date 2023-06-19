/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "hw3.y"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "SymbolTable.h"
#include "SymbolDesc.h"

#define Trace(t)        printf(t)
extern FILE *yyin;
int yylex(void);
extern "C"
{
    int yyparse(void);
    int yywrap()
    {
        return 1;
    }
}

void yyerror(char *s);
FILE *output;
Hash *idtab, *current_idtab;
bool has_error = false;
int varList[255]={-1};
int size = 0;
int LabelIndex = 0;
std::string ClassName;
int hasMain = 0;
int hasProgram = 0;
int loop_number = 0;
std::vector<int> exitLabels = std::vector<int>(255, -1);
int if_number = 0;
std::vector<int> ifLabels = std::vector<int>(255, -1);

union uDependency{
	int low;
	int high;
	int baseType;
	int retType;
	int argType;
	
	int _int;
	bool _bool;
	double _real;
	char * _str;
	void * value;
};

struct SymbolDesc
{
    int symtype = vunknown;
    bool readonly = false;
    bool global = false;
    bool hasValue = false;
	bool returnByFun = false;
    int iValue;
    char * sValue;
    bool bValue;
    std::vector<uDependency> symdeps;
    int symindex;
};

// class variable{
// public:

// 	std::string type;
// }


// class Layer{
// public:
// 	std::vector<variable> varList;
// }

// std::vector<Layer> scope;
// int number_scope = 0;

char* SymType2Str(int type){
	switch(type){
	case sinteger :
		return "int";
	case sreal :
		return "float";
	case sboolean :
		return "bool";
	case sstring :
		return "java.lang.String";
	case none :
		return "void";
	default:
		return "unknown";
	}
}
std::string SymType2JBStr(int type){
	switch(type){
	case sinteger :
		return "int";
	case sreal :
		return "float";
	case sboolean :
		return "bool";
	case sstring :
		return "java.lang.String";
	case sarray :
		return "array";
	case sfunction :
		return "function";
	case sprocedure :
		return "procedure";
	case none :
		return "void";
	default:
		return "unknown";
	}
}


int Symbol2Token(int symbol){
	switch(symbol){
		case SymbolType::sinteger:
			return  TokenType::vint;
		break;
		case SymbolType::sreal:
			return  TokenType::vreal;
		break;
		case SymbolType::sstring:
			return  TokenType::vstring;
		break;
		case SymbolType::sboolean:
			return  TokenType::vbool;
		break;
		case SymbolType::none:
			return TokenType::blank;
		break;
		default:
			return TokenType::vunknown;
		break;
	}
}

int Token2Symbol(int token){
	switch(token){
		case vint:
			return sinteger;
		break;
		case vreal : 
			return sreal;
		break;
		case vstring :
			return sstring;
		break;
		case vbool :
			return sboolean;
		break;
		case blank:
			return none;
		break;
		default:
			return sunknown;
		break;
	}
}

std::vector<std::map<std::string,SymbolDesc>> SymTableStack;
std::vector<int> SymTableIndexStack;
std::vector<int> SCOPERET;

void InitialTableStack(){
	SymTableStack.push_back(std::map<std::string,SymbolDesc>());
	SymTableIndexStack.push_back(0);
}

void ENTERSCOPE(){
	SymTableStack.push_back(std::map<std::string,SymbolDesc>());
	SymTableIndexStack.push_back(0);
	//number_scope++;
	//scope.push_back(
}

void LEAVESCOPE(){
	SymTableStack.pop_back();
	SymTableIndexStack.pop_back();
}


int GETSCOPERETURN(){
	if(SCOPERET.size()==0){
		return SymbolType::none;
	}
	else {
		return SCOPERET.back();
	}
}



bool seize(std::string id,SymbolDesc *& sd){
	for(int i = SymTableStack.size() - 1 ; i>=0;--i){
		if(SymTableStack[i].count(id)){
			sd = &(SymTableStack[i][id]);
			return true;
		}
	}
	return false;
}

bool seize(std::string id,SymbolDesc & sd){
	for(int i = SymTableStack.size() - 1 ; i>=0;--i){
		if(SymTableStack[i].count(id)){
			sd = (SymTableStack[i][id]);
			return true;
		}
	}
	return false;
}

bool inScope(std::string id){
	if(SymTableStack.back().count(id)){
		return true;
	}
	return false;
}

bool insert(std::string id,SymbolDesc& sd){
	if(inScope(id)){
		return false;
	}
	if(sd.symtype <= SymbolType::sarray){
		//Variable IDs
		if(!sd.readonly){
			//Non Constant Variable IDs
			if(SymTableStack.size()==1){
				//Global Non Constant Variable IDs
				sd.global = true;
				fprintf(output, "\tfield static %s %s", SymType2JBStr(sd.symtype).c_str(), id.c_str());
                                if(sd.hasValue){
                                        if(sd.symtype == sinteger){
                                                fprintf(output, " = %d", sd.iValue);
                                        }else if(sd.symtype == sboolean){
                                                if(sd.bValue){
                                                        fprintf(output, " = true");
                                                }else{
                                                        fprintf(output, " = false");
                                                }
                                        }else if(sd.symtype == sstring){
                                                fprintf(output, " = %s", sd.sValue);
                                        }else if(sd.symtype == sreal){
                                                fprintf(output, " = %d", sd.iValue);
                                        }
                                }
                                fprintf(output, "\n");
			}
			else{
				//Local Non Constan Variable IDs
				sd.symindex = (SymTableIndexStack.back())++;
				if(sd.hasValue){
					if(!sd.returnByFun){
						if(sd.symtype == sinteger){
							// printf("...%s %d...", id.c_str(), sd.iValue);
							fprintf(output, "sipush %d\n", sd.iValue);
						}else if(sd.symtype == sboolean){
							if(sd.bValue){
								fprintf(output, "iconst_1\n");
							}
							else {
								fprintf(output, "iconst_0\n");
							}
						}else if(sd.symtype == sstring){
							fprintf(output, "\t\tldc %s\n", sd.sValue);
						}else if(sd.symtype == sreal){
							fprintf(output, "sipush %d\n", sd.iValue);
						}
					}
					
				}else{
					if(!sd.returnByFun){
						if(sd.symtype == sinteger){
							fprintf(output, "sipush %d\n", 0);
						}else if(sd.symtype == sboolean){
							fprintf(output, "iconst_1\n");
						}else if(sd.symtype == sstring){
							fprintf(output, "\t\tldc %s\n", "");
						}else if(sd.symtype == sreal){
							fprintf(output, "sipush %d\n", 0);
						}
					}
				}
				switch(sd.symtype){
					case SymbolType::sinteger:
						fprintf(output, "istore %d\n",  sd.symindex);
						break;
					case SymbolType::sreal:
						fprintf(output, "fstore  %d\n", sd.symindex);
						break;
					case SymbolType::sstring:
						fprintf(output, "astore  %d\n", sd.symindex);
						break;	
				}	
			}
		}
	}
	else{
		//Unknown,Function,Procedure IDs
	}
	SymTableStack.back()[id] = sd;
	return true;
}

bool insert(std::vector<std::string> list,SymbolDesc& sd){
	bool success = true;
	for(int i = 0 ; i < list.size() ; ++i){
		insert(list[i],sd);
	}
	return success;
}

bool insert(std::string id,SymbolDesc& sd,int scope){
	std::map<std::string,SymbolDesc> & EarlyScope =   SymTableStack[SymTableStack.size()-1-scope];
	int & EarlySymIndex = SymTableIndexStack[SymTableIndexStack.size()-scope];
	if(EarlyScope.count(id)){
		return false;
	}
	if(sd.symtype <= SymbolType::sarray){
		//Variable IDs
		if(!sd.readonly){
			//Non Constant Variable IDs
			if(SymTableStack.size() - scope == 1){
				//Global Non Constant Variable IDs
				sd.global = true;
				fprintf(output, "field static %s %s\n", SymType2JBStr(sd.symtype).c_str(), id.c_str());
			}
			else{
				//Local Non Constan Variable IDs
				sd.symindex = EarlySymIndex++;
				// switch(sd.symtype){
				// 	case SymbolType::sinteger:
				// 	fprintf(output, "istore %d\n",  sd.symindex);
				// 	break;
				// 	case SymbolType::sreal:
				// 	fprintf(output, "fstore  %d\n", sd.symindex);
				// 	break;
				// 	case SymbolType::sstring:
				// 	fprintf(output, "astore  %d\n", sd.symindex);
				// 	break;
				// }		
			}
		}
	}
	else{
		//Unknown,Function,Procedure IDs
	}
	EarlyScope[id] = sd;
	return true;
}

bool insertArg(std::string id,SymbolDesc& sd){
	if(inScope(id)){
		return false;
	}
	sd.symindex = (SymTableIndexStack.back())++;
	SymTableStack.back()[id] = sd;
	return true;
}

void insertList(int type){
        varList[size++] = type;
}

void resetList(){
        int i = 0;
        for(i;i<255;i++){
                varList[i] = -1;
        }
}

// void printList(){
// 	for(auto it = varList
// }

bool matchArgs(std::vector<int>& list,SymbolDesc & sd){
	if(list.size()  != sd.symdeps.size() - 1){
		return false;
	}
	else{
		for(int i = 0; i < list.size();++i){
			if(list[i] !=sd.symdeps[i+1].argType) return false;
		}	
	}
	return true;
}

// ast_node_t* n(ast_node_type_t t, YYLTYPE l) { return new_ast_node(t, l.first_line, l.first_column); }
// void vid(ast_node_t *n, LinkedList *v) { if (v) ast_node_set_value_identifier(n, v); }
// void vopt(ast_node_t *n, int v) { ast_node_set_value_operatr(n, v); }
// void vint(ast_node_t *n, int v) { ast_node_set_value_integer(n, v); }
// void vstr(ast_node_t *n, char *v) { ast_node_set_value_string(n, v); }
// void ich(ast_node_t *n, ast_node_t *child) { ast_node_insert_child(n, child); }
// void isb(ast_node_t *n, ast_node_t *sibling) { ast_node_insert_sibling(n, sibling); }
// void esp(LinkedList *sid) { current_idtab = idtab_entry_idtab_create(current_idtab, sid); }
// void lsp() { if (current_idtab->upper_idtab) current_idtab = current_idtab->upper_idtab; }

#line 478 "y.tab.c"

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
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "hw3.y"

   #include "token.h"

#line 517 "y.tab.c"

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
#line 412 "hw3.y"

    Token                    token;

#line 661 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_DE = 3,                         /* DE  */
  YYSYMBOL_ME = 4,                         /* ME  */
  YYSYMBOL_SE = 5,                         /* SE  */
  YYSYMBOL_AE = 6,                         /* AE  */
  YYSYMBOL_NE = 7,                         /* NE  */
  YYSYMBOL_EQ = 8,                         /* EQ  */
  YYSYMBOL_GE = 9,                         /* GE  */
  YYSYMBOL_LE = 10,                        /* LE  */
  YYSYMBOL_ASSIGN = 11,                    /* ASSIGN  */
  YYSYMBOL_AND = 12,                       /* AND  */
  YYSYMBOL_OR = 13,                        /* OR  */
  YYSYMBOL_NOT = 14,                       /* NOT  */
  YYSYMBOL_15_ = 15,                       /* '>'  */
  YYSYMBOL_16_ = 16,                       /* '<'  */
  YYSYMBOL_17_ = 17,                       /* '+'  */
  YYSYMBOL_18_ = 18,                       /* '-'  */
  YYSYMBOL_19_ = 19,                       /* '*'  */
  YYSYMBOL_20_ = 20,                       /* '/'  */
  YYSYMBOL_MOD = 21,                       /* MOD  */
  YYSYMBOL_UMINUS = 22,                    /* UMINUS  */
  YYSYMBOL_LOWER_THAN_ELSE = 23,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_ELSE = 24,                      /* ELSE  */
  YYSYMBOL_BREAK = 25,                     /* BREAK  */
  YYSYMBOL_CHAR = 26,                      /* CHAR  */
  YYSYMBOL_CASE = 27,                      /* CASE  */
  YYSYMBOL_CLASS = 28,                     /* CLASS  */
  YYSYMBOL_CONTINUE = 29,                  /* CONTINUE  */
  YYSYMBOL_DECLARE = 30,                   /* DECLARE  */
  YYSYMBOL_DO = 31,                        /* DO  */
  YYSYMBOL_IF = 32,                        /* IF  */
  YYSYMBOL_EXIT = 33,                      /* EXIT  */
  YYSYMBOL_FOR = 34,                       /* FOR  */
  YYSYMBOL_FUNCTION = 35,                  /* FUNCTION  */
  YYSYMBOL_LOOP = 36,                      /* LOOP  */
  YYSYMBOL_PRINT = 37,                     /* PRINT  */
  YYSYMBOL_PRINTLN = 38,                   /* PRINTLN  */
  YYSYMBOL_RETURN = 39,                    /* RETURN  */
  YYSYMBOL_VAR = 40,                       /* VAR  */
  YYSYMBOL_REAL = 41,                      /* REAL  */
  YYSYMBOL_ARRAY = 42,                     /* ARRAY  */
  YYSYMBOL_OF = 43,                        /* OF  */
  YYSYMBOL_END = 44,                       /* END  */
  YYSYMBOL_PROCEDURE = 45,                 /* PROCEDURE  */
  YYSYMBOL_CONST = 46,                     /* CONST  */
  YYSYMBOL_CBEGIN = 47,                    /* CBEGIN  */
  YYSYMBOL_PUT = 48,                       /* PUT  */
  YYSYMBOL_GET = 49,                       /* GET  */
  YYSYMBOL_RESULT = 50,                    /* RESULT  */
  YYSYMBOL_WHEN = 51,                      /* WHEN  */
  YYSYMBOL_SKIP = 52,                      /* SKIP  */
  YYSYMBOL_THEN = 53,                      /* THEN  */
  YYSYMBOL_DEFAULT = 54,                   /* DEFAULT  */
  YYSYMBOL_DECREASING = 55,                /* DECREASING  */
  YYSYMBOL_IN = 56,                        /* IN  */
  YYSYMBOL_TRUE = 57,                      /* TRUE  */
  YYSYMBOL_FALSE = 58,                     /* FALSE  */
  YYSYMBOL_str = 59,                       /* str  */
  YYSYMBOL_id = 60,                        /* id  */
  YYSYMBOL_integer = 61,                   /* integer  */
  YYSYMBOL_real = 62,                      /* real  */
  YYSYMBOL_KW_STRING = 63,                 /* KW_STRING  */
  YYSYMBOL_INT = 64,                       /* INT  */
  YYSYMBOL_FLOAT = 65,                     /* FLOAT  */
  YYSYMBOL_BOOL = 66,                      /* BOOL  */
  YYSYMBOL_67_ = 67,                       /* '('  */
  YYSYMBOL_68_ = 68,                       /* ')'  */
  YYSYMBOL_69_ = 69,                       /* ':'  */
  YYSYMBOL_70_ = 70,                       /* ','  */
  YYSYMBOL_71_ = 71,                       /* '['  */
  YYSYMBOL_72_ = 72,                       /* ']'  */
  YYSYMBOL_73_ = 73,                       /* '!'  */
  YYSYMBOL_74_ = 74,                       /* '&'  */
  YYSYMBOL_75_ = 75,                       /* '|'  */
  YYSYMBOL_76_ = 76,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 77,                  /* $accept  */
  YYSYMBOL_program = 78,                   /* program  */
  YYSYMBOL_79_1 = 79,                      /* $@1  */
  YYSYMBOL_body = 80,                      /* body  */
  YYSYMBOL_81_2 = 81,                      /* @2  */
  YYSYMBOL_fd = 82,                        /* fd  */
  YYSYMBOL_function = 83,                  /* function  */
  YYSYMBOL_84_3 = 84,                      /* $@3  */
  YYSYMBOL_85_4 = 85,                      /* @4  */
  YYSYMBOL_fun_re = 86,                    /* fun_re  */
  YYSYMBOL_procedure = 87,                 /* procedure  */
  YYSYMBOL_88_5 = 88,                      /* $@5  */
  YYSYMBOL_89_6 = 89,                      /* @6  */
  YYSYMBOL_arguments = 90,                 /* arguments  */
  YYSYMBOL_argument = 91,                  /* argument  */
  YYSYMBOL_seperator = 92,                 /* seperator  */
  YYSYMBOL_returnType = 93,                /* returnType  */
  YYSYMBOL_statements = 94,                /* statements  */
  YYSYMBOL_statements_r = 95,              /* statements_r  */
  YYSYMBOL_type = 96,                      /* type  */
  YYSYMBOL_statement_tmp = 97,             /* statement_tmp  */
  YYSYMBOL_98_7 = 98,                      /* $@7  */
  YYSYMBOL_99_8 = 99,                      /* $@8  */
  YYSYMBOL_statement_r = 100,              /* statement_r  */
  YYSYMBOL_statement = 101,                /* statement  */
  YYSYMBOL_return = 102,                   /* return  */
  YYSYMBOL_exit_optional = 103,            /* exit_optional  */
  YYSYMBOL_declaration_value = 104,        /* declaration_value  */
  YYSYMBOL_expression = 105,               /* expression  */
  YYSYMBOL_expression_list = 106,          /* expression_list  */
  YYSYMBOL_boolean = 107,                  /* boolean  */
  YYSYMBOL_integer_expression = 108,       /* integer_expression  */
  YYSYMBOL_bool_expresssion = 109,         /* bool_expresssion  */
  YYSYMBOL_endif = 110,                    /* endif  */
  YYSYMBOL_condition = 111,                /* condition  */
  YYSYMBOL_112_9 = 112,                    /* $@9  */
  YYSYMBOL_113_10 = 113,                   /* $@10  */
  YYSYMBOL_114_11 = 114,                   /* $@11  */
  YYSYMBOL_condition_r = 115,              /* condition_r  */
  YYSYMBOL_116_12 = 116,                   /* $@12  */
  YYSYMBOL_117_13 = 117,                   /* $@13  */
  YYSYMBOL_118_14 = 118,                   /* $@14  */
  YYSYMBOL_IF_PREACT = 119,                /* IF_PREACT  */
  YYSYMBOL_block = 120,                    /* block  */
  YYSYMBOL_121_15 = 121,                   /* $@15  */
  YYSYMBOL_loop = 122,                     /* loop  */
  YYSYMBOL_123_16 = 123,                   /* $@16  */
  YYSYMBOL_124_17 = 124,                   /* @17  */
  YYSYMBOL_125_18 = 125,                   /* @18  */
  YYSYMBOL_126_19 = 126,                   /* $@19  */
  YYSYMBOL_comparison = 127,               /* comparison  */
  YYSYMBOL_declaration = 128,              /* declaration  */
  YYSYMBOL_constant_declaration = 129,     /* constant_declaration  */
  YYSYMBOL_variable_declaration = 130,     /* variable_declaration  */
  YYSYMBOL_arrays_declaration = 131        /* arrays_declaration  */
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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_uint8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   510

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  220

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   315


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
       2,     2,     2,    73,     2,     2,     2,     2,    74,     2,
      67,    68,    19,    17,    70,    18,    76,    20,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    69,     2,
      16,     2,    15,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    71,     2,    72,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    75,     2,     2,     2,     2,     2,
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
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   444,   444,   444,   492,   496,   500,   504,   504,   539,
     543,   544,   547,   550,   547,   605,   606,   610,   613,   610,
     657,   676,   702,   707,   708,   711,   716,   717,   720,   721,
     724,   725,   726,   727,   730,   731,   732,   733,   734,   763,
     764,   764,   788,   788,   812,   816,   826,   827,   828,   831,
     832,   835,   863,   869,   876,   880,   883,   886,   919,   922,
     923,  1021,  1027,  1033,  1039,  1048,  1051,  1054,  1088,  1091,
    1094,  1175,  1179,  1185,  1191,  1197,  1205,  1209,  1215,  1222,
    1223,  1226,  1231,  1236,  1241,  1246,  1251,  1258,  1263,  1267,
    1273,  1277,  1277,  1283,  1287,  1283,  1295,  1295,  1301,  1305,
    1301,  1313,  1323,  1323,  1331,  1331,  1346,  1432,  1445,  1346,
    1513,  1525,  1537,  1549,  1561,  1573,  1587,  1588,  1589,  1592,
    1619,  1651,  1658,  1683,  1712
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "DE", "ME", "SE", "AE",
  "NE", "EQ", "GE", "LE", "ASSIGN", "AND", "OR", "NOT", "'>'", "'<'",
  "'+'", "'-'", "'*'", "'/'", "MOD", "UMINUS", "LOWER_THAN_ELSE", "ELSE",
  "BREAK", "CHAR", "CASE", "CLASS", "CONTINUE", "DECLARE", "DO", "IF",
  "EXIT", "FOR", "FUNCTION", "LOOP", "PRINT", "PRINTLN", "RETURN", "VAR",
  "REAL", "ARRAY", "OF", "END", "PROCEDURE", "CONST", "CBEGIN", "PUT",
  "GET", "RESULT", "WHEN", "SKIP", "THEN", "DEFAULT", "DECREASING", "IN",
  "TRUE", "FALSE", "str", "id", "integer", "real", "KW_STRING", "INT",
  "FLOAT", "BOOL", "'('", "')'", "':'", "','", "'['", "']'", "'!'", "'&'",
  "'|'", "'.'", "$accept", "program", "$@1", "body", "@2", "fd",
  "function", "$@3", "@4", "fun_re", "procedure", "$@5", "@6", "arguments",
  "argument", "seperator", "returnType", "statements", "statements_r",
  "type", "statement_tmp", "$@7", "$@8", "statement_r", "statement",
  "return", "exit_optional", "declaration_value", "expression",
  "expression_list", "boolean", "integer_expression", "bool_expresssion",
  "endif", "condition", "$@9", "$@10", "$@11", "condition_r", "$@12",
  "$@13", "$@14", "IF_PREACT", "block", "$@15", "loop", "$@16", "@17",
  "@18", "$@19", "comparison", "declaration", "constant_declaration",
  "variable_declaration", "arrays_declaration", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-180)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-76)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -180,    11,  -180,  -180,   157,   -34,   -29,   -19,   -15,   420,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,    -5,  -180,    17,
     333,   333,   -37,   -10,  -180,  -180,  -180,  -180,    10,  -180,
    -180,  -180,  -180,    32,  -180,  -180,   333,   333,  -180,  -180,
     202,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,   -27,
     437,    81,    21,   437,   117,   -42,   -38,   202,   333,  -180,
      24,   420,   333,   420,   333,  -180,   333,   333,   333,    64,
     202,   333,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,  -180,   231,   133,   246,   263,   333,
    -180,   202,   278,   293,   308,   324,    40,  -180,  -180,  -180,
    -180,    95,  -180,  -180,   108,    69,   202,   333,    82,   420,
     202,    83,   202,   202,   202,    41,   154,  -180,     2,     2,
       2,     2,     2,     2,    46,    46,   -38,   -38,   -38,   202,
     202,   -36,   333,   169,    54,   437,   -33,   437,   420,   202,
      98,  -180,  -180,  -180,   333,  -180,    67,    68,  -180,    63,
     339,    75,  -180,  -180,  -180,   131,    84,  -180,   202,   117,
     117,  -180,   354,    97,   420,  -180,   115,    89,   121,  -180,
     420,   124,   149,   420,   162,  -180,   333,  -180,  -180,    66,
     117,   135,  -180,  -180,  -180,   202,   333,  -180,   333,   420,
    -180,  -180,  -180,  -180,   115,   420,   202,   202,   149,  -180,
    -180,   143,  -180,   155,   384,   164,   177,  -180,   384,  -180,
    -180,  -180,  -180,   115,  -180,   384,  -180,  -180,   115,  -180
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     9,     1,     7,     0,     0,     0,     0,     0,
       5,     6,     4,   116,   117,   118,    12,     0,    17,     0,
       0,     0,    54,     0,   104,    42,   102,    40,     0,    44,
      79,    80,    73,    70,    72,    75,     0,     0,    49,     8,
      37,    74,    65,    68,    50,    35,    36,    69,    34,     0,
       0,     0,     0,     0,     0,    70,    82,   101,     0,    45,
       0,    26,     0,    26,     0,    39,     0,    76,     0,     0,
      87,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,    62,    60,    61,    64,     0,
     122,     0,    63,    55,    58,    59,     0,    30,    31,    33,
      32,   121,    21,   119,     0,     0,    53,     0,     0,    26,
      43,     0,    41,    38,    77,     0,     0,    66,   115,   112,
     114,   111,   113,   110,    81,    83,    84,    85,    86,    88,
      89,     0,    76,     0,     0,     0,     0,     0,    26,   106,
       0,    27,   103,    67,     0,    71,     0,     0,    20,     0,
      56,     0,   123,    18,   120,    91,     0,   105,    78,     0,
       0,    13,    57,     0,    26,    93,     0,     0,    24,    25,
      26,     0,    11,    26,     0,    92,     0,    23,    22,     0,
       0,     0,    19,    94,    90,   107,     0,    52,     0,    26,
      15,    16,   124,    10,     0,    26,   101,    51,    11,    95,
     108,     0,    14,     0,    28,     0,    96,    46,    28,    48,
      47,   109,    98,     0,    29,    28,    97,    99,     0,   100
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -180,  -180,  -180,  -180,  -180,     7,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,   104,  -180,  -180,  -180,   -60,  -140,   -52,
     -90,  -180,  -180,  -180,   204,    35,  -180,   -35,   -20,    92,
     -46,   -45,   -41,  -179,  -180,  -180,  -180,  -180,    36,  -180,
    -180,  -180,    20,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
     -40,   221,  -180,  -180,  -180
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     4,     9,   182,    10,    49,   170,   189,
      11,    52,   164,   131,   148,   178,   161,   108,   206,   101,
      38,    64,    62,   208,   109,   209,    59,    90,    40,   115,
      41,    42,    43,   175,    44,   166,   173,   194,   210,   213,
     215,   218,   105,    45,    63,    46,    61,   156,   195,   203,
      47,    48,    13,    14,    15
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,    57,   104,   111,    92,    93,    50,    92,    93,    94,
      95,     3,    94,    95,    58,   199,    69,    70,   103,    77,
      78,    79,    80,    81,   146,    67,    16,   146,    53,    68,
      91,    17,   147,    91,   216,   153,    82,    83,   106,   219,
      84,    18,   110,    66,   112,    19,   113,   114,   116,   141,
      60,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,    51,    79,    80,    81,   214,   133,
      65,    71,    72,    73,    74,   217,    82,    83,   155,    75,
      76,    77,    78,    79,    80,    81,    54,   139,   102,    92,
      93,    92,    93,   107,    94,    95,    94,    95,   186,    67,
     152,   134,   154,    68,   172,   187,   135,   168,   169,   143,
     179,   144,   114,   183,   207,    91,   188,    91,   207,   137,
      82,    83,   138,    96,   158,   207,   140,   142,   192,   198,
     151,   162,   117,   144,   157,   200,   159,   160,    82,    83,
     -70,   -70,   -70,   -70,    97,    98,    99,   100,   -70,   -70,
     -70,   163,   -70,   -70,   -70,   165,   185,    -3,   171,   174,
     167,    71,    72,    73,    74,   176,   196,   180,   197,    75,
      76,    77,    78,    79,    80,    81,    71,    72,    73,    74,
      97,    98,    99,   100,    75,    76,    77,    78,    79,    80,
      81,   177,     5,   181,   184,   193,   204,     6,   211,   205,
     132,   212,     7,     8,    68,   202,   136,   -70,   -70,    71,
      72,    73,    74,    39,   190,   191,   201,    75,    76,    77,
      78,    79,    80,    81,   149,    12,   145,     0,    82,    83,
       0,     0,     0,     0,     0,     0,     0,   150,   -73,   -73,
     -73,   -73,     0,    82,    83,     0,   -73,   -73,   -73,     0,
     -73,   -73,   -73,   -72,   -72,   -72,   -72,     0,     0,     0,
       0,   -72,   -72,   -72,     0,   -72,   -72,   -72,     0,     0,
     -75,   -75,   -75,   -75,     0,     0,    82,    83,   -75,   -75,
     -75,     0,   -75,   -75,   -75,   -74,   -74,   -74,   -74,     0,
       0,     0,     0,   -74,   -74,   -74,     0,   -74,   -74,   -74,
     -65,   -65,   -65,   -65,     0,   -73,   -73,     0,   -65,   -65,
     -65,     0,   -65,   -65,   -65,   -68,   -68,   -68,   -68,     0,
     -72,   -72,     0,   -68,   -68,   -68,     0,   -68,   -68,   -68,
       0,   -69,   -69,   -69,   -69,     0,     0,   -75,   -75,   -69,
     -69,   -69,     0,   -69,   -69,   -69,   -66,   -66,   -66,   -66,
       0,    20,   -74,   -74,   -66,   -66,   -66,     0,   -66,   -66,
     -66,   -67,   -67,   -67,   -67,     0,     0,   -65,   -65,   -67,
     -67,   -67,     0,   -67,   -67,   -67,     0,     0,     0,     0,
       0,     0,   -68,   -68,     0,     0,     0,     0,     0,     0,
      30,    31,    32,    55,    34,    35,     0,     0,   -69,   -69,
      36,     0,    20,     0,     0,     0,    37,     0,     0,     0,
       0,     0,     0,   -66,   -66,     0,   186,    22,    23,     0,
      24,     0,    25,   187,     6,     0,     0,     0,   -67,   -67,
       8,    26,    27,    28,   188,     0,    29,     0,    20,     0,
       0,    30,    31,    32,    33,    34,    35,     0,     0,     0,
       0,    36,    21,    22,    23,    20,    24,    37,    25,     0,
       6,     0,     0,     0,     0,     0,     8,    26,    27,    28,
       0,     0,    29,     0,     0,     0,     0,    30,    31,    32,
      33,    34,    35,     0,     0,     0,     0,    36,     0,     0,
       0,     0,     0,    37,    30,    31,    85,    86,    87,    88,
       0,     0,     0,     0,    89,     0,     0,     0,     0,     0,
      37
};

static const yytype_int16 yycheck[] =
{
      20,    21,    54,    63,    50,    50,    11,    53,    53,    50,
      50,     0,    53,    53,    51,   194,    36,    37,    53,    17,
      18,    19,    20,    21,    60,    67,    60,    60,    11,    71,
      50,    60,    68,    53,   213,    68,    74,    75,    58,   218,
      67,    60,    62,    11,    64,    60,    66,    67,    68,   109,
      60,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    69,    19,    20,    21,   208,    89,
      60,     7,     8,     9,    10,   215,    74,    75,   138,    15,
      16,    17,    18,    19,    20,    21,    69,   107,    67,   135,
     135,   137,   137,    69,   135,   135,   137,   137,    32,    67,
     135,    61,   137,    71,   164,    39,    11,   159,   160,    68,
     170,    70,   132,   173,   204,   135,    50,   137,   208,    11,
      74,    75,    53,    42,   144,   215,    44,    44,   180,   189,
      76,    68,    68,    70,    36,   195,    69,    69,    74,    75,
       7,     8,     9,    10,    63,    64,    65,    66,    15,    16,
      17,    76,    19,    20,    21,    24,   176,     0,    61,    44,
      76,     7,     8,     9,    10,    76,   186,    43,   188,    15,
      16,    17,    18,    19,    20,    21,     7,     8,     9,    10,
      63,    64,    65,    66,    15,    16,    17,    18,    19,    20,
      21,    70,    35,    44,    32,    60,    53,    40,    34,    44,
      67,    24,    45,    46,    71,   198,   102,    74,    75,     7,
       8,     9,    10,     9,   179,   179,   196,    15,    16,    17,
      18,    19,    20,    21,   132,     4,    72,    -1,    74,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,     7,     8,
       9,    10,    -1,    74,    75,    -1,    15,    16,    17,    -1,
      19,    20,    21,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    15,    16,    17,    -1,    19,    20,    21,    -1,    -1,
       7,     8,     9,    10,    -1,    -1,    74,    75,    15,    16,
      17,    -1,    19,    20,    21,     7,     8,     9,    10,    -1,
      -1,    -1,    -1,    15,    16,    17,    -1,    19,    20,    21,
       7,     8,     9,    10,    -1,    74,    75,    -1,    15,    16,
      17,    -1,    19,    20,    21,     7,     8,     9,    10,    -1,
      74,    75,    -1,    15,    16,    17,    -1,    19,    20,    21,
      -1,     7,     8,     9,    10,    -1,    -1,    74,    75,    15,
      16,    17,    -1,    19,    20,    21,     7,     8,     9,    10,
      -1,    18,    74,    75,    15,    16,    17,    -1,    19,    20,
      21,     7,     8,     9,    10,    -1,    -1,    74,    75,    15,
      16,    17,    -1,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    62,    -1,    -1,    74,    75,
      67,    -1,    18,    -1,    -1,    -1,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    75,    -1,    32,    33,    34,    -1,
      36,    -1,    38,    39,    40,    -1,    -1,    -1,    74,    75,
      46,    47,    48,    49,    50,    -1,    52,    -1,    18,    -1,
      -1,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      -1,    67,    32,    33,    34,    18,    36,    73,    38,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    61,    62,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    73,    57,    58,    59,    60,    61,    62,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      73
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    78,    79,     0,    80,    35,    40,    45,    46,    81,
      83,    87,   128,   129,   130,   131,    60,    60,    60,    60,
      18,    32,    33,    34,    36,    38,    47,    48,    49,    52,
      57,    58,    59,    60,    61,    62,    67,    73,    97,   101,
     105,   107,   108,   109,   111,   120,   122,   127,   128,    84,
      11,    69,    88,    11,    69,    60,   105,   105,    51,   103,
      60,   123,    99,   121,    98,    60,    11,    67,    71,   105,
     105,     7,     8,     9,    10,    15,    16,    17,    18,    19,
      20,    21,    74,    75,    67,    59,    60,    61,    62,    67,
     104,   105,   107,   108,   109,   127,    42,    63,    64,    65,
      66,    96,    67,   104,    96,   119,   105,    69,    94,   101,
     105,    94,   105,   105,   105,   106,   105,    68,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,    90,    67,   105,    61,    11,    90,    11,    53,   105,
      44,    94,    44,    68,    70,    72,    60,    68,    91,   106,
      68,    76,   104,    68,   104,    94,   124,    36,   105,    69,
      69,    93,    68,    76,    89,    24,   112,    76,    96,    96,
      85,    61,    94,   113,    44,   110,    76,    70,    92,    94,
      43,    44,    82,    94,    32,   105,    32,    39,    50,    86,
     102,   115,    96,    60,   114,   125,   105,   105,    94,   110,
      94,   119,    82,   126,    53,    44,    95,    97,   100,   102,
     115,    34,    24,   116,    95,   117,   110,    95,   118,   110
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    77,    79,    78,    80,    80,    80,    81,    80,    80,
      82,    82,    84,    85,    83,    86,    86,    88,    89,    87,
      90,    90,    91,    92,    92,    93,    94,    94,    95,    95,
      96,    96,    96,    96,    97,    97,    97,    97,    97,    97,
      98,    97,    99,    97,    97,    97,   100,   100,   100,   101,
     101,   102,   102,   103,   103,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   106,   106,   106,   107,
     107,   108,   108,   108,   108,   108,   108,   109,   109,   109,
     110,   112,   111,   113,   114,   111,   116,   115,   117,   118,
     115,   119,   121,   120,   123,   122,   124,   125,   126,   122,
     127,   127,   127,   127,   127,   127,   128,   128,   128,   129,
     129,   130,   130,   130,   131
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     0,     3,     0,
       2,     0,     0,     0,    12,     1,     1,     0,     0,     9,
       2,     0,     4,     1,     0,     2,     0,     2,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       0,     3,     0,     3,     1,     2,     1,     1,     1,     1,
       1,     2,     1,     2,     0,     1,     3,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     4,     1,     1,
       1,     4,     1,     1,     1,     1,     0,     1,     3,     1,
       1,     3,     2,     3,     3,     3,     3,     2,     3,     3,
       2,     0,     7,     0,     0,    10,     0,     7,     0,     0,
      10,     0,     0,     4,     0,     5,     0,     0,     0,    13,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     4,
       6,     4,     4,     6,    10
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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
    YYNOMEM;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 444 "hw3.y"
                {
				fprintf(output, "class %s {\n", ClassName.c_str());
				resetList();
			}
#line 1994 "y.tab.c"
    break;

  case 3: /* program: $@1 body  */
#line 449 "hw3.y"
                        {

				if(!hasMain){
					hasMain = 1;
					hasProgram = 1;
					ENTERSCOPE();
					SymbolDesc * sd = new SymbolDesc();
					sd->symtype = SymbolType::sfunction;
					uDependency dep;
					dep.retType = SymbolType::none;
					sd->symdeps.push_back(dep);
					SCOPERET.push_back(dep.retType);

					// 產生 main 函式
					fprintf(output, "\tmethod public static ");
					fprintf(output, "%s ", SymType2Str(SymbolType::none));
					fprintf(output, "%s", "main");
					fprintf(output, "(");
					fprintf(output, "java.lang.String[])\n");
					fprintf(output, "\tmax_stack 15\n\tmax_locals 15\n");
					insert("main",*sd,1);
					fprintf(output, "\t{\n");

					
					(yyval.token)._ptr = sd;
					sd->returnByFun = false;
				}
				else{
					// 什麼都不做
				}
				if(!hasProgram){
					fprintf(output, "\tmethod public static void main(java.lang.String[])\n");
					fprintf(output, "\tmax_stack 15\n");
					fprintf(output, "\tmax_locals 15\n");
					fprintf(output, "\t{\n");
				}else{
					// 什麼都不做
				}
				fprintf(output, "\t\treturn\n");
				fprintf(output, "\t}\n");
				fprintf(output, "}\n");
			}
#line 2041 "y.tab.c"
    break;

  case 4: /* body: body declaration  */
#line 492 "hw3.y"
                                {
							if(!hasProgram)
								hasProgram = 1;
						}
#line 2050 "y.tab.c"
    break;

  case 5: /* body: body function  */
#line 496 "hw3.y"
                        {
							if(!hasProgram)
								hasProgram = 1;
						}
#line 2059 "y.tab.c"
    break;

  case 6: /* body: body procedure  */
#line 500 "hw3.y"
                        {
							if(!hasProgram)
								hasProgram = 1;
						}
#line 2068 "y.tab.c"
    break;

  case 7: /* @2: %empty  */
#line 504 "hw3.y"
               {
				// hasMain == 1 代表已經有 main 函式了
				if(!hasMain){
					hasMain = 1;

					ENTERSCOPE();
					SymbolDesc * sd = new SymbolDesc();
					sd->symtype = SymbolType::sfunction;
					uDependency dep;
					dep.retType = SymbolType::none;
					sd->symdeps.push_back(dep);
					SCOPERET.push_back(dep.retType);

					// 產生 main 函式
					fprintf(output, "\tmethod public static ");
					fprintf(output, "%s ", SymType2Str(SymbolType::none));
					fprintf(output, "%s", "main");
					fprintf(output, "(");
					fprintf(output, "java.lang.String[])\n");
					fprintf(output, "\tmax_stack 15\n\tmax_locals 15\n");
					insert("main",*sd,1);
					fprintf(output, "\t{\n");

					
					(yyval.token)._ptr = sd;
					sd->returnByFun = false;
				}
				else{
					// 什麼都不做
				}
		}
#line 2104 "y.tab.c"
    break;

  case 8: /* body: body @2 statement  */
#line 535 "hw3.y"
                         {
							if(!hasProgram)
								hasProgram = 1;
						}
#line 2113 "y.tab.c"
    break;

  case 12: /* $@3: %empty  */
#line 547 "hw3.y"
                            {
                    ENTERSCOPE();
                }
#line 2121 "y.tab.c"
    break;

  case 13: /* @4: %empty  */
#line 550 "hw3.y"
                                                             {

					SymbolDesc * sd = new SymbolDesc();	
					std::vector<int> * varlist2 =(std::vector<int> *)(yyvsp[-2].token)._ptr;
					SymbolDesc * retype = (SymbolDesc*)(yyvsp[0].token)._ptr; 
					sd->symtype = SymbolType::sfunction;
					uDependency dep;
					dep.retType = (yyvsp[0].token).type;
					// printf("<%d>", dep.retType);
					sd->symdeps.push_back(dep);
					SCOPERET.push_back(dep.retType);
					fprintf(output, "\tmethod public static ");
					fprintf(output, "%s ", SymType2Str((yyvsp[0].token).type));
					fprintf(output, "%s", (yyvsp[-5].token)._str);
					fprintf(output, "(");
					if(strcmp((yyvsp[-5].token)._str, "main") != 0){
							// if(varList != NULL){
							//         int i = 0;
							//         for(i;i<255 && varList[i]!=-1;i++){
							//                 if(i!=0){
							//                         fprintf(output, ", ");
							//                 }
							//                 fprintf(output, "%s", SymType2Str(varList[i]));
							//         }
							// }
							if(varlist2 != nullptr) {
								for(int i = 0 , j = varlist2->size() ;  i < j; ++i){
									dep.argType = (*varlist2)[i];
									sd->symdeps.push_back(dep);
									if(i!=0){
										fprintf(output, ", ");
									}
									fprintf(output, "%s", SymType2Str((*varlist2)[i]));
								}
							}
							fprintf(output, ")\n");
							resetList();
					}else{
							fprintf(output, "java.lang.String[])\n");  
							//fprintf(output, ""); 
					}
					(yyval.token)._ptr = sd;
					fprintf(output, "\tmax_stack 15\n\tmax_locals 15\n");
					delete varlist2,retype;
					sd->returnByFun = false;
					insert(std::string((yyvsp[-5].token)._str),*sd,1);	
					fprintf(output, "\t{\n");
					delete sd;
                }
#line 2175 "y.tab.c"
    break;

  case 14: /* function: FUNCTION id $@3 '(' arguments ')' returnType @4 statements fun_re statements fd  */
#line 599 "hw3.y"
                                                                        {
					fprintf(output, "\t}\n");
					LEAVESCOPE();
                 }
#line 2184 "y.tab.c"
    break;

  case 17: /* $@5: %empty  */
#line 610 "hw3.y"
                         {
            	            ENTERSCOPE();
            }
#line 2192 "y.tab.c"
    break;

  case 18: /* @6: %empty  */
#line 613 "hw3.y"
                                 {
						// ENTERSCOPE();
						SymbolDesc * sd = new SymbolDesc();	
						std::vector<int> * varlist2 =(std::vector<int> *)(yyvsp[-1].token)._ptr;
						sd->symtype = SymbolType::sprocedure;
						uDependency dep;
						dep.retType = SymbolType::none;
						sd->symdeps.push_back(dep);
                        fprintf(output, "\tmethod public static ");
						fprintf(output, "%s ", SymType2Str(SymbolType::none));
                        fprintf(output, "%s", (yyvsp[-4].token)._str);
                        fprintf(output, "(");
                        if(strcmp((yyvsp[-4].token)._str, "main") != 0){
								if(varlist2 != nullptr) {
									for(int i = 0 , j = varlist2->size() ;  i < j; ++i){
										dep.argType = (*varlist2)[i];
										sd->symdeps.push_back(dep);
										if(i!=0){
                                            fprintf(output, ", ");
                                        }
										fprintf(output, "%s", SymType2Str((*varlist2)[i]));
									}
								}
                                fprintf(output, ")\n");
                                resetList();
                        }else{ 
                                // printf("procedure 名稱 不能為 main\n"); 
                        }
						(yyval.token)._ptr = sd;
                        fprintf(output, "\tmax_stack 15\n\tmax_locals 15\n");
						delete varlist2;
						sd->returnByFun = false;
						sd->returnByFun = false;
						insert(std::string((yyvsp[-4].token)._str),*sd,1);	
						fprintf(output, "\t{\n");
						delete sd;
                }
#line 2234 "y.tab.c"
    break;

  case 19: /* procedure: PROCEDURE id $@5 '(' arguments ')' @6 statements fd  */
#line 650 "hw3.y"
                                {
								fprintf(output, "\t\treturn\n");
								fprintf(output, "\t}\n");
								LEAVESCOPE();
                 }
#line 2244 "y.tab.c"
    break;

  case 20: /* arguments: arguments argument  */
#line 657 "hw3.y"
                             {
				SymbolDesc sd;
				uDependency value;
                // int i = 0;
                // for(i;i<255 && varList[i]!=-1;i++){
                //         printf("%d", varList[i]);
                // }
				sd.symtype = Token2Symbol((yyvsp[0].token).type);
				value.value = (yyvsp[0].token)._ptr;
                                
				sd.symdeps.push_back(value);
				//printf("");
				insertArg((yyvsp[0].token)._str, sd);
				(yyval.token) = (yyvsp[-1].token);
				//printf("%d", sd.symtype);
				(yyval.token).type = TokenType::typeList;
				((std::vector<int>*)(yyval.token)._ptr)->push_back(sd.symtype);
                //insertList($2.type);
        }
#line 2268 "y.tab.c"
    break;

  case 21: /* arguments: %empty  */
#line 676 "hw3.y"
                      {
				(yyval.token).type = TokenType::typeList;
				(yyval.token)._ptr = new std::vector<int>();
			}
#line 2277 "y.tab.c"
    break;

  case 22: /* argument: id ':' type seperator  */
#line 702 "hw3.y"
                                {
        (yyval.token) = (yyvsp[-3].token);
		(yyval.token).type = (yyvsp[-1].token).type;
}
#line 2286 "y.tab.c"
    break;

  case 25: /* returnType: ':' type  */
#line 711 "hw3.y"
                   {
                (yyval.token).type = (yyvsp[0].token).type;
            }
#line 2294 "y.tab.c"
    break;

  case 30: /* type: KW_STRING  */
#line 724 "hw3.y"
                   {(yyval.token).type = sstring;}
#line 2300 "y.tab.c"
    break;

  case 31: /* type: INT  */
#line 725 "hw3.y"
                {(yyval.token).type = sinteger;}
#line 2306 "y.tab.c"
    break;

  case 32: /* type: BOOL  */
#line 726 "hw3.y"
                {(yyval.token).type = sboolean;}
#line 2312 "y.tab.c"
    break;

  case 33: /* type: FLOAT  */
#line 727 "hw3.y"
                {(yyval.token).type = sreal;}
#line 2318 "y.tab.c"
    break;

  case 38: /* statement_tmp: id ASSIGN expression  */
#line 734 "hw3.y"
                              {
			SymbolDesc * pSD;
			if(seize(std::string((yyvsp[-2].token)._str),pSD)){
				if(pSD->readonly){
					//Error("Assignment to Readonly Variable!");
				}
				else if(pSD->symtype != Token2Symbol((yyvsp[0].token).type)){
					//Error("Type Unmatch");
				}
				else {
					if(pSD->global){
						fprintf(output, "putstatic %s %s.%s\n", SymType2JBStr(pSD->symtype).c_str(), ClassName.c_str(), (yyvsp[-2].token)._str);
					}
					else{
						switch(pSD->symtype){
							case SymbolType::sinteger:
							fprintf(output, "istore %d\n",  pSD->symindex);
							break;
							case SymbolType::sreal:
							fprintf(output, "fstore  %d\n", pSD->symindex);
							break;
							case SymbolType::sstring:
							fprintf(output, "astore  %d\n", pSD->symindex);
							break;
						}
					}
				}
			}
		}
#line 2352 "y.tab.c"
    break;

  case 40: /* $@7: %empty  */
#line 764 "hw3.y"
              {
                fprintf(output, "\t\tgetstatic java.io.PrintStream java.lang.System.out\n");
        }
#line 2360 "y.tab.c"
    break;

  case 41: /* statement_tmp: PUT $@7 expression  */
#line 766 "hw3.y"
                    {
                fprintf(output, "\t\tinvokevirtual void java.io.PrintStream.print(");
                switch((yyvsp[0].token).type){
		case vint:
			fprintf(output, "int");
			break;
		case vreal:
			fprintf(output, "float");
			break;
		case vbool:
			fprintf(output, "boolean");
			break;
		case vstring:
			fprintf(output, "java.lang.String");
			break;
		case blank:
			fprintf(output, "void");
		default:
			break;
		}
                fprintf(output, ")\n");
        }
#line 2387 "y.tab.c"
    break;

  case 42: /* $@8: %empty  */
#line 788 "hw3.y"
                  {
                fprintf(output, "\t\tgetstatic java.io.PrintStream java.lang.System.out\n");
        }
#line 2395 "y.tab.c"
    break;

  case 43: /* statement_tmp: PRINTLN $@8 expression  */
#line 790 "hw3.y"
                   {
                fprintf(output, "\t\tinvokevirtual void java.io.PrintStream.println(");
                switch((yyvsp[0].token).type){
		case vint:
			fprintf(output, "int");
			break;
		case vreal:
			fprintf(output, "float");
			break;
		case vbool:
			fprintf(output, "boolean");
			break;
		case vstring:
			fprintf(output, "java.lang.String");
			break;
		case blank:
			fprintf(output, "void");
		default:
			break;
		}
                fprintf(output, ")\n");
        }
#line 2422 "y.tab.c"
    break;

  case 44: /* statement_tmp: SKIP  */
#line 812 "hw3.y"
              {
			fprintf(output, "getstatic java.io.PrintStream java.lang.System.out\n");
			fprintf(output, "invokevirtual void java.io.PrintStream.println()\n");
		}
#line 2431 "y.tab.c"
    break;

  case 45: /* statement_tmp: EXIT exit_optional  */
#line 816 "hw3.y"
                            {
			
			//fprintf(output, "goto L%d\n", LabelIndex - 4);
			//fprintf(output, "goto L%d\n", $<token>2._int - 1);
		}
#line 2441 "y.tab.c"
    break;

  case 51: /* return: RESULT expression  */
#line 835 "hw3.y"
                                {
								fprintf(output, "\t\t");

								// 判斷 回傳型態
								// 選擇 不同型態 的 return
								switch((yyvsp[0].token).type){
								// int
								case SymbolType::sinteger:
								fprintf(output, "ireturn\n");
								break;
								// double
								case SymbolType::sreal:
								fprintf(output, "dreturn\n");
								break;
								// string
								case SymbolType::sstring:
								fprintf(output, "areturn\n");
								break;
								// array
								case SymbolType::sarray:
								fprintf(output, "areturn\n");
								break;
								// 其他
								default:
								fprintf(output, "ireturn\n");
								break;
							}
							}
#line 2474 "y.tab.c"
    break;

  case 52: /* return: RETURN  */
#line 863 "hw3.y"
                                                {
								fprintf(output, "\t\t");
								fprintf(output, "return\n");
							}
#line 2483 "y.tab.c"
    break;

  case 53: /* exit_optional: WHEN expression  */
#line 869 "hw3.y"
                              {
					if(exitLabels[loop_number - 1] == -1){
						exitLabels[loop_number - 1] = LabelIndex;
					}
					fprintf(output, "ifne L%d\n", LabelIndex++);

				}
#line 2495 "y.tab.c"
    break;

  case 55: /* declaration_value: integer_expression  */
#line 880 "hw3.y"
                                     {
					(yyval.token).returnByFun = false;
				}
#line 2503 "y.tab.c"
    break;

  case 56: /* declaration_value: '(' expression ')'  */
#line 883 "hw3.y"
                                {
                (yyval.token) = (yyvsp[-1].token);
            }
#line 2511 "y.tab.c"
    break;

  case 57: /* declaration_value: id '(' expression_list ')'  */
#line 886 "hw3.y"
                                        {
				SymbolDesc * pSD;
				(yyval.token).returnByFun = true;
				std::string idName = std::string((yyvsp[-3].token)._str);
				delete (yyvsp[-3].token)._str;

				if(seize(idName,pSD)){
					std::vector<int> * list = (std::vector<int>*)(yyvsp[-1].token)._ptr;
					if(pSD->symtype != SymbolType::sfunction){
						//Error(id + ": Is not a Function");
					}
					else if(!matchArgs(*list,*pSD)){
						//Error("Argument type Unmatch");
					}
					else{
						fprintf(output, "invokestatic %s %s.%s(", SymType2JBStr(pSD->symdeps[0].retType).c_str(), ClassName.c_str(), idName.c_str());
						for(int i = 0 ; i < list->size();++i ){
							fprintf(output, "%s", SymType2JBStr((*list)[i]).c_str());
							if(i != list->size()-1){
								fprintf(output, ", ");
							}
						}
						fprintf(output, ")\n");

						(yyval.token).type = Symbol2Token(pSD->symdeps[0].retType);
						//$$.type = SymbolType::sfunction;
						delete list;
					}
				}
				else {
					(yyval.token).type = TokenType::blank;
				}
			}
#line 2549 "y.tab.c"
    break;

  case 58: /* declaration_value: bool_expresssion  */
#line 919 "hw3.y"
                              {
				(yyval.token).returnByFun = false;
			}
#line 2557 "y.tab.c"
    break;

  case 60: /* declaration_value: id  */
#line 923 "hw3.y"
                {
                SymbolDesc * pSD;
				(yyval.token).returnByFun = false;
				if(seize(std::string((yyvsp[0].token)._str),pSD)){
					(yyval.token).type = Symbol2Token(pSD->symtype);
					
					if(pSD->readonly){
						switch(pSD->symtype){
							case SymbolType::sinteger:
							fprintf(output, "sipush %d\n", pSD->symdeps[0]._int);
							(yyval.token).type = TokenType::vint;
							break;
							case SymbolType::sboolean:
							if(pSD->symdeps[0]._bool){
								fprintf(output, "iconst_1\n");
							}
							else {
								fprintf(output, "iconst_0\n");
							}
							(yyval.token).type = TokenType::vbool;
							break;
							case SymbolType::sstring:
							fprintf(output, "ldc %s\n", pSD->symdeps[0]._str);
							(yyval.token).type = TokenType::vstring;
							break;
							case SymbolType::sreal:
							fprintf(output, "ldc %sf\n", pSD->symdeps[0]._real);
							break;
							default:
							break;

						}
					}
					else {
						//If ID is a Variable.
						if(pSD->global){
							//If ID is global variable.
							fprintf(output, "getstatic");
							switch(pSD->symtype){
								case SymbolType::sinteger:
								fprintf(output, " int ");
								(yyval.token).type = TokenType::vint;
								break;
								case SymbolType::sreal:
								fprintf(output, " float ");
								(yyval.token).type = TokenType::vreal;
								break;
								case SymbolType::sstring:
								fprintf(output, " java.lang.String ");
								(yyval.token).type = TokenType::vstring;
								break;
								/*case SymbolType::boolean:
								jbfile << " boolean ";
								$$.type = TokenType::vbool;
								break;
								case SymbolType::array:
								jbfile << " array ";
								$$.type = TokenType::varray;
								break;*/
								default:
								break;
							}
							fprintf(output, "%s.%s\n", ClassName.c_str(), (yyvsp[0].token)._str);
						}
						else{
							//If ID is local variable.
							switch(pSD->symtype){
								case SymbolType::sinteger:
								fprintf(output, "iload %d\n", pSD->symindex);
								(yyval.token).type = TokenType::vint;
								break;
								case SymbolType::sreal:
								fprintf(output, "fload %d\n", pSD->symindex);
								(yyval.token).type = TokenType::vreal;
								break;
								case SymbolType::sstring:
								fprintf(output, "aload %d\n", pSD->symindex);
								(yyval.token).type = TokenType::vstring;
								break;
								/*case SymbolType::boolean:
								jbfile << "cload " << <<endl;
								break;
								case SymbolType::std::string:
								jbfile << "sload " << <<endl;
								break;
								case SymbolType::array:
								jbfile << "aload " << <<endl;
								break;*/
								default:
								break;
							}
						}
					}
				}
				else {
				}
				delete (yyvsp[0].token)._str;
            }
#line 2660 "y.tab.c"
    break;

  case 61: /* declaration_value: integer  */
#line 1021 "hw3.y"
                      {
                (yyval.token) = (yyvsp[0].token);
                (yyval.token).type = vint;
				(yyval.token).returnByFun = false;
                //fprintf(output, "sipush %d\n", $1._int);
            }
#line 2671 "y.tab.c"
    break;

  case 62: /* declaration_value: str  */
#line 1027 "hw3.y"
                  {
                (yyval.token) = (yyvsp[0].token);
                (yyval.token).type = vstring;
				(yyval.token).returnByFun = false;
                //fprintf(output, "\t\tldc %s\n", $1._str);
            }
#line 2682 "y.tab.c"
    break;

  case 63: /* declaration_value: boolean  */
#line 1033 "hw3.y"
                      {
                (yyval.token) = (yyvsp[0].token);
                (yyval.token).type = vbool;
				(yyval.token).returnByFun = false;
                //fprintf(output, "ldc %s\n", $1);
            }
#line 2693 "y.tab.c"
    break;

  case 64: /* declaration_value: real  */
#line 1039 "hw3.y"
                   {
                (yyval.token) = (yyvsp[0].token);
                (yyval.token).type = vreal;
				(yyval.token).returnByFun = false;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
                //fprintf(output, "ldc %s\n", $1);
            }
#line 2704 "y.tab.c"
    break;

  case 65: /* expression: integer_expression  */
#line 1048 "hw3.y"
                              {
				(yyval.token).returnByFun = false;
			}
#line 2712 "y.tab.c"
    break;

  case 66: /* expression: '(' expression ')'  */
#line 1051 "hw3.y"
                                {
                (yyval.token) = (yyvsp[-1].token);
            }
#line 2720 "y.tab.c"
    break;

  case 67: /* expression: id '(' expression_list ')'  */
#line 1054 "hw3.y"
                                        {
				SymbolDesc * pSD;
				std::string idName = std::string((yyvsp[-3].token)._str);
				delete (yyvsp[-3].token)._str;

				if(seize(idName,pSD)){
					std::vector<int> * list = (std::vector<int>*)(yyvsp[-1].token)._ptr;
					if((pSD->symtype != SymbolType::sfunction) && (pSD->symtype != SymbolType::sprocedure)){
						// printf("%s: Is not a Function", idName);
					}
					else if(!matchArgs(*list,*pSD)){
						// printf("Argument type Unmatch");
					}
					else{
						fprintf(output, "invokestatic %s %s.%s(", SymType2JBStr(pSD->symdeps[0].retType).c_str(), ClassName.c_str(), idName.c_str());
						for(int i = 0 ; i < list->size();++i ){
							fprintf(output, "%s", SymType2JBStr((*list)[i]).c_str());
							if(i != list->size()-1){
								fprintf(output, ", ");
							}
						}
						fprintf(output, ")\n");

						(yyval.token).type = Symbol2Token(pSD->symdeps[0].retType);
						(yyval.token).returnByFun = true;
						//$$.type = SymbolType::sfunction;
						delete list;
					}
				}
				else {
					(yyval.token).type = TokenType::blank;
				}
				delete pSD;
			}
#line 2759 "y.tab.c"
    break;

  case 68: /* expression: bool_expresssion  */
#line 1088 "hw3.y"
                              {
				(yyval.token).returnByFun = false;
			}
#line 2767 "y.tab.c"
    break;

  case 69: /* expression: comparison  */
#line 1091 "hw3.y"
                        {
				(yyval.token).returnByFun = false;
			}
#line 2775 "y.tab.c"
    break;

  case 70: /* expression: id  */
#line 1094 "hw3.y"
                {
                SymbolDesc * pSD;
				(yyval.token).returnByFun = false;
				if(seize(std::string((yyvsp[0].token)._str),pSD)){
					(yyval.token).type = Symbol2Token(pSD->symtype);
					if(pSD->readonly){
						switch(pSD->symtype){
							case SymbolType::sinteger:
							fprintf(output, "sipush %d\n", pSD->symdeps[0]._int);
							(yyval.token).type = TokenType::vint;
							break;
							case SymbolType::sboolean:
							if(pSD->symdeps[0]._bool){
								fprintf(output, "iconst_1\n");
							}
							else {
								fprintf(output, "iconst_0\n");
							}
							(yyval.token).type = TokenType::vbool;
							break;
							case SymbolType::sstring:
							fprintf(output, "ldc %s\n", pSD->symdeps[0]._str);
							(yyval.token).type = TokenType::vstring;
							break;
							case SymbolType::sreal:
							fprintf(output, "ldc %sf\n", pSD->symdeps[0]._real);
							break;
							default:
							break;

						}
					}
					else {
						//If ID is a Variable.
						if(pSD->global){
							//If ID is global variable.
							fprintf(output, "getstatic");
							switch(pSD->symtype){
								case SymbolType::sinteger:
								fprintf(output, " int ");
								(yyval.token).type = TokenType::vint;
								break;
								case SymbolType::sreal:
								fprintf(output, " float ");
								(yyval.token).type = TokenType::vreal;
								break;
								case SymbolType::sstring:
								fprintf(output, " java.lang.String ");
								(yyval.token).type = TokenType::vstring;
								break;
								default:
								break;
							}
							fprintf(output, "%s.%s\n", ClassName.c_str(), (yyvsp[0].token)._str);
						}
						else{
							//If ID is local variable.
							switch(pSD->symtype){
								case SymbolType::sinteger:
								fprintf(output, "iload %d\n", pSD->symindex);
								(yyval.token).type = TokenType::vint;
								break;
								case SymbolType::sreal:
								fprintf(output, "fload %d\n", pSD->symindex);
								(yyval.token).type = TokenType::vreal;
								break;
								case SymbolType::sstring:
								fprintf(output, "aload %d\n", pSD->symindex);
								(yyval.token).type = TokenType::vstring;
								break;
								default:
								break;
							}
						}
					}
				}
				else {
				}
				delete (yyvsp[0].token)._str;
				delete pSD;
            }
#line 2861 "y.tab.c"
    break;

  case 71: /* expression: id '[' expression ']'  */
#line 1175 "hw3.y"
                                                {
				// array 的部分
				(yyval.token).type = vint;
			}
#line 2870 "y.tab.c"
    break;

  case 72: /* expression: integer  */
#line 1179 "hw3.y"
                      {
                (yyval.token) = (yyvsp[0].token);
                (yyval.token).type = vint;
				(yyval.token).returnByFun = false;
                fprintf(output, "sipush %d\n", (yyvsp[0].token)._int);
            }
#line 2881 "y.tab.c"
    break;

  case 73: /* expression: str  */
#line 1185 "hw3.y"
                  {
                (yyval.token) = (yyvsp[0].token);
                (yyval.token).type = vstring;
				(yyval.token).returnByFun = false;
                fprintf(output, "\t\tldc %s\n", (yyvsp[0].token)._str);
            }
#line 2892 "y.tab.c"
    break;

  case 74: /* expression: boolean  */
#line 1191 "hw3.y"
                      {
                (yyval.token) = (yyvsp[0].token);
                (yyval.token).type = vbool;
				(yyval.token).returnByFun = false;
                //fprintf(output, "ldc %s\n", $1);
            }
#line 2903 "y.tab.c"
    break;

  case 75: /* expression: real  */
#line 1197 "hw3.y"
                   {
                (yyval.token) = (yyvsp[0].token);
                (yyval.token).type = vreal;
				(yyval.token).returnByFun = false;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
                //fprintf(output, "ldc %s\n", $1);
            }
#line 2914 "y.tab.c"
    break;

  case 76: /* expression_list: %empty  */
#line 1205 "hw3.y"
                 {
					(yyval.token).type = TokenType::typeList;
					(yyval.token)._ptr = new std::vector<int>();
				}
#line 2923 "y.tab.c"
    break;

  case 77: /* expression_list: expression  */
#line 1209 "hw3.y"
                           {
					(yyval.token).type = TokenType::typeList;
					std::vector<int> & list = *(new std::vector<int>());
					list.push_back(Token2Symbol((yyvsp[0].token).type));
					(yyval.token)._ptr = &list;
				}
#line 2934 "y.tab.c"
    break;

  case 78: /* expression_list: expression_list ',' expression  */
#line 1215 "hw3.y"
                                                               {
					(yyval.token) = (yyvsp[-2].token);
					std::vector<int> & list = *(std::vector<int>*)(yyval.token)._ptr;
					list.push_back(Token2Symbol((yyvsp[0].token).type));
				}
#line 2944 "y.tab.c"
    break;

  case 79: /* boolean: TRUE  */
#line 1222 "hw3.y"
                { (yyval.token)._bool = 1; }
#line 2950 "y.tab.c"
    break;

  case 80: /* boolean: FALSE  */
#line 1223 "hw3.y"
                { (yyval.token)._bool = 0; }
#line 2956 "y.tab.c"
    break;

  case 81: /* integer_expression: expression '+' expression  */
#line 1226 "hw3.y"
                                             {
						(yyval.token)._int = (yyvsp[-2].token)._int + (yyvsp[0].token)._int;
						(yyval.token).type = vint;
						fprintf(output, "\t\tiadd\n"); 
                    }
#line 2966 "y.tab.c"
    break;

  case 82: /* integer_expression: '-' expression  */
#line 1231 "hw3.y"
                                                   {
						(yyval.token)._int = -(yyvsp[0].token)._int;
                        (yyval.token).type = TokenType::vint;
						fprintf(output, "ineg\n");
                    }
#line 2976 "y.tab.c"
    break;

  case 83: /* integer_expression: expression '-' expression  */
#line 1236 "hw3.y"
                                               {
						(yyval.token)._int = (yyvsp[-2].token)._int - (yyvsp[0].token)._int;
						(yyval.token).type = TokenType::vint;
						fprintf(output, "isub\n");
		   			}
#line 2986 "y.tab.c"
    break;

  case 84: /* integer_expression: expression '*' expression  */
#line 1241 "hw3.y"
                                               {
						(yyval.token).type = TokenType::vint;
						(yyval.token)._int = (yyvsp[-2].token)._int * (yyvsp[0].token)._int;
						fprintf(output, "imul\n");
					}
#line 2996 "y.tab.c"
    break;

  case 85: /* integer_expression: expression '/' expression  */
#line 1246 "hw3.y"
                                               {
						(yyval.token)._int = (yyvsp[-2].token)._int / (yyvsp[0].token)._int;
						(yyval.token).type = TokenType::vint;
						fprintf(output, "idiv\n");
					}
#line 3006 "y.tab.c"
    break;

  case 86: /* integer_expression: expression MOD expression  */
#line 1251 "hw3.y"
                                               {
						(yyval.token)._int = (yyvsp[-2].token)._int % (yyvsp[0].token)._int;
						(yyval.token).type = TokenType::vint;
						fprintf(output, "irem\n");
					}
#line 3016 "y.tab.c"
    break;

  case 87: /* bool_expresssion: '!' expression  */
#line 1258 "hw3.y"
                                 {
                        (yyval.token).type = TokenType::vbool;
						fprintf(output, "iconst_1\n");
                        fprintf(output, "ixor\n");
                }
#line 3026 "y.tab.c"
    break;

  case 88: /* bool_expresssion: expression '&' expression  */
#line 1263 "hw3.y"
                                           {
                        (yyval.token).type = TokenType::vbool;
                        fprintf(output, "iand\n");
                }
#line 3035 "y.tab.c"
    break;

  case 89: /* bool_expresssion: expression '|' expression  */
#line 1267 "hw3.y"
                                           {
                        (yyval.token).type = TokenType::vbool;
                        fprintf(output, "ior\n");
                }
#line 3044 "y.tab.c"
    break;

  case 90: /* endif: END IF  */
#line 1273 "hw3.y"
              {
	LEAVESCOPE();
}
#line 3052 "y.tab.c"
    break;

  case 91: /* $@9: %empty  */
#line 1277 "hw3.y"
                                                                          {	
			if((yyvsp[-3].token).type != TokenType::vbool){
				//Error("Expression must be boolean");
			}
			fprintf(output, "L%d:\n", (yyvsp[-2].token)._int-1);
		}
#line 3063 "y.tab.c"
    break;

  case 93: /* $@10: %empty  */
#line 1283 "hw3.y"
                                                         {
			fprintf(output, "goto L%d\n", (yyvsp[-3].token)._int);
			fprintf(output, "L%d:\n", (yyvsp[-3].token)._int - 1);
		}
#line 3072 "y.tab.c"
    break;

  case 94: /* $@11: %empty  */
#line 1287 "hw3.y"
                            {	
			if((yyvsp[-6].token).type != TokenType::vbool){
				//Error("Expression must be boolean");
			}
			fprintf(output, "L%d:\n", (yyvsp[-5].token)._int);
		}
#line 3083 "y.tab.c"
    break;

  case 96: /* $@12: %empty  */
#line 1295 "hw3.y"
                                                                              {	
			if((yyvsp[-3].token).type != TokenType::vbool){
				// printf("Expression must be boolean");
			}
			fprintf(output, "L%d:\n", (yyvsp[-2].token)._int-1);
		}
#line 3094 "y.tab.c"
    break;

  case 98: /* $@13: %empty  */
#line 1301 "hw3.y"
                                                           {
			fprintf(output, "goto L%d\n", (yyvsp[-3].token)._int);
			fprintf(output, "L%d:\n", (yyvsp[-3].token)._int - 1);
		}
#line 3103 "y.tab.c"
    break;

  case 99: /* $@14: %empty  */
#line 1305 "hw3.y"
                              {	
			if((yyvsp[-6].token).type != TokenType::vbool){
				// printf("Expression must be boolean");
			}
			fprintf(output, "L%d:\n", (yyvsp[-5].token)._int);
		}
#line 3114 "y.tab.c"
    break;

  case 101: /* IF_PREACT: %empty  */
#line 1313 "hw3.y"
           {
		fprintf(output, "ifeq L%d\n", LabelIndex++);
		(yyval.token)._int = LabelIndex++;
		// // printf("%d", LabelIndex);

		ENTERSCOPE();
		if_number++;
	}
#line 3127 "y.tab.c"
    break;

  case 102: /* $@15: %empty  */
#line 1323 "hw3.y"
             {
				ENTERSCOPE();
}
#line 3135 "y.tab.c"
    break;

  case 103: /* block: CBEGIN $@15 statements END  */
#line 1326 "hw3.y"
              {
	LEAVESCOPE();
}
#line 3143 "y.tab.c"
    break;

  case 104: /* $@16: %empty  */
#line 1331 "hw3.y"
           {
		ENTERSCOPE();
		loop_number++;

		fprintf(output, "L%d:\n", LabelIndex++);
		// $<token>$._int = LabelIndex++;
	}
#line 3155 "y.tab.c"
    break;

  case 105: /* loop: LOOP $@16 statements END LOOP  */
#line 1338 "hw3.y"
                            {
		
		fprintf(output, "goto L%d\n", LabelIndex - 4);
		fprintf(output, "L%d:\n", exitLabels[loop_number - 1]);
		
		
		LEAVESCOPE();
	}
#line 3168 "y.tab.c"
    break;

  case 106: /* @17: %empty  */
#line 1346 "hw3.y"
                            {
			ENTERSCOPE();

			SymbolDesc sd;
			uDependency value;

			sd.symtype = Token2Symbol((yyvsp[0].token).type);
			sd.iValue = (yyvsp[0].token)._int;
			value.value = (yyvsp[0].token)._ptr;
							
			sd.symdeps.push_back(value);
			sd.returnByFun = false;

			SymbolDesc * pSD;
			std::string idName = std::string((yyvsp[-2].token)._str);

			if(seize(idName, pSD)){
				if(pSD->readonly){
					// printf("Assignment to Readonly Variable!");
				}
				else if(pSD->symtype != Token2Symbol((yyvsp[0].token).type)){
					// printf("Type Unmatch");
				}
				else {
					if(pSD->global){
						fprintf(output, "putstatic %s %s.%s\n", SymType2JBStr(pSD->symtype).c_str(), ClassName.c_str(), (yyvsp[-2].token)._str);
					}
					else{
						switch(pSD->symtype){
							case SymbolType::sinteger:
							fprintf(output, "istore %d\n",  pSD->symindex);
							break;
							case SymbolType::sreal:
							fprintf(output, "fstore  %d\n", pSD->symindex);
							break;
							case SymbolType::sstring:
							fprintf(output, "astore  %d\n", pSD->symindex);
							break;
						}
					}
				}
			}
			(yyval.token)._int = LabelIndex;
			fprintf(output, "L%d:\n", LabelIndex++);
			// $<token>$._int = LabelIndex++;
			
			// If ID is a Variable.
			if(pSD->global){
				//If ID is global variable.
				fprintf(output, "getstatic");
				switch(pSD->symtype){
					case SymbolType::sinteger:
					fprintf(output, " int ");
					break;
					case SymbolType::sreal:
					fprintf(output, " float ");
					break;
					case SymbolType::sstring:
					fprintf(output, " java.lang.String ");
					break;
					default:
					break;
				}
				fprintf(output, "%s.%s\n", ClassName.c_str(), (yyvsp[-2].token)._str);
			}
			else{
				// If ID is local variable.
				switch(pSD->symtype){
					case SymbolType::sinteger:
					fprintf(output, "iload %d\n", pSD->symindex);
					break;
					case SymbolType::sreal:
					fprintf(output, "fload %d\n", pSD->symindex);
					break;
					case SymbolType::sstring:
					fprintf(output, "aload %d\n", pSD->symindex);
					break;
					case SymbolType::sboolean:
					fprintf(output, "iload %d\n", pSD->symindex);
					break;
					default:
					break;
				}
			}
			delete pSD;
		}
#line 3259 "y.tab.c"
    break;

  case 107: /* @18: %empty  */
#line 1432 "hw3.y"
                                   {
			std::string L1 = "L" + std::to_string(LabelIndex++);
			std::string L2 = "L" + std::to_string(LabelIndex++);
			fprintf(output, "isub\n");
			fprintf(output, "ifgt %s\n", L1.c_str());
			fprintf(output, "iconst_0\n");
			fprintf(output, "goto %s\n", L2.c_str());
			fprintf(output, "%s:\n", L1.c_str());
			fprintf(output, "iconst_1\n");
			fprintf(output, "%s:\n", L2.c_str());
			fprintf(output, "ifne L%d\n", LabelIndex);
			(yyval.token)._int = LabelIndex++;
		}
#line 3277 "y.tab.c"
    break;

  case 108: /* $@19: %empty  */
#line 1445 "hw3.y"
                           { 
			SymbolDesc * pSD;
			if(seize(std::string((yyvsp[-8].token)._str),pSD)){
				if(pSD->global){
					// If ID is global variable.
					fprintf(output, "getstatic");
					switch(pSD->symtype){
						case SymbolType::sinteger:
						fprintf(output, " int ");
						break;
						case SymbolType::sreal:
						fprintf(output, " float ");
						break;
						case SymbolType::sstring:
						fprintf(output, " java.lang.String ");
						break;
						default:
						break;
					}
					fprintf(output, "%s.%s\n", ClassName.c_str(), (yyvsp[-8].token)._str);
				}
				else{
					// If ID is local variable.
					switch(pSD->symtype){
						case SymbolType::sinteger:
						fprintf(output, "iload %d\n", pSD->symindex);
						break;
						case SymbolType::sreal:
						fprintf(output, "fload %d\n", pSD->symindex);
						break;
						case SymbolType::sstring:
						fprintf(output, "aload %d\n", pSD->symindex);
						break;
						case SymbolType::sboolean:
						fprintf(output, "iload %d\n", pSD->symindex);
						break;
						default:
						break;
					}
				}
				fprintf(output, "sipush 1\n");
				fprintf(output, "iadd\n");
				if(pSD->global){
					fprintf(output, "putstatic %s %s.%s\n", SymType2JBStr(pSD->symtype).c_str(), ClassName.c_str(), (yyvsp[-8].token)._str);
				}
				else{
					switch(pSD->symtype){
						case SymbolType::sinteger:
						fprintf(output, "istore %d\n",  pSD->symindex);
						break;
						case SymbolType::sreal:
						fprintf(output, "fstore  %d\n", pSD->symindex);
						break;
						case SymbolType::sstring:
						fprintf(output, "astore  %d\n", pSD->symindex);
						break;
					}
				}
				fprintf(output, "goto L%d\n", (yyvsp[-5].token)._int);
				fprintf(output, "L%d:\n", (yyvsp[-1].token)._int);
				
			}
			LEAVESCOPE();
			delete pSD;
		}
#line 3347 "y.tab.c"
    break;

  case 110: /* comparison: expression '<' expression  */
#line 1513 "hw3.y"
                                     {
				(yyval.token).type = TokenType::vbool;
				std::string L1 = "L" + std::to_string(LabelIndex++);
				std::string L2 = "L" + std::to_string(LabelIndex++);
				fprintf(output, "isub\n");
				fprintf(output, "iflt %s\n", L1.c_str());
				fprintf(output, "iconst_0\n");
				fprintf(output, "goto %s\n", L2.c_str());
				fprintf(output, "%s:\n", L1.c_str());
				fprintf(output, "iconst_1\n");
				fprintf(output, "%s:\n", L2.c_str());
			}
#line 3364 "y.tab.c"
    break;

  case 111: /* comparison: expression LE expression  */
#line 1525 "hw3.y"
                                      {
				(yyval.token).type = TokenType::vbool;
				std::string L1 = "L" + std::to_string(LabelIndex++);
				std::string L2 = "L" + std::to_string(LabelIndex++);
				fprintf(output, "isub\n");
				fprintf(output, "ifle %s\n", L1.c_str());
				fprintf(output, "iconst_0\n");
				fprintf(output, "goto %s\n", L2.c_str());
				fprintf(output, "%s:\n", L1.c_str());
				fprintf(output, "iconst_1\n");
				fprintf(output, "%s:\n", L2.c_str());
			}
#line 3381 "y.tab.c"
    break;

  case 112: /* comparison: expression EQ expression  */
#line 1537 "hw3.y"
                                      {
				(yyval.token).type = TokenType::vbool;
				std::string L1 = "L" + std::to_string(LabelIndex++);
				std::string L2 = "L" + std::to_string(LabelIndex++);
				fprintf(output, "isub\n");
				fprintf(output, "ifeq %s\n", L1.c_str());
				fprintf(output, "iconst_0\n");
				fprintf(output, "goto %s\n", L2.c_str());
				fprintf(output, "%s:\n", L1.c_str());
				fprintf(output, "iconst_1\n");
				fprintf(output, "%s:\n", L2.c_str());
			}
#line 3398 "y.tab.c"
    break;

  case 113: /* comparison: expression '>' expression  */
#line 1549 "hw3.y"
                                       {
				(yyval.token).type = TokenType::vbool;
				std::string L1 = "L" + std::to_string(LabelIndex++);
				std::string L2 = "L" + std::to_string(LabelIndex++);
				fprintf(output, "isub\n");
				fprintf(output, "ifgt %s\n", L1.c_str());
				fprintf(output, "iconst_0\n");
				fprintf(output, "goto %s\n", L2.c_str());
				fprintf(output, "%s:\n", L1.c_str());
				fprintf(output, "iconst_1\n");
				fprintf(output, "%s:\n", L2.c_str());
			}
#line 3415 "y.tab.c"
    break;

  case 114: /* comparison: expression GE expression  */
#line 1561 "hw3.y"
                                      {
				(yyval.token).type = TokenType::vbool;
				std::string L1 = "L" + std::to_string(LabelIndex++);
				std::string L2 = "L" + std::to_string(LabelIndex++);
				fprintf(output, "isub\n");
				fprintf(output, "ifge %s\n", L1.c_str());
				fprintf(output, "iconst_0\n");
				fprintf(output, "goto %s\n", L2.c_str());
				fprintf(output, "%s:\n", L1.c_str());
				fprintf(output, "iconst_1\n");
				fprintf(output, "%s:\n", L2.c_str());
			}
#line 3432 "y.tab.c"
    break;

  case 115: /* comparison: expression NE expression  */
#line 1573 "hw3.y"
                                      {
				(yyval.token).type = TokenType::vbool;
				std::string L1 = "L" + std::to_string(LabelIndex++);
				std::string L2 = "L" + std::to_string(LabelIndex++);
				fprintf(output, "isub\n");
				fprintf(output, "ifne %s\n", L1.c_str());
				fprintf(output, "iconst_0\n");
				fprintf(output, "goto %s\n", L2.c_str());
				fprintf(output, "%s:\n", L1.c_str());
				fprintf(output, "iconst_1\n");
				fprintf(output, "%s:\n", L2.c_str());
			}
#line 3449 "y.tab.c"
    break;

  case 119: /* constant_declaration: CONST id ASSIGN declaration_value  */
#line 1592 "hw3.y"
                                                       {
						if (((yyvsp[0].token).type < SymbolType::sarray) && ((yyvsp[0].token).type < SymbolType::sarray)){
							char * name = (yyvsp[-2].token)._str;
							SymbolDesc sd;
							uDependency value;

							sd.symtype = Token2Symbol((yyvsp[0].token).type);
							sd.readonly = true;
							sd.hasValue = true;
							if((yyvsp[0].token).type == vint){
								sd.iValue = (yyvsp[0].token)._int;
							}else if((yyvsp[0].token).type == vbool){
								sd.bValue = (yyvsp[0].token)._bool;
							}else if((yyvsp[0].token).type == vstring){
								sd.sValue = (yyvsp[0].token)._str;
							}else if((yyvsp[0].token).type == vbool){
								sd.iValue = (yyvsp[0].token)._int;
							}
							value.value = (yyvsp[0].token)._ptr;
							sd.returnByFun = (yyvsp[0].token).returnByFun;
							sd.symdeps.push_back(value);
							insert(std::string(name),sd);
							delete name;
						}else{
							// printf("declaration 型態錯誤\n" );
						}
                    }
#line 3481 "y.tab.c"
    break;

  case 120: /* constant_declaration: CONST id ':' type ASSIGN declaration_value  */
#line 1619 "hw3.y"
                                                                 {
						if (((yyvsp[-2].token).type < SymbolType::sarray) && ((yyvsp[-2].token).type < SymbolType::sarray)){
							if ((yyvsp[-2].token).type == (yyvsp[0].token).type){
								char * name = (yyvsp[-4].token)._str;
								SymbolDesc sd;
								uDependency value;

								sd.symtype = Token2Symbol((yyvsp[-2].token).type);
								sd.readonly = true;
								sd.hasValue = true;
								if((yyvsp[-2].token).type == vint){
									sd.iValue = (yyvsp[0].token)._int;
								}else if((yyvsp[-2].token).type == vbool){
									sd.bValue = (yyvsp[0].token)._bool;
								}else if((yyvsp[-2].token).type == vstring){
									sd.sValue = (yyvsp[0].token)._str;
								}else if((yyvsp[-2].token).type == vbool){
									sd.iValue = (yyvsp[0].token)._int;
								}
								value.value = (yyvsp[0].token)._ptr;
								sd.returnByFun = (yyvsp[0].token).returnByFun;
								sd.symdeps.push_back(value);

								insert(std::string(name),sd);
								delete name;
							}
						}else{
							// printf("declaration 型態錯誤或型態不一樣\n" );
						}
                    }
#line 3516 "y.tab.c"
    break;

  case 121: /* variable_declaration: VAR id ':' type  */
#line 1651 "hw3.y"
                                     { 
			std::string name((yyvsp[-2].token)._str);
			SymbolDesc sd;
			sd.symtype = Token2Symbol((yyvsp[0].token).type);
			sd.returnByFun = false;
			insert(std::string(name),sd);
		    }
#line 3528 "y.tab.c"
    break;

  case 122: /* variable_declaration: VAR id ASSIGN declaration_value  */
#line 1658 "hw3.y"
                                                     { 
						if (((yyvsp[0].token).type < SymbolType::sarray) && ((yyvsp[0].token).type < SymbolType::sarray)){
							char * name = (yyvsp[-2].token)._str;
							SymbolDesc sd;
							uDependency value;
							sd.symtype = Token2Symbol((yyvsp[0].token).type);
							sd.hasValue = true;
							if((yyvsp[0].token).type == vint){
								sd.iValue = (yyvsp[0].token)._int;
							}else if((yyvsp[0].token).type == vbool){
								sd.bValue = (yyvsp[0].token)._bool;
							}else if((yyvsp[0].token).type == vstring){
								sd.sValue = (yyvsp[0].token)._str;
							}else if((yyvsp[0].token).type == vbool){
								sd.iValue = (yyvsp[0].token)._int;
							}
							value.value = (yyvsp[0].token)._ptr;
							sd.returnByFun = (yyvsp[0].token).returnByFun;
							sd.symdeps.push_back(value);
							insert(std::string(name),sd);
							delete name;
						}else{
							// printf("declaration 型態錯誤\n" );
						}
		    		}
#line 3558 "y.tab.c"
    break;

  case 123: /* variable_declaration: VAR id ':' type ASSIGN declaration_value  */
#line 1683 "hw3.y"
                                                              { 
						if (((yyvsp[-2].token).type < SymbolType::sarray) && ((yyvsp[-2].token).type < SymbolType::sarray)){
							if ((yyvsp[-2].token).type == (yyvsp[0].token).type){
								char * name = (yyvsp[-4].token)._str;
								SymbolDesc sd;
								uDependency value;
								sd.symtype = Token2Symbol((yyvsp[-2].token).type);
								sd.hasValue = true;
								if((yyvsp[-2].token).type == vint){
									sd.iValue = (yyvsp[0].token)._int;
								}else if((yyvsp[-2].token).type == vbool){
									sd.bValue = (yyvsp[0].token)._bool;
								}else if((yyvsp[-2].token).type == vstring){
									sd.sValue = (yyvsp[0].token)._str;
								}else if((yyvsp[-2].token).type == vbool){
									sd.iValue = (yyvsp[0].token)._int;
								}
								value.value = (yyvsp[0].token)._ptr;
								sd.returnByFun = (yyvsp[0].token).returnByFun;
								sd.symdeps.push_back(value);
								insert(std::string(name),sd);
								delete name;
							}
						}else{
							// printf("declaration 型態錯誤或型態不一樣\n" );
						}
		    		}
#line 3590 "y.tab.c"
    break;

  case 124: /* arrays_declaration: VAR id ':' ARRAY integer '.' '.' integer OF type  */
#line 1712 "hw3.y"
                                                                    {
						SymbolDesc sd;
						uDependency value;
						value.low = (yyvsp[-5].token)._int;
						value.high = (yyvsp[-2].token)._int;
						
						sd.returnByFun = (yyvsp[0].token).returnByFun;
						sd.symtype = SymbolType::sarray;
						sd.symdeps.push_back(value);
						insert((yyvsp[-8].token)._str, sd);
					}
#line 3606 "y.tab.c"
    break;


#line 3610 "y.tab.c"

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
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1725 "hw3.y"


void yyerror(char *msg)
{
    fprintf(stderr, "%s\n", msg);
}
int main(int argc, char **argv)
{
    /* open the source program file */
    if (argc != 2)
    {
        printf("Usage: sc filename\n");
        exit(1);
    }
    yyin = fopen(argv[1], "r"); /* open input file */

	// 改 classname 為 wholename(完整檔案名稱)
	char *filename = strtok(argv[1], ".");
	char *wholeName;
	ClassName = filename;
	sprintf(wholeName, "%s.jasm", filename);

    output = fopen(wholeName, "w");
    InitialTableStack();
    /* perform parsing */
    if (yyparse() == 1)             /* parsing */
        yyerror("Parsing error !"); /* syntax error */

    fclose(output);

}
