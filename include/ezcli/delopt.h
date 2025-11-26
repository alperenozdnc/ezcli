#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

/*
 * deletes an option from the `opts` dynamic array in a `cli` struct.
 */
void delopt(struct cli *cli, struct opt *opt_d);
