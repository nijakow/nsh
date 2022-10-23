#include "command.h"

void nsh_command_create(struct nsh_command* command) {

}

void nsh_command_destroy(struct nsh_command* command) {
    
}

void nsh_command_add_redir(struct nsh_command* command, enum nsh_redirection_type type, const char* text) {
    // TODO
}

void nsh_command_add_argv(struct nsh_command* command, const char* arg) {
    // TODO
}

void nsh_command_stderr_into_stdout(struct nsh_command* command) {
    // TODO
}
