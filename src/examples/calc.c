#include <ezcli.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int sum;
    bool operation_mode;
    cli_s *cli;
} ctx_s;

ret_e add_body(void *_ctx, char *stry) {
    ctx_s *ctx = _ctx;

    char *strx = gettok_prev(ctx->cli);

    if (!strx) {
        cliprint(CLI_ERROR, CLI_EMPTY_PREFIX,
                 "Can't add nothing to %s. Please provide two numbers for +.",
                 stry);

        return RET_FAIL;
    }

    int x = atoi(strx);
    int y = atoi(stry);

    if (ctx->operation_mode) {
        printf("%d + %d = %d\n", ctx->sum, y, ctx->sum + y);

        ctx->sum += y;
    } else {
        ctx->operation_mode = true;
        ctx->sum = x + y;

        printf("%d + %d = %d\n", x, y, x + y);
    }

    if (!gettok_offset(ctx->cli, 2)) {
        printf("\nTotal sum is %d.", ctx->sum);
    }

    return RET_NORMAL;
}

ret_e subtract_body(void *_ctx, char *stry) {
    ctx_s *ctx = _ctx;

    char *strx = gettok_prev(ctx->cli);

    if (!strx) {
        cliprint(CLI_ERROR, CLI_EMPTY_PREFIX,
                 "Can't subtract anything from %s. Please provide two numbers "
                 "for -.",
                 stry);

        return RET_FAIL;
    }

    int x = atoi(strx);
    int y = atoi(stry);

    if (ctx->operation_mode) {
        printf("%d - %d = %d\n", ctx->sum, y, ctx->sum - y);

        ctx->sum -= y;
    } else {
        ctx->operation_mode = true;
        ctx->sum = x - y;

        printf("%d - %d = %d\n", x, y, x - y);
    }

    if (!gettok_offset(ctx->cli, 2)) {
        printf("\nTotal sum is %d.", ctx->sum);
    }

    return RET_NORMAL;
}

ret_e multiply_body(void *_ctx, char *stry) {
    ctx_s *ctx = _ctx;

    char *strx = gettok_prev(ctx->cli);

    if (!strx) {
        cliprint(CLI_ERROR, CLI_EMPTY_PREFIX,
                 "Can't add nothing to %s. Please provide two numbers for +.",
                 stry);

        return RET_FAIL;
    }

    int x = atoi(strx);
    int y = atoi(stry);

    if (ctx->operation_mode) {
        printf("%d * %d = %d\n", ctx->sum, y, ctx->sum * y);

        ctx->sum *= y;
    } else {
        ctx->operation_mode = true;
        ctx->sum = x * y;

        printf("%d * %d = %d\n", x, y, x * y);
    }

    if (!gettok_offset(ctx->cli, 2)) {
        printf("\nTotal sum is %d.", ctx->sum);
    }

    return RET_NORMAL;
}

ret_e pow_body(void *_ctx, char *stry) {
    ctx_s *ctx = _ctx;

    char *strx = gettok_prev(ctx->cli);

    if (!strx) {
        cliprint(CLI_ERROR, CLI_EMPTY_PREFIX,
                 "Can't add nothing to %s. Please provide two numbers for +.",
                 stry);

        return RET_FAIL;
    }

    int x = atoi(strx);
    int y = atoi(stry);

    if (ctx->operation_mode) {
        printf("%d ^ %d = %d\n", (int)ctx->sum, y, (int)pow(ctx->sum, y));

        ctx->sum = pow(ctx->sum, y);
    } else {
        ctx->operation_mode = true;
        ctx->sum = pow(x, y);

        printf("%d ^ %d = %d\n", x, y, (int)pow(x, y));
    }

    if (!gettok_offset(ctx->cli, 2)) {
        printf("\nTotal sum is %d.", ctx->sum);
    }

    return RET_NORMAL;
}

ret_e _nonopt(CLI_IGNORE_ARGS) {
    return RET_NORMAL;
}

opt_s nonopt = {.aliases = CLI_ALIASES(CLI_NONOPT), .body = _nonopt};

int main(int argc, char *argv[]) {
    cli_s cli;

    opt_s *opts[] = {&nonopt, NULL};
    char *help_aliases[] = {"help", "--help", NULL};

    CLI_ALLOW_NONOPT = true;

    initcli(
        &cli, "calc",
        "Mini calculator program to show off ezcli. (no order of operations)",
        "x {operand} y", "Check src/examples/calculator.c for source code.",
        opts, help_aliases);

    ctx_s ctx = {.cli = &cli, .sum = 0, .operation_mode = false};

    opt_s add = {.aliases = CLI_ALIASES("+", "ADD"),
                 .want_input = true,
                 .desc = "Adds two numbers together.",
                 .body = add_body,
                 .ctx = &ctx};

    opt_s subtract = {.aliases = CLI_ALIASES("-", "SUB"),
                      .want_input = true,
                      .desc = "Subtracts two numbers.",
                      .body = subtract_body,
                      .ctx = &ctx};

    opt_s multiply = {.aliases = CLI_ALIASES("x", "MUL"),
                      .want_input = true,
                      .desc = "Multiplies two numbers.",
                      .body = multiply_body,
                      .ctx = &ctx};

    opt_s pow = {.aliases = CLI_ALIASES("^", "POW"),
                 .want_input = true,
                 .desc = "Exponentiates first number to second.",
                 .body = pow_body,
                 .ctx = &ctx};

    addopt(&cli, &add, &subtract, &multiply, &pow);

    runcli(&cli, argc, argv);

    freecli(&cli);

    return 0;
}
