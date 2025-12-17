#pragma once

#ifdef CLI_EMBEDDED

#error "ezcli: freecli() is not available on embedded mode."

#endif // CLI_EMBEDDED

#include <ezcli/cli.h>

/*
 * frees all internally allocated memory.
 *
 * this is linux-only.
 */
void freecli(cli_s *cli);
