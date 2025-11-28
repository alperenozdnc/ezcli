#pragma once

#include <ezcli/opt.h>

#define CLI_VALIDATE_ELSE_NULLIFY(val) val ? val : NULL

void validate_opt(opt_s *opt);
