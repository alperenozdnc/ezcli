/*
    DISCLAIMER: this is a linux-only header.
*/

#ifndef CLI_EMBEDDED

#pragma once

#include <sys/ioctl.h>
#include <unistd.h>

/* cryptic magic number that corresponds to getting the x and y axis
   for a terminal window using ioctl()

   not sure, but it might stand for:

   T--I--O--C--G-------WIN----SZ
   e  n  u  o  e    window  size
   r  p  t  n  t
   m  u  p  t
   i  t  t  r
   n        o
   a        l
   l

   this is linux-only.
*/
#define IOCTL_GET_WIN_SIZE TIOCGWINSZ

typedef unsigned short window_size_t;

/*
 * keeps the length information for the current terminal window.
 *
 * `window_size_t` stands for `unsigned short`.
 *
 * `x` and `y` are the column and row sizes respectively, assuming one character
 * or newline as the unit.
 *
 * this is linux-only.
 */
typedef struct {
    window_size_t x;
    window_size_t y;
} window_s;

/*
 * gets information about the sizes of the current
 * terminal window and returns it in a `window_s` struct.
 *
 * the info is `ioctl()` sourced, so the info is neither ezcli nor user owned.
 *
 * this is linux-only.
 */
window_s cliwininfo();

#endif // CLI_EMBEDDED
