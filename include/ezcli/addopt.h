#pragma once

#ifdef CLI_EMBEDDED

#error "ezcli: addopt() is not available on embedded mode."

#endif // CLI_EMBEDDED

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
