#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <stdbool.h>

/*
 * handles non-optional (positional) arguments. if true, a `continue` keyword
 * should be thrown, and if false, the program should continue normally.
 */
bool handle_nonopt(struct cli *cli, char *tok, bool is_unrecog,
                   bool any_option_seen);
