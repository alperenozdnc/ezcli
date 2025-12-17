#pragma once

#include <ezcli/cli.h>

/*
 * prints all options with their values in cli->opts.
 *
 * this is linux-only.
 */
void printopts(cli_s *cli);
