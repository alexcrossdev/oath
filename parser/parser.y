%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

%token IDENTIFIER
%token INTEGER

%token RETURN
%token VOID

%token I8
%token I16
%token I32
%token I64

%%

program:
        function
    ;

function:
        type IDENTIFIER '(' parameters ')' block
    ;

parameters:
        VOID
    ;

type:
        VOID
    |   I32
    ;

block:
        '{' statements '}'
    ;

statements:
        statement
    |   statements statement
    ;

statement:
        RETURN INTEGER ';'
        {
            printf("return: %d\n", $2);
        }
    ;

%%

void yyerror(const char *s)
{
    fprintf(stderr, "parser error: %s\n", s);
}
