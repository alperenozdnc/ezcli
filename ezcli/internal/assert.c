#include <ezcli/freecli.h>
#include <ezcli/platform.h>
#include <ezcli/print.h>

#include "internal/assert.h"

#include <stdbool.h>

void _assert(bool expr, char *label) {
    if (expr)
        return;

    ASSERT_PRINT_ERR();

    c_exit(EXIT_FAILURE);
}

void _assert_free(cli_s *cli, bool expr, char *label) {
    if (expr)
        return;

    ASSERT_PRINT_ERR();

    freecli(cli);
    c_exit(EXIT_FAILURE);
}
