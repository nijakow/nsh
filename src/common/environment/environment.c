#include "environment.h"

void nsh_environment_create(struct nsh_environment* env) {
    charpp_create(&env->bindings);
}

void nsh_environment_destroy(struct nsh_environment* env) {
    charpp_destroy(&env->bindings);
}

void nsh_environment_add_all(struct nsh_environment* env, char** envp) {
    size_t  index;

    for (index = 0; envp[index] != NULL; index++)
        charpp_append(&env->bindings, envp[index]);
}

const char* nsh_environment_lookup(struct nsh_environment* env, const char* key, const char* default_val) {
    size_t       entry;
    size_t       index;
    const char*  text;

    for (entry = 0; entry < charpp_get_size(&env->bindings); entry++) {
        text = charpp_get_static_at(&env->bindings, entry);
        for (index = 0;; index++) {
            if (text[index] != key[index]) {
                if (key[index] == '\0') {
                         if (text[index] ==  '=') return &text[index + 1];
                    else if (text[index] == '\0') return &text[index];
                }
                break;
            }
        }
    }

    return default_val;
}

void nsh_environment_put(struct nsh_environment* env, const char* value) {
    size_t       entry;
    size_t       index;
    const char*  text;

    for (entry = 0; entry < charpp_get_size(&env->bindings); entry++) {
        text = charpp_get_static_at(&env->bindings, entry);
        for (index = 0;; index++) {
            if (text[index] != value[index] || text[index] == '=' || text[index] == '\0') {
                if (value[index] == '=' || value[index] == '\0') {
                    charpp_put(&env->bindings, entry, value);
                    return;
                }
            }
        }
    }

    charpp_append(&env->bindings, value);
}

void nsh_environment_set(struct nsh_environment* env, const char* key, const char* value) {
    struct stringbuilder  sb;

    stringbuilder_create(&sb);
    stringbuilder_append_cstr(&sb, key);
    stringbuilder_append_char(&sb, '=');
    stringbuilder_append_cstr(&sb, value);
    nsh_environment_put(env, stringbuilder_get_static(&sb));
    stringbuilder_destroy(&sb);
}

char *const* nsh_environment_get_static(struct nsh_environment* env) {
    return charpp_get_static(&env->bindings);
}
