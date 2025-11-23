#pragma once

#include <ezcli/opt.h>

/*
 * prefixes required amount of hyphens to `opt->name` and returns the result.
 * responsibility of freeing is with the caller.
 */
char *expand(struct opt *opt);
