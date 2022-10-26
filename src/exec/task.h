#ifndef NSH_EXEC_TASK_H
#define NSH_EXEC_TASK_H

#include "../defs.h"

#include "../util/charpp.h"
#include "../util/closelist.h"


#define NSH_WAITSET_MAX 32

struct nsh_waitset {
    size_t  fill;
    pid_t   pids[NSH_WAITSET_MAX];
};

void nsh_waitset_create(struct nsh_waitset* ws);
void nsh_waitset_destroy(struct nsh_waitset* ws);

bool nsh_waitset_insert(struct nsh_waitset* ws, pid_t pid);
void nsh_waitset_wait_for_all(struct nsh_waitset* ws);


struct nsh_task {
    char*          executable;

    struct charpp  argv;
    struct charpp  envp;

    struct {
        fd_t        in;
        fd_t        out;
        fd_t        err;
    } fds;

    struct nsh_closelist  closelist;
};

void nsh_task_create(struct nsh_task* task, const char* executable);
void nsh_task_destroy(struct nsh_task* task);

void nsh_task_add_argv(struct nsh_task* task, const char* str);
void nsh_task_add_envp(struct nsh_task* task, const char* str);

void nsh_task_set_input_fd(struct nsh_task* task, fd_t fd);
void nsh_task_set_output_fd(struct nsh_task* task, fd_t fd);
void nsh_task_set_error_fd(struct nsh_task* task, fd_t fd);
void nsh_task_set_io_fds(struct nsh_task* task, fd_t in_fd, fd_t out_fd);
void nsh_task_close_later(struct nsh_task* task, fd_t fd);

bool nsh_task_perform(struct nsh_task* task, struct nsh_waitset* ws);

#endif
