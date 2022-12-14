#include "defs.h"

#include "nsh/nsh.h"
#include "nsh/nsh_main.h"

struct nsh  the_nsh;

void nsh_signal_handler(int signal) {
    nsh_signal(&the_nsh, signal);
}

int main(int argc, char* argv[], char* envp[]) {
    nsh_create(&the_nsh);
    signal(SIGINT, &nsh_signal_handler);
    signal(SIGQUIT, &nsh_signal_handler);
    nsh_main(&the_nsh, argc, argv, envp);
    nsh_destroy(&the_nsh);
    return 0;
}
