#ifndef NSH_EXEC_TASK_H
#define NSH_EXEC_TASK_H

#include "../defs.h"

struct nsh_task {
    
};

void nsh_task_create(struct nsh_task* task);
void nsh_task_destroy(struct nsh_task* task);

void nsh_task_add_arg(struct nsh_task* task, const char* arg);

void nsh_task_set_input_fd(struct nsh_task* task, int fd);
void nsh_task_set_output_fd(struct nsh_task* task, int fd);
void nsh_task_set_io_fds(struct nsh_task* task, int in_fd, int out_fd);

#endif
