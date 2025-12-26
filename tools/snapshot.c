#include <ezcli.h>

#include "internal/assert.h"
#include "internal/join_str.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RUN_NO_ARGS "RUN_DEFAULT"
#define SNAPSHOT_FILENAME "ezcli.snapshot"
#define PREFIX "ezcli/snapshot: "

typedef struct {
    char *binary_ref;
    char *input_filename;
    cli_s *cli;

    bool run_mode;
} snapshot_ctx;

// i know all of these fields are initialized NULL/false by default, but being
// explicit about them is better to me
static snapshot_ctx ctx = {
    .binary_ref = NULL, .input_filename = NULL, .run_mode = false};

ret_e binary_ref_opt_body(void *_ctx, char *binary_ref) {
    snapshot_ctx *ctx = _ctx;

    ctx->binary_ref = strdup(binary_ref);

    ctx->run_mode = true;

    return RET_NORMAL;
}

opt_s binary_ref_opt = {.aliases = CLI_ALIASES("-b", "--binary"),
                        .desc =
                            "takes in a binary path to be fed the inputs to.",
                        .body = binary_ref_opt_body,
                        .ctx = &ctx,
                        .want_input = true};

ret_e input_opt_body(void *_ctx, char *input_filename) {
    snapshot_ctx *ctx = _ctx;

    ctx->input_filename = strdup(input_filename);

    ctx->run_mode = true;

    return RET_NORMAL;
}

opt_s input_opt = {.aliases = CLI_ALIASES("-i", "--input"),
                   .desc = "takes in a file path to feed the binary reference.",
                   .body = input_opt_body,
                   .ctx = &ctx,
                   .want_input = true};

ret_e snapshot_creator_body(void *_ctx, CLI_IGNORE_TOK) {
    snapshot_ctx *ctx = _ctx;

    bool both_inputs_are_valid = ctx->input_filename && ctx->binary_ref;

    // the first next token is the argument passed to the current option,
    // so 2 offsets gets the next option/lack thereof
    char *next_tok = gettok_offset(ctx->cli, 2);

    if (!both_inputs_are_valid && !next_tok && ctx->run_mode) {
        if (!ctx->binary_ref) {
            cliprint(CLI_ERROR, PREFIX, "a binary reference must be given.");

            return RET_FAIL;
        }

        if (!ctx->input_filename) {
            cliprint(CLI_ERROR, PREFIX, "an input filename must be given.");

            return RET_FAIL;
        }
    }

    if (!both_inputs_are_valid)
        return RET_NORMAL;

    FILE *input_fptr = fopen(ctx->input_filename, "r");
    FILE *output_fptr = fopen(SNAPSHOT_FILENAME, "w");
    fclose(output_fptr);

    _assert(input_fptr, "the input filename must exist on disk");

    size_t buf_size = 256;
    char buf[buf_size];

    while (fgets(buf, buf_size, input_fptr)) {
        // this trims the newline
        size_t actual_len = strcspn(buf, "\n");
        buf[actual_len] = '\0';

        char *bin_cmd_lhs = join_str(ctx->binary_ref, " ");

        if (strcmp(buf, RUN_NO_ARGS) == 0)
            buf[0] = '\0';

        char *bin_cmd = join_str(bin_cmd_lhs, buf);
        char *cmd = join_str(bin_cmd, " >> " SNAPSHOT_FILENAME);

        system(cmd);

        free(cmd);
        free(bin_cmd_lhs);
        free(bin_cmd);
    }

    fclose(input_fptr);
    free(ctx->input_filename);
    free(ctx->binary_ref);

    cliprint(CLI_HINT, PREFIX,
             "all outputs have been written to '" SNAPSHOT_FILENAME "'.");

    return RET_NORMAL;
}

opt_s snapshot_creator_opt = {.aliases = CLI_ALIASES(CLI_POST_COMMON_OPT),
                              .ctx = &ctx,
                              .body = snapshot_creator_body};

int main(int argc, char *argv[]) {
    cli_s cli = {0};

    initcli(&cli, "snapshot",
            "an ezcli tool that lets you create sane snapshots for testing.",
            "-i [input-file] -b [binary-reference]",
            "all code under ezcli is licensed with gplv3.\n", CLI_EMPTY_OPTS,
            CLI_ALIASES("help", "--help", "-h"));

    ctx.cli = &cli;

    addopt(&cli, &binary_ref_opt, &input_opt, &snapshot_creator_opt);

    runcli(&cli, argc, argv);

    freecli(&cli);
}
