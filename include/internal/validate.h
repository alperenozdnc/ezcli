#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

#define VALIDATE_ELSE_NULLIFY(val) val ? val : NULL

/*
 * validates an option all all of its required fields.
 */
void validate_opt(cli_s *cli, opt_s *opt);
