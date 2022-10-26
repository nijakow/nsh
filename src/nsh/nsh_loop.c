#include "../parser/parser.h"
#include "../exec/exec.h"

#include "nsh_loop.h"

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
    nsh_ast_dump(ast);

    return true;
}

static bool nsh_process_command(struct nsh* nsh, const char* cmd) {
    struct nsh_ast*  ast;

    return nsh_parse_command(nsh, cmd, &ast)
        && nsh_run_command(nsh, ast);
}

void nsh_loop(struct nsh* nsh) {
    char input_buffer[1024];

    while (nsh->is_running) {
        printf("nsh $ ");
        fflush(stdout);
        if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
            nsh_process_command(nsh, input_buffer);
        }
    }
}
