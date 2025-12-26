#pragma once

#include <ezcli/cli.h>

#include <test/integrity/sig_arena_s.h>

#include <stdbool.h>

void __assert(bool expr, sig_arena_s *arena);
void __assert_free(cli_s *cli, bool expr, sig_arena_s *arena);

#define _assert(expr) __assert(expr, arena)
#define _assert_free(cli, expr) __assert_free(cli, expr, arena)
