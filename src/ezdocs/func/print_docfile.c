#include <ezcli.h>

#include "../main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_docfile(char *docname) {
    const char *HOME = getenv("HOME");

    size_t size = strlen(HOME) + strlen(LOCAL_EZCLI_DIR) + strlen(docname) +
                  strlen(DOCS_FILE_EXT) + sizeof('\0');

    char *doc_file_path = malloc(size);

    snprintf(doc_file_path, size, "%s%s%s%s", HOME, LOCAL_EZCLI_DIR, docname,
             DOCS_FILE_EXT);

    FILE *doc_file = fopen(doc_file_path, "r");

    if (doc_file == NULL) {
        cliprint(CLI_ERROR, "ezdocs: ",
                 "no documentation found for '%s'.\nmake sure you're up to "
                 "date with "
                 "the git repository.\n",
                 docname);

        exit(EXIT_FAILURE);
    }

    char buffer[1024] = "";
    int i = 0;

    bool is_description_over = false;
    bool skip_after_delimiter = false;

    while (true) {
        char c = fgetc(doc_file);

        if (c == EOF)
            break;

        if (is_description_over && !skip_after_delimiter) {
            putchar(c);

            continue;
        }

        if (is_description_over) {
            skip_after_delimiter = false;
            continue;
        }

        buffer[i++] = c;

        if (c != '\n')
            continue;

        buffer[i] = '\0';

        if (strcmp(DESC_DELIMITER, buffer) == 0) {
            is_description_over = true;
            skip_after_delimiter = true;
        } else {
            buffer[0] = '\0';
            i = 0;
        }
    }

    fclose(doc_file);
    free(doc_file_path);
}
