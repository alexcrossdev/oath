%{
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <ast.h>

void yyerror(const char *s);
int yylex(void);

ast_node *root;
%}

%define parse.error detailed
%define parse.lac full

%union {
    long integer;
    char *string;
    ast_node *node;
}

%token <string> IDENTIFIER
%token <integer> INTEGER

%token RETURN
%token VOID

%token IF
%token ELSE
%token WHILE

%token B8
%token B32

%token F32
%token F64

%token U8
%token U16
%token U32
%token U64

%token I8
%token I16
%token I32
%token I64

%token LP RP
%token LB RB
%token LCB RCB

%token SEMICOLON
%token COMMA

%token ASSIGN

%token PLUS
%token MINUS
%token STAR
%token SLASH

%left PLUS MINUS
%left STAR SLASH

%type <node> type

%type <node> program
%type <node> functions
%type <node> function

%type <node> parameters
%type <node> parameter_list
%type <node> parameter

%type <node> scope
%type <node> statements
%type <node> statements_opt
%type <node> statement

%type <node> declaration
%type <node> assignment

%type <node> expression
%type <node> function_call

%type <node> arguments
%type <node> argument_list

%%

program:
        functions
        {
            root = $1;
            $$ = $1;
        }
    ;

functions:
        function
        {
            $$ = ast_program();
            ast_program_add_function($$, $1);
        }
    |   functions function
        {
            ast_program_add_function($1, $2);
            $$ = $1;
        }
    ;

function:
        type IDENTIFIER LP parameters RP scope
        {
            $$ = ast_function(
                $2,
                $1,
                $4,
                $6
            );
        }
    ;

parameters:
        VOID
        {
            $$ = ast_parameter_list();
        }
    |   parameter_list
        {
            $$ = $1;
        }
    |   /* empty */
        {
            $$ = ast_parameter_list();
        }
    ;

parameter_list:
        parameter
        {
            $$ = ast_parameter_list();
            ast_parameter_list_add($$, $1);
        }
    |   parameter_list COMMA parameter
        {
            ast_parameter_list_add($1, $3);
            $$ = $1;
        }
    ;

parameter:
        type IDENTIFIER
        {
            $$ = ast_parameter($1, $2);
        }
    ;

type:
        VOID { $$ = ast_type("void"); }
    |   B8   { $$ = ast_type("b8"); }
    |   B32  { $$ = ast_type("b32"); }
    |   F32  { $$ = ast_type("f32"); }
    |   F64  { $$ = ast_type("f64"); }
    |   U8   { $$ = ast_type("u8"); }
    |   U16  { $$ = ast_type("u16"); }
    |   U32  { $$ = ast_type("u32"); }
    |   U64  { $$ = ast_type("u64"); }
    |   I8   { $$ = ast_type("i8"); }
    |   I16  { $$ = ast_type("i16"); }
    |   I32  { $$ = ast_type("i32"); }
    |   I64  { $$ = ast_type("i64"); }
    ;

scope:
        LCB statements_opt RCB
        {
            $$ = $2;
        }
    ;

statements_opt:
        {
            $$ = ast_scope();
        }
    |   statements
        {
            $$ = $1;
        }
    ;

statements:
        statement
        {
            $$ = ast_scope();
            ast_scope_add($$, $1);
        }
    |   statements statement
        {
            ast_scope_add($1, $2);
            $$ = $1;
        }
    ;

statement:
        declaration SEMICOLON
        {
            $$ = $1;
        }
    |   assignment SEMICOLON
        {
            $$ = $1;
        }
    |   expression SEMICOLON
        {
            $$ = $1;
        }
    |   RETURN expression SEMICOLON
        {
            $$ = ast_return($2);
        }
    |   IF LP expression RP scope
        {
            $$ = ast_if($3, $5, NULL);
        }
    |   IF LP expression RP scope ELSE scope
        {
            $$ = ast_if($3, $5, $7);
        }
    |   WHILE LP expression RP scope
        {
            $$ = ast_while($3, $5);
        }
    |   scope
        {
            $$ = $1;
        }
    ;

declaration:
        type IDENTIFIER
        {
            $$ = ast_declaration($1, $2);
        }
    ;

assignment:
        IDENTIFIER ASSIGN expression
        {
            $$ = ast_assignment($1, $3);
        }
    ;

expression:
        INTEGER
        {
            $$ = ast_integer($1);
        }
    |   IDENTIFIER
        {
            $$ = ast_identifier($1);
        }
    |   LP expression RP
        {
            $$ = $2;
        }
    |   expression PLUS expression
        {
            $$ = ast_binary('+', $1, $3);
        }
    |   expression MINUS expression
        {
            $$ = ast_binary('-', $1, $3);
        }
    |   expression STAR expression
        {
            $$ = ast_binary('*', $1, $3);
        }
    |   expression SLASH expression
        {
            $$ = ast_binary('/', $1, $3);
        }
    |   function_call
        {
            $$ = $1;
        }
    ;

function_call:
        IDENTIFIER LP arguments RP
        {
            $$ = ast_call($1, $3);
        }
    ;

arguments:
        {
            $$ = ast_argument_list();
        }
    |   argument_list
        {
            $$ = $1;
        }
    ;

argument_list:
        expression
        {
            $$ = ast_argument_list();
            ast_argument_list_add($$, $1);
        }
    |   argument_list COMMA expression
        {
            ast_argument_list_add($1, $3);
            $$ = $1;
        }
    ;

%%

void yyerror(const char *s)
{
    fprintf(stderr, "parser error: %s\n", s);
}
