%{
#define LIST     strcat(buf,yytext)
#define token(t) {LIST; printf("<%s>\n",#t);}
#define tokenInteger(t,i) {LIST; printf("<%s:%s>\n",#t,i);}
#define tokenReal(t, r)	{LIST; printf("<%s:%s>\n", #t, r);}
#define tokenString(t,s) {LIST; printf("<%s:%s>\n",#t,s);}

#define MAX_LINE_LENG 256

#include "SymbolTable.h"

int linenum = 1;
char buf[MAX_LINE_LENG];
Hash *symbolTable;
char *dumpResult;
%}

digit     [0-9]
letter    [A-Za-z]
identifier	{letter}({letter}|{digit})*
integer	[+-]?{digit}+
real	[+-]?{digit}*\.{digit}+([Ee]([+-]?{digit})*)?
string	\"(\\.|[^"\\])*\"
bool true|false
%x COMMENT
%x S_COMMENT
%%
"."	{
	token('.');
	}

","	{
	token(',');
	}

":"	{
	token(':');
	}

";"	{
	token(';');
	}

"("     {
	token('(');
	}

")"	{
	token(')');
	}

"["	{
	token('[');
	}

"]"	{
	token(']');
	}

"{"	{
	token('{');
	}

"}"	{
	token('}');
	}

"+"	{
	token('+');
	}

"-"	{
	token('-');
	}

"*"	{
	token('*');
	}

"/"	{
	token('/');
	}

"mod"	{
	token('mod');
	}

":="	{
	token(':=');
	}

"<"	{
	token('<');
	}

"<="	{
	token('<=');
	}

">="	{
	token('>=');
	}

">"	{
	token('>');
	}

"="	{
	token('=');
	}

"not="	{
	token('not=');
	}

"and"	{
	token('and');
	}

"or"	{
	token('or');
	}

"not"	{
	token('not');
	}

"function"	{
	token(FUNCTION);
	}

"array" {
	token(ARRAY);
	}

"bool"	{
	token(BOOL);
	}

"end"	{
	token(END);
	}

"char"	{
	token(CHAR);
	}

"const"	{
	token(CONST);
	}

"decreasing"	{
		token(DECREASING);
		}

"default"	{
		token(DEFAULT);
		}

"do"	{
	token(DO);
	}

"else"
	{
	token(ELSE);
	}

"exit"	{
	token(EXIT);
	}

"false"	{
	token(FALSE);
	}

"for"	{
	token(FOR);
	}

"get"	{
	token(GET);
	}

"if"	{
	token(IF);
	}

"int"	{
	token(INT);
	}

"loop"	{
	token(LOOP);
	}

"of"	{
	token(OF);
	}

"put"	{
	token(PUT);
	}

"procedure"	{
	token(PROCEDURE);
	}

"real"	{
	token(REAL);
	}

"result"	{
	token(RESULT);
	}

"return"	{
		token(RETURN);
		}

"skip"	{
	token(SKIP);
	}

"string"	{
		token(STRING);
		}

"then"	{
	token(THEN);
	}

"true"	{
	token(TRUE);
	}

"var"	{
	token(VAR);
	}

"when"	{
	token(WHEN);
	}


{identifier}	{
		tokenString(id, yytext);
		insert(symbolTable, yytext);
		}

{string}	{
		tokenString(string, yytext);
		}

{integer}	{
		tokenInteger(integer, yytext);
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
