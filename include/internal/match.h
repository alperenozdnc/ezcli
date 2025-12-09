#pragma once

#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <stdbool.h>

/*
 * stands for option_token_match.
 * checks if the given token and option name match.
 */
bool ot_match(opt_s *opt, char *token);

/*
 * stands for option_token_match_any.
 * checks if the given token and any option aliases match. returns the option
 * if any matches are found.
 */
opt_s *ot_match_any(cli_s *cli, char *token);

/*
 * stands for option_alias_match_first.
 * checks if the given alias and one of any option's first alias and only
 * first alias match. returns the option if any does, returns `NULL` if it
 * doesn't. this is saves the cost of looping through every alias for special
 * options.
 */
opt_s *oa_match_first(cli_s *cli, char *alias);

/*
 * checks if a string exists at least once inside of an array.
 */
bool match_str(char **arr, char *str);

/*
 * checks if a string `*str` contains an inner string `*inner`.
 */
bool match_str_contains(char *str, char *inner);
