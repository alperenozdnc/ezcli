#include <ezcli/cli.h>
#include <ezcli/freecli.h>
#include <ezcli/opt.h>

#include "assert.h"
#include "match.h"
#include "validate.h"

#include <string.h>

void validate_opt(cli_s *cli, opt_s *opt) {
    char *blacklist[] = {CLI_NONOPT, CLI_DEFAULT_OPT, CLI_COMMON_OPT, NULL};

    _assert_free(cli, opt->aliases && opt->aliases[0],
                 "an option must have at least one alias");

    _assert_free(cli, opt->body, "an option must have a body");

    if (match_str(blacklist, opt->aliases[0]))
        return;

    _assert_free(cli, opt->desc && strlen(opt->desc) > 0,
                 "an option must have a description");
}
