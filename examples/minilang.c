/*
  note that this 'example' is probably too convoluted and single-file
  for me to ensure you've read it.

  this is more of a proof of concept that ezcli is only opinionated about
  its own implementation and implementation-agnostic any other place.

  the point is, you can make a mini interpreter that implements pseudo-
  recursion, functions, and variables, using a CLI LIBRARY!

  yeah, you shouldn't use ezcli for projects like this, but isn't it cool?
*/

#include <ezcli.h>

// you obviously can't use internal headers on a normal project
// but since this is an example, i absolutely can and i will
#include "internal/match.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGV_SIZE(n) sizeof(char *) * (n + 1)
#define BODY_SIZE(n) ARGV_SIZE(n)
#define FUNCTIONS_SIZE(n) sizeof(func_s *) * (n + 1)
#define BUF_SIZE(n) sizeof(char) * (n + 1)

char *KEYWORDS[] = {"func",      "end",       "print", "exec", "def",
                    "increment", "decrement", "=",     NULL};

typedef struct {
    int argc;
    char **argv;
} cmd_info_s;

typedef struct {
    char *name;

    int body_len;
    cmd_info_s **body;
} func_s;

typedef struct {
    char *name;
    int value;
} variable_s;

typedef struct {
    bool func_mode;

    int funcs_len;
    int variables_len;

    func_s *current_func;
    func_s **functions;

    variable_s *current_variable;
    variable_s **variables;
} interpreter_state_s;

typedef struct {
    cli_s *cli;
    interpreter_state_s *state;
    char *curr_line;
} minilang;

char **dup_argv(int argc, char **argv) {
    char **argvd = malloc(ARGV_SIZE(0));

    for (int i = 0; i < argc; i++) {
        argvd = realloc(argvd, ARGV_SIZE(i + 1));
        argvd[i] = strdup(argv[i]);
    }

    argvd[argc] = NULL;

    return argvd;
}

void free_argv(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        free(argv[i]);
    }

    free(argv);
}

cmd_info_s *get_info(char *cmd) {
    cmd_info_s *info = malloc(sizeof(cmd_info_s));
    size_t len = strlen(cmd);

    int argc = 0;
    int buf_idx = 0;

    char **argv = malloc(ARGV_SIZE(argc));
    char *buffer = malloc(BUF_SIZE(buf_idx));

    for (size_t i = 0; i < len; i++) {
        char c = cmd[i];

        if (i == len - 1) {
            if (c == ' ') {
                free(buffer);
                break;
            }

            buffer = realloc(buffer, BUF_SIZE(buf_idx + 1));
            buffer[buf_idx] = c;
            buf_idx++;

            buffer[buf_idx] = '\0';

            argc++;
            argv = realloc(argv, ARGV_SIZE(argc));
            argv[argc - 1] = strdup(buffer);

            free(buffer);

            break;
        }

        if (c == ' ') {
            if (i == 0 || cmd[i - 1] == ' ')
                continue;

            buffer[buf_idx] = '\0';

            argc++;
            argv = realloc(argv, ARGV_SIZE(argc));
            argv[argc - 1] = strdup(buffer);

            buf_idx = 0;

            free(buffer);
            buffer = malloc(BUF_SIZE(buf_idx));

            continue;
        }

        buffer = realloc(buffer, BUF_SIZE(buf_idx + 1));
        buffer[buf_idx] = c;
        buf_idx++;
    }

    argv[argc] = NULL;

    info->argc = argc;
    info->argv = argv;

    return info;
}

void free_info(cmd_info_s *info) {
    free_argv(info->argc, info->argv);
    free(info);
}

void free_variable(variable_s *var) {
    free(var->name);
    free(var);
}

void free_variables(interpreter_state_s *state) {
    for (int i = 0; i < state->variables_len; i++) {
        variable_s *var = state->variables[i];

        free_variable(var);
    }

    free(state->variables);
}

ret_e prompt(void *ctx, CLI_IGNORE_TOK) {
    minilang *lang = ctx;

    cli_s *cli = lang->cli;
    interpreter_state_s *state = lang->state;

    int argcd = cli->argc;
    char **argvd = dup_argv(cli->argc, cli->argv);

    while (true) {
        if (state->func_mode) {
            printf("[%s()] ", state->current_func->name);
        } else {
            printf("minilang > ");
        }

        char buffer[512];

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            cliprint(CLI_ERROR, "minilang: ", "failed to get input. aborting.");

            return RET_FAIL;
        }

        // fgets includes the \n for when return is pressed
        size_t trim_len = strcspn(buffer, "\n");
        buffer[trim_len] = '\0';

        if (strcmp(buffer, "exit") == 0) {
            printf("bye. \n");

            free_argv(argcd, argvd);
            free_variables(state);

            return RET_NORMAL;
        }

        if (strlen(buffer) <= 0)
            continue;

        // + 1 is for space after cmd name
        size_t injection_len = strlen(cli->cmd) + strlen(buffer) + 1;

        // + 1 is for null
        char *cmd_injected_buffer = malloc(sizeof(char) * (injection_len + 1));

        snprintf(cmd_injected_buffer, injection_len + 1, "%s %s", cli->cmd,
                 buffer);

        cmd_info_s *info = get_info(cmd_injected_buffer);
        free(cmd_injected_buffer);

        if (state->func_mode && strcmp(buffer, "end") != 0) {
            state->current_func->body_len++;
            state->current_func->body =
                realloc(state->current_func->body,
                        BODY_SIZE(state->current_func->body_len));

            state->current_func->body[state->current_func->body_len - 1] = info;
            state->current_func->body[state->current_func->body_len] = NULL;

            continue;
        }

        lang->curr_line = buffer;
        runcli(cli, info->argc, info->argv);
        lang->curr_line = NULL;

        cli->argc = argcd;
        cli->argv = argvd;

        free_info(info);
    }

    return RET_NORMAL;
}

