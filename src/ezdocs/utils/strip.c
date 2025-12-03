#include "strip.h"

#include <stdlib.h>
#include <string.h>

char *strip(char *str, char *ext) {
    size_t ext_len = strlen(ext);

    char *stripped = malloc(ext_len + 1);

    for (size_t i = 0; i < ext_len; i++) {
        char c = str[i];

        if (c == ext[0])
            break;

        stripped[i] = c;
    }

    stripped[ext_len] = '\0';

    return stripped;
}
