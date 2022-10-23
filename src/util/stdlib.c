#include "stdlib.h"

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

char* nsh_strdup(const char* str) {
    return strdup(str);
}


typedef void (*nsh_del_func)(void*);

void nsh_delete(void* ptr, void* func) {
    if (ptr != NULL && func != NULL)
        ((nsh_del_func) func)(ptr);
    nsh_free(ptr);
}
