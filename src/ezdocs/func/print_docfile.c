#include <ezcli.h>

#include <ezdocs/join_str.h>
#include <ezdocs/main.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_docfile(char *docname) {
    char *HOME = getenv("HOME");

    char *dirname = join_str(HOME, LOCAL_EZCLI_DIR);
    char *filename = join_str(docname, DOCS_FILE_EXT);
    char *path = join_str(dirname, filename);

    FILE *doc_file = fopen(path, "r");

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
    free(dirname);
    free(filename);
    free(path);
}
