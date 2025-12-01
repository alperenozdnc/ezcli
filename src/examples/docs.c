#include <ezcli.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DOC_OPT(alias, descr)                                                  \
    (opt_s) {                                                                  \
        .aliases = CLI_ALIASES(alias), .desc = descr, .body = doc_body,        \
        .ctx = &cli,                                                           \
    }

void read_docs(char *name) {
    char *doc_file_dir = "./docs/docs_program/";
    char *doc_file_path =
        malloc(strlen(doc_file_dir) + strlen(name) + strlen(".docs"));

    sprintf(doc_file_path, "%s%s.docs", doc_file_dir, name);

    FILE *doc_file = fopen(doc_file_path, "r");

    if (doc_file == NULL) {
        cliprint(CLI_ERROR, "docs: ",
                 "no documentation found for '%s'.\nmake sure you're up to "
                 "date with "
                 "the git repository.\n",
                 name);

        exit(EXIT_FAILURE);
    }

    while (true) {
        char c = fgetc(doc_file);

        if (c == EOF)
            break;

        putchar(c);
    }

    fclose(doc_file);
    free(doc_file_path);
}

ret_e doc_body(void *ctx, CLI_IGNORE_TOK) {
    cli_s *cli = ctx;
    char *curr_tok = gettok_offset(cli, 0);

    read_docs(curr_tok);

    return RET_NORMAL;
}

ret_e _doc_version(CLI_IGNORE_ARGS) {
    printf("ezcli current version -> v%s\n", CLI_STRING_V);
    printf("YOU can definitely help that go up.\n");

    return RET_NORMAL;
}

ret_e _section_categorizer(void *ctx, CLI_IGNORE_TOK) {
    cli_s *cli = ctx;

    char *curr_tok = gettok_offset(cli, 0);
    int curr_tok_len = strlen(curr_tok);

    if (cli->argc < 2)
        return RET_NORMAL;

    if (cli->tok_idx > 1)
        printf("\n");

    for (int i = 0; i < curr_tok_len * 3; i++)
        putchar('-');

    printf("\n%*s\n", curr_tok_len * 2, curr_tok);

    for (int i = 0; i < curr_tok_len * 3; i++)
        putchar('-');

    printf("\n\n");

    return RET_NORMAL;
}

int main(int argc, char *argv[]) {
    cli_s cli;
    char *help_aliases[] = {"help", "--help", "-h", NULL};

    initcli(&cli, "docs",
            "this program is a cli documentation for ezcli.\nyou should "
            "probably start with 'docs entrypoint'.",
            "[concept]",
            "for source code, visit <https://github.com/alperenozdnc/ezcli>\n",
            (opt_s *[]){NULL}, help_aliases);

    opt_s doc_entry = {
        .aliases = CLI_ALIASES("entrypoint", "root"),
        .desc = "root of documentation.",
        .body = doc_body,
        .ctx = &cli,
    };

    opt_s doc_structure =
        DOC_OPT("structure", "structuring projects using ezcli.");
    opt_s doc_initcli = DOC_OPT("initcli", "initcli() core function.");
    opt_s doc_runcli = DOC_OPT("runcli", "runcli() core function.");
    opt_s doc_freecli = DOC_OPT("freecli", "freecli() core function.");
    opt_s doc_external = DOC_OPT("external", "core externals/globals.");
    opt_s doc_addopt = DOC_OPT("addopt", "addopt() utility function.");
    opt_s doc_delopt = DOC_OPT("delopt", "delopt() utility function.");
    opt_s doc_gettok = DOC_OPT("gettok", "gettok_*() utility functions.");
    opt_s doc_print = DOC_OPT("cliprint", "cliprint() utility function.");
    opt_s doc_cli_s = DOC_OPT("cli_s", "struct cli_s.");
    opt_s doc_opt_s = DOC_OPT("opt_s", "struct opt_s.");

    opt_s section_categorizer = {.aliases = CLI_ALIASES(CLI_COMMON_OPT),
                                 .body = _section_categorizer,
                                 .ctx = &cli};

    opt_s doc_version = {
        .aliases = CLI_ALIASES("version", "-v", "--version"),
        .desc = "version of ezcli.",
        .body = _doc_version,
    };

    addopt(&cli, &doc_entry, &doc_structure, &doc_initcli, &doc_runcli,
           &doc_freecli, &doc_external, &doc_addopt, &doc_delopt, &doc_gettok,
           &doc_print, &doc_cli_s, &doc_opt_s, &section_categorizer,
           &doc_version);

    runcli(&cli, argc, argv);

    freecli(&cli);
}
