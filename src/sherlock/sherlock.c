#include "sherlock.h"

void nsh_sherlock_create(struct nsh_sherlock* sherlock, struct nsh_environment* environment) {
    sherlock->environment = environment;
}

void nsh_sherlock_destroy(struct nsh_sherlock* sherlock) {

}


static bool nsh_sherlock_lookup__trypath(struct nsh_sherlock* sherlock, const char* path) {
    return nsh_file_is_executable(path);
}

static bool nsh_sherlock_lookup__with_pathvar(struct nsh_sherlock* sherlock, const char* pathvar, const char* path, char** result) {
    struct stringbuilder  sb;
    size_t  index;

    if (path[0] == '/' || path[0] == '.') {
        if (nsh_sherlock_lookup__trypath(sherlock, path)) {
            *result = nsh_strdup(path);
            return true;
        }
        return false;
    }

    stringbuilder_create(&sb);
    for (index = 0;; index++) {
        switch (pathvar[index]) {
            case ':':
            case '\0':
                stringbuilder_append_char(&sb, '/');
                stringbuilder_append_cstr(&sb, path);
                if (nsh_sherlock_lookup__trypath(sherlock, stringbuilder_get_static(&sb))) {
                    *result = stringbuilder_get(&sb);
                    stringbuilder_destroy(&sb);
                    return true;
                }
                stringbuilder_clear(&sb);
                break;
            default:
                stringbuilder_append_char(&sb, pathvar[index]);
                break;
        }
        if (pathvar[index] == '\0') break;
    }
    stringbuilder_destroy(&sb);

    return false;
}

bool nsh_sherlock_lookup(struct nsh_sherlock* sherlock, const char* pathname, char** result) {
    const char*  pathvar;

    pathvar = nsh_environment_lookup(sherlock->environment, "PATH", "/usr/local/bin:/usr/bin:/bin");
    return nsh_sherlock_lookup__with_pathvar(sherlock, pathvar, pathname, result);
}
