#ifndef NSH_EXEC_EXEC_H
#define NSH_EXEC_EXEC_H

#include "../defs.h"

#include "../common/ast/ast.h"
#include "../common/environment/environment.h"
#include "../sherlock/sherlock.h"

#include "piper.h"
#include "task.h"


struct nsh_exec {
    struct nsh_environment*  environment;
    struct nsh_sherlock*     sherlock;
    struct nsh_waitset       waitset;
    struct nsh_piper         piper;
};

void nsh_exec_create(struct nsh_exec* exec, struct nsh_environment* environment, struct nsh_sherlock* sherlock);
void nsh_exec_destroy(struct nsh_exec* exec);

bool nsh_exec_ast(struct nsh_exec* exec, struct nsh_ast* ast);
void nsh_exec_wait(struct nsh_exec* exec);

#endif
