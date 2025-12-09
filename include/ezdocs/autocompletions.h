#pragma once

#include <ezcli.h>

#define AUTOCOMPLETIONS_PATH_BASH                                              \
    "/.local/share/bash-completion/completions/ezdocs"
#define AUTOCOMPLETIONS_PATH_ZSH "/.local/share/zsh/site-functions/_ezdocs"

/*
 * body of the 'autocomplete' option that generates autocompletions.
 */
ret_e _autocompletions(void *ctx, CLI_IGNORE_TOK);

/*
 * adds the 'autocomplete' option
 */
void _autocompletions_add(cli_s *cli);
