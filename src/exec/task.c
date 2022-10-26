#include "task.h"


void nsh_task_create(struct nsh_task* task) {
    charpp_create(&task->argv);
    
    task->in_fd  = NSH_INVALID_FD;
    task->out_fd = NSH_INVALID_FD;
}

void nsh_task_destroy(struct nsh_task* task) {
    charpp_destroy(&task->argv);
}


void nsh_task_add_arg(struct nsh_task* task, const char* arg) {

}

void nsh_task_set_input_fd(struct nsh_task* task, fd_t fd) {

}

void nsh_task_set_output_fd(struct nsh_task* task, fd_t fd) {

}

void nsh_task_set_io_fds(struct nsh_task* task, fd_t in_fd, fd_t out_fd) {
    nsh_task_set_input_fd(task, in_fd);
    nsh_task_set_output_fd(task, out_fd);
}
