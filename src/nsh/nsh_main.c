#include "nsh_loop.h"

#include "nsh_main.h"


void nsh_main(struct nsh* nsh, int argc, char* argv[], char* envp[]) {
    nsh_setup_env(nsh, envp);
    nsh_environment_set(nsh_get_environment(nsh), "SHELL", argv[0]);
    nsh_loop(nsh);
}
