#include <ezcli/print.h>

#include "assert.h"

#include <stdlib.h>

/*
 * prints `label` and exits with failure if `expr` is `false`.
 */
void _assert(bool expr, char *label) {
    if (expr)
        return;

    cliprint(CLI_ERROR, "[ezcli] _assertion failed: ", "%s\n", label);
    exit(EXIT_FAILURE);
}
