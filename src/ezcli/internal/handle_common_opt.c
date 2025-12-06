#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>

#include "context.h"
#include "handle_common_opt.h"
#include "match.h"

void handle_common_opt(cli_s *cli, char *tok) {
    opt_s *opt_common = oa_match_first(cli, CLI_COMMON_OPT);

    if (opt_common) {
        CLI_DEBUG_ONLY(
            cliprint(CLI_HINT, "[ezcli] ", "executing common opt -> %s", tok));

        opt_common->body(_CLI_CONTEXT(opt_common), tok);
    }
}
