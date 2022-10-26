#ifndef NSH_EXEC_PIPER_H
#define NSH_EXEC_PIPER_H

#include "../defs.h"

struct nsh_piper {
    fd_t  in;
    fd_t  out;
    fd_t  next_in;
};

void nsh_piper_create(struct nsh_piper* piper);
void nsh_piper_destroy(struct nsh_piper* piper);

void nsh_piper_open_new_pipe(struct nsh_piper* piper);
void nsh_piper_rollover(struct nsh_piper* piper);

void nsh_piper_redirect_input(struct nsh_piper* piper, fd_t fd);
void nsh_piper_redirect_output(struct nsh_piper* piper, fd_t fd);

#endif
