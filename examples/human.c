#include <ezcli.h>
#include <stdio.h>

ret_e _eat(CLI_IGNORE_CTX, char *food) {
    printf("human: consuming %s\n", food);

    return RET_NORMAL;
}

ret_e _sleep(CLI_IGNORE_ARGS) {
    printf("human: sleeping...\n");

    return RET_NORMAL;
}

ret_e _secret(void *ctx, char *secret_str) {
    printf("human: %s...\n", secret_str);
    printf("%s\n", (char *)ctx);

    return RET_NORMAL;
}

ret_e _unwanted(CLI_IGNORE_CTX, char *name) {
    printf("human: my name is %s, and nobody wants me...\n", name);

    return RET_NORMAL;
}

ret_e _nonopt(CLI_IGNORE_CTX, char *arg) {
    printf("%s\n", arg);

    return RET_NORMAL;
}

ret_e __default(CLI_IGNORE_ARGS) {
    printf("wassup dawg\n");

    return RET_NORMAL;
}

opt_s eat = {
    .aliases = CLI_ALIASES("eat", "--eat"),
    .body = *_eat,
    .want_input = true,
    .desc = "every human needs something to consoom.",
};

// 'sleep' is taken by unistd so that's why this option breaks the
// naming pattern.
opt_s sleep_opt = {.aliases = CLI_ALIASES("sleep", "--sleep"),
                   .body = *_sleep,
                   .want_input = false,
                   .desc = "zzzzzz. i'm always sleepy, man."};

opt_s secret = {.aliases = CLI_ALIASES("secret", "--secret"),
                .ctx = "i use contexts!",
                .desc = "hey, lemme tell you b secret.",
                .body = *_secret,
                .want_input = true};

opt_s __secret = {
    .aliases = CLI_ALIASES("-S", "--secrets"),
    .body = *_secret,
    .ctx = "i use contexts!",
    .want_input = true,
    .desc = "hey, lemme tell you a secret.",
};

opt_s unwanted = {
    .body = *_unwanted,
    .aliases = CLI_ALIASES("-U", "--unwanted"),
    .want_input = true,
    .desc = "this is for when you feel unwanted.",
};

opt_s __unwanted = {
    .aliases = CLI_ALIASES("-UW", "-unwanteed"),
    .body = *_unwanted,
    .want_input = true,
    .desc = "this is for when you feel even more unwanted.",
};

opt_s nonopt = {.aliases = CLI_ALIASES(CLI_NONOPT), .body = *_nonopt};

opt_s _default = {
    .aliases = CLI_ALIASES(CLI_DEFAULT_OPT),
    .body = *__default,
};

int main(int argc, char *argv[]) {
    cli_s cli;
    opt_s *opts[] = {&eat,    &sleep_opt, &secret, &__secret,
                     &nonopt, &_default,  NULL};

    CLI_ALLOW_NONOPT = true;
    CLI_MODE_DEBUG = true;

    initcli(&cli, "human", "This program mimicks human-like behaviours.",
            "[command] [args]",
            "For documentation: <https://github.com/alperenozdnc/ezcli>\nFor "
            "license: <https://www.gnu.org/licenses/gpl-3.0.en.html>\n",
            opts, CLI_ALIASES("help", "--help"));

    addopt(&cli, &unwanted, &__unwanted);
    delopt(&cli, &__secret);

    runcli(&cli, argc, argv);

    freecli(&cli);
}
