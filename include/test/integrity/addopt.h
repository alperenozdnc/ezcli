#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <test/integrity/sig_arena_s.h>

void _addopt(cli_s *cli, sig_arena_s *arena, ...);

#define addopt(cli, ...) _addopt(cli, arena, __VA_ARGS__, NULL)
