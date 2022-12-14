#include "../common/ast/ast.h"
#include "../common/exec/command.h"

#include "parser.h"


static struct nsh_ast* nsh_parser_parse_full_expr(struct nsh_parser* parser);


void nsh_parser_create(struct nsh_parser* parser, struct reader* reader, struct nsh_environment* env) {
    parser->reader      = reader;
    parser->environment = env;
}

void nsh_parser_destroy(struct nsh_parser* parser) {

}

static bool nsh_parser_is_var_ident(char c) {
    return (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z')
        || (c >= '0' && c <= '9')
        || (c == '?' || c == '!' || c == '_');
}

static void nsh_parser_read_ident(struct nsh_parser* parser, struct stringbuilder* sb) {
    while (reader_has(parser->reader) && nsh_parser_is_var_ident(reader_get(parser->reader))) {
        stringbuilder_append_char(sb, reader_get_and_advance(parser->reader));
    }
}

static void nsh_parser_read_variable(struct nsh_parser* parser, struct stringbuilder* sb) {
    struct stringbuilder  varname;

    stringbuilder_create(&varname);
    {
        nsh_parser_read_ident(parser, &varname);
        stringbuilder_append_cstr(sb, nsh_environment_lookup(parser->environment, stringbuilder_get_static(&varname), ""));
    }
    stringbuilder_destroy(&varname);
}

static void nsh_parser_read_quoted(struct nsh_parser* parser, struct stringbuilder* sb, char quote) {
    while (reader_has(parser->reader) && !reader_check(parser->reader, quote)) {
        if (quote == '\"' && reader_check(parser->reader, '$')) nsh_parser_read_variable(parser, sb);
        else stringbuilder_append_char(sb, reader_get_and_advance(parser->reader));
    }
}

static bool nsh_parser_read_word(struct nsh_parser* parser, struct stringbuilder* sb) {
    bool result;

    result = false;

    reader_skip_whitespaces(parser->reader);

    while (reader_has(parser->reader) && !reader_is_space(parser->reader) && !reader_is_any(parser->reader, "|<>&;(){}")) {
             if (reader_check(parser->reader, '\"')) nsh_parser_read_quoted(parser, sb, '\"');
        else if (reader_check(parser->reader, '\'')) nsh_parser_read_quoted(parser, sb, '\'');
        else if (reader_check(parser->reader, '$'))  nsh_parser_read_variable(parser, sb);
        else                                         stringbuilder_append_char(sb, reader_get_and_advance(parser->reader));
        result = true;
    }

    return result;
}

static nsh_ast* nsh_parser_parse_command(struct nsh_parser* parser) {
    struct stringbuilder  sb;
    struct nsh_command*   command;
    unsigned int          words;

    words   = 0;
    command = nsh_command_new();

    stringbuilder_create(&sb);

    while (true) {
        stringbuilder_clear(&sb);

        reader_skip_whitespaces(parser->reader);

        if (!reader_has(parser->reader)) break;

        if (reader_checks(parser->reader, "<<")) {
            nsh_parser_read_word(parser, &sb);
            nsh_command_add_redir(command, nsh_redirection_type_heredoc, stringbuilder_get_static(&sb));
        } else if (reader_checks(parser->reader, "<")) {
            nsh_parser_read_word(parser, &sb);
            nsh_command_add_redir(command, nsh_redirection_type_input_file, stringbuilder_get_static(&sb));
        } else if (reader_checks(parser->reader, ">>")) {
            nsh_parser_read_word(parser, &sb);
            nsh_command_add_redir(command, nsh_redirection_type_append_file, stringbuilder_get_static(&sb));
        } else if (reader_checks(parser->reader, ">")) {
            nsh_parser_read_word(parser, &sb);
            nsh_command_add_redir(command, nsh_redirection_type_output_file, stringbuilder_get_static(&sb));
        } else if (reader_checks(parser->reader, "2>&1")) {
            nsh_command_set_stderr_into_stdout(command);
        } else if (!reader_iss(parser->reader, "&&") && reader_checks(parser->reader, "&")) {
            nsh_command_set_detached(command);
        } else {
            if (!nsh_parser_read_word(parser, &sb))
                break;
            else {
                nsh_command_add_argv(command, stringbuilder_get_static(&sb));
                words++;
            }
        }
    }

    stringbuilder_destroy(&sb);

    if (words == 0) {
        nsh_command_delete(command);
        return nsh_ast_new_none();
    }

    return nsh_ast_new_command(command);
}

static struct nsh_ast* nsh_parser_parse_simple_expr(struct nsh_parser* parser) {
    struct nsh_ast*  ast;

    reader_skip_whitespaces(parser->reader);

    if (reader_checks(parser->reader, "(")) {
        ast = nsh_parser_parse_full_expr(parser);
        reader_checks(parser->reader, ")");
        return ast;
    } else if (reader_checks(parser->reader, "while ")) {
        ast = nsh_parser_parse_full_expr(parser);
        reader_skip_whitespaces(parser->reader);
        reader_checks(parser->reader, "{");
        ast = nsh_ast_new_while(ast, nsh_parser_parse_full_expr(parser));
        reader_skip_whitespaces(parser->reader);
        reader_checks(parser->reader, "}");
        return ast;
    } else {
        return nsh_parser_parse_command(parser);
    }
}

static struct nsh_ast* nsh_parser_parse_expr(struct nsh_parser* parser, int prec) {
    struct nsh_ast*  expr;

    expr = nsh_parser_parse_simple_expr(parser);

    while (true) {
        reader_skip_whitespaces(parser->reader);
        if (!reader_has(parser->reader)) break;
        
        if (reader_checks(parser->reader, "||"))
            expr = nsh_ast_new_or(expr, nsh_parser_parse_expr(parser, 1));
        else if (prec >= 2 && reader_checks(parser->reader, "&&"))
            expr = nsh_ast_new_and(expr, nsh_parser_parse_expr(parser, 1));
        else if (reader_checks(parser->reader, "|"))
            expr = nsh_ast_new_pipe(expr, nsh_parser_parse_expr(parser, 1));
        else if (prec >= 3 && reader_checks(parser->reader, ";"))
            expr = nsh_ast_new_semicolon(expr, nsh_parser_parse_expr(parser, prec));
        else
            break;
    }

    return expr;
}

static struct nsh_ast* nsh_parser_parse_full_expr(struct nsh_parser* parser) {
    return nsh_parser_parse_expr(parser, 100);
}

bool nsh_parser_parse(struct nsh_parser* parser, struct nsh_ast** ast) {
    *ast = nsh_parser_parse_full_expr(parser);
    return ast != NULL;
}
