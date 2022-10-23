#ifndef NSH_COMMON_EXEC_REDIRECTION_H
#define NSH_COMMON_EXEC_REDIRECTION_H

#include "../../defs.h"

enum nsh_redirection_type {
    nsh_redirection_type_input_file,
    nsh_redirection_type_heredoc,
    nsh_redirection_type_output_file,
    nsh_redirection_type_append_file
};

struct nsh_redirection {
    enum nsh_redirection_type redirection_type;
    char*                     text;
};

void nsh_redirection_create(struct nsh_redirection* redir,
                            enum nsh_redirection_type redir_type,
                            char*                     redir_text);
void nsh_redirection_destroy(struct nsh_redirection* redir);

#endif
