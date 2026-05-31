#include "ast.h"

#include <stdio.h>

static void indent(int depth)
{
    for (int i = 0; i < depth; i++)
        printf("  ");
}

void ast_dump(ast_node *node, int depth)
{
    if (!node) {
        indent(depth);
        printf("(null)\n");
        return;
    }

    switch (node->kind) {

    case AST_PROGRAM:
        indent(depth);
        printf("PROGRAM\n");

        for (size_t i = 0;
             i < node->program.count;
             i++)
        {
            ast_dump(
                node->program.functions[i],
                depth + 1);
        }
        break;

    case AST_FUNCTION:
        indent(depth);
        printf(
            "FUNCTION %s -> %s\n",
            node->function.name,
            node->function.return_type);

        indent(depth + 1);
        printf("PARAMETERS\n");

        for (size_t i = 0;
             i < node->function.parameter_count;
             i++)
        {
            ast_dump(
                node->function.parameters[i],
                depth + 2);
        }

        indent(depth + 1);
        printf("BODY\n");

        ast_dump(
            node->function.body,
            depth + 2);
        break;

    case AST_TYPE:
        indent(depth);
        printf(
            "TYPE %s\n",
            node->type.name);
        break;

    case AST_PARAMETER:
        indent(depth);
        printf(
            "PARAMETER %s\n",
            node->parameter.name);

        ast_dump(
            node->parameter.type,
            depth + 1);
        break;

    case AST_PARAMETER_LIST:
        indent(depth);
        printf("PARAMETER_LIST\n");

        for (size_t i = 0;
             i < node->parameter_list.count;
             i++)
        {
            ast_dump(
                node->parameter_list.parameters[i],
                depth + 1);
        }
        break;

    case AST_ARGUMENT_LIST:
        indent(depth);
        printf("ARGUMENT_LIST\n");

        for (size_t i = 0;
             i < node->argument_list.count;
             i++)
        {
            ast_dump(
                node->argument_list.arguments[i],
                depth + 1);
        }
        break;

    case AST_SCOPE:
        indent(depth);
        printf("SCOPE\n");

        for (size_t i = 0;
             i < node->scope.count;
             i++)
        {
            ast_dump(
                node->scope.statements[i],
                depth + 1);
        }
        break;

    case AST_RETURN:
        indent(depth);
        printf("RETURN\n");

        ast_dump(
            node->ret.value,
            depth + 1);
        break;

    case AST_IF:
        indent(depth);
        printf("IF\n");

        indent(depth + 1);
        printf("CONDITION\n");

        ast_dump(
            node->if_stmt.condition,
            depth + 2);

        indent(depth + 1);
        printf("THEN\n");

        ast_dump(
            node->if_stmt.then_scope,
            depth + 2);

        if (node->if_stmt.else_scope) {
            indent(depth + 1);
            printf("ELSE\n");

            ast_dump(
                node->if_stmt.else_scope,
                depth + 2);
        }
        break;

    case AST_WHILE:
        indent(depth);
        printf("WHILE\n");

        indent(depth + 1);
        printf("CONDITION\n");

        ast_dump(
            node->while_stmt.condition,
            depth + 2);

        indent(depth + 1);
        printf("BODY\n");

        ast_dump(
            node->while_stmt.body,
            depth + 2);
        break;

    case AST_DECLARATION:
        indent(depth);
        printf(
            "DECLARATION %s\n",
            node->declaration.name);

        ast_dump(
            node->declaration.type,
            depth + 1);
        break;

    case AST_ASSIGNMENT:
        indent(depth);
        printf(
            "ASSIGNMENT %s\n",
            node->assignment.name);

        ast_dump(
            node->assignment.value,
            depth + 1);
        break;

    case AST_CALL:
        indent(depth);
        printf(
            "CALL %s\n",
            node->call.name);

        for (size_t i = 0;
             i < node->call.argc;
             i++)
        {
            ast_dump(
                node->call.args[i],
                depth + 1);
        }
        break;

    case AST_BINARY:
        indent(depth);
        printf(
            "BINARY %c\n",
            node->binary.op);

        ast_dump(
            node->binary.left,
            depth + 1);

        ast_dump(
            node->binary.right,
            depth + 1);
        break;

    case AST_INTEGER:
        indent(depth);
        printf(
            "INTEGER %ld\n",
            node->integer);
        break;

    case AST_IDENTIFIER:
        indent(depth);
        printf(
            "IDENTIFIER %s\n",
            node->identifier);
        break;

    default:
        indent(depth);
        printf(
            "UNKNOWN NODE (%d)\n",
            node->kind);
        break;
    }
}
