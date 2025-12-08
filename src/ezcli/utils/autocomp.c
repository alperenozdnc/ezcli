#include <ezcli/autocomp.h>
#include <ezcli/cli.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>

#include <internal/blacklist.h>
#include <internal/join_str.h>
#include <internal/match.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _genautocomp(cli_s *cli, char *ref_filename, char *filename) {
    FILE *reference = fopen(ref_filename, "r");
    FILE *new = fopen(filename, "w");

    if (reference == NULL) {
        cliprint(CLI_ERROR,
                 "ezdocs: ", "can't find reference file for completions.");

        exit(EXIT_FAILURE);
    }

    if (new == NULL) {
        cliprint(CLI_ERROR, "ezdocs: ", "error opening file '%s' for writing.",
                 filename);

        exit(EXIT_FAILURE);
    }

    while (true) {
        char c = fgetc(reference);

        if (c == EOF)
            break;

        if (c == CMD_NAME_CHAR) {
            fprintf(new, "%s", cli->cmd);

            continue;
        }

        if (c == OPTS_CHAR) {
            for (size_t i = 0; i < cli->opts_len; i++) {
                opt_s *opt = cli->opts[i];

                if (match_str(BLACKLIST, opt->aliases[0]))
                    continue;

                int j = 0;

                fprintf(new, TWO_TABS);

                while (opt->aliases[j]) {
                    char *alias = opt->aliases[j];

                    fprintf(new, "%s", alias);

                    if (opt->aliases[j + 1])
                        fprintf(new, " ");

                    j++;
                }

                if (i < cli->opts_len - 1)
                    fprintf(new, "\n");
            }

            continue;
        }

        fprintf(new, "%c", c);
    }

    fclose(reference);
    fclose(new);
}

void genautocomp(cli_s *cli, char *filename, bool bash, bool zsh) {
    char *home = getenv("HOME");

    char *template_dir = join_str(home, EZCLI_DIR);

    if (zsh) {
        char *zsh_filename = join_str(filename, ".zsh");
        char *template_filename = join_str("template", ".zsh");
        char *template_path = join_str(template_dir, template_filename);

        _genautocomp(cli, template_path, zsh_filename);

        free(zsh_filename);
        free(template_filename);
        free(template_path);
    }

    if (bash) {
        char *bash_filename = join_str(filename, ".bash");
        char *template_filename = join_str("template", ".bash");
        char *template_path = join_str(template_dir, template_filename);

        _genautocomp(cli, template_path, bash_filename);

        free(bash_filename);
        free(template_filename);
        free(template_path);
    }

    free(template_dir);
}
