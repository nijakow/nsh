#include "../parser/parser.h"

#include "nsh_loop.h"

void nsh_process_command(struct nsh* nsh, const char* cmd) {
    struct reader      reader;
    struct nsh_parser  parser;
    struct nsh_ast*    ast;

    reader_create(&reader, cmd);
    nsh_parser_create(&parser, &reader);

    ast = nsh_parser_parse(&parser);

    nsh_ast_dump(ast);

    nsh_ast_delete(ast);

    nsh_parser_destroy(&parser);
    reader_destroy(&reader);
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
