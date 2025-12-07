#include <ezcli/freecli.h>
#include <ezcli/print.h>

#include "internal/check_ret.h"

#include <stdlib.h>

/*
 * prints/exits appropriately for warnings/errors.
 */
void _check_ret(cli_s *cli, ret_e ret, bool *any_warnings) {
    if (ret == RET_FAIL) {
        cliprint(CLI_ERROR, CLI_EMPTY_PREFIX, "%s: exited with an error.",
                 cli->cmd);

        freecli(cli);

        exit(EXIT_FAILURE);
    }

    if (ret == RET_WARN)
        *any_warnings = true;
}
