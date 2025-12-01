#include <ezcli.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_docs(char *name) {
    char doc_file_path[100] = "./docs/docs_program/";

    strcat(doc_file_path, name);
    strcat(doc_file_path, ".docs");

    FILE *doc_file = fopen(doc_file_path, "r");

    if (doc_file == NULL) {
        cliprint(CLI_ERROR, "docs: ",
                 "no documentation found for '%s'.\nmake sure you're up to "
                 "date with "
                 "the git repository.\n",
                 name);

        exit(EXIT_FAILURE);
    }

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), doc_file)) {
        printf("%s", buffer);
    }

    fclose(doc_file);
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

opt_s doc_version = {
    .aliases = CLI_ALIASES("version", "-v", "--version"),
    .desc = "version of ezcli.",
    .body = _doc_version,
};

#define create_doc_opt(alias, descr)                                           \
    (opt_s) {                                                                  \
        .aliases = CLI_ALIASES(alias), .desc = descr, .body = doc_body,        \
        .ctx = &cli,                                                           \
    }

void print_title_edge(size_t size) {
    for (size_t i = 0; i < size; i++)
        printf("-");
}

ret_e _common(void *ctx, CLI_IGNORE_TOK) {
    cli_s *cli = ctx;

    char *curr_tok = gettok_offset(cli, 0);

    if (cli->argc > 2) {
        if (cli->tok_idx > 1) {
            printf("\n");
        }

        print_title_edge(strlen(curr_tok) * 3);

        printf("\n");

        printf("%*s\n", (int)strlen(curr_tok) * 2, curr_tok);

        print_title_edge(strlen(curr_tok) * 3);

        printf("\n\n");
    }

    return RET_NORMAL;
}

int main(int argc, char *argv[]) {
    cli_s cli;
    opt_s *opts[] = {NULL};
    char *help_aliases[] = {"help", "--help", "-h", NULL};

    initcli(&cli, "docs",
            "this program is a cli documentation for ezcli.\nyou should "
            "probably start with 'docs entrypoint'.",
            "[concept]",
            "for source code, visit <https://github.com/alperenozdnc/ezcli>\n",
            opts, help_aliases);

    opt_s doc_entry = {
        .aliases = CLI_ALIASES("entrypoint", "root"),
        .desc = "root of documentation.",
        .body = doc_body,
        .ctx = &cli,
    };

    opt_s common = {
        .aliases = CLI_ALIASES(CLI_COMMON_OPT), .body = _common, .ctx = &cli};

    opt_s doc_structure =
        create_doc_opt("structure", "structuring projects using ezcli.");
    opt_s doc_initcli = create_doc_opt("initcli", "initcli() core function.");
    opt_s doc_runcli = create_doc_opt("runcli", "runcli() core function.");
    opt_s doc_freecli = create_doc_opt("freecli", "freecli() core function.");
    opt_s doc_external = create_doc_opt("external", "core externals/globals.");
    opt_s doc_addopt = create_doc_opt("addopt", "addopt() utility function.");
    opt_s doc_delopt = create_doc_opt("delopt", "delopt() utility function.");
    opt_s doc_gettok =
        create_doc_opt("gettok", "gettok_*() utility functions.");
    opt_s doc_print =
        create_doc_opt("cliprint", "cliprint() utility function.");
    opt_s doc_cli_s = create_doc_opt("cli_s", "struct cli_s.");
    opt_s doc_opt_s = create_doc_opt("opt_s", "struct opt_s.");

    addopt(&cli, &doc_entry, &doc_structure, &doc_initcli, &doc_runcli,
           &doc_freecli, &doc_external, &doc_addopt, &doc_delopt, &doc_gettok,
           &doc_print, &doc_cli_s, &doc_opt_s, &common, &doc_version);

    runcli(&cli, argc, argv);

    freecli(&cli);
}
