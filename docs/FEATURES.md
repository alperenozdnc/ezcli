# features

## expandable option types (wut?)

the number of leading hyphens for an option depends on an enum value you
set yourself (either `OPTION_BARE`, `OPTION_SINGLE` or `OPTION_DOUBLE`).
i believe this is prettier than just including the hyphens in the
option definition.

## options are context-aware behaviour containers

not only can you define what an option does, but you can optionally pass
context down to it. this means you can share state, set configurations with flags,
define your own parsing methods, inject context based on input, and even more.

## dynamic option definitions

you can add new options with the `addopt` function
(and obviously remove with `delopt`). this enables you to make programs that
have user defined commands (and have those user-defined commands persist across sessions),
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
if you do though, any program that is ran with argc=0, argv={} immediately calls
this default option behaviour. this can also take context, which would make
totally weird ideas like a program that increments a certain number in a file
by just being ran. let's say the program is named 'sum' and you do,
`sum set num.txt`, and `sum` 5 times and you could see 5 in `num.txt`. this
obviously isn't something that's viable, or usable looking from a ux perspective,
but it just goes to show the flexibility and unopinionated-ness of ezcli.

## injectable runner

the `runcli(int argc, char *argv[])` function doesn't care about the source of
the arguments, so you can inject any arguments you want. this allows for creation
of interactive cli's, and maybe even might make ezcli kind of a 'programming interface'.
you could do recursion, calculations, and other weird things you don't expect a cli
library to be able to do.
