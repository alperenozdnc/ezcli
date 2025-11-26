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
    printf("%s", (char *)ctx);

    return RET_NORMAL;
}

ret_e _unwanted(CLI_IGNORE_CTX, char *name) {
    printf("human: my name is %s, and nobody wants me...\n", name);

    return RET_NORMAL;
}

ret_e _nonopt(CLI_IGNORE_CTX, char *arg) {
    printf("%s", arg);

    return RET_NORMAL;
}

ret_e __default(CLI_IGNORE_ARGS) {
    printf("wassup dawg");

    return RET_NORMAL;
}

opt_s eat = {
    .type = OPTION_BARE,
    .name = "eat",
    .body = *_eat,
    .want_input = true,
    .desc = "every human needs something to consoom.",
};

opt_s sleep = {.type = OPTION_BARE,
               .name = "sleep",
               .body = *_sleep,
               .want_input = false,
               .desc = "zzzzzz. i'm always sleepy, man."};

opt_s secret = {.type = OPTION_DOUBLE,
                .name = "secret",
                .ctx = "i use contexts!",
                .desc = "hey, lemme tell you b secret.",
                .body = *_secret,
                .want_input = true};

opt_s __secret = {
    .type = OPTION_SINGLE,
    .name = "S",
    .body = *_secret,
    .ctx = "i use contexts!",
    .want_input = true,
    .desc = "hey, lemme tell you a secret.",
};

opt_s unwanted = {
    .type = OPTION_BARE,
    .name = "unwanted",
    .body = *_unwanted,
    .want_input = true,
    .desc = "this is for when you feel unwanted.",
};

opt_s __unwanted = {
    .type = OPTION_DOUBLE,
    .name = "unwanted2",
    .body = *_unwanted,
    .want_input = true,
    .desc = "this is for when you feel even more unwanted.",
};

opt_s nonopt = {.type = OPTION_BARE, .name = CLI_NONOPT, .body = *_nonopt};

opt_s _default = {
    .type = OPTION_BARE,
    .name = CLI_DEFAULT_OPT,
    .body = *__default,
};

int main(int argc, char *argv[]) {
    cli_s cli;
    opt_s *opts[] = {&eat,    &sleep,    &secret, &__secret,
                     &nonopt, &_default, NULL};
    char *help_aliases[] = {"help", "--help", NULL};

    CLI_ALLOW_NONOPT = true;
    CLI_MODE_DEBUG = true;

    initcli(&cli, "human", "This program mimicks human-like behaviours.",
            "[command] [args]",
            "For documentation: <https://github.com/alperenozdnc/ezcli>\nFor "
            "license: <https://www.gnu.org/licenses/gpl-3.0.en.html>",
            opts, help_aliases);

    addopt(&cli, &unwanted);
    addopt(&cli, &__unwanted);
    delopt(&cli, &__secret);

    runcli(&cli, argc, argv);

    freecli(&cli);
}
