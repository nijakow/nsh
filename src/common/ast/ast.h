#ifndef NSH_COMMON_AST_AST_H
#define NSH_COMMON_AST_AST_H

#include "../../defs.h"

#include "../exec/command.h"

struct nsh_ast {
    struct command*  command;
    struct nsh_ast*  left;
    struct nsh_ast*  right;
};

void nsh_ast_create(struct nsh_ast* ast);
void nsh_ast_destroy(struct nsh_ast* ast);

#endif
