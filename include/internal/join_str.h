#pragma once

#ifdef CLI_EMBEDDED

#error "ezcli: join_str() is not available on embedded mode."

#endif // CLI_EMBEDDED

/*
 * joins two strings using `snprintf()` and allocates on heap.
 * it's your responsibility to free the returned string.
 *
 * this is linux-only.
 */
char *join_str(char *str1, char *str2);
