#include <ezcli/opt.h>

#include "assert.h"
#include "match.h"
#include "validate.h"

#include <string.h>

void validate_opt(opt_s *opt) {
    char *blacklist[] = {CLI_NONOPT, CLI_DEFAULT_OPT, NULL};

    cliassert(opt->aliases && opt->aliases[0],
              "an option must have at least one alias");

    cliassert(opt->body, "an option must have a body");

    if (match_str(blacklist, opt->aliases[0]))
        return;

    cliassert(opt->desc && strlen(opt->desc) > 0,
              "an option must have a description");
}
