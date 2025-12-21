#include <test/sanity.h>

#include <ezcli.h>
#include <ezcli/platform.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

#include "internal/assert.h"
#include "internal/check_alloc.h"
#include "internal/join_str.h"
#include "internal/match.h"

/*
 * reads any subdirectory to the filesystem sane snapshot.
 */
char **read_sane_dir(char *dirname) {
    struct dirent *dir_entry;

    char *blacklist[] = {".", "..", NULL};

    char *actual_path = join_str(SANE_DIR, dirname);

    DIR *dir = opendir(actual_path);
    _assert(dir, "directories passed to read_sane_dir() must exist.");

    size_t len = 0;

    // +1 for entry and +1 for NULL pointer
    char **entries = malloc(sizeof(char *));
    CHECK_ALLOC(entries);

    while (true) {
        dir_entry = readdir(dir);

        if (!dir_entry)
            break;

        if (match_str(blacklist, dir_entry->d_name)) {
            continue;
        }

        entries[len] = strdup(dir_entry->d_name);

        // +1 for entry and +1 for NULL pointer
        len++;
        entries = realloc(entries, sizeof(char *) * (len + 1));
    }

    entries[len] = NULL;

    closedir(dir);

    free(actual_path);

    _assert(len >= 1, "there should be at least one reference to run.");

    return entries;
}

/*
 * reads and returns only the first line from a file.
 */
char *file_read_first_line(char *filename) {
    char *path = join_str(SANE_DIR, filename);

    FILE *fptr = fopen(path, "r");

    _assert(fptr, "files passed to file_read_first_line() must exist.");

    char buf[BUF_SIZE];
    size_t buf_idx = 0;

    while (true) {
        char c = fgetc(fptr);

        if (c == '\n' || c == EOF)
            break;

        buf[buf_idx++] = c;
    }

    buf[buf_idx] = '\0';

    _assert(buf_idx > 0,
            "a first line must exist to read in file_read_first_line().");

    fclose(fptr);

    free(path);

    return strdup(buf);
}

/*
 * reads content from a file stream and concatenates them into a single large
 * string.
 */
char *file_read_content(FILE *fptr, bool include_newlines) {
    char buf[BUF_SIZE];
    size_t buf_idx = 0;

    char *content = malloc(STR_SIZE(0));
    CHECK_ALLOC(content);
    content[0] = '\0';

    size_t lines_size = 0;

    while (true) {
        char c = fgetc(fptr);

        if (c == '\n' || c == EOF) {
            if (c == '\n' && include_newlines)
                buf[buf_idx++] = c;

            buf[buf_idx] = '\0';
            buf_idx = 0;

            size_t buf_len = strlen(buf);

            lines_size += buf_len;
            content = realloc(content, STR_SIZE(lines_size));
            strcat(content, buf);

            if (c == EOF)
                break;

            continue;
        }

        buf[buf_idx++] = c;
    }

    content[lines_size] = '\0';

    return content;
}

/*
 * fills all fields of the sane snapshot with the correct information.
 */
sane_dir_s *compile_sane_state() {
    sane_dir_s *sane_dir = malloc(sizeof(*sane_dir));
    CHECK_ALLOC(sane_dir);

    char **ref_filenames = read_sane_dir(BIN_DIR);

    sane_dir->ref_vers = file_read_first_line(REF_VERS_FILE);
    sane_dir->refs_count = 0;
    sane_dir->refs = malloc(REF_SIZE(1));

    while (ref_filenames[sane_dir->refs_count]) {
        size_t i = sane_dir->refs_count;

        ref_file_s *ref_file = malloc(sizeof(*ref_file));

        char *bin_path = join_str(BIN_DIR, ref_filenames[i]);
        char *input_path = join_str(INPUT_DIR, ref_filenames[i]);
        char *output_path = join_str(OUTPUT_DIR, ref_filenames[i]);

        ref_file->binary_ref = file_read_first_line(bin_path);
        ref_file->input = fopen(input_path, "r");
        ref_file->output = fopen(output_path, "r");

        free(bin_path);
        free(input_path);
        free(output_path);

        sane_dir->refs_count++;

        sane_dir->refs =
            realloc(sane_dir->refs, REF_SIZE(sane_dir->refs_count));

        sane_dir->refs[sane_dir->refs_count - 1] = ref_file;
    }

    for (size_t i = 0; i < sane_dir->refs_count; i++) {
        free(ref_filenames[i]);
    }

    free(ref_filenames);

    return sane_dir;
}

