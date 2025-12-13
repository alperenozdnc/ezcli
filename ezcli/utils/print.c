#include <ezcli/platform.h>
#include <ezcli/print.h>

#include <stdarg.h>

const char *PREFIXES[] = {"HINT: ", "WARN: ", "ERROR: "};

void cliprint(print_e type, char *prefix, char *fmt, ...) {
    const char *_prefix = prefix ? prefix : PREFIXES[type];

#ifndef CLI_EMBEDDED

    const char *COLORS[] = {ANSI_BLUE, ANSI_YELLOW, ANSI_RED};

    c_printf("%s%s", COLORS[type], _prefix);

    va_list args;
    va_start(args, fmt);

    c_vprintf(fmt, args);

    va_end(args);

    c_printf("%s\n", ANSI_RESET);

#else

    c_puts(_prefix);
    c_puts(fmt);

#endif // CLI_EMBEDDED
}
