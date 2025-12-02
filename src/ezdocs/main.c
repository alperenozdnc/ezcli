#include <ezcli.h>
#include <string.h>

#include "main.h"

#include "utils/doc_body.h"

#include "opts/section_categorizer.h"
#include "opts/version.h"

int main(int argc, char *argv[]) {
    cli_s cli;
    char *help_aliases[] = {"help", "--help", "-h", NULL};

    initcli(&cli, "ezdocs",
            "this program is a cli documentation for ezcli.\nyou should "
            "probably start with 'ezdocs entrypoint'.",
            "[concept]",
            "for source code, visit <https://github.com/alperenozdnc/ezcli>\n",
            (opt_s *[]){NULL}, help_aliases);

    opt_s doc_entry = {
        .aliases = CLI_ALIASES("entrypoint", "root"),
        .desc = "root of documentation.",
        .body = doc_body,
        .ctx = &cli,
    };

    opt_s doc_structure =
        DOC_OPT("structure", "structuring projects using ezcli.");
    opt_s doc_initcli = DOC_OPT("initcli", "initcli() core function.");
    opt_s doc_runcli = DOC_OPT("runcli", "runcli() core function.");
    opt_s doc_freecli = DOC_OPT("freecli", "freecli() core function.");
    opt_s doc_external = DOC_OPT("external", "core externals/globals.");
    opt_s doc_addopt = DOC_OPT("addopt", "addopt() utility function.");
    opt_s doc_allocopt = DOC_OPT("allocopt", "allocopt() utility function.");
    opt_s doc_delopt = DOC_OPT("delopt", "delopt() utility function.");
    opt_s doc_gettok = DOC_OPT("gettok", "gettok_*() utility functions.");
    opt_s doc_print = DOC_OPT("cliprint", "cliprint() utility function.");
    opt_s doc_special = DOC_OPT("specials", "special option behaviours.");
    opt_s doc_cli_s = DOC_OPT("cli_s", "struct cli_s.");
    opt_s doc_opt_s = DOC_OPT("opt_s", "struct opt_s.");

    _section_categorizer_add(&cli);
    _version_add(&cli);

    addopt(&cli, &doc_entry, &doc_structure, &doc_initcli, &doc_runcli,
           &doc_freecli, &doc_external, &doc_addopt, &doc_allocopt, &doc_delopt,
           &doc_gettok, &doc_print, &doc_special, &doc_cli_s, &doc_opt_s);

    runcli(&cli, argc, argv);

    freecli(&cli);
}
