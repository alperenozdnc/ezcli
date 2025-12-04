#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

/*
 * frees a heap-allocated `opt_s` struct and all its
 * allocated fields.
 */
void free_heap_opt(opt_s *opt);
