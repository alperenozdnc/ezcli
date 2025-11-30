# example usage

so, we start by defining a `cli_s` struct. this is where all of the information
about your command line interface lives:

```c
typedef struct __cli_s {
    char *cmd;
    char *desc;
    char *usage;
    char *footer;

    opt_s **opts;
    size_t opts_len;

    char **help_aliases;
    void (*help)(struct __cli_s *cli, opt_s **opts);
} cli_s;
```

`cli_s` consists of:

- 1. information that concerns the user (cmd, desc, usage, footer)
- 2. information that concerns ezcli (opts, opts_len, help_aliases, help)

you can go check out `include/ezcli/cli.h` for information on what each field
represents.

you must use the `initcli` function (code present in `src/ezcli/initcli.c`) to
initialize your instance of `cli_s`.

this function will allocate memory for your options, define a default help command,
and copy all other information.

> [!CAUTION]
> note that `**opts` and `*help_aliases[]` MUST be null terminated.

```c
void initcli(cli_s *cli, char *cmd, char *desc, char *usage, char *footer,
             opt_s **opts, char *help_aliases[]);
```

after initializing your cli instance, you can set how ezcli will behave.

`CLI_ALLOW_NONOPT`, if set to true, will allow for the 'non-option options'
i was talking about earlier in features. else, ezcli will throw an error for
these nonopts.

`CLI_MODE_LAIDBACK`, if set to true, will enable 'laidback' mode, which
doesn't terminate when parsing errors are found. you can also read about that
in features.

## ok, i get it. but what i do even fill `**opts` with?

here comes the part where we define our options. every option is defined using
an `opt_s` struct.

```c
typedef struct {
    char **aliases;
    char *desc;

    bool want_input;

    void *ctx;
    ret_e (*body)(void *ctx, char *tok);
} opt_s;
```

these options are the little bits and pieces that make up our program.
you can think of the `aliases`, and `desc` as the labels on a box, the context (`*ctx`)
and the `*body` as the stuff inside that box, and `want_input` as a guard waiting
to punish you if you do the wrong thing.

the aliases are defined using the `CLI_ALIASES` macro provided in `include/opt.h`.

it expands to:

```c
// CLI_ALIASES(a, b, c, d)
(char *[]){a, b, c, d, NULL};
```

this macro is just to save you time wasted creating variables / casting, you
don't really have to use it if you don't want.

the description is what's shown in the help command, and `want_input` obviously
specifies if the option wants input or not.

the `ctx` is the state that is passed down to the body, this can be anything you
want, your global state, the previous parsed option, a configuration, all of them,
none of them, you decide.

the body is the behaviour of the option, it only knows about the context,
and the input passed to it (if `want_input`) is true.

the combination of shareable state and custom functionality allows you to make
almost any kind of cli you want. interactive, non-interactive, game, utility,
etc.

there are three special cases for names you can't take: `"NONOPT"`, `"DEFAULT"`, and `"COMMON_OPT"`.
these live under the macros names respectively, `CLI_NONOPT`, `CLI_DEFAULT_OPT` and `CLI_COMMON_OPT`.

any opt struct named these macros is now special options and will be used in
contexts that require them.

setting the name to `CLI_NONOPT` lets you define behaviour when the parsing
comes across a non-option option. this lets you create programs that take
arguments that can't be known before being run. for example, in the command
`ls home/ etc/`, the `home/` and `etc/` are non-option options.

setting the name to `CLI_DEFAULT_OPT` lets you define behaviour when no
external input is given. if not defined, ezcli will print out the result of calling
help. (note that you can set your own help behaviour by writing your own help fn
and pointing it to `cli->help`). the help function is passed the cli struct and opts.

setting the name to `CLI_COMMON_OPT` lets you create a common option that is
run before any successfully parsed option. this can be useful for logging, debugging,
reporting, special behaviour, etc.

now, with all of this info, let's create a simple cli that has version `v1.0.0`,
prints "hello, world" when being run with no input, and replaces the 'world'
in "hello, world" with the given nonopt if any is given.
to start, import ezcli and create an empty `cli_s` struct:

```c
#include <ezcli.h>

cli_s cli;
```

then, let's define our options:

```c
#include <stdio.h>

ret_e _default_opt(CLI_IGNORE_ARGS) {
    printf("hello, world\n");

    return RET_NORMAL;
}

opt_s default_opt = {
    .aliases = CLI_ALIASES(CLI_DEFAULT_OPT), .body = _default_opt};
```

this is the default option. the `ret_e` enum has three values, `RET_NORMAL`
just continues parsing, `RET_WARN` warns the user that they probably did
something wrong, and `RET_FAIL` just flat-out exits the program. i like to
name like this for clarity, you may like to do it some other way, and that's
totally okay.

```c
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
```

this is the version option, the default option and the nonopt aren't
printed in help, so no need to bother setting `desc`. you will also see how the value in
`ctx` comes into play.

```c
ret_e _nonopt(CLI_IGNORE_CTX, char *tok) {
    printf("hello, %s\n", tok);

    return RET_NORMAL;
}

opt_s nonopt = {
    .aliases = CLI_ALIASES(CLI_NONOPT),
    .body = _nonopt,
};
```

this is the non-option option. now, we should allow for them to be able to
implement this functionality.

```c
CLI_ALLOW_NONOPT = true;
```

```c
ret_e _common_opt(CLI_IGNORE_ARGS) {
    printf("hey, i always run.\n");

    return RET_NORMAL;
}

opt_s common_opt = {
    .aliases = CLI_ALIASES(CLI_COMMON_OPT),
    .body = _common_opt,
};
```

this is the common option. we'll see this run before all options in our output.

ok, so now, we should compile together our cli struct with inputs we have created.

```c
opt_s *opts[] = {&version_opt, &default_opt, &nonopt, &common_opt, NULL};
char *help_aliases[] = {"help", "--help", NULL};

initcli(&cli, "program", "This program is an example on ezcli.",
        "[option]/[name]", "And this is the footer.\n",
        opts, help_aliases);
```

and finally, we can inject arguments and parse them with `runcli` and gracefully
exit with `freecli`.

```c
runcli(&cli, argc, argv);

freecli(&cli);
```

you can also add options with `addopt` if you wish (accepts variable amount of options).

```c
addopt(&cli, &version_opt, ...);
```

or, remove them with `delopt`.

```c
delopt(&cli, &version_opt, ...);
```

now, when compiling and running this,
we get (i sourced `./scripts/examples.sh` from project root):

```
% program
    hey, i always run.
    hello, world

% program --help
    [USAGE]: program [option]/[name]
    This program is an example on ezcli.

        help, --help -> prints this menu.
        -v, --version -> prints out the version.

    And this is the footer.

% program --version
    hey, i always run.
    my program is version, v1.0.0

% program -v
    hey, i always run.
    my program is version, v1.0.0

% program name1 name2 name3 name4
    hey, i always run.
    hello, name1
    hey, i always run.
    hello, name2
    hey, i always run.
    hello, name3
    hey, i always run.
    hello, name4
```
