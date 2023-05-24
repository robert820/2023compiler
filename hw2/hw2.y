%{
#include "SymbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#define Trace(t)        printf(t)
extern FILE *yyin;
int yylex();
void yyerror(char *s);
%}

%union {
    Hash*          symbol;
    int                      ivalue;
    char*                    str;
    float                    fvalue;
    _Bool                    bvalue;
    //identifier_type*           identifier;
    //value_type identifier_value_type;
}

%start program


/* tokens */
/*
%token SEMICOLON
*/
/*
%token id
%token string
%token integer
%token real
*/
%token DE ME SE AE NE EQ GE LE ASSIGN AND OR NOT

//%token <str> identifier
//%token <ivalue> NUMBER
/*%left <integer> OP_ADDITION OP_SUBTRACTION
%left <integer> OP_MULTIPLICATION OP_DIVISION*/

%left '>' '<' LE EQ GE NE

%left '+' '-'
%left '*' '/' MOD
%left UMINUS

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

//%nonassoc ONE
//%nonassoc TWO
//%nonassoc THREE

//%nonassoc FOUR
//%nonassoc FIVE

%token BOOL BREAK CHAR CASE CLASS CONTINUE DECLARE DO IF EXIT FLOAT FOR FUNCTION INT LOOP PRINT PRINTLN RETURN STRING VAR REAL ARRAY OF END PROCEDURE CONST CBEGIN PUT GET RESULT WHEN SKIP THEN DEFAULT DECREASING

%token <bvalue> TRUE
%token <bvalue> FALSE

//%type <ivalue> integer_expression
//%type <bvalue> bool_expresssion
%type <bvalue> boolean
%token <str> string id
%token <ivalue> integer
%token <fvalue> real

%%

program:  program declaration
        | program function
        | program procedure
        | program statement
        //| program class
        |
        ;

/* classes: class classes
        |//empty
        ;

class:          CLASS id '{' declarations_and_functions '}'
                {
                Trace("Reducing to program\n");
                }
                ; 
*/

/* declaration_and_function: declaration
                        | function
                        ;

declarations_and_functions: declaration_and_function declarations_and_functions
                            |
                            ; */



/* functions:      function functions
                |
                ; */

fd:     statements END id
        |
        ;

function:       FUNCTION id '(' arguments ')' returnType fd
                ;


procedure:      PROCEDURE id '(' arguments ')' fd
                ;

arguments: argument arguments
            |/*empty*/
            ;

argument: id ':' type  seperator;

seperator: ','
            |/*empty*/
            ;

returnType:/*empty*/
            | ':' type
            ;

statements:/*empty*/
    | statement statements
    ;

type:   STRING  // {$$ = bool_v;}
        | INT
        | BOOL
        | FLOAT
        ;

statement: declaration
        | block
        | condition
        | loop
        | id ASSIGN expression
        | return
        | PUT expression
        | GET expression
        | EXIT exit_optional
        | PRINTLN expression
        | SKIP
        ;

return: RESULT returnValue
        | RETURN
        ;

exit_optional: WHEN expression
                |
                ;

returnValue: expression
        |
        ;

expression: integer_expression
            | '(' expression ')'
            | id '(' expression_list ')'
            | bool_expression
            | comparison
            | id
            | integer
            | string
            | boolean
            | real
            ;

expression_list: 
                |expression
		|expression_list ',' expression
                ;

boolean: TRUE
        |FALSE
        ;

integer_expression: expression '+' expression
                    | '-' expression   %prec UMINUS
                    | expression '-' expression
                    | expression '*' expression
                    | expression '/' expression
                    | expression MOD expression
                    ;

bool_expression:  NOT expression              //{$$ = !$2;}
                | expression AND expression
                | expression OR expression
                ;

condition: IF expression THEN statements END IF %prec LOWER_THAN_ELSE
        | IF expression THEN statements ELSE statements END IF
        ;

/* condition: IF bool_expression THEN statements Y_N_else END IF
        ;

Y_N_else:
        | ELSE statements
        ; */

block: CBEGIN statements END
        ;

loop: LOOP statements END LOOP
    | FOR id ':' expression '.' '.' expression statements END FOR
    ;

comparison: expression '<' expression
            | expression LE expression
            | expression EQ expression
            | expression '>' expression
            | expression GE expression
            | expression NE expression
            ;

/* declarations: declaration declarations
            | // empty
            ; */

declaration: constant_declaration
            |variable_declaration
            |arrays_declaration
            ;

constant_declaration: CONST id ASSIGN expression
                    | CONST id ':' type ASSIGN expression 
                    ;

variable_declaration: VAR id ':' type
                    | VAR id ASSIGN expression
                    | VAR id ':' type ASSIGN expression
                    ;

arrays_declaration: VAR id ':' ARRAY integer '.' '.' integer OF type
                    ;

/*semi:           SEMICOLON
                {
                Trace("Reducing to semi\n");
                }
                ;
*/
%%

void yyerror(char *msg)
{
    fprintf(stderr, "%s\n", msg);
}

int main(int argc, char** argv)
{
    /* open the source program file */
    if (argc != 2) {
        printf ("Usage: sc filename\n");
        exit(1);
    }
    yyin = fopen(argv[1], "r");         /* open input file */

    /* perform parsing */
    if (yyparse() == 1)                 /* parsing */
        yyerror("Parsing error !");     /* syntax error */
}
