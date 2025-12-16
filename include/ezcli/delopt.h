/*
    DISCLAIMER: this is a linux-only header.
*/

#ifndef CLI_EMBEDDED

#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

/*
 * deletes a variable amount of options from the `opts` dynamic array in a `cli`
 * struct.
 *
 * this is linux-only.
 */
void _delopt(cli_s *cli, ...);

#define delopt(cli, ...) _delopt(cli, __VA_ARGS__, NULL)

#endif // CLI_EMBEDDED
