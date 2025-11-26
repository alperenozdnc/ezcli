# example usage

so, we start by defining a `cli` struct. this is where all of the information
about your command line interface lives:

```c
struct cli {
    char *cmd;
    char *desc;
    char *usage;
    char *footer;

    struct opt **opts;
    size_t opts_len;

    char **help_aliases;
    void (*help)(struct cli *cli, struct opt **opts);
}
```

a `cli` struct consists of:
- 1) information that concerns the user (cmd, desc, usage, footer)
- 2) information that concerns ezcli (opts, opts_len, help_aliases, help)

you can go check out `include/ezcli/cli.h` for information on what each field
represents.

you must use the `initcli` function (code present in `src/ezcli/initcli.c`) to
initialize your instance of the cli struct.

this function will allocate memory for your options, define a default help command,
and copy all other information.

> [!CAUTION]
note that `**opts` and `*help_aliases[]` MUST be null terminated.
> 

```c
void initcli(struct cli *cli, char *cmd, char *desc, char *usage, char *footer,
             struct opt **opts, char *help_aliases[]);
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
an `opt` struct.

```c
struct opt {
    enum otype type;
    char *name;
    char *desc;

    bool want_input;

    void *ctx;
    enum rtype (*body)(void *ctx, char *tok);
};
```

these options are the little bits and pieces that make up our program.
you can think of the `type`, `name`, and description as the labels on a box, the context (`*ctx`)
and the `*body` as the stuff inside that box, and `want_input` as a guard waiting
to punish you if you do the wrong thing.

the `enum otype type` specifies how many hyphens come before `name`.
`OPTION_BARE` is for none, `OPTION_SINGLE` is for one, and `OPTION_DOUBLE` is for two.

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

there are two special cases for names you cant take: `"NONOPT"`, and `"DEFAULT"`,
these live under the macros names respectively, `CLI_NONOPT` and `CLI_DEFAULT_OPT`.

any opt struct named these macros are now special options and will be used in
contexts that require them.

setting the name to `CLI_NONOPT` lets you define behaviour when the parsing
comes across a non-option option. this lets you create programs that take
arguments that can't be known before being ran. for example, in the command 
`ls home/ etc/`, the `home/` and `etc/` are non-option options.

if the name is set to `CLI_DEFAULT_OPT` lets you define behaviour when no
external input is given. if not defined, ezcli will print out the result of calling
help. (note that you can set your own help behaviour by writing your own help fn
and pointing it to `cli->help`. the help function is passed the cli struct and opts.

now, with all of this info, lets create a simple cli that has version `v1.0.0`,
prints "hello, world" when being ran with no input, and replaces the 'world'
in hello world with the given nonopt if any is given.
to start, import ezcli and create an empty `cli` struct:

```c
#include <ezcli.h>

struct cli cli;
```

then, lets define our options:

```c
enum rtype _default_opt(CLI_IGNORE_ARGS) {
    printf("hello, world");

    return RET_NORMAL;
}

struct opt default_opt = {
    .type = OPTION_BARE, .name = CLI_DEFAULT_OPT, .body = _default_opt};

```

this is the default option. the `enum rtype` has three values, `RET_NORMAL`
just continues parsing, `RET_WARN` warns the user that they probably did
something wrong, and `RET_FAIL` just flat out exits the program. i like to
name like this for clarity, you may like to do it some other way, and that's
totally okay.

```c
enum rtype _version_opt(void *ctx, CLI_IGNORE_TOK) {
    char *prefix = (char *)ctx;

    printf("%s, v1.0.0", prefix);

    return RET_NORMAL;
}

struct opt version_opt = {
    .type = OPTION_DOUBLE,
    .name = "version",
    .desc = "prints out the version.",
    .want_input = false,
    .ctx = "my program is version",
    .body = _version_opt,
};
``` 

this is the version option, the default option and the nonopt aren't
printed in help, so no need to bother setting `desc`. you will also see how the value in
`ctx` comes to play.

```c
enum rtype _nonopt(CLI_IGNORE_CTX, char *tok) {
    printf("hello, %s", tok);

    return RET_NORMAL;
}

struct opt nonopt = {
    .type = OPTION_BARE,
    .name = CLI_NONOPT,
    .body = _nonopt,
};
```

this is the non-option option. now, we should allow for them to be able to
implement this functionality.

```c
CLI_ALLOW_NONOPT = true;
```

ok, so now, we should compile together our cli struct with inputs we have created.

```c
struct opt *opts[] = {&version_opt, &default_opt, &nonopt, NULL};
char *help_aliases[] = {"help", "--help", NULL};

initcli(&cli, "program", "This program is an example on ezcli.",
        "[option]/[name]", "And this is the footer.",
        opts, help_aliases);
```

and finally, we can inject arguments and parse them with `runcli` and gracefully
exit with `freecli`.

```c
runcli(&cli, argc, argv);

freecli(&cli);
```

you can also add options with `addopt` if you wish.

```c
addopt(&cli, &version_opt);
```

now, when compiling and running this,
we get (i moved the binary to `/usr/bin/program`):

```
% program                                                   
    hello, world                                                                        
                                                                                    
% program --help                                            
    [USAGE]: program [option]/[name]                                                    
    This program is an example on ezcli.                                                  
                                                                                        
        help, --help -> prints this menu.                                               
        --version -> prints out the version.                                              
                                                                                          
                                                                                        
    And this is the footer.                                                             

% program --version                                           
    my program is version, v1.0.0                                                       
                                                                                    
% program name1 name2 name3 name4                                                                   
    hello, name1                                                                          
    hello, name2                                                                        
    hello, name3                                                                          
    hello, name4                                                                        
```
