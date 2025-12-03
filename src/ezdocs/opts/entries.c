#include <ezcli/cli.h>

#include "../utils/doc_body.h"
#include "../utils/join_str.h"
#include "../utils/strip.h"
#include "entries.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * gets the description for an entry in `path`. for every entry, its description
 * is in its first line.
 */
char *get_entry_description(char *path) {
    FILE *entry = fopen(path, "r");

    if (entry == NULL) {
        cliprint(CLI_ERROR, "ezdocs: ",
                 "no documentation found for.\nmake sure you're up to "
                 "date with "
                 "the git repository.\n");

        exit(EXIT_FAILURE);
    }

    char buffer[1024] = "";
    int i = 0;

    while (true) {
        char c = fgetc(entry);

        if (c == '\n') {
            buffer[i] = '\0';
            break;
        }

        buffer[i++] = c;
    }

    char *desc = strdup(buffer);

    fclose(entry);

    return desc;
}

void _entry_opts_add(char *entries_path, char **entries, cli_s *cli) {
    int i = 0;

    static opt_s template_entry = {.body = doc_body};

    template_entry.ctx = cli;

    while (entries[i]) {
        char *entry_path = join_str(entries_path, entries[i]);

        char **aliases = malloc(sizeof(char *) * 2);

        char *name = strip(entries[i], ".docs");
        char *desc = get_entry_description(entry_path);

        opt_s entry = template_entry;

        aliases[0] = name;
        aliases[1] = NULL;

        entry.desc = desc;
        entry.aliases = aliases;

        allocopt(cli, &entry);

        free(entry_path);

        i++;
    }
}
