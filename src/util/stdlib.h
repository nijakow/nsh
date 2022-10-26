#ifndef NSH_UTIL_STDLIB_H
#define NSH_UTIL_STDLIB_H

#include "../defs.h"


/*
 *     C l a s s y   S t u f f
 */

#define nsh_class(name, fields) \
typedef struct name fields name; \
void name ## _create(name* ptr); \
void name ## _destroy(name* ptr); \
static inline struct name* name ## _new() { return nsh_new(name); } \
static inline void name ## _delete(struct name* self) { nsh_delete(name, self); }


/*
 *     M e m o r y   S t u f f
 */

void* nsh_malloc(size_t size);
void* nsh_realloc(void* ptr, size_t size);
void  nsh_free(void* ptr);

void nsh_free_charpp(char** ptr);

#define nsh_new(what) nsh_new_impl(what ## _create, sizeof(struct what))
#define nsh_delete(what, ptr) nsh_delete_impl(what ## _create, ptr)

void* nsh_new_impl(void* func, size_t size);
void  nsh_delete_impl(void* func, void* ptr);

char* nsh_strdup(const char* str);


/*
 *     F i l e   D e s c r i p t o r   S t u f f
 */

typedef int fd_t;
#define NSH_INVALID_FD -1

void nsh_close(fd_t fd);

struct nsh_pipe {
    fd_t  in;
    fd_t  out;
};

bool nsh_pipe_create(struct nsh_pipe* pipe);
void nsh_pipe_destroy(struct nsh_pipe* pipe);

#endif
