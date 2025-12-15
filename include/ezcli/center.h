#pragma once

#include <ezcli/window.h>

/*
 * general rendering function signature.
 *
 * this is used to generalize `clicenter_vert` and `clicenter_both` by using
 * `c_printf` for the former, and `clicenter_horiz_line` for the latter
 * (internal utility in this header's source file).
 */
typedef void (*render_fn_t)(window_s, char *);

/*
 * this is a utility that prints a line or a block (single string seperated by
 * newlines) of text centered horizontally.
 */
void clicenter_horiz(window_s wininfo, char *str);

/*
 * this is a utility that prints a line or a block (single string seperated by
 * newlines) of text centered vertically.
 */
void clicenter_vert(window_s wininfo, char *str);

/*
 * this is a utility that prints a line or a block (single string seperated by
 * newlines) of text centered both vertically and horizontally.
 */
void clicenter_both(window_s wininfo, char *str);
