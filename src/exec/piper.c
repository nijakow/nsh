#include "piper.h"


static void nsh_piper_safe_close(fd_t fd) {
    if (fd != NSH_STDIN_FD && fd != NSH_STDOUT_FD && fd != NSH_STDERR_FD)
        nsh_close(fd);
}

static void nsh_piper_safe_assign(fd_t* loc, fd_t val) {
    if (*loc != val) {
        nsh_piper_safe_close(*loc);
        *loc = val;
    }
}

static bool nsh_piper_safe_pipe(fd_t* in, fd_t* out) {
    struct nsh_pipe  pipe;

    if (!nsh_pipe_create(&pipe)) return false;

    nsh_piper_safe_assign(in, pipe.in);
    nsh_piper_safe_assign(out, pipe.out);

    /*
     * No call to nsh_pipe_destroy() - we hijacked the fd's! :P
     */

    return true;
}


void nsh_piper_create(struct nsh_piper* piper) {
    piper->in      = NSH_STDIN_FD;
    piper->out     = NSH_STDOUT_FD;
    piper->next_in = NSH_STDIN_FD;
}

void nsh_piper_destroy(struct nsh_piper* piper) {
    nsh_piper_safe_close(piper->in);
    nsh_piper_safe_close(piper->out);
    nsh_piper_safe_close(piper->next_in);
}


void nsh_piper_open_new_pipe(struct nsh_piper* piper) {
    nsh_piper_safe_pipe(&piper->out, &piper->next_in);
}

void nsh_piper_rollover(struct nsh_piper* piper) {
    nsh_piper_safe_assign(&piper->in, piper->next_in);
    nsh_piper_safe_assign(&piper->out, NSH_STDOUT_FD);
    nsh_piper_safe_assign(&piper->next_in, NSH_STDIN_FD);
}

void nsh_piper_reset(struct nsh_piper* piper) {
    nsh_piper_safe_assign(&piper->in, NSH_STDIN_FD);
    nsh_piper_safe_assign(&piper->out, NSH_STDOUT_FD);
    nsh_piper_safe_assign(&piper->next_in, NSH_STDIN_FD);
}

fd_t nsh_piper_get_input_fd(struct nsh_piper* piper) {
    return piper->in;
}

fd_t nsh_piper_get_output_fd(struct nsh_piper* piper) {
    return piper->out;
}

void nsh_piper_setup_task(struct nsh_piper* piper, struct nsh_task* task) {
    nsh_task_set_io_fds(task, piper->in, piper->out);
}

void nsh_piper_redirect_input(struct nsh_piper* piper, fd_t fd) {
    nsh_piper_safe_assign(&piper->in, fd);
}

void nsh_piper_redirect_output(struct nsh_piper* piper, fd_t fd) {
    nsh_piper_safe_assign(&piper->out, fd);
}

void nsh_piper_run_redirections(struct nsh_piper* piper, struct nsh_redirection* redir) {
    fd_t  fd;

    while (redir != NULL) {
        switch (nsh_redirection_get_type(redir)) {
            case nsh_redirection_type_input_file: {
                if (nsh_open_reading(nsh_redirection_get_text(redir), &fd))
                    nsh_piper_redirect_input(piper, fd);
                break;
            }
            case nsh_redirection_type_output_file: {
                if (nsh_open_writing(nsh_redirection_get_text(redir), &fd))
                    nsh_piper_redirect_output(piper, fd);
                break;
            }
            case nsh_redirection_type_append_file: {
                if (nsh_open_writing_append(nsh_redirection_get_text(redir), &fd))
                    nsh_piper_redirect_output(piper, fd);
                break;
            }
            default:
                /* TODO: Error or Warning */
                break;
        }
        redir = nsh_redirection_get_next(redir);
    }
}
