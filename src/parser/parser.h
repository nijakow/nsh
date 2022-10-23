#ifndef NSH_PARSER_PARSER_H
#define NSH_PARSER_PARSER_H

#include "../defs.h"
#include "../common/ast/ast.h"
#include "../util/reader.h"

struct nsh_parser {
    struct reader*  reader;
};

void nsh_parser_create(struct nsh_parser* parser, struct reader* reader);
void nsh_parser_destroy(struct nsh_parser* parser);

struct nsh_ast* nsh_parser_parse(struct nsh_parser* parser);

#endif