/*
 * frees all information about the sane implementation.
 */
void free_sane_state(sane_dir_s *sane_dir) {
    free(sane_dir->ref_vers);

    for (size_t i = 0; i < sane_dir->refs_count; i++) {
        ref_file_s *ref_file = sane_dir->refs[i];

        free(ref_file->binary_ref);
        fclose(ref_file->input);
        fclose(ref_file->output);

        free(ref_file);
    }

    free(sane_dir->refs);
    free(sane_dir);
}

/*
 * injects sane input into a binary reference.
 */
void exec_injected_input(ref_file_s *ref_file, char *input) {
    // $ [bin] [args] >> tmp
    char *runner_cmd_lhs = join_str(ref_file->binary_ref, " ");
    char *runner_cmd = join_str(runner_cmd_lhs, input);
    char *cmd = join_str(runner_cmd, " >> " TMP_FILENAME);

    system(cmd);

    free(runner_cmd_lhs);
    free(runner_cmd);
    free(cmd);
}

/*
 * takes all sane outputs, injects sane inputs into the binaries currently being
 * tested, and compares outputs.
 */
void test_refs_io(sane_dir_s *sane_state) {
    printf("%s\n\n", sane_state->ref_vers);

    printf("STARTING SANITY CHECK\n\n");

    size_t pass_cnt = 0;
    size_t fail_cnt = 0;

    for (size_t i = 0; i < sane_state->refs_count; i++) {
        ref_file_s *ref_file = sane_state->refs[i];

        // just for creating tmp, we read later
        FILE *new_output_fptr = fopen(TMP_FILENAME, "w");
        fclose(new_output_fptr);

        char *input_str = file_read_content(ref_file->input, true);
        size_t input_len = strlen(input_str);

        _assert(input_len > 0, "input must exist.");

        char *output_str = file_read_content(ref_file->output, false);

        char buf[BUF_SIZE];
        size_t buf_idx = 0;

        for (size_t i = 0; i < input_len; i++) {
            char c = input_str[i];

            if (c == '\n' || i == input_len - 1) {
                if (i == input_len - 1) {
                    _assert(c == '\n', "all input files must be "
                                       "newline-terminated.");
                }

                buf[buf_idx] = '\0';
                buf_idx = 0;

                if (strcmp(buf, NO_ARGS_TOKEN) == 0)
                    buf[0] = '\0';

                exec_injected_input(ref_file, buf);

                continue;
            }

            buf[buf_idx++] = c;
        }

        new_output_fptr = fopen(TMP_FILENAME, "r");

        char *new_output_str = file_read_content(new_output_fptr, false);

        if (strcmp(output_str, new_output_str) == 0) {
            cliprint(CLI_HINT, INDENT "[ PASS ] ", " %s", ref_file->binary_ref);

            pass_cnt++;
        } else {
            cliprint(CLI_ERROR, INDENT "[ FAIL ] ", " %s",
                     ref_file->binary_ref);

            fail_cnt++;
        }

        unlink(TMP_FILENAME);

        free(input_str);
        free(output_str);
        free(new_output_str);

        fclose(new_output_fptr);
    }

    printf("\nENDING SANITY CHECK\n");

    cliprint(CLI_HINT, CLI_EMPTY_PREFIX, "%ld total, %ld passed, %ld failed.",
             pass_cnt + fail_cnt, pass_cnt, fail_cnt);
}

void check_sanity() {
    sane_dir_s *sane_state = compile_sane_state();

    test_refs_io(sane_state);

    free_sane_state(sane_state);
}
