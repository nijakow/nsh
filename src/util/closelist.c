#include "closelist.h"

void nsh_closelist_create(struct nsh_closelist* lst) {
    lst->fill = 0;
}

void nsh_closelist_destroy(struct nsh_closelist* lst) {

}

void nsh_closelist_insert(struct nsh_closelist* lst, fd_t fd) {
    if (lst->fill >= NSH_CLOSELIST_MAX) return;
    lst->fds[lst->fill++] = fd;
}

void nsh_closelist_close_all(struct nsh_closelist* lst) {
    while (lst->fill > 0) {
        lst->fill--;
        nsh_close(lst->fds[lst->fill]);
    }
}
