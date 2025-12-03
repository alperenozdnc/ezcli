#include "get_entries.h"

#include "../../ezcli/internal/match.h"

#include <dirent.h>
#include <ezcli.h>
#include <stdlib.h>
#include <string.h>

char **get_entries(char *path) {
    char *ignore[] = {".", "..", "README", NULL};

    struct dirent *dir_entry;
    DIR *dir = opendir(path);

    size_t len = 0;

    // +1 for entry and +1 for NULL pointer
    char **entries = malloc(sizeof(char *));

    if (!dir) {
        cliprint(CLI_ERROR, CLI_EMPTY_PREFIX, "ezdocs: couldn't open %s.",
                 path);

        exit(EXIT_FAILURE);
    }

    while (true) {
        dir_entry = readdir(dir);

        if (!dir_entry)
            break;

        if (match_str(ignore, dir_entry->d_name))
            continue;

        entries[len] = strdup(dir_entry->d_name);

        // +1 for entry and +1 for NULL pointer
        len++;
        entries = realloc(entries, sizeof(char *) * (len + 1));
    }

    entries[len] = NULL;

    closedir(dir);

    return entries;
}
