
#pragma once

#include <ezcli.h>

/*
 * body of 'version' option printing ezcli's version.
 */
ret_e _version(CLI_IGNORE_ARGS);

/*
 * adds option 'version'.
 */
void _version_add(cli_s *cli);
