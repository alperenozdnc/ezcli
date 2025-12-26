#include <test/integrity/integrity.h>

#include <test/integrity/free_sig_arena.h>
#include <test/integrity/freecli.h>
#include <test/integrity/init_sig_arena.h>
#include <test/integrity/initcli.h>
#include <test/integrity/runcli.h>
#include <test/integrity/sig_arena_s.h>

#include <stdio.h>
#include <stdlib.h>

/*
 * compares a given list of asserted signals and the actual emitted signals
 * which are taken from a given arena.
 */
void _assert_signals(sig_type_e sigs[], size_t assert_size,
                     sig_arena_s *arena) {
    if (assert_size != arena->signals_size) {
        fprintf(stderr, "wrong amount of signals emitted.");
        exit(EXIT_FAILURE);
    }

    bool signals_match = true;

    for (size_t i = 0; i < arena->signals_size; i++) {
        sig_type_e assert_sig_type = sigs[i];
        sig_type_e actual_sig_type = arena->signals[i]->type;

        if (assert_sig_type != actual_sig_type) {
            signals_match = false;

            break;
        }
    }

    if (!signals_match) {
        fprintf(stderr, "wrong signals emitted.\n");
        exit(EXIT_FAILURE);
    }
}

/*
 * injects a synthetic `argv` array into `runcli()` using a provided `cli_s`
 * and `sig_arena_s` instance.
 */
void exec_inj_args(cli_s *cli, sig_arena_s *arena, char *argv[]) {
    size_t argc = 0;

    while (argv[argc])
        argc++;

    runcli(cli, argc, argv);

    cli->tok_idx = 0;
}

int main() {
    BEGIN_TEST(CLI_NO_OPTS);

    sig_type_e signals[] = {CLI_SIG_INIT_SELF};
    assert_signals(signals);

    END_TEST;
}
