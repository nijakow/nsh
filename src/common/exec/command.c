#include "command.h"

void nsh_command_create(struct nsh_command* command) {
    charpp_create(&command->argv);
}

void nsh_command_destroy(struct nsh_command* command) {
    charpp_destroy(&command->argv);
}

void nsh_command_add_redir(struct nsh_command* command, enum nsh_redirection_type type, const char* text) {
    // TODO
}

void nsh_command_add_argv(struct nsh_command* command, const char* arg) {
    charpp_append(&command->argv, arg);
}

void nsh_command_set_stderr_into_stdout(struct nsh_command* command) {
    // TODO
}

void nsh_command_set_detached(struct nsh_command* command) {
    // TODO
}

const char* nsh_command_get_name(struct nsh_command* command) {
    return charpp_get_static_at(&command->argv, 0);
}

size_t nsh_command_get_argv_count(struct nsh_command* command) {
    return charpp_get_size(&command->argv);
}

const char*  nsh_command_get_argv(struct nsh_command* command, size_t index) {
    return charpp_get_static_at(&command->argv, index);
}
