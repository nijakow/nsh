#include "../parser/parser.h"
#include "../exec/exec.h"

#include "nsh_loop.h"

void nsh_print_prompt(struct nsh* nsh) {
    if (isatty(NSH_STDIN_FD)) {
        printf("nsh $ ");
        fflush(stdout);
    }
}

static bool nsh_parse_command(struct nsh* nsh, const char* cmd, struct nsh_ast** ast) {
    struct reader      reader;
    struct nsh_parser  parser;
    bool               result;

    reader_create(&reader, cmd);
    nsh_parser_create(&parser, &reader);

    result = nsh_parser_parse(&parser, ast);

    nsh_parser_destroy(&parser);
    reader_destroy(&reader);

    return result;
}

static bool nsh_run_command(struct nsh* nsh, struct nsh_ast* ast) {
    struct nsh_exec  exec;
    bool             result;

    nsh_exec_create(&exec, &nsh->environment, &nsh->sherlock);
    result = nsh_exec_ast(&exec, ast);
    nsh_exec_wait(&exec);
    nsh_exec_destroy(&exec);

    return result;
}

static bool nsh_process_command(struct nsh* nsh, const char* cmd) {
    struct nsh_ast*  ast;
    bool             result;

    result = nsh_parse_command(nsh, cmd, &ast)
          && nsh_run_command(nsh, ast);
    
    if (ast != NULL) nsh_ast_delete(ast);

    return result;
}

void nsh_loop(struct nsh* nsh) {
    char input_buffer[1024];

    while (nsh->is_running) {
        nsh_print_prompt(nsh);
        nsh->ignore_kill = false;
        nsh->is_reading  = true;
        if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
            nsh->is_reading = false;
            nsh_process_command(nsh, input_buffer);
        } else {
            nsh_halt(nsh);
        }
    }
}
