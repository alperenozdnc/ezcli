#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include "handle_common_opt.h"
#include "match.h"

void handle_common_opt(cli_s *cli, void *ctx, char *tok) {
    opt_s *opt_common = oa_match_first(cli, CLI_COMMON_OPT);

    if (!opt_common)
        return;

    opt_common->body(ctx, tok);
}
