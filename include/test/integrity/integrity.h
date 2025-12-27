#pragma once

/*
 * initializes a 'mock' cli instance with specified options.
 */
#define BEGIN_TEST(opts, _label)                                               \
    (void)__COUNTER__;                                                         \
    char *label = _label;                                                      \
    cliprint(CLI_HINT,                                                         \
             "    "                                                            \
             "[ TEST ]"                                                        \
             "  ",                                                             \
             "%s", label);                                                     \
    sig_arena_s *arena = init_sig_arena();                                     \
    cli_s cli = {0};                                                           \
    initcli(&cli, "test", "test", "test", "test", opts, CLI_ALIASES("help"),   \
            arena);

/*
 * kills a 'mock' cli instance and its corresponding signal arena.
 */
#define END_TEST(signals)                                                      \
    do {                                                                       \
        freecli(&cli);                                                         \
        assert_signals(signals);                                               \
        free_sig_arena(arena);                                                 \
    } while (0)
;

#define CLI_NO_OPTS                                                            \
    (opt_s *[]) {                                                              \
        NULL                                                                   \
    }

#define ASSERTED_SIGNALS_SIZE(signals) sizeof(signals) / sizeof(signals[0])

#define assert_signals(signals)                                                \
    _assert_signals(signals, ASSERTED_SIGNALS_SIZE(signals), arena)

#define print_signals_asserted(sigs, size)                                     \
    print_signals(false, NULL, sigs, size)

#define print_signals_arena() print_signals(true, arena, NULL, 0)

#define wrap_with_label(label, content)                                        \
    do {                                                                       \
        cliprint(CLI_HINT, label, "");                                         \
        content;                                                               \
        printf("\n");                                                          \
    } while (0)

#define DUMMY_BODY()                                                           \
    ret_e dummy_body(CLI_IGNORE_ARGS) {                                        \
        return RET_NORMAL;                                                     \
    }

#define DUMMY_OPT                                                              \
    (opt_s) {                                                                  \
        .aliases = CLI_ALIASES("dummy"), .body = dummy_body, .desc = "_",      \
        .want_input = false                                                    \
    }
