#include <ezcli.h>

#include "internal/join_str.h"

#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TMP_FILE_NAME "/tmp/versioner_commits.txt"
#define OUTPUT_FILE_NAME "version.txt"

#define clean_tmp_file() system("rm -rf " TMP_FILE_NAME)
#define build_str(...) _build_str(NULL, __VA_ARGS__, NULL)
#define clear_screen() system("clear")

#define BUF_SIZE 256

volatile sig_atomic_t sigint_seen = 0;

/*
 * small helper for concatenating a variable amount of strings.
 */
char *_build_str(void *start, ...) {
    char *ret_str = NULL;
    char *tmp = NULL;

    va_list args;
    va_start(args, start);

    while (true) {
        char *str = va_arg(args, char *);

        if (!str)
            break;

        if (!ret_str) {
            ret_str = strdup(str);

            continue;
        }

        tmp = join_str(ret_str, str);
        free(ret_str);

        ret_str = strdup(tmp);
        free(tmp);
    }

    va_end(args);

    (void)start;

    return ret_str;
}

/*
 * sets the flag `sigint_seen` to `true` if an interrupt signal is seen.
 */
void handle_sigint(__attribute((unused)) int code) {
    sigint_seen = 1;
}

/*
 * the cleanup ritual.
 */
void cleanup(FILE *file_commits, FILE *file_output, char *vers_curr,
             char *vers_initial) {
    fclose(file_commits);
    fclose(file_output);

    clear_screen();
    clean_tmp_file();

    free(vers_curr);
    free(vers_initial);
}

/*
 * aborts the program if an interrupt signal is received mid-run.
 */
void abort_loop(FILE *file_commits, FILE *file_output, char *vers_curr,
                char *vers_initial) {
    cleanup(file_commits, file_output, vers_curr, vers_initial);

    printf("versioner > aborting.\n");

    exit(EXIT_FAILURE);
}

/*
 * gets input from user and writes into `buf`. returns `true` or `false` for
 * indication of success.
 */
bool get_input(char *buf) {
    if (fgets(buf, BUF_SIZE, stdin) == NULL) {
        cliprint(CLI_ERROR, "versioner > ", "error reading input.");

        return false;
    }

    // fgets includes the \n for when return is pressed
    size_t trim_len = strcspn(buf, "\n");
    buf[trim_len] = '\0';

    return true;
}

/*
 * writes commit and its corresponding version to the output file.
 */
void commit_write(FILE *fptr, char *commit_name, char *version) {
    fprintf(fptr, "%s -> %s\n\n", commit_name, version);
}

/*
 * gets and lists available tags to reference from.
 */
void list_tags() {
    printf("versioner > all available tags: \n\n");
    system("git tag");
    printf("\n");
}

/*
 * gets the reference tag that the user wants to reference commits against.
 */
char *get_ref_tag() {
    static char buf[BUF_SIZE];

    list_tags();

    printf("versioner > which tag do you want to compare? ");

    get_input(buf);

    char *cmd = build_str("git log", " ", buf,
                          "...HEAD --oneline --reverse --pretty=format:'%s'",
                          " ", ">>", " ", TMP_FILE_NAME);

    clean_tmp_file();
    system(cmd);

    free(cmd);

    return buf;
}

/*
 * prints the current version and the next commit in the iteration.
 */
void print_curr_info(char *vers_curr, char *commit) {
    printf("versioner > current version is %s\n\n", vers_curr);
    printf("commit > %s\n\n", commit);
    printf("new version or leave empty or 'abort': ");
}

/*
 * prints the new version, amount of commits and bumps, and gives information
 * about the output file for kind of a closing 'ritual'.
 */
void print_final_info(char *vers_initial, char *vers_curr, size_t commit_cnt,
                      size_t bump_cnt) {
    printf("versioner > %s -> %s, %ld commits, %ld bumps.\n", vers_initial,
           vers_curr, commit_cnt, bump_cnt);

    printf("versioner > all commits and their corresponding versions have been "
           "written to " OUTPUT_FILE_NAME " in your current directory.\n");
}

/*
 * validates a file stream, returns `false` and prints error if it doesn't
 * exist, and just returns `true` if it does.
 */
bool validate_file(FILE *fptr, char *path) {
    if (!fptr) {
        cliprint(CLI_ERROR, "versioner > ", "couldn't read file '%s'.", path);

        return false;
    }

    return true;
}

/*
 * the main option that compiles querying, iterating, and cleanup together.
 */
ret_e body_start(CLI_IGNORE_ARGS) {
    signal(SIGINT, handle_sigint);

    char commit[BUF_SIZE];
    char tmp[BUF_SIZE];

    char *ref_tag = get_ref_tag();

    FILE *file_commits = fopen(TMP_FILE_NAME, "r");
    FILE *file_output = fopen(OUTPUT_FILE_NAME, "w");

    if (!validate_file(file_commits, TMP_FILE_NAME) ||
        !validate_file(file_output, OUTPUT_FILE_NAME)) {
        return RET_FAIL;
    }

    char *vers_initial = strdup(ref_tag);
    char *vers_curr = strdup(ref_tag);

    size_t commit_cnt = 0;
    size_t bump_cnt = 0;

    while (fgets(commit, BUF_SIZE, file_commits)) {
        clear_screen();

        print_curr_info(vers_curr, commit);

        if (!get_input(tmp))
            abort_loop(file_commits, file_output, vers_curr, vers_initial);

        if (sigint_seen)
            abort_loop(file_commits, file_output, vers_curr, vers_initial);

        if (strcmp(tmp, "abort") == 0) {
            cleanup(file_commits, file_output, vers_curr, vers_initial);

            printf("aborting.\n");

            return RET_FAIL;
        }

        if (strlen(tmp) == 0) {
            commit_write(file_output, commit, vers_curr);
            commit_cnt++;

            continue;
        }

        free(vers_curr);
        vers_curr = strdup(tmp);

        commit_write(file_output, commit, vers_curr);

        commit_cnt++;
        bump_cnt++;
    }

    if (commit_cnt == 0) {
        cleanup(file_commits, file_output, vers_curr, vers_initial);
        cliprint(CLI_ERROR, "versioner > ",
                 "no commits were found after this tag. aborting.\n");

        return RET_FAIL;
    }

    print_final_info(vers_initial, vers_curr, commit_cnt, bump_cnt);

    cleanup(file_commits, file_output, vers_curr, vers_initial);

    return RET_NORMAL;
}

opt_s opt_start = {
    .aliases = CLI_ALIASES(CLI_DEFAULT_OPT),
    .body = body_start,
};

int main(int argc, char *argv[]) {
    if (system("git --version > /dev/null 2>&1") != 0) {
        cliprint(CLI_ERROR, "versioner > ",
                 "git is required to run this program.");

        exit(EXIT_FAILURE);
    }

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
