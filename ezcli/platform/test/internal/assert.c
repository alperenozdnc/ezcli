#include <ezcli/cli.h>

#include <test/integrity/emit_signal.h>
#include <test/integrity/freecli.h>
#include <test/integrity/platform.h>
#include <test/integrity/sig_arena_s.h>

#include <stdbool.h>

void __assert(bool expr, sig_arena_s *arena) {
    if (expr)
        return;

    emit_signal(CLI_SIG_PRINT_ERR);

    c_exit(EXIT_FAILURE);
}

void __assert_free(cli_s *cli, bool expr, sig_arena_s *arena) {
    if (expr)
        return;

    freecli(cli);

    c_exit(EXIT_FAILURE);
}
