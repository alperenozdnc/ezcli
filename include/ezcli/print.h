#pragma once

#define ANSI_RED "\x1b[31m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_BLUE "\x1b[34m"
#define ANSI_RESET "\x1b[0m"

#define CLI_EMPTY_PREFIX ""

typedef enum { CLI_HINT, CLI_WARN, CLI_ERROR } print_e;

/*
 * prints a hint, a warning, or an error.
 * default prefixes are in format `TYPE: `.
 * `enum print_type` has to be `CLI_HINT`, `CLI_WARNING`, or `CLI_ERROR`.
 * a hint is blue, a warning is yellow, and an error is red.
 */
void cliprint(print_e type, char *prefix, char *fmt, ...);
