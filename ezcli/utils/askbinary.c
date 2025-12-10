#include <ezcli/askbinary.h>
#include <ezcli/print.h>

#include <internal/panic.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * either exits cli or returns `false` depending on laidback value.
 */
bool ask_panic(char *msg) {
    cliprint(CLI_ERROR, NULL, "%s", msg);

    if (panic() == RET_WARN)
        return false;

    exit(EXIT_FAILURE);
}

bool askbinary(char *msg, char **yes_aliases, char **no_aliases,
               bool is_no_inclusive) {
    printf("%s", msg);

    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return ask_panic("error reading input.");

    int i = 0;
    int j = 0;

    // fgets includes the \n for when return is pressed
    size_t trim_len = strcspn(buffer, "\n");
    buffer[trim_len] = '\0';

    while (yes_aliases[i]) {
        char *alias = yes_aliases[i];

        if (strcmp(alias, buffer) == 0)
            return true;

        i++;
    }

    if (is_no_inclusive)
        return false;

    while (no_aliases[j]) {
        char *alias = no_aliases[j];

        if (strcmp(alias, buffer) == 0)
            return false;

        j++;
    }

    return ask_panic("answer not recognized.");
}
