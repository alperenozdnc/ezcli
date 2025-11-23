#ifndef EZCLI_OPT_H
#define EZCLI_OPT_H

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

/*
 * keeps the information about an option.
 * `type`: type of option (see enum otype)
 * `name`: name of option
 * `desc`: description of option. this is printed in help in format `opt ->
 * desc`.
 * `want_input`: true if option requires an input. if not filled,
 * undefined parsing behaviour may occur. `body`: functionality of option. this
 * is the function that is feeded the word that comes after an option.
 */
struct opt {
    enum otype type;
    char *name;
    char *desc;
    bool want_input;
    enum rtype (*body)(char *);
};

#endif
