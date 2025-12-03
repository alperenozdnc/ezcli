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

    size_t entries_len = 0;
    char **entries = malloc(sizeof(char *) * (entries_len + 1));

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

        entries_len++;
        entries = realloc(entries, sizeof(char *) * (entries_len + 1));
        entries[entries_len - 1] = strdup(dir_entry->d_name);
    }

    entries[entries_len - 1] = NULL;

    closedir(dir);

    return entries;
}
