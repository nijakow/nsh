#ifndef NSH_COMMON_AST_AST_H
#define NSH_COMMON_AST_AST_H

#include "../../defs.h"

#include "../exec/command.h"

nsh_class(nsh_ast, {
    struct nsh_command*  command;
    struct nsh_ast*      left;
    struct nsh_ast*      right;
});

struct nsh_ast*  nsh_ast_new_command(struct nsh_command* command);
struct nsh_ast*  nsh_ast_new_pipe(struct nsh_ast* left, struct nsh_ast* right);

#endif