void test_info(cmd_info_s *info, char *cmd) {
    size_t separator_len = strlen("-----  -----");
    int cmd_len = strlen(cmd) - separator_len;

    printf("----- %*s -----\n", cmd_len, cmd);

    printf("argc indexing\n");
    printf("argc = %d\n", info->argc);
    printf("-------------\n\n");

    for (int i = 0; i < info->argc; i++) {
        printf("%d ", i);
        fflush(stdout);

        printf("%s, len = %ld\n", info->argv[i], strlen(info->argv[i]));
    }

    printf("\nnull indexing\n");
    printf("-------------\n\n");

    int i = 0;

    while (info->argv[i]) {
        printf("%d ", i);
        fflush(stdout);

        printf("%s, len = %ld\n", info->argv[i], strlen(info->argv[i]));
        i++;
    }

    printf("\n--------------------------------\n\n");
}

func_s *init_func(interpreter_state_s *state, char *func_name) {
    func_s *func = malloc(sizeof(func_s));

    func->name = strdup(func_name);
    func->body_len = 0;
    func->body = malloc(BODY_SIZE(func->body_len));
    func->body[0] = NULL;

    state->funcs_len++;

    state->functions =
        realloc(state->functions, FUNCTIONS_SIZE(state->funcs_len));

    state->functions[state->funcs_len - 1] = func;
    state->functions[state->funcs_len] = NULL;

    return func;
}

void free_func(func_s *func) {
    int j = 0;

    free(func->name);

    while (func->body[j]) {
        free_info(func->body[j]);

        j++;
    }

    free(func->body);
    free(func);
}

void free_functions(interpreter_state_s *state) {
    for (int i = 0; i < state->funcs_len; i++) {
        func_s *func = state->functions[i];

        free_func(func);
    }
}

ret_e _keyword_func(void *ctx, char *func_name) {
    if (match_str(KEYWORDS, func_name)) {
        cliprint(CLI_ERROR, "minilang: ",
                 "function can't be named '%s' because it's a keyword.",
                 func_name);

        return RET_FAIL;
    }

    interpreter_state_s *state = ctx;

    if (state->func_mode) {
        cliprint(CLI_ERROR, "minilang: ", "already inside a function.",
                 func_name);

        return RET_FAIL;
    }

    func_s *func = init_func(state, func_name);

    state->func_mode = true;
    state->current_func = func;

    return RET_NORMAL;
}

ret_e _keyword_end(void *ctx, CLI_IGNORE_TOK) {
    interpreter_state_s *state = ctx;

    state->func_mode = false;
    state->current_func = NULL;

    return RET_NORMAL;
}

ret_e _keyword_exec(void *ctx, char *func_name) {
    minilang *lang = ctx;

    interpreter_state_s *state = lang->state;
    cli_s *cli = lang->cli;

    bool did_exec = false;

    for (int i = 0; i < state->funcs_len; i++) {
        func_s *func = state->functions[i];

        if (strcmp(func->name, func_name) != 0)
            continue;

        did_exec = true;

        for (int j = 0; j < func->body_len; j++) {
            cmd_info_s *info = func->body[j];

            runcli(cli, info->argc, info->argv);
        }
    }

    if (!did_exec) {
        cliprint(CLI_ERROR, "minilang: ", "undefined function '%s'", func_name);

        return RET_FAIL;
    }

    return RET_NORMAL;
}

ret_e _keyword_print(void *ctx, char *content) {
    interpreter_state_s *state = ctx;

    for (int i = 0; i < state->variables_len; i++) {
        variable_s *var = state->variables[i];

        if (strcmp(var->name, content) != 0)
            continue;

        printf("%d\n", var->value);

        return RET_NORMAL;
    }

    for (int i = 0; i < state->funcs_len; i++) {
        func_s *func = state->functions[i];

        if (strcmp(func->name, content) != 0)
            continue;

        printf("[function %s()]\n", func->name);

        return RET_NORMAL;
    }

    printf("%s\n", content);

    return RET_NORMAL;
}

