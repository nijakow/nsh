#include "nsh.h"

void nsh_create(struct nsh* nsh) {
    nsh_sherlock_create(&nsh->sherlock);
    nsh->is_running = true;
}

void nsh_destroy(struct nsh* nsh) {

}

void nsh_halt(struct nsh* nsh) {
    nsh->is_running = false;
}

void nsh_signal(struct nsh* nsh, int signal) {
    if (signal == SIGINT) nsh_halt(nsh);
}
