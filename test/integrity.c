#include <test/integrity/integrity.h>

#include <ezcli/print.h>
#include <test/integrity/free_sig_arena.h>
#include <test/integrity/freecli.h>
#include <test/integrity/init_sig_arena.h>
#include <test/integrity/initcli.h>
#include <test/integrity/runcli.h>
#include <test/integrity/sig_arena_s.h>

#include <stdio.h>
#include <stdlib.h>

void print_signals(bool use_arena, sig_arena_s *arena, sig_type_e sigs[],
                   size_t sigs_size) {
    size_t size = use_arena ? arena->signals_size : sigs_size;

    printf("{ ");

    for (size_t i = 0; i < size; i++) {
        char *sig =
            use_arena ? sig_names[arena->signals[i]->type] : sig_names[sigs[i]];

        if (i == size - 1) {
            printf("%s", sig);

            break;
        }

        printf("%s, ", sig);
    }

    printf(" }");
}

void compare_signals(sig_type_e assert_sigs[], size_t assert_size,
                     sig_arena_s *arena) {
    wrap_with_label("test/integrity: expected: ",
                    print_signals_asserted(assert_sigs, assert_size));

    wrap_with_label("test/integrity: got: ", print_signals_arena());
}

/*
 * compares a given list of asserted signals and the actual emitted signals
 * which are taken from a given arena.
 */
void _assert_signals(sig_type_e sigs[], size_t assert_size,
                     sig_arena_s *arena) {
    if (assert_size != arena->signals_size) {
        fprintf(stderr, "\ntest/integrity: wrong amount of signals emitted.\n");

        compare_signals(sigs, assert_size, arena);

        exit(EXIT_FAILURE);
    }

    bool signals_match = true;

    for (size_t i = 0; i < arena->signals_size; i++) {
        sig_type_e assert_sig_type = sigs[i];
        sig_type_e actual_sig_type = arena->signals[i]->type;

        if (assert_sig_type != actual_sig_type) {
            signals_match = false;

            printf("\ntest/integrity: discrepancy found after signal '%s'\n"
                   "emitted (%s:%d).\n\n",
                   sig_names[arena->signals[i]->type], arena->signals[i]->file,
                   arena->signals[i]->line);

            break;
        }
    }

    if (!signals_match) {
        compare_signals(sigs, assert_size, arena);

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
    BEGIN_TEST(CLI_NO_OPTS, "base");

    sig_type_e signals[] = {CLI_SIG_INIT_SELF, CLI_SIG_FREE_SELF};

    END_TEST(signals);
}
