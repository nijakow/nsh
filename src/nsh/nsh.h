#ifndef NSH_NSH_H
#define NSH_NSH_H

#include "../defs.h"
#include "../sherlock/sherlock.h"

struct nsh {
    struct nsh_sherlock  sherlock;
    bool                 is_running;
};

void nsh_create(struct nsh* nsh);
void nsh_destroy(struct nsh* nsh);

void nsh_halt(struct nsh* nsh);

void nsh_signal(struct nsh* nsh, int signal);

#endif
