#include <ezcli/platform.h>

#include <limits.h>

int c_abs(int n) {
    if (n == INT_MIN)
        return INT_MAX;

    if (n < 0)
        return -n;

    return n;
}
