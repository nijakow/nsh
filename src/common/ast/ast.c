#include "../../util/stdlib.h"

#include "ast.h"

void nsh_ast_create(struct nsh_ast* ast) {
    ast->type    = nsh_ast_type_none;
    ast->command = NULL;
    ast->left    = NULL;
    ast->right   = NULL;
}

void nsh_ast_destroy(struct nsh_ast* ast) {
    if (ast->command != NULL) nsh_command_delete(ast->command);
    if (ast->left    != NULL) nsh_ast_delete(ast->left);
    if (ast->right   != NULL) nsh_ast_delete(ast->right);
}


struct nsh_ast* nsh_ast_new_command(struct nsh_command* command) {
    struct nsh_ast*  ast;

    ast = nsh_ast_new();

    if (ast != NULL) {
        ast->type  = nsh_ast_type_command;
        ast->command = command;
    }

    return ast;
}

struct nsh_ast* nsh_ast_new_binary(enum nsh_ast_type type, struct nsh_ast* left, struct nsh_ast* right) {
    struct nsh_ast*  ast;

    ast = nsh_ast_new();

    if (ast != NULL) {
        ast->type  = type;
        ast->left  = left;
        ast->right = right;
    }

    return ast;
}


struct nsh_ast* nsh_ast_new_pipe(struct nsh_ast* left, struct nsh_ast* right) {
    return nsh_ast_new_binary(nsh_ast_type_pipe, left, right);
}

struct nsh_ast* nsh_ast_new_semicolon(struct nsh_ast* left, struct nsh_ast* right) {
    return nsh_ast_new_binary(nsh_ast_type_semicolon, left, right);
}

struct nsh_ast* nsh_ast_new_and(struct nsh_ast* left, struct nsh_ast* right) {
    return nsh_ast_new_binary(nsh_ast_type_and, left, right);
}

struct nsh_ast* nsh_ast_new_or(struct nsh_ast* left, struct nsh_ast* right) {
    return nsh_ast_new_binary(nsh_ast_type_or, left, right);
}

struct nsh_ast* nsh_ast_new_while(struct nsh_ast* left, struct nsh_ast* right) {
    return nsh_ast_new_binary(nsh_ast_type_while, left, right);
}

static void nsh_ast_dump_with_depth(struct nsh_ast* ast, unsigned int depth) {
    unsigned int  index;

    if (ast->left != NULL) nsh_ast_dump_with_depth(ast->left, depth + 1);
    for (index = 0; index < depth; index++)
        printf("  ");
    printf("%p ", ast);
    switch (ast->type) {
        case nsh_ast_type_command: printf("command"); break;
        case nsh_ast_type_pipe: printf("pipe"); break;
        case nsh_ast_type_semicolon: printf("semicolon"); break;
        case nsh_ast_type_and: printf("&&"); break;
        case nsh_ast_type_or: printf("||"); break;
        case nsh_ast_type_while: printf("while"); break;
        default: printf("???"); break;
    }
    printf("\n");
    if (ast->right != NULL) nsh_ast_dump_with_depth(ast->right, depth + 1);
}

void nsh_ast_dump(struct nsh_ast* ast) {
    nsh_ast_dump_with_depth(ast, 0);
}
