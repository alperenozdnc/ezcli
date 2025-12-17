#pragma once

#ifdef CLI_EMBEDDED

#error "ezcli: autocomp() is not available on embedded mode."

#endif // CLI_EMBEDDED

#include <ezcli/cli.h>
#include <stdbool.h>

#define TWO_TABS "        " // 8 spaces

// these define sections that get replaced by ezcli,
// you can see them for yourself in autocomp/.
#define CMD_NAME_CHAR '^'
#define OPTS_CHAR '>'

#define EZCLI_DIR "/.local/ezcli/"

/*
 * generates autocompletions based on `cli->opts` and `cli->cmd` and puts them
 * in the current working directory.
 *
 * `filename` should have no extensions.
 * `bool bash` generates completions for bash if `true`.
 * `bool zsh` generates completions for zsh if `true`.
 *
 * this is linux-only.
 */
void genautocomp(cli_s *cli, char *filename, bool bash, bool zsh);
