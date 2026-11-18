#ifndef PYC_H
#define PYC_H

/* Minimal Python-inspired helpers for ordinary C17. No Python runtime. */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline void pyc_print_int(int x) { printf("%d\n", x); }
static inline void pyc_print_long(long x) { printf("%ld\n", x); }
static inline void pyc_print_double(double x) { printf("%g\n", x); }
static inline void pyc_print_bool(bool x) { puts(x ? "True" : "False"); }
static inline void pyc_print_str(const char *x) { puts(x ? x : "(null)"); }

/* Supports one argument, with automatic type-based dispatch. */
#define print(x) _Generic((x), \
    int: pyc_print_int, \
    long: pyc_print_long, \
    float: pyc_print_double, \
    double: pyc_print_double, \
    bool: pyc_print_bool, \
    char *: pyc_print_str, \
    const char *: pyc_print_str \
)(x)

/* Returns a heap-owned line without '\n', or NULL on EOF/error/OOM.
   Caller must free() the result. A blank line returns an allocated "". */
static inline char *pyc_input(const char *prompt) {
    if (prompt != NULL) {
        fputs(prompt, stdout);
        fflush(stdout);
    }
    size_t cap = 64, len = 0;
    char *s = malloc(cap);
    if (s == NULL) return NULL;
    for (;;) {
        int ch = fgetc(stdin);
        if (ch == EOF) {
            if (ferror(stdin) || len == 0) { free(s); return NULL; }
            break;
        }
        if (ch == '\n') break;
        if (len == cap - 1) {
            if (cap > SIZE_MAX / 2) { free(s); return NULL; }
            size_t newcap = cap * 2;
            char *p = realloc(s, newcap);
            if (p == NULL) { free(s); return NULL; }
            s = p;
            cap = newcap;
        }
        s[len++] = (char)ch;
    }
    s[len] = '\0';
    return s;
}

/* Declares a typed vector: Name, Name_push(), Name_free().
   Initialize with Name v = {0}. push returns false on allocation failure. */
#define PYC_VECTOR(Type, Name) \
    typedef struct { Type *items; size_t len, cap; } Name; \
    static inline void Name##_free(Name *v) { \
        free(v->items); v->items = NULL; v->len = v->cap = 0; \
    } \
    static inline bool Name##_push(Name *v, Type value) { \
        if (v->len == v->cap) { \
            size_t max_count = SIZE_MAX / sizeof(Type); \
            if (v->cap >= max_count) return false; \
            size_t newcap = v->cap ? v->cap * 2 : 8; \
            if (newcap < v->cap || newcap > max_count) newcap = max_count; \
            Type *p = realloc(v->items, newcap * sizeof(Type)); \
            if (!p) return false; \
            v->items = p; v->cap = newcap; \
        } \
        v->items[v->len++] = value; \
        return true; \
    }

#endif /* PYC_H */
