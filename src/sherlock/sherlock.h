#ifndef NSH_SHERLOCK_SHERLOCK_H
#define NSH_SHERLOCK_SHERLOCK_H

#include "../defs.h"
#include "../common/environment/environment.h"

struct nsh_sherlock {
    struct nsh_environment*  environment;
};

void nsh_sherlock_create(struct nsh_sherlock* sherlock, struct nsh_environment* environment);
void nsh_sherlock_destroy(struct nsh_sherlock* sherlock);

bool nsh_sherlock_lookup(struct nsh_sherlock* sherlock, const char* pathname, char** result);

#endif
