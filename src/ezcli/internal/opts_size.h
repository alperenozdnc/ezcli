#ifndef EZCLI_OPTS_SIZE_H
#define EZCLI_OPTS_SIZE_H

#define opts_size(x) (sizeof(struct opt *)) * (x) + sizeof(NULL)

#endif
