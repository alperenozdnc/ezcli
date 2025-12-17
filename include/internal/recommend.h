#pragma once

#ifdef CLI_EMBEDDED

#error "ezcli: recommend_opt() is not available on embedded mode."

#endif // CLI_EMBEDDED

#include <ezcli/cli.h>

/*
 * gives approximately the closest option to an unrecognized input.
 *
 * this is linux-only.
 */
char *recommend_opt(cli_s *cli, char *input);
