#pragma once

#include "internal/validate.h"

#define _CLI_CONTEXT(opt) VALIDATE_ELSE_NULLIFY(opt->ctx)
