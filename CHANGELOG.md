# changelog

---

## [v0.5.0](https://github.com/alperenozdnc/ezcli/releases/tag/v0.5.0) - 2025-11-27

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
