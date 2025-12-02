#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

/*
 * allocates an `opt_s` struct in heap and adds it to `cli->opts`.
 */
void allocopt(cli_s *cli, const opt_s *stack_opt);
