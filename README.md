## ezcli 

ezcli is a cli library that doesn't have much content
but has a lot of flexibility.

no annoying defaults, no opinionated parsing styles,
no forced behaviour. **you** define your own context,
your own behaviour, your own parsing style, because
a cli library shouldn't police the programmer. the
programmer should police the user for correct input,
using the cli library.

---

### what you're about to see next;
- installation
- features
- example usage 
- the philosophy and why ezcli just "clicks" for me
- contributing
- license

### installation

#### (1) obviously, you probably want to clone this.

```bash
% git clone https://github.com/alperenozdnc/ezcli
```

#### (2) now, it's time to build.

```bash
% make all
```

this command creates the shared object for the library
in `lib/` and an example executable in `examples/`.

you can play around with examples to kind of get
an idea on things you can create using ezcli.

#### (3) and finally, the reason you're reading this section. 

```bash
% sudo make install
```

this command puts the shared object file `libezcli.so` in
`/usr/local/lib` and the header file
`ezcli.h` in `/usr/local/include`.

you can now just `#include <ezcli.h>` from anywhere
if you also use flag `-lezcli` when compiling.

```bash
% sudo make uninstall
```

you can also do this if you decide you don't like it.

---

### features

#### expandable option types (wut?)

the number of leading hyphens for an option depends
on an enum value you set yourself
(either `OPTION_BARE`, `OPTION_SINGLE`
or `OPTION_DOUBLE`). i believe this
is prettier than just including the hyphens in the
option definition.

#### options are context-aware behaviour containers

not only can you define what an option does, but you can optionally pass
context down to it. this means you can share state, set configurations with flags,
define your own parsing methods, inject context based on input, and even more.

#### dynamic option definitions

you can add new options with the `addopt` function
(and obviously remove with `delopt`). this enables you to make programs that
have user defined commands (and have those user-defined commands persist across sessions),
or you can even make a wrapper around my library
if you don't really like the philosophy behind it.

#### **you** pick how the program branches, not the library

ezcli strictly forbids any syntax errors in inputs, but there exists a laidback
mode if you want ezcli to omit all errors, but still print them. every option
also can set branching with;
- continuing
- sending warnings
- making errors and panicking

#### non-option options (wut??)

non-option options are tokens that don't cause any syntax errors, but also
don't belong as a value passed to any option. this might be useful for programs
looking to allow for filename/directory/etc options.

you can set to allow these non-option options (weirdly named, i know), and
give them behaviour that also can take context too. if you don't set behaviour
or don't explicitly allow these non-options options in your program, ezcli
will handle printing out an error for you.

#### default option

if you don't define a default option, ezcli prints out an help menu by default.
if you do though, any program that is ran with argc=0, argv={} immediately calls
this default option behaviour. this can also take context, which would make
totally weird ideas like a program that increments a certain number in a file
by just being ran. let's say the program is named 'sum' and you do,
`sum set num.txt`, and `sum` 5 times and you could see 5 in `num.txt`. this
obviously isn't something that's viable, or usable looking from a ux perspective,
but it just goes to show the flexibility and unopinionated-ness of ezcli.

#### injectable runner

the `runcli(int argc, char *argv[])` function doesn't care about the source of
the arguments, so you can inject any arguments you want. this allows for creation
of interactive cli's, and maybe even might make ezcli kind of a 'programming interface'.
you could do recursion, calculations, and other weird things you don't expect a cli
library to be able to do.

---

### example usage

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

`EZCLI_ALLOW_NONOPT`, if set to true, will allow for the 'non-option options'
i was talking about earlier in features. else, ezcli will throw an error for
these nonopts.

`EZCLI_MODE_LAIDBACK`, if set to true, will enable 'laidback' mode, which
doesn't terminate when parsing errors are found. you can also read about that
in features.

#### ok, i get it. but what i do even fill `**opts` with?

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
these live under the macros names respectively, `EZCLI_NONOPT` and `EZCLI_DEFAULT_OPT`.

any opt struct named these macros are now special options and will be used in
contexts that require them.

