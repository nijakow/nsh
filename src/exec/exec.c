#include "task.h"

#include "exec.h"


void nsh_exec_create(struct nsh_exec* exec) {
    nsh_piper_create(&exec->piper);
}

void nsh_exec_destroy(struct nsh_exec* exec) {
    nsh_piper_destroy(&exec->piper);
}


static bool nsh_exec_lookup_path(struct nsh_exec* exec, const char* pathname, char** result) {
    // TODO
    *result = nsh_strdup("/bin/ls");
    return true;
}


static bool nsh_exec_ast_command(struct nsh_exec* exec, struct nsh_ast* ast) {
    struct nsh_task      task;
    struct nsh_command*  command;
    char*                path;

    command = nsh_ast_get_command(ast);

    if (!nsh_exec_lookup_path(exec, nsh_command_get_name(command), &path))
        return false;

    nsh_task_create(&task, path);
    if (!nsh_task_perform(&task)) {
        // TODO
    } else {
        // TODO
    }
    nsh_task_destroy(&task);
    nsh_free(path);

    return true;
}

bool nsh_exec_ast(struct nsh_exec* exec, struct nsh_ast* ast) {
    switch (nsh_ast_get_type(ast)) {
        case nsh_ast_type_command: return nsh_exec_ast_command(exec, ast);
        default: return false;
    }
}
