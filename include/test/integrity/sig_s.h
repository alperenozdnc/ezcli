#pragma once

#include <stdint.h>

/*
 * all of the available signal types. human-readable string representations
 * defined in extern `sig_names` can be found in `init_sig_arena()`.
 */
typedef enum {
    CLI_SIG_INIT_SELF,
    CLI_SIG_FREE_SELF,
    CLI_SIG_EXIT,
    CLI_SIG_INIT_OPT,
    CLI_SIG_DEL_OPT,
    CLI_SIG_PRINT_ERR,
    CLI_SIG_EXEC_DEF_OPT,
    CLI_SIG_EXEC_HELP_OPT,
    CLI_SIG_EXEC_PARSED_OPT,
    CLI_SIG_EXEC_PARSED_OPT_NO_TOK,
    CLI_SIG_EXEC_NONOPT_OPT,
    CLI_SIG_ERR_PASS_NO_WANT_ARGS,
    CLI_SIG_ERR_NOT_PASS_BUT_WANT_ARGS,
    CLI_SIG_ERR_UNALLOWED_ARG,
    CLI_SIG_ERR_UNRECOG_ARG,
    CLI_SIG_ERR_CANT_CHAIN_NONOPT_AFTER_OPTS,
    CLI_SIG_WARN_DEL_NONEXISTENT_OPT,
    CLI_SIG_CONSUME_TOK,
} sig_type_e;

extern char **sig_names;

/*
 * this is the struct that carries the type, line, and file info about a signal.
 */
typedef struct {
    sig_type_e type;
    uint16_t line;
    char *file;
} sig_s;
