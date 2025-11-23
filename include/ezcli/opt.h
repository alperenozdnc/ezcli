#pragma once

#include <stdbool.h>

/*
 * keeps track of the type of an option.
 *
 * `OPTION_BARE` -> `option`
 * `OPTION_SINGLE` -> `-option`
 * `OPTION_DOUBLE` -> `--option`
 */
enum otype { OPTION_BARE, OPTION_SINGLE, OPTION_DOUBLE };

/*
 * keeps track of the return type of an option.
 *
 * `RET_NORMAL` -> returns 0.
 * `RET_WARN` -> returns 0, prints as a warning.
 * `RET_FAIL` -> returns -1, prints as an error, exits.
 */
enum rtype { RET_NORMAL, RET_WARN, RET_FAIL };

#define EZCLI_NONOPT "NONOPT"
#define EZCLI_DEFAULT_OPT "DEFAULT"

#define EZCLI_IGNORE_ARGS                                                      \
    __attribute((unused)) void *_, __attribute((unused)) char *__

#define EZCLI_IGNORE_TOK __attribute((unused)) char *_
#define EZCLI_IGNORE_CTX __attribute((unused)) void *_

/*
 * keeps the information about an option.
 * `type`: type of option (see enum otype)
 * `name`: name of option
 * `desc`: description of option. this is printed in help in format `opt ->
 * desc`.
 * `want_input`: true if option requires an input. if not filled,
 * undefined parsing behaviour may occur.
 * `ctx`: state to be passed to the body when running. this allows for
 * functionality like chaining, state tracking, multiple argument options,
 * etc. `body`: functionality of option. this is the function that is feeded
 * the word that comes after an option.
 */
struct opt {
    enum otype type;
    char *name;
    char *desc;

    bool want_input;

    void *ctx;
    enum rtype (*body)(void *ctx, char *tok);
};
