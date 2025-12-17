#pragma once

#ifdef CLI_EMBEDDED

#error "ezcli: printaliases() is not available on embedded mode."

#endif // CLI_EMBEDDED

/*
 * prints at most 3 aliases for an option. color is blue and the separator is
 *
 * this is linux-only.
 * '->'.
 */
void printaliases(char **aliases);
