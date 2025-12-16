/*
    DISCLAIMER: this is a linux-only header.
*/

#pragma once

#include <ezcli/cli.h>

#ifndef CLI_EMBEDDED

/*
 * gives approximately the closest option to an unrecognized input.
 *
 * this is linux-only.
 */
char *recommend_opt(cli_s *cli, char *input);

#endif // CLI_EMBEDDED
