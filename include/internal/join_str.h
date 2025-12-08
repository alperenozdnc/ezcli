#pragma once

/*
 * joins two strings using `snprintf()` and allocates on heap.
 * it's your responsibility to free the returned string.
 */
char *join_str(char *str1, char *str2);
