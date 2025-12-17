#pragma once

#ifdef CLI_EMBEDDED

#error "ezcli: printopts() is not available on embedded mode."

#endif // CLI_EMBEDDED

#include <ezcli/cli.h>

/*
 * prints all options with their values in cli->opts.
 *
 * this is linux-only.
 */
void printopts(cli_s *cli);
