#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include "free_heap_opt.h"

#include <stdlib.h>

void free_heap_opt(opt_s *opt) {
    int i = 0;

    while (opt->aliases[i]) {
        free(opt->aliases[i]);

        i++;
    }

    free(opt->aliases);

    if (opt->desc)
        free(opt->desc);

    free(opt);
}
