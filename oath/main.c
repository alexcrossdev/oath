#include <stdio.h>

extern int yyparse(void);
extern FILE *yyin;

int main(int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: oath <file>\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");

    if (!yyin) {
        perror(argv[1]);
        return 1;
    }

    yyparse();

    fclose(yyin);

    return 0;
}
