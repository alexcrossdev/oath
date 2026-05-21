%option noyywrap
%option noinput nounput

%{
#include "../parser/parser.tab.h"

#include <stdlib.h>
%}

DIGIT      [0-9]
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*

%%

"return"        { return RETURN; }
"void"          { return VOID; }

"i8"            { return I8; }
"i16"           { return I16; }
"i32"           { return I32; }
"i64"           { return I64; }

[-]*{DIGIT}+    {
                    yylval = atoi(yytext);
                    return INTEGER;
                }

{IDENTIFIER}    { return IDENTIFIER; }

"("             { return '('; }
")"             { return ')'; }
"{"             { return '{'; }
"}"             { return '}'; }
";"             { return ';'; }

[ \t\n]+        {}

.               {
                    return yytext[0];
                }

%%
