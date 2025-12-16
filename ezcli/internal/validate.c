#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/freecli.h>
#include <ezcli/opt.h>
#include <ezcli/platform.h>
#include <ezcli/print.h>

#include "internal/assert.h"
#include "internal/blacklist.h"
#include "internal/match.h"
#include "internal/validate.h"

void validate_opt(cli_s *cli, opt_s *opt) {
    CLI_DEBUG_ONLY(
        cliprint(CLI_HINT, "[ezcli] ", "validating opt %s", opt->aliases[0]));

    _assert_free(cli, opt->aliases && opt->aliases[0],
                 "an option must have at least one alias");

    _assert_free(cli, opt->body, "an option must have a body");

    if (match_str(BLACKLIST, opt->aliases[0]))
        return;

    _assert_free(cli, opt->desc && c_strlen(opt->desc) > 0,
                 "an option must have a description");
}
