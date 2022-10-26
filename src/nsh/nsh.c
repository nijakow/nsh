#include "nsh.h"

void nsh_create(struct nsh* nsh) {
    nsh_environment_create(&nsh->environment);
    nsh_sherlock_create(&nsh->sherlock);
    nsh->is_running = true;
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

void nsh_signal(struct nsh* nsh, int signal) {
    if (signal == SIGINT) nsh_halt(nsh);
}
