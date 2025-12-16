# changelog

## [v1.5.0](https://github.com/alperenozdnc/ezcli/releases/tag/v1.5.0) - 2025-12-16

### add

- the `cliwininfo()` utility was added for getting information about the current
  terminal window's width and height (desktop-only).
- `clicenter_horiz()`, `clicenter_vert()`, and `clicenter_both` utilities for,
  horizontally, vertically, or horizontally and vertically centering a single/multi line string.
  this only supports ASCII and does not support unicode characters yet.
- macro guards and comment notes were added for desktop-only headers and functions.

### modify

- the platform-agnostic `c_printf` implementation needed to use `vprintf()`
  internally, so that was fixed.

- some platform-agnostic headers used linux-specific libraries, so that was fixed.

## [v1.2.7](https://github.com/alperenozdnc/ezcli/releases/tag/v1.2.7) - 2025-12-14

### modify

- the embedded build mode now doesn't include examples compilation because
  examples are desktop-sided.

## [v1.2.6](https://github.com/alperenozdnc/ezcli/releases/tag/v1.2.6) - 2025-12-14

### add

- minimal interpreter example built in ezcli (why not?). supports functions, variables,
  pseudo-recursion, and incrementing/decrementing. source code available
  `src/examples/minilang.c`.
- ezdocs now generates its autocompletions.
- commands like `make install`, `make install-docs` don't require sudo for initiation
  now, they just ask for it while running.
- ezcli now has an 'embedded mode' that uses no heap allocation and no platform-
  specific libraries.
- embedded mode can be build with `make embedded` or `make debug-embedded` for
  development of the embedded mode.
- all build/teardown processes have been verified to be bijective (as in
  perfectly reversing themselves filesystem-wise).

## [v1.0.0](https://github.com/alperenozdnc/ezcli/releases/tag/v1.0.0) - 2025-12-08 - initial stable release

from now on, all public headers in `include/ezcli` will not break without a major version bump.

### add

- autocompletion generator for `bash` and `zsh`.
- `askbinary()` utility for yes/no questions.
- recommendation 'engine' that suggests options to the end user by string-distance ranking (if wrong input was given).
- pseudo-recursion support (saw 1.2 billion iterations on my computer with `src/examples/recursor.c`
- a documentation website - https://ezcli.ozdinc.org

### modify

- no more relative includes (ezdocs and internal headers now line in `include/`
- added a `make debug` build mode to the `Makefile` and now `make all` doesn't have asan.
- cleaned up documentation, optimized code, improved naming.

## [v0.7.0](https://github.com/alperenozdnc/ezcli/releases/tag/v0.7.0) - 2025-12-04

### add

- `allocopt()` utility function for heap-allocation of options.
- a lot more debugging prints if you enable `CLI_MODE_DEBUG`.
- `make install-docs` and `make uninstall-docs` for installing and uninstalling
  `ezdocs` to shell binaries.
- `opt_s` structs now have an `allocated` field that is used in `delopt()` and
  `freeopt()` to check stack/heap.
- support for 'post-common options' - these are options that are run after every
  successfully parsed option.
- `ezdocs` now inserts separators if multiple subjects are asked for.
- `specials` page in `ezdocs` explaining all special options.

### modify

- `src/examples/docs.c` is now named `ezdocs` and has its own subdirectory in `src/`.
- `ezdocs` now dynamically creates options at runtime reading from `.docs` files in `docs/docs_program/*.docs`.
- all development will now continue under `-O3` and `faddress=sanitize` to minimize/
  destroy all undefined behaviour.
- some general, non-behaviour changing refactors might have modified code.

### delete

- some general, non-behaviour changing refactors might have deleted redundant
  code.

---

## [v0.5.1](https://github.com/alperenozdnc/ezcli/releases/tag/v0.5.1) - 2025-11-30

### modify

- removed an unintended `printf()` left in the common option handler that caused
  user-visible output.

---

## [v0.5.0](https://github.com/alperenozdnc/ezcli/releases/tag/v0.5.0) - 2025-11-30

### add

- `gettok_*()` token peeking utilities.
  - `gettok_prev()` for the previous token.
  - `gettok_next()` for the next token.
  - `gettok_offset()` for getting tokens relatively.
- an example calculator-ish program.
- a header included in the public header of ezcli that reports its version.
- all options passed to `initcli()` or `addopt()` are now validated for required fields.
- `initcli()` validates the `cli_s` struct for required fields.
- `program` program seen in `docs/EXAMPLE.md` added to `src/examples/program.c`.
- a script in `scripts/examples.sh` that automatically creates aliases for all
  example programs.
- ezcli now documents itself using ezcli. code in `src/examples/docs.c`. content
  in `docs/docs_program/*.docs`.
- support for 'common options' - these are options that are run before every
  successfully parsed option.

### delete

- no default newline is printed after every opt anymore.

### modify

- renamed `extern` -> `external` for clarity.
- `examples/main.c` -> `examples/human.c` because there's more than one example now.
- `addopt()` and `delopt()` now accepts a variable amount of options.
- `delopt()` skips entirely if option doesn't exist in `cli->opts`.
- all possible code execution paths in `runcli()` have been optimized to `return`/`continue`
  as early as possible for better performance.

---

## [v0.3.0](https://github.com/alperenozdnc/ezcli/releases/tag/v0.3.0) - 2025-11-27

### add

- option definitions using `opt_s` structs
- artifically injectable command parser `runcli()`
- utility function `cliprint` for printing hints, warnings, and errors with colored output.
- context-aware options support for shared state and dynamic behaviour
- support for a default option (`CLI_DEFAULT_OPT`) when no arguments are provided
- support for non-option options (`CLI_NONOPT`) with custom behaviour
- `CLI_ALLOW_NONOPT` flag to enable non-option parsing and omit related syntax errors
- laidback mode (`CLI_MODE_LAIDBACK`) for turning all errors to warnings
- debug mode (`CLI_MODE_DEBUG`) for showing parse log during development
- alias system for options using a macro (`CLI_ALIASES()`)
- runtime option manipulation with `addopt` and `delopt`
- default, changeable help system with `help_aliases[]` and `clihelp()`
- `initcli()` and `freecli()` for starting and killing a cli instance
- example cli program demonstrating aliases, nonopts, and default options.
- comprehensive documentation including example usage, philosophy, features, and installation.
