#pragma once

#include <ezcli/cli.h>

/*
 * gets the previously parsed token. if idx=1, returns `NULL`.
 */
char *gettok_prev(cli_s *cli);

/*
 * gets the next parsed token. if idx=end, returns `NULL`.
 */
char *gettok_next(cli_s *cli);
