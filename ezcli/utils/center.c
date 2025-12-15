#include <ezcli/center.h>
#include <ezcli/platform.h>
#include <ezcli/window.h>

#include "internal/match.h"

/*
 * this is a neat little hack so that the `c_printf` signature fits the
 * signature type `render_fn_t` found in `include/ezcli/center.h`.
 */
void renderer_printf(__attribute((unused)) window_s wininfo, char *str) {
    c_printf("%s", str);
}

/*
 * this is the building block of the actual utility `clicenter_horiz` that
 * prints one and only one line horizontally centered.
 */
void clicenter_horiz_line(window_s wininfo, char *str, size_t len_str) {
    int len_left_pad = (wininfo.x - len_str) / 2;
    int len_right_pad = wininfo.x - (len_left_pad + len_str);

    if (len_str == 0) {
        c_printf("\n");

        return;
    }

    // +2 is for at least once space on left and right
    if (wininfo.x < (len_str + 2)) {
        len_left_pad = 0;
        len_right_pad = 0;
    }

    c_printf("%*s%s%*s", len_left_pad, " ", str, len_right_pad, " ");
}

void clicenter_horiz(window_s wininfo, char *str) {
    size_t len_str = c_strlen(str);

    int line_count = match_str_newlines(str) + 1;

    if (line_count == 1)
        return clicenter_horiz_line(wininfo, str, len_str);

    char buffer[len_str];

    size_t buffer_idx = 0;

    for (size_t i = 0; i < len_str; i++) {
        char c = str[i];

        if (c == '\n' || i == len_str - 1) {
            buffer[buffer_idx] = '\0';

            clicenter_horiz_line(wininfo, buffer, buffer_idx);

            c_printf("\n");

            buffer_idx = 0;

            continue;
        }

        buffer[buffer_idx++] = c;
    }
}

/*
 * this is just a renderer-agnostic (`c_printf` vs `clicenter_horiz`)
 * generalization of the `clicenter_vert` utility. it's used for
 * `clicenter_vert`, and `clicenter_both`.
 */
void clicenter_vert_renderer(window_s wininfo, char *str, render_fn_t render) {
    int height_str = match_str_newlines(str) + 1;

    int len_upper_pad = (wininfo.y - height_str) / 2;
    int len_lower_pad = (wininfo.y - height_str) - len_upper_pad;

    for (int i = 0; i < len_upper_pad; i++) {
        c_printf("\n");
    }

    render(wininfo, str);

    for (int i = 0; i < len_lower_pad; i++) {
        c_printf("\n");
    }
}

void clicenter_vert(window_s wininfo, char *str) {
    clicenter_vert_renderer(wininfo, str, renderer_printf);
}

void clicenter_both(window_s wininfo, char *str) {
    clicenter_vert_renderer(wininfo, str, clicenter_horiz);
}
