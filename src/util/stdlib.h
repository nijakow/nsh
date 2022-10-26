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

#define NSH_INVALID_FD  -1
#define NSH_STDIN_FD    STDIN_FILENO
#define NSH_STDOUT_FD   STDOUT_FILENO
#define NSH_STDERR_FD   STDERR_FILENO

bool nsh_open_reading(const char* path, fd_t* fd);
bool nsh_open_writing(const char* path, fd_t* fd);
bool nsh_open_writing_append(const char* path, fd_t* fd);

void nsh_close(fd_t fd);

bool nsh_dup(fd_t fd, fd_t* into);
bool nsh_dup2_from_into(fd_t from, fd_t to);

struct nsh_pipe {
    fd_t  in;
    fd_t  out;
};

bool nsh_pipe_create(struct nsh_pipe* pipe);
void nsh_pipe_destroy(struct nsh_pipe* pipe);

void nsh_write_string_to_fd(fd_t fd, const char* str);


/*
 *     F o r k e y   S t u f f
 */

enum nsh_fork_result {
    nsh_fork_result_error,
    nsh_fork_result_i_am_parent,
    nsh_fork_result_i_am_child
};

enum nsh_fork_result nsh_fork(pid_t* pid);
bool                 nsh_wait_for(pid_t pid);

void nsh_execve(const char* executable, char*const* argv, char*const* envp);
void nsh_exit(int code);


/*
 *     F i l e   S y s t e m   S t u f f
 */

bool nsh_file_is_executable(const char* path);

#endif
