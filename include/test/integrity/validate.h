#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <test/integrity/sig_arena_s.h>

#define VALIDATE_ELSE_NULLIFY(val) val ? val : NULL

void _validate_opt(cli_s *cli, opt_s *opt, sig_arena_s *arena);

#define validate_opt(cli, opt) _validate_opt(cli, opt, arena)
