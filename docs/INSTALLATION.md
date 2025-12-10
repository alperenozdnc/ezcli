# installation

## (1) obviously, you probably want to clone this.

```bash
% git clone https://github.com/alperenozdnc/ezcli
```

## (2) now, it's time to build.

```bash
% make all
```

this command creates the static library in `lib/` and example
executables in `build/examples/`. for easy testing of examples,
run `source ./tools/loadexamples.sh` from project root. this creates aliases
where `alias abc = ./build/examples/abc`.

you can play around with examples to kind of get
an idea on things you can create using ezcli.

## (3) and finally, the reason you're reading this section.

```bash
% make install
```

this command puts the static library file `libezcli.a` in
`/usr/local/lib` and the header file
`ezcli.h` in `/usr/local/include`.

you can now just `#include <ezcli.h>` from anywhere
if you also use flag `-lezcli` when compiling.

also, if you don't want to waste disk space,

```bash
make clean
```

removes all files the linker creates while compilation.

```bash
% make uninstall
```

you can also do this if you decide you don't like it.
