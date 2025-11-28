#include "assert.h"
#include "ezcli/print.h"

#include <stdlib.h>

/*
 * prints `label` and exits with failure if `expr` is `false`.
 */
void cliassert(bool expr, char *label) {
    if (expr)
        return;

    cliprint(CLI_ERROR, "[assertion failed] ", "%s\n", label);
    exit(EXIT_FAILURE);
}
