#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>

#include "context.h"
#include "handle_post_common_opt.h"
#include "match.h"

void handle_post_common_opt(cli_s *cli, char *tok) {
    opt_s *opt_post_common = oa_match_first(cli, CLI_POST_COMMON_OPT);

    if (opt_post_common) {
        CLI_DEBUG_ONLY(cliprint(CLI_HINT, "[ezcli] ",
                                "executing post common opt -> %s", tok));

        opt_post_common->body(_CLI_CONTEXT(opt_post_common), tok);
    }
}
