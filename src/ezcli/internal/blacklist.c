#include <ezcli/opt.h>

#include "internal/blacklist.h"

#include <stddef.h>

char *BLACKLIST[] = {CLI_NONOPT, CLI_DEFAULT_OPT, CLI_COMMON_OPT,
                     CLI_POST_COMMON_OPT, NULL};
