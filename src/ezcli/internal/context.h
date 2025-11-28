#pragma once

#include "validate.h"

#define _CLI_CONTEXT(opt) CLI_VALIDATE_ELSE_NULLIFY(opt->ctx)
