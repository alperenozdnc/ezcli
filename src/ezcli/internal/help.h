#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

/*
 * prints a help function that lists
 * usage,
 * description,
 * and information about options.
 */
void clihelp(cli_s *cli, opt_s **opts);
