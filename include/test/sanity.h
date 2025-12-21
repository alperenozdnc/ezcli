#include <stdio.h>

#pragma once

#define SANE_DIR "./test/sane/"
#define BIN_DIR "bin/"
#define INPUT_DIR SANE_DIR "input/"
#define OUTPUT_DIR SANE_DIR "output/"
#define TMP_FILENAME "tmp"

#define REF_VERS_FILE "VERSION"
#define BUF_SIZE 256
#define STR_SIZE(n) sizeof(char) * (n + 1)

#define NO_ARGS_TOKEN "RUN_DEFAULT"

#define INDENT "    " // 4 spaces

/*
 * this is the struct that holds information about a reference source. it has a
 * sane input, output, and binary path reference.
 */
typedef struct {
    FILE *input;
    FILE *output;
    char *binary_ref;
} ref_file_s;

#define REF_SIZE(n) sizeof(ref_file_s *) * (n)

/*
 * this is the struct that defines the sane information source.
 * it holds the version of the sane snapshot, and all input and output
 * references.
 */
typedef struct {
    char *ref_vers;

    ref_file_s **refs;
    size_t refs_count;
} sane_dir_s;

/*
 * this checks ezcli for sanity. all reference outputs in `sane/` is compared
 * with the new outputs from the current ezcli implementation using reference
 * inputs.
 */
void check_sanity();
