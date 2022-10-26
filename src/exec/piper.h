#ifndef NSH_EXEC_PIPER_H
#define NSH_EXEC_PIPER_H

#include "../defs.h"

#include "../common/exec/redirection.h"

#include "task.h"


struct nsh_piper {
    fd_t  in;
    fd_t  out;
    fd_t  next_in;
};

void nsh_piper_create(struct nsh_piper* piper);
void nsh_piper_destroy(struct nsh_piper* piper);

void nsh_piper_open_new_pipe(struct nsh_piper* piper);
void nsh_piper_rollover(struct nsh_piper* piper);
void nsh_piper_reset(struct nsh_piper* piper);

fd_t nsh_piper_get_input_fd(struct nsh_piper* piper);
fd_t nsh_piper_get_output_fd(struct nsh_piper* piper);
void nsh_piper_setup_task(struct nsh_piper* piper, struct nsh_task* task);

void nsh_piper_redirect_input(struct nsh_piper* piper, fd_t fd);
void nsh_piper_redirect_output(struct nsh_piper* piper, fd_t fd);

void nsh_piper_run_redirections(struct nsh_piper* piper, struct nsh_redirection* redir);

#endif
