#pragma once

#include <ezcli.h>

/*
 * body of common option for visually separating when more than one
 * subject is demanded at runtime.
 */
ret_e _section_categorizer(void *ctx, CLI_IGNORE_TOK);

/*
 * adds the common option which visually separates multiple subjects.
 */
void _section_categorizer_add(cli_s *cli);
