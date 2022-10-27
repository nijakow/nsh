#ifndef NSH_NSH_H
#define NSH_NSH_H

#include "../defs.h"
#include "../common/environment/environment.h"
#include "../sherlock/sherlock.h"

struct nsh {
    struct nsh_environment  environment;
    struct nsh_sherlock     sherlock;
    bool                    ignore_kill;
    bool                    is_running;
    bool                    is_reading;
};

void nsh_create(struct nsh* nsh);
void nsh_destroy(struct nsh* nsh);

void nsh_setup_env(struct nsh* nsh, char** env);

void nsh_halt(struct nsh* nsh);

void nsh_signal(struct nsh* nsh, int signal);

struct nsh_environment*  nsh_get_environment(struct nsh* nsh);

#endif
