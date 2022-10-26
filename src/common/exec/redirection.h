#ifndef NSH_COMMON_EXEC_REDIRECTION_H
#define NSH_COMMON_EXEC_REDIRECTION_H

#include "../../defs.h"

enum nsh_redirection_type {
    nsh_redirection_type_none,
    nsh_redirection_type_input_file,
    nsh_redirection_type_heredoc,
    nsh_redirection_type_output_file,
    nsh_redirection_type_append_file
};

nsh_class(nsh_redirection, {
    enum   nsh_redirection_type  type;
    char*                        text;
    struct nsh_redirection*      next;
});

void nsh_redirection_set(struct nsh_redirection* redir, enum nsh_redirection_type type, const char* text);
void nsh_redirection_set_next(struct nsh_redirection* redir, struct nsh_redirection* next);
void nsh_redirection_push(struct nsh_redirection* redir, struct nsh_redirection* next);

struct nsh_redirection* nsh_redirection_quick_new(enum nsh_redirection_type type, const char* text);

#endif
