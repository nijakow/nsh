#ifndef NSH_COMMON_EXEC_COMMAND_H
#define NSH_COMMON_EXEC_COMMAND_H

#include "../../defs.h"

struct nsh_command {

};

void nsh_command_create(struct nsh_command* command);
void nsh_command_destroy(struct nsh_command* command);

#endif
