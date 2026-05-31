%option noyywrap
%option noinput nounput

%{
typedef struct ast_node ast_node;
#include "../parser/parser.tab.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
%}

%%

"return"      { return RETURN; }
"void"        { return VOID; }

"if"          { return IF; }
"else"        { return ELSE; }
"while"       { return WHILE; }

"b8"          { return B8; }
"b32"         { return B32; }

"f32"         { return F32; }
"f64"         { return F64; }

"u8"          { return U8; }
"u16"         { return U16; }
"u32"         { return U32; }
"u64"         { return U64; }

"i8"          { return I8; }
"i16"         { return I16; }
"i32"         { return I32; }
"i64"         { return I64; }

"("           { return LP; }
")"           { return RP; }

"["           { return LB; }
"]"           { return RB; }

"{"           { return LCB; }
"}"           { return RCB; }

";"           { return SEMICOLON; }
","           { return COMMA; }

"="           { return ASSIGN; }

"+"           { return PLUS; }
"-"           { return MINUS; }
"*"           { return STAR; }
"/"           { return SLASH; }

[0-9]+ {
    yylval.integer = strtol(yytext, NULL, 10);
    return INTEGER;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.string = strdup(yytext);
    return IDENTIFIER;
}

[ \t\r\n]+ ;

. {
    fprintf(stderr, "unknown character: %s\n", yytext);
}

%%
