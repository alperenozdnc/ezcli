#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <stdbool.h>

/*
 * prints/exits appropriately for warnings/errors. this is local to `runcli()`
 * and the `check_ret` macro shouldn't be called anywhere else.
 */
void _check_ret(cli_s *cli, ret_e ret, bool *any_warnings);

#define check_ret(fn) _check_ret(cli, fn, &any_warnings)
