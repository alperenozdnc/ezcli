#pragma once

#define LOCAL_EZCLI_DIR "/.local/ezdocs/"
#define DOCS_FILE_EXT ".docs"
#define DESC_DELIMITER "DESCRIPTION_END\n"

/*
 * template for a subject documentation option.
 */
#define DOC_OPT(alias, descr)                                                  \
    (opt_s) {                                                                  \
        .aliases = CLI_ALIASES(alias), .desc = descr, .body = doc_body,        \
        .ctx = &cli,                                                           \
    }
