#include "../../util/stdlib.h"

#include "redirection.h"


void nsh_redirection_create(struct nsh_redirection* redir) {
    redir->type = nsh_redirection_type_none;
    redir->text = NULL;
    redir->next = NULL;
}

void nsh_redirection_destroy(struct nsh_redirection* redir) {
    nsh_free(redir->text);
    nsh_redirection_delete(redir->next);
}

enum nsh_redirection_type nsh_redirection_get_type(struct nsh_redirection* redir) {
    return redir->type;
}

const char* nsh_redirection_get_text(struct nsh_redirection* redir) {
    return redir->text;
}

struct nsh_redirection* nsh_redirection_get_next(struct nsh_redirection* redir) {
    return redir->next;
}

void nsh_redirection_set(struct nsh_redirection* redir, enum nsh_redirection_type type, const char* text) {
    nsh_free(redir->text);
    redir->type = type;
    redir->text = nsh_strdup(text);
}

void nsh_redirection_set_next(struct nsh_redirection* redir, struct nsh_redirection* next) {
    nsh_redirection_delete(redir->next);
    redir->next = next;
}

struct nsh_redirection* nsh_redirection_quick_new(enum nsh_redirection_type type, const char* text) {
    struct nsh_redirection*  redir;

    redir = nsh_redirection_new();

    if (redir != NULL) {
        nsh_redirection_set(redir, type, text);
    }

    return redir;
}

void nsh_redirection_push(struct nsh_redirection* redir, struct nsh_redirection* next) {
    while (redir->next != NULL)
        redir = redir->next;
    nsh_redirection_set_next(redir, next);
}
