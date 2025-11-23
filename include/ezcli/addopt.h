#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

/*
 * adds an option to the `opts` dynamic array in a `cli` struct.
 */
void addopt(struct cli *cli, struct opt *opt_a);
