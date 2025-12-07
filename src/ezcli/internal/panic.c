#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>

#include "internal/panic.h"

ret_e panic() {
    CLI_DEBUG_ONLY(cliprint(CLI_WARN, "ezcli: ", "panicking"));

    if (CLI_MODE_LAIDBACK)
        return RET_WARN;

    return RET_FAIL;
}
