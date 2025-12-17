#pragma once

#include <ezcli/window.h>

/*
 * general rendering function signature.
 *
 * this is used to generalize `clicenter_vert` and `clicenter_both` by using
 * `c_printf` for the former, and `clicenter_horiz` for the latter
 * (internal utility in this header's source file).
 *
 * note: any centering utility only supports ascii. and it carries that
 * fact by assuming that one visual character is always one byte.
 *
 * this is linux-only.
 */
typedef void (*render_fn_t)(window_s, char *);

/*
 * this is a utility that prints a line or a block (single string seperated by
 * newlines) of text centered horizontally.
 *
 * note: any centering utility only supports ascii. and it carries that
 * fact by assuming that one visual character is always one byte.
 *
 * this is linux-only.
 */
void clicenter_horiz(window_s wininfo, char *str);

/*
 * this is a utility that prints a line or a block (single string seperated by
 * newlines) of text centered vertically.
 *
 * note: any centering utility only supports ascii. and it carries that
 * fact by assuming that one visual character is always one byte.
 *
 * this is linux-only.
 */
void clicenter_vert(window_s wininfo, char *str);

/*
 * this is a utility that prints a line or a block (single string seperated by
 * newlines) of text centered both vertically and horizontally.
 *
 * note: any centering utility only supports ascii. and it carries that
 * fact by assuming that one visual character is always one byte.
 *
 * this is linux-only.
 */
void clicenter_both(window_s wininfo, char *str);
