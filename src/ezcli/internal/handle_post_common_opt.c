#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include "handle_post_common_opt.h"
#include "match.h"

void handle_post_common_opt(cli_s *cli, void *ctx, char *tok) {
    opt_s *opt_post_common = oa_match_first(cli, CLI_POST_COMMON_OPT);

    if (opt_post_common)
        opt_post_common->body(ctx, tok);
}
