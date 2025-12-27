#include <test/integrity/external.h>
#include <test/integrity/init_sig_arena.h>
#include <test/integrity/sig_arena_s.h>
#include <test/integrity/sig_s.h>

#include <stdlib.h>

char **sig_names = (char *[]){"INIT_SELF",
                              "FREE_SELF",
                              "EXIT",
                              "INIT_OPT",
                              "DEL_OPT",
                              "PRINT_ERR",
                              "EXEC_OPT_DEFAULT",
                              "EXEC_OPT_HELP",
                              "EXEC_OPT_PARSED",
                              "EXEC_OPT_PARSED_NO_INPUT",
                              "EXEC_OPT_NONOPT",
                              "ERR_OPT_DOESNT_WANT_ARGS",
                              "ERR_OPT_REQUIRES_ARGS_BUT_NONE_PASSED",
                              "ERR_TOK_IS_UNALLOWED",
                              "ERR_TOK_IS_UNRECOGNIZED",
                              "ERR_CANT_CHAIN_NONOPT_AFTER_PARSED_OPTS",
                              "ERR_CANT_DELETE_NONEXISTENT_OPT",
                              "CONSUME_TOK"};

bool CLI_SIG_PRINT = true;

sig_arena_s *init_sig_arena() {

    sig_arena_s *arena = malloc(sizeof(*arena));

    arena->signals_size = 0;
    arena->signals = malloc(SIGNALS_SIZE(1));

    return arena;
}
