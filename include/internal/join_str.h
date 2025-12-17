#pragma once

/*
 * joins two strings using `snprintf()` and allocates on heap.
 * it's your responsibility to free the returned string.
 *
 * this is linux-only.
 */
char *join_str(char *str1, char *str2);
