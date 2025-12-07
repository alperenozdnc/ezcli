#pragma once

#include <ezcli/cli.h>

/*
 * gives approximately the closest option to an unrecognized input.
 */
char *recommend_opt(cli_s *cli, char *input);
