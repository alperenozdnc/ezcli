# ezcli-generated autocompletions for bash.

# this only supports autocompletion and cycling through options.
# if you have designed an internal subcommand system or anything
# else like that, you should extend this file.

bind 'set show-all-if-ambiguous on'
bind 'TAB:menu-complete'

_^_completions() {
	local cur="${COMP_WORDS[$COMP_CWORD]}"
	local root_words="
>"

    COMPREPLY=($(compgen -W "$root_words" -- "$cur"))
}

complete -F _^_completions ^ 
