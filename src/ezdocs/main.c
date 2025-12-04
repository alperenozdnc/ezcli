#include <ezcli.h>

#include "main.h"

#include "func/cleanup.h"
#include "func/get_entries.h"
#include "opts/entries.h"
#include "opts/section_categorizer.h"
#include "opts/version.h"
#include "utils/join_str.h"

#include <stdlib.h>

int main(int argc, char *argv[]) {
    cli_s cli;

    initcli(&cli, "ezdocs",
            "this program is a cli documentation for ezcli.\nyou should "
            "probably start with 'ezdocs entrypoint'.",
            "[concept]",
            "for source code, visit <https://github.com/alperenozdnc/ezcli>\n",
            (opt_s *[]){NULL}, CLI_ALIASES("help", "--help", "-h"));

    _section_categorizer_add(&cli);
    _version_add(&cli);

    char *HOME = getenv("HOME");
    char *entries_path = join_str(HOME, LOCAL_EZCLI_DIR);
    char **entries = get_entries(entries_path);

    _entry_opts_add(entries_path, entries, &cli);

    runcli(&cli, argc, argv);

    cleanup(&cli, entries_path, entries);
}
