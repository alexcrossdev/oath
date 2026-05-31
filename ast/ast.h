#ifndef AST_H
#define AST_H

#include <stddef.h>

typedef enum {
    AST_PROGRAM,

    AST_FUNCTION,

    AST_TYPE,

    AST_PARAMETER,
    AST_PARAMETER_LIST,

    AST_ARGUMENT_LIST,

    AST_SCOPE,

    AST_RETURN,
    AST_IF,
    AST_WHILE,

    AST_DECLARATION,
    AST_ASSIGNMENT,

    AST_CALL,

    AST_BINARY,

    AST_INTEGER,
    AST_IDENTIFIER
} ast_kind;

typedef struct ast_node ast_node;

struct ast_node {
    ast_kind kind;

    union {

        struct {
            ast_node **functions;
            size_t count;
        } program;

        struct {
            char *name;
            char *return_type;

            ast_node **parameters;
            size_t parameter_count;

            ast_node *body;
        } function;

        struct {
            char *name;
        } type;

        struct {
            ast_node *type;
            char *name;
        } parameter;

        struct {
            ast_node **parameters;
            size_t count;
        } parameter_list;

        struct {
            ast_node **arguments;
            size_t count;
        } argument_list;

        struct {
            ast_node **statements;
            size_t count;
        } scope;

        struct {
            ast_node *value;
        } ret;

        struct {
            ast_node *condition;
            ast_node *then_scope;
            ast_node *else_scope;
        } if_stmt;

        struct {
            ast_node *condition;
            ast_node *body;
        } while_stmt;

        struct {
            ast_node *type;
            char *name;
        } declaration;

        struct {
            char *name;
            ast_node *value;
        } assignment;

        struct {
            char *name;

            ast_node **args;
            size_t argc;
        } call;

        struct {
            int op;

            ast_node *left;
            ast_node *right;
        } binary;

        long integer;

        char *identifier;
    };
};

void ast_dump(ast_node *node, int depth);

ast_node *ast_new(ast_kind kind);

ast_node *ast_program(void);
void ast_program_add_function(
    ast_node *program,
    ast_node *function);

ast_node *ast_function(
    char *name,
    ast_node *return_type,
    ast_node *parameters,
    ast_node *body);

ast_node *ast_type(
    const char *name);

ast_node *ast_parameter(
    ast_node *type,
    char *name);

ast_node *ast_parameter_list(void);

void ast_parameter_list_add(
    ast_node *list,
    ast_node *parameter);

ast_node *ast_argument_list(void);

void ast_argument_list_add(
    ast_node *list,
    ast_node *argument);

ast_node *ast_scope(void);

void ast_scope_add(
    ast_node *scope,
    ast_node *statement);

ast_node *ast_return(
    ast_node *value);

ast_node *ast_if(
    ast_node *condition,
    ast_node *then_scope,
    ast_node *else_scope);

ast_node *ast_while(
    ast_node *condition,
    ast_node *body);

ast_node *ast_declaration(
    ast_node *type,
    char *name);

ast_node *ast_assignment(
    char *name,
    ast_node *value);

ast_node *ast_call(
    char *name,
    ast_node *arguments);

ast_node *ast_binary(
    int op,
    ast_node *left,
    ast_node *right);

ast_node *ast_integer(
    long value);

ast_node *ast_identifier(
    char *name);

#endif
