#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/gettok.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>

#include "context.h"
#include "execopt.h"
#include "handle_common_opt.h"
#include "handle_post_common_opt.h"

void _execopt(cli_s *cli, opt_s *opt, char *tok) {
    void *ctx = _CLI_CONTEXT(opt);

    CLI_DEBUG_ONLY(
        cliprint(CLI_HINT, "[ezcli] ", "executing common opt -> %s", tok));

    handle_common_opt(cli, ctx, tok);

    CLI_DEBUG_ONLY(
        cliprint(CLI_HINT, "ezcli: ", "%s -> %s", gettok_offset(cli, 0), tok));

    opt->body(ctx, tok);

    CLI_DEBUG_ONLY(
        cliprint(CLI_HINT, "[ezcli] ", "executing post common opt -> %s", tok));

    handle_post_common_opt(cli, ctx, tok);
}
