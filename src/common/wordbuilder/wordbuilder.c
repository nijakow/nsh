#include "wordbuilder.h"


enum nsh_word_type {
    nsh_word_type_none,
    nsh_word_type_text,
    nsh_word_type_var,
};

nsh_class(nsh_word, {
    enum nsh_word_type  type;
    char*               text;
    struct nsh_word*    next;
});


void nsh_word_create(struct nsh_word* word) {
    word->type = nsh_word_type_none;
    word->next = NULL;
    word->text = NULL;
}

void nsh_word_destroy(struct nsh_word* word) {
    nsh_delete(nsh_word, word->next);
    nsh_free(word->text);
}

struct nsh_word* nsh_word_new_text(const char* text) {
    struct nsh_word*  word;

    word = nsh_new(nsh_word);
    if (word != NULL) {
        word->type = nsh_word_type_text;
        word->text = nsh_strdup(text);
    }
    return word;
}

struct nsh_word* nsh_word_new_var(const char* text) {
    struct nsh_word*  word;

    word = nsh_new(nsh_word);
    if (word != NULL) {
        word->type = nsh_word_type_var;
        word->text = nsh_strdup(text);
    }
    return word;
}

static void nsh_word_push(struct nsh_word* word, struct nsh_word* other) {
    while (word->next != NULL)
        word = word->next;
    word->next = other;
}


void nsh_wordbuilder_create(struct nsh_wordbuilder* wb) {
    wb->next  = NULL;
    wb->words = NULL;
}

void nsh_wordbuilder_destroy(struct nsh_wordbuilder* wb) {
    nsh_delete(nsh_wordbuilder, wb->next);
    nsh_delete(nsh_word, wb->words);
}

static void nsh_wordbuilder_push(struct nsh_wordbuilder* wb, struct nsh_word* word) {
    if (wb->words == NULL)
        wb->words = word;
    else {
        nsh_word_push(wb->words, word);
    }
}

void nsh_wordbuilder_push_text(struct nsh_wordbuilder* builder, const char* text) {
    nsh_wordbuilder_push(builder, nsh_word_new_text(text));
}

void nsh_wordbuilder_push_var(struct nsh_wordbuilder* builder, const char* var) {
    nsh_wordbuilder_push(builder, nsh_word_new_text(var));
}

void nsh_wordbuilder_build(struct nsh_wordbuilder* builder, struct stringbuilder* sb) {
    struct nsh_word*  word;

    for (word = builder->words; word != NULL; word = word->next) {
        switch (word->type) {
            case nsh_word_type_text:
                stringbuilder_append_cstr(sb, word->text);
                break;
            default:
                /* TODO */
                break;
        }
    }
}
