#include "expand.h"

#include <stdlib.h>
#include <string.h>

char *expand(struct opt *opt) {
    // enum otype directly corresponds to how much hyphens are needed
    int hyphen_len = opt->type;
    char *token = malloc(strlen(opt->name) + hyphen_len + 1);

    memset(token, '-', hyphen_len);
    token[hyphen_len] = '\0';

    strcat(token, opt->name);

    return token;
}