setting the name to `EZCLI_NONOPT` lets you define behaviour when the parsing
comes across a non-option option. this lets you create programs that take
arguments that can't be known before being ran. for example, in the command 
`ls home/ etc/`, the `home/` and `etc/` are non-option options.

if the name is set to `EZCLI_DEFAULT_OPT` lets you define behaviour when no
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
enum rtype _default_opt(EZCLI_IGNORE_ARGS) {
    printf("hello, world");

    return RET_NORMAL;
}

struct opt default_opt = {
    .type = OPTION_BARE, .name = EZCLI_DEFAULT_OPT, .body = _default_opt};

```

this is the default option. the `enum rtype` has three values, `RET_NORMAL`
just continues parsing, `RET_WARN` warns the user that they probably did
something wrong, and `RET_FAIL` just flat out exits the program. i like to
name like this for clarity, you may like to do it some other way, and that's
totally okay.

```c
enum rtype _version_opt(void *ctx, EZCLI_IGNORE_TOK) {
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
enum rtype _nonopt(EZCLI_IGNORE_CTX, char *tok) {
    printf("hello, %s", tok);

    return RET_NORMAL;
}

struct opt nonopt = {
    .type = OPTION_BARE,
    .name = EZCLI_NONOPT,
    .body = _nonopt,
};
```

this is the non-option option. now, we should allow for them to be able to
implement this functionality.

```c
EZCLI_ALLOW_NONOPT = true;
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

and that's how you create command line interfaces with ezcli.

---

### the philosophy and why ezcli just "clicks" for me

i always go through this with my own projects, or also when i see neatly done
ones. but the concept of taking structurally sound and logical building blocks
that are also not too big to swallow just makes some very satisfying buttons
click in my head.

these building blocks should also be necessary or way too useful to not be
included.

#### there is SUCH a thing as too much abstraction

personally, i hate libraries with so much abstractions it feels like you're
writing python. the programmer doesn't need that much handholding. i mean
sure, i am stupid, but somebody accepting that annoys me to my core.

#### ezcli is the tool, not the ultimate way

this misunderstanding between a goal and the means to getting to that goal
is why we started seeing terms like "experienced react developer". like,
do you help maintain react, if no, then hell nah.

too much opinions bundled in something that many people use isn't always nice.
i could have also added interactivity, input type enforcement, some structs to
use for contexts, and all other bundled shit that comes with some libraries.

and sure, maybe that would save you some time, but how much code should a person
write for you before they program your whole application? you might not like
all of my methods to approach things, something you want to change in ezcli
might just be too internal to change, or here comes the worst part: you could use
some of that code without even understanding it (THAT my friend, is the root of
most bugs).

#### there is a philosophy to c many people forget

i recently saw a library that used macros to let someone,
create artificial function defitions, and nest them in order too (cli>arg>usage),
and names, the usages, the descriptions were all taken inside a single string
as an argument to some of those "functions".

i'm not kidding you, dennis ritchie would stab you with a fork if he was alive
to see your implementations.

stop creating your own languages with macros, stop making everything so easy
its not descriptive anymore. storing information in strings is done with yml,
csv, and json files. not c. also, use python if you want nested functions. also,
that implementation requires at least 4-5 levels of indentation or hundreds of
modules to be created that also require hundreds of header files.

---

### contributing

i accept any kind of feedback as a contribution. here are some ways though;
- opening an issue talking about something in (or not in) ezcli you don't like.
- forking ezcli and opening a pull request.
- tossing a star.

any code written with a nice idea is good enough for me, i will migrate any
contributions to my own code style preferences, so do as you want. but please,
please, no more than 3 indentations.

---

### license

i think all software should be free and open-source, and even if there needs
to be a paywall, the user should know the code that is running on their device.
pirating exists alongside proprietary code and open-source is generally safer
to use because of the sheer amount of workforce that open-source projects have,
so why would anybody want to make proprietary software if it's not malicious or
behind a paywall?

for those reasons, i use `GPLv3` in all of my projects. see `LICENSE` in the
root directory for details.
