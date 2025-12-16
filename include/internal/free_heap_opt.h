/*
    DISCLAIMER: this is a linux-only header.
*/

#ifndef CLI_EMBEDDED

#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

/*
 * frees a heap-allocated `opt_s` struct and all its
 * allocated fields.
 *
 * this is linux-only.
 */
void free_heap_opt(opt_s *opt);

#endif // CLI_EMBEDDED
