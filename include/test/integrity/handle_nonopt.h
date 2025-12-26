#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <test/integrity/sig_arena_s.h>

#include <stdbool.h>

bool handle_nonopt(cli_s *cli, bool is_unrecog, bool any_option_seen,
                   sig_arena_s *arena);
