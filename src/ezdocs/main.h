#pragma once

/*
 * template for a subject documentation option.
 */
#define DOC_OPT(alias, descr)                                                  \
    (opt_s) {                                                                  \
        .aliases = CLI_ALIASES(alias), .desc = descr, .body = doc_body,        \
        .ctx = &cli,                                                           \
    }
