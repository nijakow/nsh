#ifndef NSH_COMMON_EXEC_COMMAND_H
#define NSH_COMMON_EXEC_COMMAND_H

#include "../../defs.h"

#include "../../util/charpp.h"

#include "redirection.h"

nsh_class(nsh_command, {
    struct charpp            argv;
    struct nsh_redirection*  redirections;
    bool                     detached;
});

void nsh_command_add_redir(struct nsh_command* command, enum nsh_redirection_type type, const char* text);
void nsh_command_add_argv(struct nsh_command* command, const char* arg);
void nsh_command_set_stderr_into_stdout(struct nsh_command* command);
void nsh_command_set_detached(struct nsh_command* command);

const char*  nsh_command_get_name(struct nsh_command* command);
size_t       nsh_command_get_argv_count(struct nsh_command* command);
const char*  nsh_command_get_argv(struct nsh_command* command, size_t index);

struct nsh_redirection* nsh_command_get_redirections(struct nsh_command* command);

bool nsh_command_is_detached(struct nsh_command* command);

#endif
