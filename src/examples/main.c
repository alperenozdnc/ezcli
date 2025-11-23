#include <ezcli.h>
#include <stdio.h>

enum rtype _eat(char *food) {
    printf("human: consuming %s\n", food);

    return RET_NORMAL;
}

enum rtype _sleep(__attribute((unused)) char *str) {
    printf("human: sleeping...\n");

    return RET_NORMAL;
}

enum rtype _secret(char *secret_str) {
    printf("human: %s...\n", secret_str);

    return RET_NORMAL;
}

enum rtype _unwanted(char *name) {
    printf("human: my name is %s, and nobody wants me...\n", name);

    return RET_NORMAL;
}

enum rtype _nonopt(char *arg) {
    printf("%s", arg);

    return RET_NORMAL;
}

enum rtype __default(__attribute((unused)) char *_) {
    printf("wassup dawg");

    return RET_NORMAL;
}

struct opt eat = {
    .type = OPTION_BARE,
    .name = "eat",
    .body = *_eat,
    .want_input = true,
    .desc = "every human needs something to consoom.",
};

struct opt sleep = {.type = OPTION_BARE,
                    .name = "sleep",
                    .body = *_sleep,
                    .want_input = false,
                    .desc = "zzzzzz. i'm always sleepy, man."};

struct opt secret = {.type = OPTION_DOUBLE,
                     .name = "secret",
                     .desc = "hey, lemme tell you b secret.",
                     .body = *_secret,
                     .want_input = true};

struct opt __secret = {
    .type = OPTION_SINGLE,
    .name = "S",
    .body = *_secret,
    .want_input = true,
    .desc = "hey, lemme tell you a secret.",
};

struct opt unwanted = {
    .type = OPTION_BARE,
    .name = "unwanted",
    .body = *_unwanted,
    .want_input = true,
    .desc = "this is for when you feel unwanted.",
};

struct opt __unwanted = {
    .type = OPTION_DOUBLE,
    .name = "unwanted",
    .body = *_unwanted,
    .want_input = true,
    .desc = "this is for when you feel even more unwanted.",
};

struct opt nonopt = {
    .type = OPTION_BARE, .name = EZCLI_NONOPT, .body = *_nonopt};

struct opt _default = {
    .type = OPTION_BARE,
    .name = EZCLI_DEFAULT_OPT,
    .body = *__default,
};

int main(int argc, char *argv[]) {
    struct cli cli;
    struct opt *opts[] = {&eat,    &sleep,    &secret, &__secret,
                          &nonopt, &_default, NULL};
    char *help_aliases[] = {"help", "--help", NULL};

    initcli(&cli, "human", "This program mimicks human-like behaviours.",
            "[command] [args]",
            "For documentation: <https://github.com/alperenozdnc/ezcli>\nFor "
            "license: <https://www.gnu.org/licenses/gpl-3.0.en.html>",
            true, opts, help_aliases);

    addopt(&cli, &unwanted);
    addopt(&cli, &__unwanted);

    runcli(&cli, argc, argv);

    freecli(&cli);
}
