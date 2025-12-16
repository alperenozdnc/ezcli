/*
    DISCLAIMER: this is a linux-only header.
*/

#ifndef CLI_EMBEDDED

#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

/*
 * adds a variable amount of options to the `opts` dynamic array in a `cli`
 * struct.
 *
 * this is linux-only.
 */
void _addopt(cli_s *cli, ...);

#define addopt(cli, ...) _addopt(cli, __VA_ARGS__, NULL)

#endif // CLI_EMBEDDED
