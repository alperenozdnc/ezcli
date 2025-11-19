#include <ezcli.h>
#include <stdio.h>

enum rtype _eat(char *food) {
    if (!food) {
        cliprint(CLI_HINT, "human: ",
                 "i can't eat air, man. you should try to give me something to "
                 "work with here.");

        return RET_FAIL;
    }

    printf("human: consuming %s\n", food);

    return RET_NORMAL;
}

enum rtype _sleep(char *str) {
    if (str) {
        cliprint(CLI_ERROR, "human: ", "don't need input on 'sleep', asshole.");

        return RET_FAIL;
    }

    printf("human: sleeping...\n");

    return RET_NORMAL;
}

enum rtype _secret(char *secret_str) {
    if (!secret_str) {
        cliprint(CLI_ERROR, "human: ", "need a secret to tell, asshole.");

        return RET_FAIL;
    }

    printf("human: %s...\n", secret_str);

    return RET_NORMAL;
}

enum rtype _unwanted(char *name) {
    printf("human: my name is %s, and nobody wants me...\n", name);

    return RET_NORMAL;
}

struct opt eat = {.type = OPTION_BARE, .name = "eat", .body = *_eat};

struct opt sleep = {.type = OPTION_BARE, .name = "sleep", .body = *_sleep};

struct opt secret = {.type = OPTION_DOUBLE, .name = "secret", .body = *_secret};

struct opt __secret = {.type = OPTION_SINGLE, .name = "S", .body = *_secret};

struct opt unwanted = {
    .type = OPTION_BARE, .name = "unwanted", .body = *_unwanted};

int main(int argc, char *argv[]) {
    struct cli cli;
    struct opt *opts[] = {&eat, &sleep, &secret, &__secret, NULL};

    initcli(&cli, "human", true, opts);

    addopt(&cli, &unwanted);

    runcli(&cli, argc, argv);

    freecli(&cli);
}
