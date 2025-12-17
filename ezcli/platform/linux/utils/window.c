#include <ezcli/window.h>

window_s cliwininfo() {
    struct winsize winsize_s;

    ioctl(STDOUT_FILENO, IOCTL_GET_WIN_SIZE, &winsize_s);

    window_s win_info = {
        .x = winsize_s.ws_col,
        .y = winsize_s.ws_row,
    };

    return win_info;
}
