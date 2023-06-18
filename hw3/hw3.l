%{
#define LIST     strcat(buf,yytext)
#define token(t) {LIST; printf("<%s>\n",#t);}
#define tokenInteger(t,i) {LIST; printf("<%s:%s>\n", #t, i); return t;}
#define tokenReal(t, r)	{LIST; printf("<%s:%s>\n", #t, r); return t;}
#define tokenString(t,s) {LIST; printf("<%s:%s>\n", #t, s); }

#define MAX_LINE_LENG 256

#include <iostream>
#include <vector>
#include <string>
#include "SymbolTable.h"
#include "token.h"
#include "y.tab.h"

int linenum = 1;
char buf[MAX_LINE_LENG];
Hash *symbolTable;
std::vector<std::string> dumpResult;
%}

digit     [0-9]
letter    [A-Za-z]
identifier	{letter}({letter}|{digit})*
integer	[+-]?{digit}+
real	[+-]?{digit}+(\.{digit}+)?([Ee]([+-]?{digit})*)?
string	\"(\\.|[^"\\])*\"
bool true|false
%x COMMENT
%x S_COMMENT
%%
"."	{
	token('.');
	return('.');
	}

","	{
	token(',');
	return(',');
	}

":"	{
	token(':');
	return(':');
	}

";"	{
	token(';');
	return(';');
	}

"("     {
	token('(');
	return('(');
	}

")"	{
	token(')');
	return(')');
	}

"["	{
	token('[');
	return('[');
	}

"]"	{
	token(']');
	return(']');
	}

"{"	{
	token('{');
	return('{');
	}

"}"	{
	token('}');
	return('}');
	}

"+"	{
	token('+');
	return('+');
	}

"-"	{
	token('-');
	return('-');
	}

"*"	{
	token('*');
	return('*');
	}

"/"	{
	token('/');
	return('/');
	}

"mod"	{
	token('mod');
	return(MOD);
	}

":="	{
	token(':=');
	return(ASSIGN);
	}

"<"	{
	token('<');
	return('<');
	}

"<="	{
	token('<=');
	return(LE);
	}

">="	{
	token('>=');
	return(GE);
	}

">"	{
	token('>');
	return('>');
	}

"="	{
	token('=');
	return(EQ);
	}

"not="	{
	token('not=');
	return(NE);
	}

"and"	{
	token('and');
	return(AND);
	}

"or"	{
	token('or');
	return(OR);
	}

"not"	{
	token('not');
	return(NOT);
	}

"function"	{
	token(FUNCTION);
	return(FUNCTION);
	}

"array" {
	token(ARRAY);
	return(ARRAY);
	}

"begin" {
	token(BEGIN);
	return(CBEGIN);
	}

"bool"	{
	token(BOOL);
	return(BOOL);
	}

"end"	{
	token(END);
	return(END);
	}

"char"	{
	token(CHAR);
	return(CHAR);
	}

"const"	{
	token(CONST);
	return(CONST);
	}

"decreasing"	{
		token(DECREASING);
		return(DECREASING);
		}

"default"	{
		token(DEFAULT);
		return(DEFAULT);
		}

"do"	{
	token(DO);
	return(DO);
	}

"else"	{
	token(ELSE);
	return(ELSE);
	}

"exit"	{
	token(EXIT);
	return(EXIT);
	}

"false"	{
	token(FALSE);
	return(FALSE);
	}

"for"	{
	token(FOR);
	return(FOR);
	}

"get"	{
	token(GET);
	return(GET);
	}

"if"	{
	token(IF);
	return(IF);
	}

"int"	{
	token(INT);
	return(INT);
	}

"loop"	{
	token(LOOP);
	return(LOOP);
	}

"of"	{
	token(OF);
	return(OF);
	}

"put"	{
	token(PUT);
	return(PUT);
	}

"procedure"	{
	token(PROCEDURE);
	return(PROCEDURE);
	}

"real"	{
	token(REAL);
	return(REAL);
	}

"result"	{
	token(RESULT);
	return(RESULT);
	}

"return"	{
		token(RETURN);
		return(RETURN);
		}

"skip"	{
	token(SKIP);
	return(SKIP);
	}

"string"	{
		token(STRING);
		return(KW_STRING);
		}

"then"	{
	token(THEN);
	return(THEN);
	}

"true"	{
	token(TRUE);
	return(TRUE);
	}

"var"	{
	token(VAR);
	return(VAR);
	}

"when"	{
	token(WHEN);
	return(WHEN);
	}


{identifier}	{
		yylval.token._str = strdup(yytext);
		yylval.token.type = TokenType::idType;
		tokenString(id, yytext);
		return(id);
		insert(symbolTable, yytext);
		}

{string}	{
		yylval.token._str = strdup(yytext);
		yylval.token.type = TokenType::vstring;
		tokenString(string, yytext);
		return(str);
		}

{integer}	{
		yylval.token._int = atoi(yytext);
		yylval.token.type = TokenType::vint;
		tokenInteger(integer, yytext);
		}

{real}	{
		yylval.token._int = atof(yytext);
		yylval.token.type = TokenType::vreal;
		tokenReal(real, yytext);
		}

\n      {
        LIST;
        printf("%d: %s", linenum++, buf);
        buf[0] = '\0';
        }

[ \t]*  { LIST; }

"{%"	{
	LIST;
	BEGIN(COMMENT);
	}
<COMMENT>"%}" {
		LIST;
		BEGIN(INITIAL);
		}
<COMMENT>.    { LIST; }

"%"	{
	LIST;
	BEGIN(S_COMMENT);
	}
<S_COMMENT>\n	{
		LIST;
		printf("%d:%s", linenum++, buf);
		buf[0] = '\0';
		BEGIN(INITIAL);
		}
<S_COMMENT>.	{ LIST; }





.       {
        LIST;
        printf("%d:%s\n", linenum+1, buf);
        printf("bad character:'%s'\n",yytext);
        exit(-1);
        }
%%


//原本的

/*
int main() {
    symbolTable = create();
	
    yylex();

    printf("\nSymbol Table:\n");

	dumpResult = dump(symbolTable);
	char *cur = dumpResult;
	for(int i = 0; i < symbolTable->size; i++) {
        cur = dumpResult + i * NAME_MAX_LENGTH;
		for(int j = 0; j < NAME_MAX_LENGTH; j++){
        	printf("%c", cur[j]);
		}
		printf("\n");
    }

    exit(0);
}
*/


//想改++

// int main() {
//     symbolTable = create();
	
//     yylex();

//     printf("\nSymbol Table:\n");

// 	dumpResult = dump(symbolTable);
// 	for(int i = 0; i < symbolTable->size; i++) {
//      printf("%c", dumpResult[j]);
// 		printf("\n");
//     }

//     exit(0);
// }