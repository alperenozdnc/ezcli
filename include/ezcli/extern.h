#pragma once

#include <stdbool.h>

/*
 * setting for the laidback mode.
 * if set to true, all ezcli-created errors will be set as not a breaking point.
 */
extern bool EZCLI_MODE_LAIDBACK;

/*
 * setting for the allowing of non option-preceded arguments, (positional
 * options).
 * like `ls /home` where `/home` is the non option-preceded argument.
 * you should create an opt in `opts` that has name `EZCLI_NONOPT` and type
 * `OPTION_BARE` to handle these inputs.
 * */
extern bool EZCLI_ALLOW_NONOPT;

/*
 * setting for the debug.
 * if set to true, all hints ezcli gives during parsing will be printing.
 */
extern bool EZCLI_MODE_DEBUG;
