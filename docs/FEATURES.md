# features

## this library documents itself

yes, you read that right. there a program called `ezdocs` that uses ezcli to
generate documentation about ezcli. build ezcli and ezdocs with `make all`, install
ezdocs as a binary with `sudo make install-docs` and run `ezdocs help` to get started.

## options are context-aware behaviour containers

not only can you define what an option does, but you can optionally pass
context down to it. this means you can share state, set configurations with flags,
define your own parsing methods, inject context based on input, and even more.

## dynamic option definitions

you can add new options with the `addopt` function
(and obviously remove with `delopt`).

## dynamic option allocation

you can allocate options to the heap with the `allocopt` function
(and remove, again, with `delopt`).this enables you to make programs that
have user-defined commands (and have those user-defined commands persist across sessions),
or you can even make a wrapper around my library
if you don't really like the philosophy behind it.

## **you** pick how the program branches, not the library

ezcli strictly forbids any syntax errors in inputs, but there exists a laidback
mode if you want ezcli to omit all errors, but still print them. every option
also can set branching with;

- continuing
- sending warnings
- making errors and panicking

## non-option options (wut??)

non-option options are tokens that don't cause any syntax errors, but also
don't belong as a value passed to any option. this might be useful for programs
looking to allow for filename/directory/etc options.

you can set to allow these non-option options (weirdly named, i know), and
give them behaviour that also can take context too. if you don't set behaviour
or don't explicitly allow these non-options options in your program, ezcli
will handle printing out an error for you.

## default option

if you don't define a default option, ezcli prints out an help menu by default.
if you do though, any program that's run with no args immediately calls
this default option behaviour. this can also take context.

## common option / post-common options

a common option is a behaviour that is only executed before every individual
successfully parsed option. using common options, you can do easy logging,
debugging, benchmarking, reporting, and all sorts of stuff.

there is also a post-common option that is executed _after_ every individual
successfully parsed option.

## injectable runner

the `runcli(int argc, char *argv[])` function doesn't care about the source of
the arguments, so you can inject any arguments you want. this allows for creation
of interactive clis, and maybe might even make ezcli kind of a 'programming interface'.
you could do recursion, calculations, and other weird things you don't expect a cli
library to be able to do.

> [!CAUTION]
> yes, you can do recursion. but you MUST restore `cli->tok_idx`, `cli->argc`, and `cli->argv`
> before and after any nested `runcli()` call to prevent undefined behaviour
> (notably, in token peeking utilities).

## debug mode

setting `CLI_MODE_DEBUG` to true enables all prints ezcli creates about
parsing. these are printed in blue, and formatted as `opt -> input`.
you can also add some debug-only functionality if you wrap your debug-only
code with `CLI_DEBUG_ONLY()`.

## recommendations

`CLI_MODE_RECOMMEND` (`true` by default) enables recommendations for if an unrecognized
option is seen while parsing. this doesn't print anything if no strong-enough matches
are found.

## printing utility with colored output

not every warning, error, and hint can be printed by ezcli because it can't
know the bounds of your program. that's why you can use the `cliprint` function
provided in `include/ezcli.h` to print hints, warnings, and errors with colored
outputs, and custom prefixes. it also works like printf meaning that it can
take percent sign (%) formats.

```c
void cliprint(print_e type, char *prefix, char *fmt, ...);
```

## taking yes/no inputs

99 times out of 100, you will need to take a `[y/n]?` type of input in your
command line interface program. so, why write the dreaded `scanf/fgets` and
`if input == 'y' do stuff` implementations for the one thousandth time? you
can use the `askbinary()` utility provided in `include/ezcli.h` to automatically
validate your inputs, parse them, and throw an error/continue based on your
preference.

```c
bool askbinary(char *msg, char **yes_aliases, char **no_aliases,
               bool is_no_inclusive);
```

## accessing tokens with ease

for accessing the tokens that come before and after the currently parsed token,
you can use the `gettok_prev()`, `gettok_next()`, and `gettok_offset()` functions.

```c
char *gettok_prev(cli_s *cli);

char *gettok_next(cli_s *cli);

char *gettok_offset(cli_s *cli, int n);
```

note that passing `CLI_TOK_FIRST` and `CLI_TOK_LAST` to `int n` in `gettok_offset()`
will get you the absolute first or last token respectively. otherwise, it's always
relative to the current token.

these require your cli instance to be passed on to the context of which option
you will use them for.
