#pragma once

#ifdef CLI_EMBEDDED

#error "ezcli: allocopt() is not available on embedded mode."

#endif // CLI_EMBEDDED

#include <ezcli/cli.h>
#include <ezcli/opt.h>

/*
 * allocates an `opt_s` struct and all its stack-allocated fields
 * in heap and adds it to `cli->opts`.
 *
 * ezcli owns memory of all opts passed to `allocopt()`. your only
 * responsibility is to keep the `ctx` and `body` fields alive, and run
 * `freecli()` at the end of your program.
 *
 * this is linux-only.
 */
void allocopt(cli_s *cli, const opt_s *stack_opt);
