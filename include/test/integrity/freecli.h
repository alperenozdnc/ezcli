#pragma once

#include <ezcli/cli.h>

#include <test/integrity/sig_arena_s.h>

void _freecli(cli_s *cli, sig_arena_s *arena);

#define freecli(cli) _freecli(cli, arena)
