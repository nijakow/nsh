#include "nsh_loop.h"

#include "nsh_main.h"


void nsh_main(struct nsh* nsh, int argc, char* argv[], char* envp[]) {
    nsh_setup_env(nsh, envp);
    nsh_loop(nsh);
}
