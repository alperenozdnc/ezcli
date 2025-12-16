#pragma once

#include <stdarg.h>
#include <stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/*
 * for basic output. for embedded systems, these may write to uart, swo, etc.
 * for pc, these map out to their libc counterparts.
 */
int c_fprintf(void *stream, const char *restrict format, ...);
int c_vprintf(const char *restrict format, va_list ap);
int c_printf(const char *restrict format, ...);
int c_puts(const char *str);

/*
 * basic exiting function.
 * for embedded systems, this isn't defined. this usually halts or resets.
 * for pc, this maps out to libc exit().
 */
void c_exit(int status);

/*
 * basic string functions. for embedded systems, ezcli provides standalone
 * implementations. for pc, these map out to their libc counterparts.
 */
size_t c_strlen(const char *str);
int c_strcmp(const char *a, const char *b);

/*
 * memory allocation functions. for embedded systems, these don't have
 * definitions, and don't run anyways. for pc, these map out to their libc
 * counterparts.
 */
void *c_realloc(void *ptr, size_t n);
void *c_malloc(size_t n);
void c_free(void *ptr);

/*
 * function for finding the absolute value of an int.
 * for embedded systems, this is defined using a minimal implementation that
 * also handles the INT_MIN edge case. for pc, this maps out to libc abs().
 */
int c_abs(int n);
