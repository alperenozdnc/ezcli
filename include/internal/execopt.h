#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

/*
 * handles the common option, the post common option, and the option body
 * execution for a single option.
 */
void _execopt(cli_s *cli, opt_s *opt, char *tok);

/*
 * this macro just inserts the repeated cli input into _execopt().
 * don't use if you don't have 'cli' as 'cli_s' in your local scope.
 */
#define execopt(opt, tok) _execopt(cli, opt, tok)
