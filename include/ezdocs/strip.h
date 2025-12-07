#pragma once

/*
 * strips a file extension 'ext' from string 'str'.
 * the dot at the beginning of the extension must be included.
 */
char *strip(char *str, char *ext);
