#pragma once

#include <ezcli/cli.h>
#include <stdbool.h>

#define TWO_TABS "        " // 8 spaces

// these define sections that get replaced by ezcli,
// you can see them for yourself in autocomp/.
#define CMD_NAME_CHAR '^'
#define OPTS_CHAR '>'

#define EZCLI_DIR "/.local/ezcli/"

void genautocomp(cli_s *cli, char *filename, bool bash, bool zsh);
