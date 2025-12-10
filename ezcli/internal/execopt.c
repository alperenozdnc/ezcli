#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/gettok.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>

#include "internal/context.h"
#include "internal/execopt.h"
#include "internal/handle_common_opt.h"
#include "internal/handle_post_common_opt.h"

void _execopt(cli_s *cli, opt_s *opt, char *tok) {
    void *ctx = _CLI_CONTEXT(opt);

    handle_common_opt(cli, tok);

    CLI_DEBUG_ONLY(
        cliprint(CLI_HINT, "ezcli: ", "%s -> %s", gettok_offset(cli, 0), tok));

    opt->body(ctx, tok);

    handle_post_common_opt(cli, tok);
}
