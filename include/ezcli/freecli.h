#pragma once

#include <ezcli/cli.h>

/*
 * frees all internally allocated memory.
 *
 * this is linux-only.
 */
void freecli(cli_s *cli);
