#ifndef EZCLI_FREECLI_H
#define EZCLI_FREECLI_H

#include <ezcli/cli.h>

/*
 * frees all allocated memory. this is the only function you need to
 * run for cleanup.
 */
void freecli(struct cli *cli_p);

#endif
