/*
    DISCLAIMER: this is a linux-only header.
*/

#ifndef CLI_EMBEDDED

#pragma once

#include <ezcli/cli.h>

/*
 * prints all options with their values in cli->opts.
 *
 * this is linux-only.
 */
void printopts(cli_s *cli);

#endif // CLI_EMBEDDED
