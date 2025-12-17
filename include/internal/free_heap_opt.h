#pragma once

#ifdef CLI_EMBEDDED

#error "ezcli: free_heap_opt() is not available on embedded."

#endif // CLI_EMBEDDED

#include <ezcli/cli.h>
#include <ezcli/opt.h>

/*
 * frees a heap-allocated `opt_s` struct and all its
 * allocated fields.
 *
 * this is linux-only.
 */
void free_heap_opt(opt_s *opt);
