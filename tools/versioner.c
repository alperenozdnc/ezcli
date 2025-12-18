#include <ezcli.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *join_str(char *str1, char *str2) {
    size_t size = strlen(str1) * strlen(str2) + sizeof('\0');

    char *str3 = malloc(size);

    snprintf(str3, size, "%s%s", str1, str2);

    return str3;
}

void get_input(char *buffer) {
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        cliprint(CLI_ERROR, "versioner > ", "error reading input.");
        exit(EXIT_FAILURE);
    }

    // fgets includes the \n for when return is pressed
    size_t trim_len = strcspn(buffer, "\n");
    buffer[trim_len] = '\0';
}

void write_commit(FILE *fptr, char *commit_name, char *version) {
    fprintf(fptr, "%s -> %s\n\n", commit_name, version);
}

ret_e body_start(CLI_IGNORE_ARGS) {
    printf("all available tags: \n\n");
    system("git tag");
    printf("\n");

    printf("versioner > which tag do you want to compare? ");

    char buffer[256];

    get_input(buffer);

    char *lhs = join_str("git log ", buffer);
    char *rhs = "...HEAD --oneline --reverse --pretty=format:'%s'";
    char *git_cmd = join_str(lhs, rhs);
    char *cmd = join_str(git_cmd, ">> /tmp/versioner_commits.txt");

    system("rm -rf /tmp/versioner_commits.txt");
    system(cmd);

    free(lhs);
    free(git_cmd);
    free(cmd);

    char commit[256];
    FILE *commits_fptr = fopen("/tmp/versioner_commits.txt", "r");
    FILE *version_file_fptr = fopen("./version.txt", "w");

    char *initial_version = strdup(buffer);
    char *curr_version = strdup(buffer);
    char tmp[256];

    int commit_count = 0;
    int bump_count = 0;

    while (fgets(commit, sizeof(commit), commits_fptr)) {
        system("clear");

        printf("versioner > current version is %s\n\n", curr_version);
        printf("commit > %s\n\n", commit);

        printf("new version or leave empty: ");

        get_input(tmp);

        if (strlen(tmp) == 0) {
            write_commit(version_file_fptr, commit, curr_version);
            commit_count++;

            continue;
        }

        free(curr_version);
        curr_version = strdup(tmp);

        write_commit(version_file_fptr, commit, curr_version);
        bump_count++;

        commit_count++;
    }

    system("clear");
    system("rm -rf /tmp/versioner_commits.txt");

    printf("versioner > %s -> %s, %d commits, %d bumps.\n", initial_version,
           curr_version, commit_count, bump_count);
    printf("versioner > all commits and their corresponding versions have been "
           "written to "
           "'version.txt' in your current directory.\n");

    free(curr_version);
    free(initial_version);

    fclose(commits_fptr);
    fclose(version_file_fptr);

    return RET_NORMAL;
}

opt_s opt_start = {
    .aliases = CLI_ALIASES(CLI_DEFAULT_OPT),
    .body = body_start,
};

int main(int argc, char *argv[]) {
    cli_s cli = {0};
    opt_s *opts[] = {&opt_start, NULL};

    initcli(&cli, "versioner", "a tool for simplifying ezcli versioning.",
            "[just run with no arguments]",
            "source code is at <https://github.com/alperenozdnc/ezcli> in "
            "directory "
            "'tools/'.\n",
            opts, CLI_ALIASES("help", "--help"));

    runcli(&cli, argc, argv);

    freecli(&cli);

    return 0;
}
