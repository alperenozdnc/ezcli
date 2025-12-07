#pragma once

#include <ezcli.h>

/*
 * frees all heap allocated memory.
 */
void cleanup(cli_s *cli, char *entries_path, char **entries);
