#ifndef NSH_COMMON_EXEC_COMMAND_H
#define NSH_COMMON_EXEC_COMMAND_H

#include "../../defs.h"

#include "redirection.h"

struct nsh_command {

};

void nsh_command_create(struct nsh_command* command);
void nsh_command_destroy(struct nsh_command* command);

void nsh_command_add_redir(struct nsh_command* command, enum nsh_redirection_type type, const char* text);
void nsh_command_add_argv(struct nsh_command* command, const char* arg);
void nsh_command_stderr_into_stdout(struct nsh_command* command);

#endif
