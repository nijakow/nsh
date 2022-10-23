#ifndef NSH_UTIL_STDLIB_H
#define NSH_UTIL_STDLIB_H

void* nsh_malloc(size_t size);
void* nsh_realloc(void* ptr, size_t size);
void  nsh_free(void* ptr);

void  nsh_delete(void* ptr, void* func);

char* nsh_strdup(const char* str);

#endif
