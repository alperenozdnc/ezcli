#pragma once

#include <stdarg.h>
#include <stddef.h>

#include <test/integrity/sig_arena_s.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int c_fprintf(void *stream, const char *restrict format, ...);
int c_vprintf(const char *restrict format, va_list ap);
int c_printf(const char *restrict format, ...);
int c_puts(const char *str);

void _c_exit(int status, sig_arena_s *arena);
#define c_exit(status) _c_exit(status, arena)

size_t c_strlen(const char *str);
int c_strcmp(const char *a, const char *b);
void *c_realloc(void *ptr, size_t n);
void *c_malloc(size_t n);
void c_free(void *ptr);
int c_abs(int n);
