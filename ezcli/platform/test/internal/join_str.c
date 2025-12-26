#include "internal/join_str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *join_str(char *str1, char *str2) {
    size_t size = strlen(str1) + strlen(str2) + sizeof('\0');

    char *str3 = malloc(size);

    snprintf(str3, size, "%s%s", str1, str2);

    return str3;
}
