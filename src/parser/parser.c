#include "parser.h"

void nsh_parser_create(struct nsh_parser* parser, struct reader* reader) {
    parser->reader = reader;
}

void nsh_parser_destroy(struct nsh_parser* parser) {

}

bool nsh_parser_parse(struct nsh_parser* parser, struct nsh_program* program) {
    // TODO
}
