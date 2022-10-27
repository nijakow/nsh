#ifndef NSH_PARSER_PARSER_H
#define NSH_PARSER_PARSER_H

#include "../defs.h"
#include "../common/ast/ast.h"
#include "../common/environment/environment.h"
#include "../util/reader.h"

struct nsh_parser {
    struct reader*           reader;
    struct nsh_environment*  environment;
};

void nsh_parser_create(struct nsh_parser* parser, struct reader* reader, struct nsh_environment* env);
void nsh_parser_destroy(struct nsh_parser* parser);

bool nsh_parser_parse(struct nsh_parser* parser, struct nsh_ast** ast);

#endif
