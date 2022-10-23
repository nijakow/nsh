#include "../../util/stdlib.h"

#include "ast.h"

void nsh_ast_create(struct nsh_ast* ast) {
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
        ast->command = command;
    }

    return ast;
}

struct nsh_ast* nsh_ast_new_pipe(struct nsh_ast* left, struct nsh_ast* right) {
    struct nsh_ast*  ast;

    ast = nsh_ast_new();

    if (ast != NULL) {
        ast->left  = left;
        ast->right = right;
        // TODO: Set type to pipe
    }

    return ast;
}
