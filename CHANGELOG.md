# changelog

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
