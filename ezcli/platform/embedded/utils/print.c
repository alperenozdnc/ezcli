#include <ezcli/platform.h>
#include <ezcli/print.h>

void cliprint(print_e type, char *prefix, char *fmt, ...) {
    const char *PREFIXES[] = {"HINT: ", "WARN: ", "ERROR: "};
    const char *_prefix = prefix ? prefix : PREFIXES[type];

    c_puts(_prefix);
    c_puts(fmt);
}
