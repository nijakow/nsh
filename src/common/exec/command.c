#include "command.h"

void nsh_command_create(struct nsh_command* command) {
    charpp_create(&command->argv);
    command->redirections = NULL;
    command->detached     = false;
}

void nsh_command_destroy(struct nsh_command* command) {
    charpp_destroy(&command->argv);
    nsh_redirection_delete(command->redirections);
}

void nsh_command_add_redir(struct nsh_command* command, enum nsh_redirection_type type, const char* text) {
    struct nsh_redirection*  redir;

    redir = nsh_redirection_quick_new(type, text);

    if (redir != NULL) {
        if (command->redirections == NULL)
            command->redirections = redir;
        else
            nsh_redirection_push(command->redirections, redir);
    }
}

void nsh_command_add_argv(struct nsh_command* command, const char* arg) {
    charpp_append(&command->argv, arg);
}

void nsh_command_set_stderr_into_stdout(struct nsh_command* command) {
    // TODO
}

void nsh_command_set_detached(struct nsh_command* command) {
    command->detached = true;
}

const char* nsh_command_get_name(struct nsh_command* command) {
    return charpp_get_static_at(&command->argv, 0);
}

size_t nsh_command_get_argv_count(struct nsh_command* command) {
    return charpp_get_size(&command->argv);
}

const char* nsh_command_get_argv(struct nsh_command* command, size_t index) {
    return charpp_get_static_at(&command->argv, index);
}

struct nsh_redirection* nsh_command_get_redirections(struct nsh_command* command) {
    return command->redirections;
}

bool nsh_command_is_detached(struct nsh_command* command) {
    return command->detached;
}
