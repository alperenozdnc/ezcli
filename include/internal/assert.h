#pragma once

#include <ezcli/cli.h>

#include <stdbool.h>

#define ASSERT_PRINT_ERR()                                                     \
    cliprint(CLI_ERROR, "[ezcli] assertion failed: ", "%s\n", label)

/*
 * prints `label` and exits with failure if `expr` is `false`.
 */
void _assert(bool expr, char *label);

/*
 * prints `label`, frees all allocated memory, and exits with failure
 * if `expr` is `false`.
 *
 * this is linux-only.
 */
void _assert_free(cli_s *cli, bool expr, char *label);
