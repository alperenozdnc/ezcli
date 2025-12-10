#include <ezdocs/strip.h>

#include <stdlib.h>
#include <string.h>

char *strip(char *str, char *ext) {
    size_t stripped_len = strlen(str) - strlen(ext);

    char *stripped = malloc(stripped_len + 1);

    for (size_t i = 0; i < stripped_len; i++) {
        char c = str[i];

        stripped[i] = c;
    }

    stripped[stripped_len] = '\0';

    return stripped;
}
