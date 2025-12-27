#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/opt.h>

#include <test/integrity/integrity.h>

#include <test/integrity/addopt.h>
#include <test/integrity/delopt.h>
#include <test/integrity/free_sig_arena.h>
#include <test/integrity/freecli.h>
#include <test/integrity/init_sig_arena.h>
#include <test/integrity/initcli.h>
#include <test/integrity/runcli.h>
#include <test/integrity/sig_arena_s.h>

#include <stdio.h>
#include <stdlib.h>

/*
 * prints signals in an array-like format `{ a, b, c, d }`.
 * accepts either an arena or an array of signal types as its source of data.
 * `use_arena` can be flipped `true` or `false` to determine behaviour.
 */
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

/*
 * prints the expected and the actual array of signals, only triggers if a
 * discrepancy is found.
 */
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

/*
 * test: base case.
 *
 * baseline behaviour with no opts.
 */
void test_base() {
    sig_type_e signals[] = {CLI_SIG_INIT_SELF, CLI_SIG_FREE_SELF};

    BEGIN_TEST(CLI_NO_OPTS, "base");
    END_TEST(signals);
}

/*
 * test: help case.
 *
 * baseline behaviour with the help alias inputted.
 */
void test_help() {
    sig_type_e signals[] = {CLI_SIG_INIT_SELF, CLI_SIG_EXEC_HELP_OPT,
                            CLI_SIG_FREE_SELF};

    BEGIN_TEST(CLI_NO_OPTS, "help");

    exec_inj_args(&cli, arena, (char *[]){"test", "help", NULL});

    END_TEST(signals);
}

DUMMY_BODY();

/*
 * test: 'initializing option' case.
 *
 * behaviour of adding an option.
 */
void test_init_opt() {
    sig_type_e signals[] = {CLI_SIG_INIT_SELF, CLI_SIG_INIT_OPT,
                            CLI_SIG_FREE_SELF};

    BEGIN_TEST(CLI_NO_OPTS, "initopt");

    opt_s dummy = DUMMY_OPT;
    addopt(&cli, &dummy);

    END_TEST(signals);
}

/*
 * test: 'initializing and deleting option' case.
 *
 * behaviour of adding and deleting an option.
 */
void test_init_del_opt() {
    sig_type_e signals[] = {CLI_SIG_INIT_SELF, CLI_SIG_INIT_OPT,
                            CLI_SIG_DEL_OPT, CLI_SIG_FREE_SELF};

    BEGIN_TEST(CLI_NO_OPTS, "delopt");

    opt_s dummy = DUMMY_OPT;

    addopt(&cli, &dummy);
    delopt(&cli, &dummy);

    END_TEST(signals);
}

/*
 * test: 'deleting a non-existent option' case.
 *
 * behaviour of adding and deleting an option.
 */
void test_del_nonexistent_opt() {
    sig_type_e signals[] = {CLI_SIG_INIT_SELF, CLI_SIG_WARN_DEL_NONEXISTENT_OPT,
                            CLI_SIG_FREE_SELF};

    BEGIN_TEST(CLI_NO_OPTS, "delnonexistentopt");

    opt_s dummy = DUMMY_OPT;

    delopt(&cli, &dummy);

    END_TEST(signals);
}

/*
 * test: 'executing an option with no input' case.
 *
 * behaviour of executing an option.
 */
void test_run_opt() {
    sig_type_e signals[] = {CLI_SIG_INIT_SELF, CLI_SIG_EXEC_PARSED_OPT_NO_TOK,
                            CLI_SIG_FREE_SELF};

    opt_s dummy = DUMMY_OPT;
    opt_s *opts[] = {&dummy, NULL};

    BEGIN_TEST(opts, "execoptnoinput");

    exec_inj_args(&cli, arena, (char *[]){"test", "dummy", NULL});

    END_TEST(signals);
}

/*
 * test: 'executing an option with input' case.
 *
 * behaviour of executing an option.
 */
void test_run_opt_with_input() {
    sig_type_e signals[] = {CLI_SIG_INIT_SELF, CLI_SIG_EXEC_PARSED_OPT,
                            CLI_SIG_CONSUME_TOK, CLI_SIG_FREE_SELF};

    opt_s dummy = DUMMY_OPT;
    dummy.want_input = true;

    opt_s *opts[] = {&dummy, NULL};

    BEGIN_TEST(opts, "execoptwithinput");

    exec_inj_args(&cli, arena, (char *[]){"test", "dummy", "input", NULL});

    END_TEST(signals);
}

/*
 * test: 'executing an option with input but it wants an input' case.
 *
 * behaviour of executing an option but not respecting its `want_input` value.
 */
void test_run_opt_with_no_input_but_wants_input_is_true() {
    CLI_MODE_LAIDBACK = true;

    sig_type_e signals[] = {CLI_SIG_INIT_SELF,
                            CLI_SIG_ERR_NOT_PASS_BUT_WANT_ARGS,
                            CLI_SIG_FREE_SELF};

    opt_s dummy = DUMMY_OPT;
    dummy.want_input = true;

    opt_s *opts[] = {&dummy, NULL};

    BEGIN_TEST(opts, "execoptwithnoinputbutinputisrequired");

    exec_inj_args(&cli, arena, (char *[]){"test", "dummy", NULL});

    END_TEST(signals);

    CLI_MODE_LAIDBACK = false;
}

/*
 * test: 'executing an option with input but doesnt want an input' case.
 *
 * behaviour of executing an option but not respecting its `want_input` value.
 */
