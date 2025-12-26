#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <test/integrity/sig_arena_s.h>

void _allocopt(cli_s *cli, const opt_s *stack_opt, sig_arena_s *arena);

#define allocopt(cli, opt) _allocopt(cli, opt, arena)