ret_e _keyword_def(void *ctx, char *name) {
    interpreter_state_s *state = ctx;

    variable_s *var = malloc(sizeof(variable_s));

    var->name = strdup(name);
    var->value = -1;

    state->variables_len++;
    state->variables = realloc(state->variables,
                               sizeof(variable_s) * (state->variables_len + 1));

    state->variables[state->variables_len - 1] = var;
    state->variables[state->variables_len] = NULL;

    state->current_variable = var;

    return RET_NORMAL;
}

ret_e _keyword_equals(void *ctx, char *value) {
    interpreter_state_s *state = ctx;

    bool special_value = false;

    for (int i = 0; i < state->variables_len; i++) {
        variable_s *var = state->variables[i];

        if (strcmp(var->name, value) != 0)
            continue;

        special_value = true;

        state->current_variable->value = var->value;

        return RET_NORMAL;
    }

    if (!special_value)
        state->current_variable->value = atoi(value);

    state->current_variable = NULL;

    return RET_NORMAL;
}

ret_e _keyword_increment(void *ctx, char *variable) {
    interpreter_state_s *state = ctx;

    bool added = false;

    for (int i = 0; i < state->variables_len; i++) {
        variable_s *var = state->variables[i];

        if (strcmp(var->name, variable) != 0)
            continue;

        added = true;
        var->value++;
        break;
    }

    if (!added) {
        cliprint(CLI_ERROR, "minilang: ", "that variable doesn't exist.");

        return RET_FAIL;
    }

    return RET_NORMAL;
}

ret_e _keyword_decrement(void *ctx, char *variable) {
    interpreter_state_s *state = ctx;

    bool subtracted = false;

    for (int i = 0; i < state->variables_len; i++) {
        variable_s *var = state->variables[i];

        if (strcmp(var->name, variable) != 0)
            continue;

        subtracted = true;
        var->value--;
        break;
    }

    if (!subtracted) {
        cliprint(CLI_ERROR, "minilang: ", "that variable doesn't exist.");

        return RET_FAIL;
    }

    return RET_NORMAL;
}

interpreter_state_s init_interpreter_state() {
    static interpreter_state_s state = {};

    state.funcs_len = 0;
    state.func_mode = false;
    state.functions = malloc(FUNCTIONS_SIZE(0));

    return state;
}

void free_interpreter_state(interpreter_state_s *state) {
    free_functions(state);
    free(state->functions);
}

int main(int argc, char *argv[]) {
    cli_s cli;

    minilang lang = {};
    interpreter_state_s state = init_interpreter_state();

    lang.cli = &cli;
    lang.state = &state;

    opt_s init = {
        .aliases = CLI_ALIASES(CLI_DEFAULT_OPT), .body = prompt, .ctx = &lang};

    opt_s placeholder_default = {.aliases =
                                     CLI_ALIASES("(when run with no options)"),
                                 .body = prompt,
                                 .ctx = &lang,
                                 .desc = "starts the interpreter."};

    opt_s keyword_func = {.aliases = CLI_ALIASES("func"),
                          .want_input = true,
                          .desc = "defines a function.",
                          .body = _keyword_func,
                          .ctx = &state};

    opt_s keyword_end = {.aliases = CLI_ALIASES("end"),
                         .want_input = false,
                         .desc = "defines the ending of a function.",
                         .body = _keyword_end,
                         .ctx = &state};

    opt_s keyword_exec = {.aliases = CLI_ALIASES("exec"),
                          .want_input = true,
                          .desc = "executes a function.",
                          .body = _keyword_exec,
                          .ctx = &lang};

    opt_s keyword_def = {.aliases = CLI_ALIASES("def"),
                         .want_input = true,
                         .desc = "sets the name of a variable to be defined.",
                         .body = _keyword_def,
                         .ctx = &state};

    opt_s keyword_print = {.aliases = CLI_ALIASES("print"),
                           .want_input = true,
                           .desc = "prints text.",
                           .body = _keyword_print,
                           .ctx = &state};

    opt_s keyword_equals = {.aliases = CLI_ALIASES("="),
                            .want_input = true,
                            .desc =
                                "sets the value of a variable to be defined.",
                            .body = _keyword_equals,
                            .ctx = &state};

    opt_s keyword_increment = {.aliases = CLI_ALIASES("increment"),
                               .want_input = true,
                               .desc = "increases value of a variable by one.",
                               .body = _keyword_increment,
                               .ctx = &state};

    opt_s keyword_decrement = {.aliases = CLI_ALIASES("decrement"),
                               .want_input = true,
                               .desc = "decreases value of a variable by one.",
                               .body = _keyword_decrement,
                               .ctx = &state};

    initcli(&cli, "minilang",
            "a very minimal 'programming language' written in ezcli",
            "[operation] [value]", "code present in src/examples/minilang.c\n",
            (opt_s *[]){&init, &placeholder_default, &keyword_func,
                        &keyword_end, &keyword_exec, &keyword_print,
                        &keyword_def, &keyword_equals, &keyword_increment,
                        &keyword_decrement, NULL},
            CLI_ALIASES("help", "--help"));

    runcli(&cli, argc, argv);

    free_interpreter_state(&state);

    return 0;
}