void test_run_opt_with_input_but_wants_input_is_false() {
    CLI_MODE_LAIDBACK = true;

    sig_type_e signals[] = {CLI_SIG_INIT_SELF, CLI_SIG_EXEC_PARSED_OPT_NO_TOK,
                            CLI_SIG_ERR_PASS_NO_WANT_ARGS, CLI_SIG_FREE_SELF};

    opt_s dummy = DUMMY_OPT;
    dummy.want_input = false;

    opt_s *opts[] = {&dummy, NULL};

    BEGIN_TEST(opts, "execoptwithinputbutinputisforbidden");

    exec_inj_args(&cli, arena, (char *[]){"test", "dummy", "input", NULL});

    END_TEST(signals);

    CLI_MODE_LAIDBACK = false;
}

/*
 * test: 'trying to execute an unrecognized token' case.
 *
 * behaviour of executing an unrecognized token as an option.
 */
void test_run_unrecognized_tok() {
    CLI_MODE_LAIDBACK = true;

    sig_type_e signals[] = {CLI_SIG_INIT_SELF, CLI_SIG_ERR_UNRECOG_ARG,
                            CLI_SIG_EXIT, CLI_SIG_FREE_SELF};

    opt_s dummy = DUMMY_OPT;
    dummy.want_input = true;

    opt_s *opts[] = {&dummy, NULL};

    BEGIN_TEST(opts, "execunrecognizedtok");

    exec_inj_args(&cli, arena, (char *[]){"test", "dommy", NULL});

    END_TEST(signals);

    CLI_MODE_LAIDBACK = false;
}

/*
 * test: 'trying to execute an option immediately after an option that wants
 * input' case. it's unallowed 'argument' and not 'token' because the parser
 * tries to understand the second option as an argument but fails to do so.
 *
 * behaviour of executing an unallowed argument.
 */
void test_run_unallowed_tok() {
    CLI_MODE_LAIDBACK = true;
    sig_type_e signals[] = {CLI_SIG_INIT_SELF, CLI_SIG_ERR_UNALLOWED_ARG,
                            CLI_SIG_ERR_NOT_PASS_BUT_WANT_ARGS,
                            CLI_SIG_FREE_SELF};

    opt_s dummy = DUMMY_OPT;
    dummy.want_input = true;

    opt_s *opts[] = {&dummy, NULL};

    BEGIN_TEST(opts, "execunallowedarg");

    exec_inj_args(&cli, arena, (char *[]){"test", "dummy", "dummy", NULL});

    END_TEST(signals);

    CLI_MODE_LAIDBACK = false;
}

/*
 * test: 'executing a nonopt' case.
 *
 * behaviour of executing a nonopt.
 */
void test_run_nonopt() {
    CLI_ALLOW_NONOPT = true;

    sig_type_e signals[] = {CLI_SIG_INIT_SELF, CLI_SIG_EXEC_NONOPT_OPT,
                            CLI_SIG_FREE_SELF};

    opt_s dummy = DUMMY_OPT;
    dummy.aliases = CLI_ALIASES(CLI_NONOPT);

    opt_s *opts[] = {&dummy, NULL};

    BEGIN_TEST(opts, "execnonopt");

    exec_inj_args(&cli, arena, (char *[]){"test", "my_special_nonopt", NULL});

    END_TEST(signals);

    CLI_ALLOW_NONOPT = false;
}

/*
 * test: 'trying to execute a nonopt after any option' case.
 *
 * behaviour of executing a nonopt after an option.
 */
void test_run_nonopt_after_opt() {
    CLI_MODE_LAIDBACK = true;
    CLI_ALLOW_NONOPT = true;

    sig_type_e signals[] = {
        CLI_SIG_INIT_SELF,   CLI_SIG_EXEC_PARSED_OPT,
        CLI_SIG_CONSUME_TOK, CLI_SIG_ERR_CANT_CHAIN_NONOPT_AFTER_OPTS,
        CLI_SIG_EXIT,        CLI_SIG_FREE_SELF};

    opt_s dummy = DUMMY_OPT;
    dummy.want_input = true;

    opt_s nonopt = DUMMY_OPT;
    nonopt.aliases = CLI_ALIASES(CLI_NONOPT);

    opt_s *opts[] = {&dummy, &nonopt, NULL};

    BEGIN_TEST(opts, "execnonoptafteropt");

    exec_inj_args(
        &cli, arena,
        (char *[]){"test", "dummy", "input", "my_special_nonopt", NULL});

    END_TEST(signals);

    CLI_MODE_LAIDBACK = false;
    CLI_ALLOW_NONOPT = false;
}

/*
 * test: 'executing a default option' case.
 *
 * behaviour of executing default option.
 */
void test_run_default_opt() {
    sig_type_e signals[] = {CLI_SIG_INIT_SELF, CLI_SIG_EXEC_DEF_OPT,
                            CLI_SIG_FREE_SELF};

    opt_s default_opt = DUMMY_OPT;
    default_opt.aliases = CLI_ALIASES(CLI_DEFAULT_OPT);

    opt_s *opts[] = {&default_opt, NULL};

    BEGIN_TEST(opts, "execdefaultopt");

    exec_inj_args(&cli, arena, (char *[]){"test", NULL});

    END_TEST(signals);
}

int main() {
    test_base();
    test_help();

    test_init_opt();
    test_init_del_opt();
    test_del_nonexistent_opt();

    test_run_opt();
    test_run_opt_with_input();
    test_run_opt_with_no_input_but_wants_input_is_true();
    test_run_opt_with_input_but_wants_input_is_false();

    test_run_unrecognized_tok();
    test_run_unallowed_tok();

    test_run_nonopt();
    test_run_nonopt_after_opt();

    test_run_default_opt();
}
