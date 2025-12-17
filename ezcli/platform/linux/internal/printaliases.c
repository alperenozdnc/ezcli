#include <ezcli/print.h>

#include "internal/printaliases.h"

#include <stdio.h>

void printaliases(char **aliases) {
    int i = 0;

    printf(ANSI_BLUE);

    while (aliases[i] && i <= 2) {
        char *alias = aliases[i];

        printf("%s", alias);

        if (aliases[i + 1] && i + 1 <= 2) {
            printf(", ");
        }

        i++;
    }

    printf(ANSI_RESET);
}
