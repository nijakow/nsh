#ifndef NSH_UTIL_CLOSELIST_H
#define NSH_UTIL_CLOSELIST_H

#include "../defs.h"

#define NSH_CLOSELIST_MAX  16

nsh_class(nsh_closelist, {
    size_t  fill;
    fd_t    fds[NSH_CLOSELIST_MAX];
});

void nsh_closelist_insert(struct nsh_closelist* lst, fd_t fd);
void nsh_closelist_close_all(struct nsh_closelist* lst);

#endif
