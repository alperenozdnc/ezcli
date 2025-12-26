#pragma once

#include <test/integrity/sig_arena_s.h>
#include <test/integrity/sig_s.h>

void _emit_signal(sig_arena_s *arena, sig_type_e type, uint16_t line,
                  char *file);

#define emit_signal(type) _emit_signal(arena, type, __LINE__, __FILE__)

#define emit_signal_verbose(type, line, file)                                  \
    _emit_signal(arena, type, line, file)
