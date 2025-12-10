#include <ezcli/print.h>

#include <stdarg.h>
#include <stdio.h>

const char *PREFIXES[] = {"HINT: ", "WARN: ", "ERROR: "};
const char *COLORS[] = {ANSI_BLUE, ANSI_YELLOW, ANSI_RED};

void cliprint(print_e type, char *prefix, char *fmt, ...) {
    const char *_prefix = prefix ? prefix : PREFIXES[type];

    printf("%s%s", COLORS[type], _prefix);

    va_list args;
    va_start(args, fmt);

    vprintf(fmt, args);

    va_end(args);

    printf("%s\n", ANSI_RESET);
}
