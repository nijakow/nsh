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



bool nsh_open_reading(const char* path, fd_t* fd) {
    return (*fd = open(path, O_RDONLY)) >= 0;
}

bool nsh_open_writing(const char* path, fd_t* fd) {
    return (*fd = open(path, O_WRONLY)) >= 0;
}

bool nsh_open_writing_append(const char* path, fd_t* fd) {
    return (*fd = open(path, O_WRONLY | O_APPEND)) >= 0;
}

void nsh_close(fd_t fd) {
    if (fd != NSH_INVALID_FD)
        close(fd);
}


bool nsh_dup(fd_t fd, fd_t* into) {
    *into = dup(fd);
    return *into >= 0;
}

bool nsh_dup2_from_into(fd_t from, fd_t to) {
    return dup2(from, to) >= 0;
}


bool nsh_pipe_create(struct nsh_pipe* the_pipe) {
    int  fds[2];

    if (pipe(fds) != 0) return false;

    the_pipe->in  = fds[1];
    the_pipe->out = fds[0];

    return true;
}

void nsh_pipe_destroy(struct nsh_pipe* the_pipe) {
    nsh_close(the_pipe->in);
    nsh_close(the_pipe->out);
}


enum nsh_fork_result nsh_fork(pid_t* pid) {
    *pid = fork();

         if (*pid <  0) return nsh_fork_result_error;
    else if (*pid == 0) return nsh_fork_result_i_am_parent;
    else                return nsh_fork_result_i_am_child;
}

bool nsh_wait_for(pid_t pid) {
    return waitpid(pid, NULL, 0) >= 0;
}

void nsh_execve(const char* executable, char*const* argv, char*const* envp) {
    execve(executable, argv, envp);
}

void nsh_exit(int code) {
    exit(code);
}
