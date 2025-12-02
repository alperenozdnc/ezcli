#include <ezcli.h>

#include "../func/print_docfile.h"

ret_e doc_body(void *ctx, CLI_IGNORE_TOK) {
    cli_s *cli = ctx;
    char *curr_tok = gettok_offset(cli, 0);

    print_docfile(curr_tok);

    return RET_NORMAL;
}
