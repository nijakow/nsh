#include "../../util/stdlib.h"

#include "redirection.h"

void nsh_redirection_create(struct nsh_redirection*   redir,
                            enum nsh_redirection_type redir_type,
                            char*                     redir_text) {
    redir->redirection_type = redir_type;
    redir->text             = nsh_strdup(redir_text);
}

void nsh_redirection_destroy(struct nsh_redirection* redir) {
    nsh_free(redir->text);
}
