#pragma once

#ifdef CLI_EMBEDDED

#error "ezcli: help() is not available on embedded mode."

#endif // CLI_EMBEDDED

#include <ezcli/cli.h>
#include <ezcli/opt.h>

/*
 * prints a help function that lists
 * usage,
 * description,
 * and information about options.
 *
 * this is linux-only.
 */
void help(cli_s *cli, opt_s **opts);
