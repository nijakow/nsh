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

static struct nsh_ast* nsh_parser_parse_expr(struct nsh_parser* parser) {
    struct stringbuilder  sb;
    struct nsh_command*   command;

    // TODO: Allocate and initialize command

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

    // TODO: Create an AST for the command

    return NULL;
}

bool nsh_parser_parse(struct nsh_parser* parser, struct nsh_program* program) {
    // TODO
    return false;
}
