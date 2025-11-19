#include <ezcli.h>

#include <stdio.h>

enum rtype _eat(char *food) {
    if (!food) {
        return RET_FAIL;
    }

    printf("human: consuming %s", food);

    return RET_NORMAL;
}

enum rtype _sleep(char *str) {
    if (str) {
        printf("human: don't need input on 'sleep'");

        return RET_WARN;
    }

    printf("human: sleeping...");

    return RET_NORMAL;
}

int main(int argc, char *argv[]) {
    struct cli cli;

    struct opt eat = {.type = OPTION_BARE, .name = "eat", .body = *_eat};
    struct opt sleep = {.type = OPTION_BARE, .name = "sleep", .body = *_sleep};

    struct opt *opts[] = {&eat, &sleep};

    initcli(&cli, "human", NULL, true, opts);

    runcli(&cli, argc, argv);

    freecli(&cli);
}
