/*
    DISCLAIMER: this is a linux-only header.
*/

#ifndef CLI_EMBEDDED

#pragma once

#include <ezcli/window.h>

/*
 * general rendering function signature.
 *
 * this is used to generalize `clicenter_vert` and `clicenter_both` by using
 * `c_printf` for the former, and `clicenter_horiz` for the latter
 * (internal utility in this header's source file).
 *
 * this is linux-only.
 */
typedef void (*render_fn_t)(window_s, char *);

/*
 * this is a utility that prints a line or a block (single string seperated by
 * newlines) of text centered horizontally.
 *
 * this is linux-only.
 */
void clicenter_horiz(window_s wininfo, char *str);

/*
 * this is a utility that prints a line or a block (single string seperated by
 * newlines) of text centered vertically.
 *
 * this is linux-only.
 */
void clicenter_vert(window_s wininfo, char *str);

/*
 * this is a utility that prints a line or a block (single string seperated by
 * newlines) of text centered both vertically and horizontally.
 *
 * this is linux-only.
 */
void clicenter_both(window_s wininfo, char *str);

#endif // CLI_EMBEDDED
