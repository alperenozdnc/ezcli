#pragma once

#include <ezcli/cli.h>

/*
 * handles post common options. post common options are options that are run
 * after every single successful option body execution.
 */
void handle_post_common_opt(cli_s *cli, void *ctx, char *tok);
