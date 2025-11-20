#ifndef EZCLI_PRINT_H
#define EZCLI_PRINT_H

#define ANSI_RED "\x1b[31m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_BLUE "\x1b[34m"
#define ANSI_RESET "\x1b[0m"

enum print_type { CLI_HINT, CLI_WARN, CLI_ERROR };

/*
 * prints a hint, a warning, or an error.
 * default prefixes are in format `TYPE: `.
 * `enum print_type` has to be `CLI_HINT`, `CLI_WARNING`, or `CLI_ERROR`.
 * a hint is blue, a warning is yellow, and an error is red.
 */
void cliprint(enum print_type type, char *prefix, char *msg, ...);

#endif
