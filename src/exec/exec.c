#include "exec.h"


void nsh_exec_create(struct nsh_exec* exec, struct nsh_sherlock* sherlock) {
    exec->sherlock = sherlock;
    nsh_waitset_create(&exec->waitset);
    nsh_piper_create(&exec->piper);
}

void nsh_exec_destroy(struct nsh_exec* exec) {
    nsh_piper_destroy(&exec->piper);
    nsh_waitset_destroy(&exec->waitset);
}


static bool nsh_exec_ast_command(struct nsh_exec* exec, struct nsh_ast* ast) {
    struct nsh_task      task;
    struct nsh_command*  command;
    char*                path;
    size_t               index;

    command = nsh_ast_get_command(ast);

    if (!nsh_sherlock_lookup(exec->sherlock, nsh_command_get_name(command), &path))
        return false;

    nsh_task_create(&task, path);
    {
        for (index = 1; index < nsh_command_get_argv_count(command); index++)
            nsh_task_add_argv(&task, nsh_command_get_argv(command, index));
        
        if (!nsh_task_perform(&task, &exec->waitset)) {
            // TODO
        } else {
            // TODO
        }
    }
    nsh_task_destroy(&task);
    nsh_free(path);

    return true;
}

static bool nsh_exec_ast_semicolon(struct nsh_exec* exec, struct nsh_ast* ast) {
    if (nsh_exec_ast(exec, nsh_ast_get_left(ast))) {
        nsh_exec_wait(exec);
        if (nsh_exec_ast(exec, nsh_ast_get_right(ast))) {
            return true;
        }
    }
    return false;
}

bool nsh_exec_ast(struct nsh_exec* exec, struct nsh_ast* ast) {
    switch (nsh_ast_get_type(ast)) {
        case nsh_ast_type_none: return true;
        case nsh_ast_type_command: return nsh_exec_ast_command(exec, ast);
        case nsh_ast_type_semicolon: return nsh_exec_ast_semicolon(exec, ast);
        default: return false;
    }
}

void nsh_exec_wait(struct nsh_exec* exec) {
    nsh_waitset_wait_for_all(&exec->waitset);
}
