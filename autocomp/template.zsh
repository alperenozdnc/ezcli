# ezcli-generated autocompletions for zsh.

# this only supports autocompletion and cycling through options.
# if you have designed an internal subcommand system or anything
# else like that, you should extend this file.

autoload -Uz compinit
compinit

_^_completions() {
    local cur="${words[CURRENT]}"
    local -a root_words

    root_words=(
>
    )

    compadd -- "${root_words[@]}"
}

compdef _^_completions ^ 
