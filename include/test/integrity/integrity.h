#pragma once

/*
 * initializes a 'mock' cli instance with specified options.
 */
#define BEGIN_TEST(opts)                                                       \
    sig_arena_s *arena = init_sig_arena();                                     \
    cli_s cli = {0};                                                           \
    initcli(&cli, "test", "test", "test", "test", opts, CLI_ALIASES("help"),   \
            arena);

/*
 * kills a 'mock' cli instance and its corresponding signal arena.
 */
#define END_TEST                                                               \
    do {                                                                       \
        freecli(&cli);                                                         \
        free_sig_arena(arena);                                                 \
        printf("test/integrity: success.\n");                                  \
    } while (0)
;

#define CLI_NO_OPTS                                                            \
    (opt_s *[]) {                                                              \
        NULL                                                                   \
    }

#define ASSERTED_SIGNALS_SIZE(signals) sizeof(signals) / sizeof(signals[0])

#define assert_signals(signals)                                                \
    _assert_signals(signals, ASSERTED_SIGNALS_SIZE(signals), arena)
