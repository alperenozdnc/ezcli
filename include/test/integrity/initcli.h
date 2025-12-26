#pragma once

#include <ezcli/cli.h>

#include <test/integrity/sig_arena_s.h>

#include <stdbool.h>

void initcli(cli_s *cli, char *cmd, char *desc, char *usage, char *footer,
             opt_s **opts, char *help_aliases[], sig_arena_s *arena);
