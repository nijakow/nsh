#include "../../util/stdlib.h"

#include "ast.h"

void nsh_ast_create(struct nsh_ast* ast) {
    ast->command = NULL;
    ast->left    = NULL;
    ast->right   = NULL;
}

void nsh_ast_destroy(struct nsh_ast* ast) {
    if (ast->command != NULL) nsh_delete(ast->command, nsh_command_destroy);
    if (ast->left    != NULL) nsh_delete(ast->left, nsh_ast_destroy);
    if (ast->right   != NULL) nsh_delete(ast->right, nsh_ast_destroy);
}
