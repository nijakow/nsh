#ifndef NSH_EXEC_TASK_H
#define NSH_EXEC_TASK_H

#include "../defs.h"

#include "../util/charpp.h"

struct nsh_task {
    struct charpp  argv;

    fd_t           in_fd;
    fd_t           out_fd;
};

void nsh_task_create(struct nsh_task* task);
void nsh_task_destroy(struct nsh_task* task);

void nsh_task_add_arg(struct nsh_task* task, const char* arg);

void nsh_task_set_input_fd(struct nsh_task* task, fd_t fd);
void nsh_task_set_output_fd(struct nsh_task* task, fd_t fd);
void nsh_task_set_io_fds(struct nsh_task* task, fd_t in_fd, fd_t out_fd);

#endif
