#include "../common/ast/ast.h"
#include "../common/exec/command.h"

#include "parser.h"

void nsh_parser_create(struct nsh_parser* parser, struct reader* reader) {
    parser->reader = reader;
}

void nsh_parser_destroy(struct nsh_parser* parser) {

}

static bool nsh_parser_read_word_into(struct nsh_parser* parser, struct stringbuilder* sb) {
    reader_skip_whitespaces(parser->reader);
    while (reader_has(parser->reader) && !reader_is_space(parser->reader)) {
        stringbuilder_append_char(sb, reader_get_and_advance(parser->reader));
    }
    return false;
}

static nsh_ast* nsh_parser_parse_simple_expr(struct nsh_parser* parser) {
    struct stringbuilder  sb;
    struct nsh_command*   command;

    command = nsh_command_new();

    stringbuilder_create(&sb);

    while (true) {
        stringbuilder_clear(&sb);

        reader_skip_whitespaces(parser->reader);
        if (reader_checks(parser->reader, "<<")) {
            nsh_parser_read_word_into(parser, &sb);
            nsh_command_add_redir(command, nsh_redirection_type_heredoc, stringbuilder_get_static(&sb));
        } else if (reader_checks(parser->reader, "<")) {
            nsh_parser_read_word_into(parser, &sb);
            nsh_command_add_redir(command, nsh_redirection_type_input_file, stringbuilder_get_static(&sb));
        } else if (reader_checks(parser->reader, ">>")) {
            nsh_parser_read_word_into(parser, &sb);
            nsh_command_add_redir(command, nsh_redirection_type_append_file, stringbuilder_get_static(&sb));
        } else if (reader_checks(parser->reader, ">")) {
            nsh_parser_read_word_into(parser, &sb);
            nsh_command_add_redir(command, nsh_redirection_type_output_file, stringbuilder_get_static(&sb));
        } else if (reader_checks(parser->reader, "2>&1")) {
            nsh_command_stderr_into_stdout(command);
        } else {
            nsh_parser_read_word_into(parser, &sb);
            nsh_command_add_argv(command, stringbuilder_get_static(&sb));
        }
    }

    stringbuilder_destroy(&sb);

    return nsh_ast_new_command(command);
}

static struct nsh_ast* nsh_parser_parse_expr(struct nsh_parser* parser) {
    struct nsh_ast*  expr;

    expr = nsh_parser_parse_simple_expr(parser);

    while (true) {
        reader_skip_whitespaces(parser->reader);
        if (reader_checks(parser->reader, "|")) expr = nsh_ast_new_pipe(expr, nsh_parser_parse_expr(parser));
        else break;
    }
}

bool nsh_parser_parse(struct nsh_parser* parser, struct nsh_program* program) {
    // TODO
    return false;
}
