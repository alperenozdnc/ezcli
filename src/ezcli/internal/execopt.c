#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include "context.h"
#include "execopt.h"
#include "handle_common_opt.h"
#include "handle_post_common_opt.h"

void _execopt(cli_s *cli, opt_s *opt, char *tok) {
    void *ctx = _CLI_CONTEXT(opt);

    handle_common_opt(cli, ctx, tok);
    opt->body(ctx, tok);
    handle_post_common_opt(cli, ctx, tok);
}
