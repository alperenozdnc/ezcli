/*
    DISCLAIMER: this is a linux-only header.
*/

#ifndef CLI_EMBEDDED

#pragma once

#include <ezcli/cli.h>

/*
 * frees all internally allocated memory.
 *
 * this is linux-only.
 */
void freecli(cli_s *cli);

#endif // CLI_EMBEDDED
