#include "exec.h"


void nsh_exec_create(struct nsh_exec* exec, struct nsh_environment* environment, struct nsh_sherlock* sherlock) {
    exec->environment = environment;
    exec->sherlock    = sherlock;
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

    if (!nsh_piper_run_redirections(&exec->piper, nsh_command_get_redirections(command)))
        return false;

    if (!nsh_sherlock_lookup(exec->sherlock, nsh_command_get_name(command), &path)) {
        if (nsh_streq(nsh_command_get_name(command), "cd") && nsh_command_get_argv_count(command) == 2) {
            /* TODO: Move this to a better location */
            if (!nsh_chdir(nsh_command_get_argv(command, 1)))
                fprintf(stderr, "%s: not found!\n", nsh_command_get_argv(command, 1));
            else {
                char buffer[1024];
                if (getcwd(buffer, sizeof(buffer)) != NULL)
                    nsh_environment_set(exec->environment, "PWD", buffer);
            }
            return true;
        } else if (nsh_streq(nsh_command_get_name(command), "export") && nsh_command_get_argv_count(command) == 2) {
            nsh_environment_put(exec->environment, nsh_command_get_argv(command, 1));
            return true;
        }
        fprintf(stderr, "%s: not found!\n", nsh_command_get_name(command));
        return false;
    }
    

    nsh_task_create(&task, path);
    {
        for (index = 1; index < nsh_command_get_argv_count(command); index++)
            nsh_task_add_argv(&task, nsh_command_get_argv(command, index));
        
        nsh_task_add_env(&task, nsh_environment_get_static(exec->environment));
        
        nsh_piper_setup_task(&exec->piper, &task);

        if (!nsh_task_perform(&task, nsh_command_is_detached(command) ? NULL : &exec->waitset)) {
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
        nsh_piper_reset(&exec->piper);
        if (nsh_exec_ast(exec, nsh_ast_get_right(ast))) {
            return true;
        }
    }
    return false;
}

static bool nsh_exec_ast_pipe(struct nsh_exec* exec, struct nsh_ast* ast) {
    bool result;

    result = false;

    nsh_piper_open_new_pipe(&exec->piper);
    if (nsh_exec_ast(exec, nsh_ast_get_left(ast))) {
        nsh_piper_rollover(&exec->piper);
        result = nsh_exec_ast(exec, nsh_ast_get_right(ast));
    }
    nsh_piper_reset(&exec->piper);
    return result;
}

bool nsh_exec_ast(struct nsh_exec* exec, struct nsh_ast* ast) {
    switch (nsh_ast_get_type(ast)) {
        case nsh_ast_type_none: return true;
        case nsh_ast_type_command: return nsh_exec_ast_command(exec, ast);
        case nsh_ast_type_semicolon: return nsh_exec_ast_semicolon(exec, ast);
        case nsh_ast_type_pipe: return nsh_exec_ast_pipe(exec, ast);
        default: return false;
    }
}

void nsh_exec_wait(struct nsh_exec* exec) {
    nsh_waitset_wait_for_all(&exec->waitset);
}
