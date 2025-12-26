#pragma once

#include <ezcli/cli.h>

#include <test/integrity/sig_arena_s.h>

void _runcli(cli_s *cli_p, int argc, char *argv[], sig_arena_s *arena);

#define runcli(cli, argc, argv) _runcli(cli, argc, argv, arena)
