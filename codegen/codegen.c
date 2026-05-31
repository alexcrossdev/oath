#include "codegen.h"
#include <stdio.h>

void emit_header()
{
    FILE* file = fopen("out.S", "w");

    fprintf(file, "test\n");
}
