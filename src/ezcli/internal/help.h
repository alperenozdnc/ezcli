#ifndef EZCLI_HELP_H
#define EZCLI_HELP_H

#include <ezcli/cli.h>
#include <ezcli/opt.h>

/*
 * prints a help function that lists
 * usage,
 * description,
 * and information about options.
 */
void cli_help(struct cli *cli, struct opt **opts);

#endif
