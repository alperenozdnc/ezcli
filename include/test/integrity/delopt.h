#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <test/integrity/sig_arena_s.h>

void _delopt(cli_s *cli, sig_arena_s *arena, ...);

#define delopt(cli, ...) _delopt(cli, arena, __VA_ARGS__, NULL)
