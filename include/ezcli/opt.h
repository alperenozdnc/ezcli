#pragma once

#include <stdbool.h>

/*
 * keeps track of the return type of an option.
 *
 * `RET_NORMAL` -> returns 0.
 * `RET_WARN` -> returns 0, prints as a warning.
 * `RET_FAIL` -> returns -1, prints as an error, exits.
 */
typedef enum { RET_NORMAL, RET_WARN, RET_FAIL } ret_e;

#define CLI_NONOPT "NONOPT"
#define CLI_DEFAULT_OPT "DEFAULT"
#define CLI_COMMON_OPT "COMMONOPT"

#define CLI_IGNORE_ARGS                                                        \
    __attribute((unused)) void *_, __attribute((unused)) char *__

#define CLI_IGNORE_TOK __attribute((unused)) char *_
#define CLI_IGNORE_CTX __attribute((unused)) void *_

#define CLI_ALIASES(...)                                                       \
    (char *[]) {                                                               \
        __VA_ARGS__, NULL                                                      \
    }

/*
 * keeps the information about an option.
 * `aliases`: names of option
 * `desc`: description of option. this is printed in help in format `opt ->
 * desc`.
 * `want_input`: true if option requires an input. if not filled,
 * this is false.
 * `ctx`: state to be passed to the body when running. this allows for
 * functionality like chaining, state tracking, multiple argument options,
 * etc. `body`: functionality of option. this is the function that is feeded
 * the word that comes after an option.
 */
typedef struct {
    char **aliases;
    char *desc;

    bool want_input;

    void *ctx;
    ret_e (*body)(void *ctx, char *tok);
} opt_s;
