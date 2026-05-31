#include <stdio.h>

#include <codegen.h>
#include <ast.h>

extern int yyparse(void);
extern FILE *yyin;
extern ast_node *root;

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

    ast_dump(root, 0);

    fclose(yyin);

    return 0;
}
