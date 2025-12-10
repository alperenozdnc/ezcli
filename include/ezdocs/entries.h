#pragma once

#include <ezcli.h>

/*
 * adds all entries dynamically in `ezdocs/content`.
 */
void _entry_opts_add(char *entries_path, char **entries, cli_s *cli);
