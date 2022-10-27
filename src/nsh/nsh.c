#include "nsh_loop.h"

#include "nsh.h"


void nsh_create(struct nsh* nsh) {
    nsh_environment_create(&nsh->environment);
    nsh_sherlock_create(&nsh->sherlock, &nsh->environment);
    nsh->ignore_kill = false;
    nsh->is_running  = true;
    nsh->is_reading  = false;
}

void nsh_destroy(struct nsh* nsh) {
    nsh_environment_destroy(&nsh->environment);
    nsh_sherlock_destroy(&nsh->sherlock);
}

void nsh_setup_env(struct nsh* nsh, char** env) {
    nsh_environment_add_all(&nsh->environment, env);
}

void nsh_halt(struct nsh* nsh) {
    nsh->is_running = false;
}

typedef void (*nsh_sighandler_t)(int signal_id);

void nsh_signal(struct nsh* nsh, int signal_id) {
    if (signal_id == SIGINT || signal_id == SIGQUIT) {
        if (nsh->ignore_kill) {
            nsh->ignore_kill = false;
            if (nsh->is_reading) {
                putchar('\n');
                nsh_print_prompt(nsh);
            }
        } else {
            nsh->ignore_kill = true;
            kill(0, signal_id);
        }
    }
}

struct nsh_environment* nsh_get_environment(struct nsh* nsh) {
    return &nsh->environment;
}
