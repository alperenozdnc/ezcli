#pragma once

#include <ezcli/print.h>

#include <stdbool.h>

/*
 * allows for asking binary-answered questions. usually yes or no.
 * `msg` is the string that gets printed while waiting for input.
 * `yes_aliases` and `no_aliases` must be `NULL` terminated.
 * if `true`, `is_no_inclusive` counts every non-yes input as no.
 * if `false`, an error is thrown that states that the input is unknown.
 *
 * note: this function is NOT interactive in the sense that it doesn't keep
 * running after a wrong input, you should use this in a loop if you desire
 * that functionality.
 */
bool askbinary(char *msg, char **yes_aliases, char **no_aliases,
               bool is_no_inclusive);
