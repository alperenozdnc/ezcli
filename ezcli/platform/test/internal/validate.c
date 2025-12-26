#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <test/integrity/assert.h>
#include <test/integrity/platform.h>
#include <test/integrity/sig_arena_s.h>
#include <test/integrity/validate.h>

#include "internal/blacklist.h"
#include "internal/match.h"

void _validate_opt(cli_s *cli, opt_s *opt, sig_arena_s *arena) {
    _assert_free(cli, opt->aliases && opt->aliases[0]);

    _assert_free(cli, opt->body);

    if (match_str(BLACKLIST, opt->aliases[0]))
        return;

    _assert_free(cli, opt->desc && c_strlen(opt->desc) > 0);
}
