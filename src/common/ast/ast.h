#ifndef NSH_COMMON_AST_AST_H
#define NSH_COMMON_AST_AST_H

#include "../../defs.h"

#include "../exec/command.h"

enum nsh_ast_type {
    nsh_ast_type_none,
    nsh_ast_type_command,
    nsh_ast_type_pipe
};

nsh_class(nsh_ast, {
    enum   nsh_ast_type  type;
    struct nsh_command*  command;
    struct nsh_ast*      left;
    struct nsh_ast*      right;
});

struct nsh_ast*  nsh_ast_new_command(struct nsh_command* command);
struct nsh_ast*  nsh_ast_new_pipe(struct nsh_ast* left, struct nsh_ast* right);

void nsh_ast_dump(struct nsh_ast* ast);

#endif
