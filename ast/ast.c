#include "ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ast_node *ast_new(ast_kind kind)
{
    ast_node *node =
        calloc(1, sizeof(ast_node));

    if (!node) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    node->kind = kind;

    return node;
}

ast_node *ast_program(void)
{
    return ast_new(AST_PROGRAM);
}

void ast_program_add_function(
    ast_node *program,
    ast_node *function)
{
    size_t count =
        program->program.count;

    program->program.functions =
        realloc(
            program->program.functions,
            sizeof(ast_node *) * (count + 1));

    program->program.functions[count] =
        function;

    program->program.count++;
}

ast_node *ast_function(
    char *name,
    ast_node *return_type,
    ast_node *parameters,
    ast_node *body)
{
    ast_node *node =
        ast_new(AST_FUNCTION);

    node->function.name =
        strdup(name);

    node->function.return_type =
        strdup(return_type->type.name);

    node->function.parameters =
        parameters->parameter_list.parameters;

    node->function.parameter_count =
        parameters->parameter_list.count;

    node->function.body =
        body;

    return node;
}

ast_node *ast_type(
    const char *name)
{
    ast_node *node =
        ast_new(AST_TYPE);

    node->type.name =
        strdup(name);

    return node;
}

ast_node *ast_parameter(
    ast_node *type,
    char *name)
{
    ast_node *node =
        ast_new(AST_PARAMETER);

    node->parameter.type =
        type;

    node->parameter.name =
        strdup(name);

    return node;
}

ast_node *ast_parameter_list(void)
{
    return ast_new(
        AST_PARAMETER_LIST);
}

void ast_parameter_list_add(
    ast_node *list,
    ast_node *parameter)
{
    size_t count =
        list->parameter_list.count;

    list->parameter_list.parameters =
        realloc(
            list->parameter_list.parameters,
            sizeof(ast_node *) * (count + 1));

    list->parameter_list.parameters[count] =
        parameter;

    list->parameter_list.count++;
}

ast_node *ast_argument_list(void)
{
    return ast_new(
        AST_ARGUMENT_LIST);
}

void ast_argument_list_add(
    ast_node *list,
    ast_node *argument)
{
    size_t count =
        list->argument_list.count;

    list->argument_list.arguments =
        realloc(
            list->argument_list.arguments,
            sizeof(ast_node *) * (count + 1));

    list->argument_list.arguments[count] =
        argument;

    list->argument_list.count++;
}

ast_node *ast_scope(void)
{
    return ast_new(AST_SCOPE);
}

void ast_scope_add(
    ast_node *scope,
    ast_node *statement)
{
    size_t count =
        scope->scope.count;

    scope->scope.statements =
        realloc(
            scope->scope.statements,
            sizeof(ast_node *) * (count + 1));

    scope->scope.statements[count] =
        statement;

    scope->scope.count++;
}

ast_node *ast_return(
    ast_node *value)
{
    ast_node *node =
        ast_new(AST_RETURN);

    node->ret.value =
        value;

    return node;
}

ast_node *ast_if(
    ast_node *condition,
    ast_node *then_scope,
    ast_node *else_scope)
{
    ast_node *node =
        ast_new(AST_IF);

    node->if_stmt.condition =
        condition;

    node->if_stmt.then_scope =
        then_scope;

    node->if_stmt.else_scope =
        else_scope;

    return node;
}

ast_node *ast_while(
    ast_node *condition,
    ast_node *body)
{
    ast_node *node =
        ast_new(AST_WHILE);

    node->while_stmt.condition =
        condition;

    node->while_stmt.body =
        body;

    return node;
}

ast_node *ast_declaration(
    ast_node *type,
    char *name)
{
    ast_node *node =
        ast_new(AST_DECLARATION);

    node->declaration.type =
        type;

    node->declaration.name =
        strdup(name);

    return node;
}

ast_node *ast_assignment(
    char *name,
    ast_node *value)
{
    ast_node *node =
        ast_new(AST_ASSIGNMENT);

    node->assignment.name =
        strdup(name);

    node->assignment.value =
        value;

    return node;
}

ast_node *ast_call(
    char *name,
    ast_node *arguments)
{
    ast_node *node =
        ast_new(AST_CALL);

    node->call.name =
        strdup(name);

    node->call.args =
        arguments->argument_list.arguments;

    node->call.argc =
        arguments->argument_list.count;

    return node;
}

ast_node *ast_binary(
    int op,
    ast_node *left,
    ast_node *right)
{
    ast_node *node =
        ast_new(AST_BINARY);

    node->binary.op =
        op;

    node->binary.left =
        left;

    node->binary.right =
        right;

    return node;
}

ast_node *ast_integer(
    long value)
{
    ast_node *node =
        ast_new(AST_INTEGER);

    node->integer =
        value;

    return node;
}

ast_node *ast_identifier(
    char *name)
{
    ast_node *node =
        ast_new(AST_IDENTIFIER);

    node->identifier =
        strdup(name);

    return node;
}
