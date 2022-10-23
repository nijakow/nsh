#include "nsh.h"

void nsh_create(struct nsh* nsh) {
    nsh->is_running = true;
}

void nsh_destroy(struct nsh* nsh) {

}

void nsh_signal(struct nsh* nsh, int signal) {
    if (signal == SIGINT) nsh->is_running = false;
}
