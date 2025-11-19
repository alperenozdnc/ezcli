#include <ezcli/print.h>

#include <stdio.h>

const char *PREFIXES[] = {"HINT: ", "WARN: ", "ERROR: "};
const char *COLORS[] = {ANSI_BLUE, ANSI_YELLOW, ANSI_RED};

void cliprint(enum print_type type, char *prefix, char *msg) {
    const char *_prefix = prefix ? prefix : PREFIXES[type];

    printf("%s%s%s%s\n", COLORS[type], _prefix, msg, ANSI_RESET);
}
