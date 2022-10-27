#include "task.h"


void nsh_waitset_create(struct nsh_waitset* ws) {
    ws->fill = 0;
}

void nsh_waitset_destroy(struct nsh_waitset* ws) {

}

bool nsh_waitset_insert(struct nsh_waitset* ws, pid_t pid) {
    if (ws->fill < NSH_WAITSET_MAX) {
        ws->pids[ws->fill++] = pid;
        return true;
    }
    return false;
}

void nsh_waitset_wait_for_all(struct nsh_waitset* ws) {
    while (ws->fill > 0) {
        ws->fill--;
        nsh_wait_for(ws->pids[ws->fill]);
    }
}


void nsh_task_create(struct nsh_task* task, const char* executable) {
    task->executable = nsh_strdup(executable);

    charpp_create(&task->argv);
    charpp_create(&task->envp);

    task->fds.in  = NSH_INVALID_FD;
    task->fds.out = NSH_INVALID_FD;
    task->fds.err = NSH_INVALID_FD;

    nsh_closelist_create(&task->closelist);

    nsh_task_add_argv(task, executable);
}

void nsh_task_destroy(struct nsh_task* task) {
    nsh_free(task->executable);

    charpp_destroy(&task->argv);
    charpp_destroy(&task->envp);

    nsh_closelist_destroy(&task->closelist);
}


void nsh_task_add_argv(struct nsh_task* task, const char* str) {
    charpp_append(&task->argv, str);
}

void nsh_task_add_envp(struct nsh_task* task, const char* str) {
    charpp_append(&task->envp, str);
}

void nsh_task_add_env(struct nsh_task* task, char*const* envp) {
    size_t  index;

    for (index = 0; envp[index] != NULL; index++)
        nsh_task_add_envp(task, envp[index]);
}


void nsh_task_set_input_fd(struct nsh_task* task, fd_t fd) {
    task->fds.in = fd;
}

void nsh_task_set_output_fd(struct nsh_task* task, fd_t fd) {
    task->fds.out = fd;
}

void nsh_task_set_error_fd(struct nsh_task* task, fd_t fd) {
    task->fds.err = fd;
}

void nsh_task_set_io_fds(struct nsh_task* task, fd_t in_fd, fd_t out_fd) {
    nsh_task_set_input_fd(task, in_fd);
    nsh_task_set_output_fd(task, out_fd);
}

void nsh_task_close_later(struct nsh_task* task, fd_t fd) {
    nsh_closelist_insert(&task->closelist, fd);
}


static void nsh_task_safe_close(fd_t fd) {
    if (fd != NSH_STDIN_FD && fd != NSH_STDOUT_FD && fd != NSH_STDERR_FD)
        nsh_close(fd);
}

static void nsh_task_do_child_stuff(struct nsh_task* task) {
    if (task->fds.in  != NSH_INVALID_FD) nsh_dup2_from_into(task->fds.in, NSH_STDIN_FD);
    if (task->fds.out != NSH_INVALID_FD) nsh_dup2_from_into(task->fds.out, NSH_STDOUT_FD);
    if (task->fds.err != NSH_INVALID_FD) nsh_dup2_from_into(task->fds.err, NSH_STDERR_FD);

    nsh_task_safe_close(task->fds.in);
    nsh_task_safe_close(task->fds.out);
    nsh_task_safe_close(task->fds.err);

    nsh_closelist_close_all(&task->closelist);

    nsh_execve(task->executable, charpp_get_static(&task->argv), charpp_get_static(&task->envp));
    nsh_exit(127);
}

bool nsh_task_perform(struct nsh_task* task, struct nsh_waitset* ws) {
    pid_t  pid;

    switch (nsh_fork(&pid))
    {
        case nsh_fork_result_error:       return false;
        case nsh_fork_result_i_am_parent: if (ws != NULL) nsh_waitset_insert(ws, pid);
                                          return true;
        case nsh_fork_result_i_am_child:  nsh_task_do_child_stuff(task);
                                          return true;
    }

    return false;
}
