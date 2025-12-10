#include <ezcli.h>
#include <stdio.h>

#include <ezdocs/version.h>

ret_e _version(CLI_IGNORE_ARGS) {
    printf("ezcli current version -> v%s\n", CLI_STRING_V);
    printf("YOU can definitely help that go up.\n");

    return RET_NORMAL;
}

void _version_add(cli_s *cli) {
    static char *version_aliases[] = {"version", "--version", "-v", NULL};
    static opt_s version = {.aliases = version_aliases,
                            .body = _version,
                            .desc = "version of ezcli."};

    addopt(cli, &version);
}
