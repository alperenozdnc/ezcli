#pragma once

#include <ezcli/cli.h>

/*
 * handles common options. common options are options that are run before
 * every single successful option body execution.
 */
void handle_common_opt(cli_s *cli, char *tok);
