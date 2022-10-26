#ifndef NSH_EXEC_EXEC_H
#define NSH_EXEC_EXEC_H

#include "../defs.h"

struct nsh_exec {

};

void nsh_exec_create(struct nsh_exec* exec);
void nsh_exec_destroy(struct nsh_exec* exec);

#endif
