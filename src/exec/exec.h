#ifndef NSH_EXEC_EXEC_H
#define NSH_EXEC_EXEC_H

#include "../defs.h"

#include "../common/ast/ast.h"

#include "piper.h"


struct nsh_exec {
    struct nsh_piper  piper;
};

void nsh_exec_create(struct nsh_exec* exec);
void nsh_exec_destroy(struct nsh_exec* exec);

bool nsh_exec_ast(struct nsh_exec* exec, struct nsh_ast* ast);

#endif
