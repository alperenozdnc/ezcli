#include <ezcli.h>
#include <stdlib.h>

/*
 * frees all pieces of dynamically allocated memory related to entries.
 */
void free_entries(char **entries) {
    int i = 0;

    while (entries[i]) {
        free(entries[i]);

        i++;
    }

    free(entries);
}

void cleanup(cli_s *cli, char *entries_path, char **entries) {
    free(entries_path);
    free_entries(entries);
    freecli(cli);
}
