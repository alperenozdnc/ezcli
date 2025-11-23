#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <stdbool.h>

/*
 * stands for option_token_match.
 * checks if the given token and option name match.
 */
bool ot_match(struct opt *opt, char *token);

/*
 * stands for option_token_match_any.
 * checks if the given token and any option names match. returns the option
 * if any matches are found.
 */
struct opt *ot_match_any(struct cli *cli, char *token);

/*
 * stands for option_match_non_option.
 * finds a 'non-option' (default) argument if it exists and returns `NULL` if it
 * doesn't
 */
struct opt *match_nonopt(struct cli *cli);

/*
 * checks if a string exists at least once inside of an array.
 */
bool match_str(char **arr, char *str);
