#include <ezcli/platform.h>
#include <ezcli/print.h>

#include "internal/check_ret.h"

/*
 * prints/exits appropriately for warnings/errors.
 */
void _check_ret(cli_s *cli, ret_e ret, bool *any_warnings) {
    if (ret == RET_FAIL) {
        cliprint(CLI_ERROR, cli->cmd, ": exited with an error.");

        c_exit(1);
    }

    if (ret == RET_WARN)
        *any_warnings = true;
}
