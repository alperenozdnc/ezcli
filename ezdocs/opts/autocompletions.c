#include <ezcli.h>

#include "internal/join_str.h"
#include "internal/match.h"

#include <ezdocs/autocompletions.h>

#include <stdlib.h>

ret_e _autocompletions(void *ctx, CLI_IGNORE_TOK) {
    cli_s *cli = ctx;

    char *HOME = getenv("HOME");
    char *SHELL = getenv("SHELL");

    if (!SHELL) {
        cliprint(CLI_ERROR, "ezdocs: ",
                 "$SHELL environment variable not found. please define it or "
                 "generate autocompletions for ezdocs yourself by doing "
                 "genautocomp().");

        return RET_FAIL;
    }

    bool bash = match_str_contains(SHELL, "bash");
    bool zsh = match_str_contains(SHELL, "zsh");

    if (!bash && !zsh) {
        cliprint(CLI_WARN, "ezdocs: ",
                 "your shell is not supported yet. ezdocs won't have "
                 "autocompletions.");

        return RET_WARN;
    }

    genautocomp(cli, "ezdocs", bash, zsh);

    if (bash) {
        char *lhs = join_str("install -D ", "ezdocs.bash ");
        char *rhs = join_str(HOME, AUTOCOMPLETIONS_PATH_BASH);
        char *cmd = join_str(lhs, rhs);

        system(cmd);
        system("rm ezdocs.bash");

        free(lhs);
        free(rhs);
        free(cmd);

        cliprint(CLI_HINT, "ezdocs: ",
                 "successfully installed autocompletions for bash.");
    } else {
        char *lhs = join_str("install -D ", "ezdocs.zsh ");
        char *rhs = join_str(HOME, AUTOCOMPLETIONS_PATH_ZSH);
        char *cmd = join_str(lhs, rhs);

        system(cmd);
        system("rm ezdocs.zsh");

        free(lhs);
        free(rhs);
        free(cmd);

        cliprint(CLI_HINT,
                 "ezdocs: ", "successfully installed autocompletions for zsh.");
    }

    return RET_NORMAL;
}

void _autocompletions_add(cli_s *cli) {
    opt_s autocompletions = {
        .aliases = CLI_ALIASES("autocompletions"),
        .body = _autocompletions,
        .desc = "generates autocompletions for zsh or bash.",
        .want_input = false,
        .ctx = cli,
    };

    allocopt(cli, &autocompletions);
}
