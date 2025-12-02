#include <ezcli.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_docfile(char *docname) {
    const char *HOME = getenv("HOME");
    char *dir = "/.local/ezdocs/";

    size_t size = strlen(HOME) + strlen(dir) + strlen(docname) +
                  strlen(".docs") + sizeof('\0');

    char *doc_file_path = malloc(size);

    snprintf(doc_file_path, size, "%s%s%s.docs", HOME, dir, docname);

    FILE *doc_file = fopen(doc_file_path, "r");

    if (doc_file == NULL) {
        cliprint(CLI_ERROR, "ezdocs: ",
                 "no documentation found for '%s'.\nmake sure you're up to "
                 "date with "
                 "the git repository.\n",
                 docname);

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
