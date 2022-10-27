#ifndef NSH_COMMON_WORDBUILDER_WORDBUILDER_H
#define NSH_COMMON_WORDBUILDER_WORDBUILDER_H

#include "../../defs.h"
#include "../../util/stringbuilder.h"

struct nsh_word;

nsh_class(nsh_wordbuilder, {
    struct nsh_wordbuilder*  next;
    struct nsh_word*         words;
});

void nsh_wordbuilder_push_text(struct nsh_wordbuilder* builder, const char* text);
void nsh_wordbuilder_push_var(struct nsh_wordbuilder* builder, const char* var);

void nsh_wordbuilder_build(struct nsh_wordbuilder* builder, struct stringbuilder* sb);


nsh_class(nsh_wordbuilders, {
    struct nsh_wordbuilder*  builders;
});

#endif
