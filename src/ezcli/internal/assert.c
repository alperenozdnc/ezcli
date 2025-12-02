#include <ezcli/freecli.h>
#include <ezcli/print.h>

#include "assert.h"

#include <stdbool.h>
#include <stdlib.h>

void _assert(bool expr, char *label) {
    if (expr)
        return;

    ASSERT_PRINT_ERR();

    exit(EXIT_FAILURE);
}

void _assert_free(cli_s *cli, bool expr, char *label) {
    if (expr)
        return;

    ASSERT_PRINT_ERR();

    freecli(cli);
    exit(EXIT_FAILURE);
}
