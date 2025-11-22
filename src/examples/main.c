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

struct opt eat = {
    .type = OPTION_BARE, .name = "eat", .body = *_eat, .want_input = true};

struct opt sleep = {
    .type = OPTION_BARE, .name = "sleep", .body = *_sleep, .want_input = false};

struct opt secret = {.type = OPTION_DOUBLE,
                     .name = "secret",
                     .body = *_secret,
                     .want_input = true};

struct opt __secret = {
    .type = OPTION_SINGLE, .name = "S", .body = *_secret, .want_input = true};

struct opt unwanted = {.type = OPTION_BARE,
                       .name = "unwanted",
                       .body = *_unwanted,
                       .want_input = true};

struct opt __unwanted = {.type = OPTION_BARE,
                         .name = "unwanted2",
                         .body = *_unwanted,
                         .want_input = true};

struct opt nonopt = {
    .type = OPTION_BARE, .name = EZCLI_NONOPT, .body = *_nonopt};

int main(int argc, char *argv[]) {
    struct cli cli;
    struct opt *opts[] = {&eat, &sleep, &secret, &__secret, &nonopt, NULL};

    initcli(&cli, "human", true, opts);

    addopt(&cli, &unwanted);
    addopt(&cli, &__unwanted);

    runcli(&cli, argc, argv);

    freecli(&cli);
}
