#include "task.h"


void nsh_task_create(struct nsh_task* task, const char* executable) {
    task->executable = nsh_strdup(executable);

    charpp_create(&task->argv);
    charpp_create(&task->envp);

    task->in_fd  = NSH_INVALID_FD;
    task->out_fd = NSH_INVALID_FD;

    nsh_task_add_argv(task, executable);
}

void nsh_task_destroy(struct nsh_task* task) {
    nsh_free(task->executable);

    charpp_destroy(&task->argv);
    charpp_destroy(&task->envp);
}


void nsh_task_add_argv(struct nsh_task* task, const char* str) {
    charpp_append(&task->argv, str);
}

void nsh_task_add_envp(struct nsh_task* task, const char* str) {
    charpp_append(&task->envp, str);
}


void nsh_task_set_input_fd(struct nsh_task* task, fd_t fd) {
    task->in_fd = fd;
}

void nsh_task_set_output_fd(struct nsh_task* task, fd_t fd) {
    task->out_fd = fd;
}

void nsh_task_set_io_fds(struct nsh_task* task, fd_t in_fd, fd_t out_fd) {
    nsh_task_set_input_fd(task, in_fd);
    nsh_task_set_output_fd(task, out_fd);
}


static void nsh_task_do_child_stuff(struct nsh_task* task) {
    nsh_execve(task->executable, charpp_get_static(&task->argv), charpp_get_static(&task->envp));
    nsh_exit(127);
}

bool nsh_task_perform(struct nsh_task* task) {
    pid_t  pid;

    nsh_fork(&pid);

         if (pid <  0) return false;
    else if (pid == 0) return true;

    nsh_task_do_child_stuff(task);

    return true;
}
