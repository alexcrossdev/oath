%{
#include "token.h"
#include <stdio.h>
%}

DIGIT   [0-9]

%%

{DIGIT}+        { printf("integer: %d\n", atoi(yytext)); return INTEGER; }

" "             {}

void            { printf("void\n"); }
return          { printf("return\n"); }
i32             { printf("i32\n"); }

"("             { printf("left_paran\n"); }
")"             { printf("right_paran\n"); }
"{"             { printf("left_c_brace\n"); }
"}"             { printf("right_c_brace\n"); }
"["             { printf("left_brace\n"); }
"]"             { printf("left_brace\n"); }
";"             { printf("semicolon\n"); }

[a-z][a-z0-9]*  { printf("identifier: %s\n", yytext); }

%%

int main(int argc, char** argv)
{
    argv++, --argc;
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;
    yylex();
}
