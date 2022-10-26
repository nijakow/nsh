#include "command.h"

void nsh_command_create(struct nsh_command* command) {
    command->name = NULL;
}

void nsh_command_destroy(struct nsh_command* command) {
    nsh_free(command->name);
}

void nsh_command_add_redir(struct nsh_command* command, enum nsh_redirection_type type, const char* text) {
    // TODO
}

void nsh_command_add_argv(struct nsh_command* command, const char* arg) {
    // TODO
}

void nsh_command_set_stderr_into_stdout(struct nsh_command* command) {
    // TODO
}

void nsh_command_set_detached(struct nsh_command* command) {
    // TODO
}


const char* nsh_command_get_name(struct nsh_command* command) {
    return command->name;
}

void nsh_command_set_name(struct nsh_command* command, const char* name) {
    if (command->name != NULL) nsh_free(command->name);
    command->name = nsh_strdup(name);
}
