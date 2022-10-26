#include "sherlock.h"

void nsh_sherlock_create(struct nsh_sherlock* sherlock) {

}

void nsh_sherlock_destroy(struct nsh_sherlock* sherlock) {

}


bool nsh_sherlock_lookup(struct nsh_sherlock* sherlock, const char* pathname, char** result) {
    // TODO
    *result = nsh_strdup(pathname);
    return true;
}
