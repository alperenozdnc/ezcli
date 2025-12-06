#pragma once

#include <stdbool.h>

/*
 * setting for the laidback mode.
 * if set to true, all ezcli-created errors will be set as not a breaking point.
 */
extern bool CLI_MODE_LAIDBACK;

/*
 * setting for the allowing of non option-preceded arguments, (positional
 * options).
 * like `ls /home` where `/home` is the non option-preceded argument.
 * you should create an opt in `opts` that has alias `CLI_NONOPT` to handle
 * these inputs.
 * */
extern bool CLI_ALLOW_NONOPT;

/*
 * setting for the debug.
 * if set to true, all hints ezcli gives during parsing will be printing.
 */
extern bool CLI_MODE_DEBUG;

/*
 * setting for recommendation mode.
 * if set to true, ezcli will try to find recommendations for unrecognized
 * inputs and print them out for the user.
 */
extern bool CLI_MODE_RECOMMEND;
