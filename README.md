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

### contributing

i accept any kind of feedback as a contribution. here are some ways though;
- opening an issue talking about something in (or not in) ezcli you don't like.
- forking ezcli and opening a pull request.
- tossing a star.

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
