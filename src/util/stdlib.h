#ifndef NSH_UTIL_STDLIB_H
#define NSH_UTIL_STDLIB_H

#include "../defs.h"

#define nsh_class(name, fields) \
typedef struct name fields name; \
void name ## _create(name* ptr); \
void name ## _destroy(name* ptr)

void* nsh_malloc(size_t size);
void* nsh_realloc(void* ptr, size_t size);
void  nsh_free(void* ptr);

void nsh_free_charpp(char** ptr);

#define nsh_new(what) nsh_new_impl(what ## _create, sizeof(what))

void* nsh_new_impl(void* func, size_t size);
void  nsh_delete(void* ptr, void* func);

char* nsh_strdup(const char* str);

#endif
