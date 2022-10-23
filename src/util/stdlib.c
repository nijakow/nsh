#include "../defs.h"

void* nsh_malloc(size_t size) {
    return malloc(size);
}

void* nsh_realloc(void* ptr, size_t size) {
    return realloc(ptr, size);
}

void nsh_free(void* ptr) {
    if (ptr != NULL)
        free(ptr);
}


void nsh_free_charpp(char** ptr) {
    size_t  index;

    if (ptr == NULL) return;

    for (index = 0; ptr[index] != NULL; index++)
        nsh_free(ptr[index]);
    nsh_free(ptr);
}


char* nsh_strdup(const char* str) {
    return strdup(str);
}


typedef void (*nsh_new_func)(void*);
typedef void (*nsh_del_func)(void*);

void* nsh_new_impl(void* func, size_t size) {
    void*  ptr;

    ptr = nsh_malloc(size);

    if (ptr != NULL) {
        ((nsh_new_func) func)(ptr);
    }

    return ptr;
}

void nsh_delete_impl(void* func, void* ptr) {
    if (ptr != NULL && func != NULL)
        ((nsh_del_func) func)(ptr);
    nsh_free(ptr);
}
