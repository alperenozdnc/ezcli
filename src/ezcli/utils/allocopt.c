#include <ezcli/addopt.h>
#include <ezcli/allocopt.h>
#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <stdlib.h>

void allocopt(cli_s *cli, const opt_s *opt_stack) {
    opt_s *opt = malloc(sizeof *opt);
    *opt = *opt_stack;

    opt->allocated = true;

    addopt(cli, opt);
}
