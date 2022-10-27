#ifndef NSH_COMMON_ENVIRONMENT_ENVIRONMENT_H
#define NSH_COMMON_ENVIRONMENT_ENVIRONMENT_H

#include "../../defs.h"
#include "../../util/charpp.h"


struct nsh_environment {
    struct charpp  bindings;
};

void nsh_environment_create(struct nsh_environment* env);
void nsh_environment_destroy(struct nsh_environment* env);

void nsh_environment_add_all(struct nsh_environment* env, char** envp);

const char* nsh_environment_lookup(struct nsh_environment* env, const char* key, const char* default_val);

void nsh_environment_put(struct nsh_environment* env, const char* value);
void nsh_environment_set(struct nsh_environment* env, const char* key, const char* value);

char *const* nsh_environment_get_static(struct nsh_environment* env);

#endif
