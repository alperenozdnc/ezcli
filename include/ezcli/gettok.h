#pragma once

#include <ezcli/cli.h>
#include <limits.h>

#define CLI_TOK_FIRST INT_MIN
#define CLI_TOK_LAST INT_MAX

/*
 * gets the previously parsed token. if idx=1, returns `NULL`.
 */
char *gettok_prev(cli_s *cli);

/*
 * gets the next parsed token. if idx=end, returns `NULL`.
 */
char *gettok_next(cli_s *cli);

/*
 * offsets `n` from the current token's position. returns `NULL` if offset is
 * too little or too large.
 *
 * use `CLI_TOK_FIRST` as `n` for the first token in `argv`, and `CLI_TOK_LAST`
 * as `n` for the final token.
 */
char *gettok_offset(cli_s *cli, int n);
