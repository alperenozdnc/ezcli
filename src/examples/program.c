#include <ezcli.h>
#include <stdio.h>

ret_e _default_opt(CLI_IGNORE_ARGS) {
    printf("hello, world\n");

    return RET_NORMAL;
}

opt_s default_opt = {.aliases = CLI_ALIASES(CLI_DEFAULT_OPT),
                     .body = _default_opt};

ret_e _version_opt(void *ctx, CLI_IGNORE_TOK) {
    char *prefix = (char *)ctx;

    printf("%s, v1.0.0\n", prefix);

    return RET_NORMAL;
}

opt_s version_opt = {
    .aliases = CLI_ALIASES("-v", "--version"),
    .desc = "prints out the version.",
    .want_input = false,
    .ctx = "my program is version",
    .body = _version_opt,
};

ret_e _nonopt(CLI_IGNORE_CTX, char *tok) {
    printf("hello, %s\n", tok);

    return RET_NORMAL;
}

opt_s nonopt = {
    .aliases = CLI_ALIASES(CLI_NONOPT),
    .body = _nonopt,
};

int main(int argc, char *argv[]) {
    cli_s cli;
    opt_s *opts[] = {&version_opt, &default_opt, &nonopt, NULL};
    char *help_aliases[] = {"help", "--help", NULL};

    CLI_ALLOW_NONOPT = true;

    initcli(&cli, "program", "This program is an example on ezcli.",
            "[option]/[name]", "And this is the footer.\n", opts, help_aliases);

    runcli(&cli, argc, argv);

    freecli(&cli);
}
