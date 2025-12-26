#pragma once

#include <test/integrity/sig_arena_s.h>
#include <test/integrity/sig_s.h>

/*
 * pushes a signal to a signal arena.
 */
void push_sig(sig_arena_s *arena, sig_s signal);
