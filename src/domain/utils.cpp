/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2004  Gunter Gerhardt

    Domain Layer - Core Utilities Implementation
*/

#include "domain/utils.h"
#include "skat.h"

#include <stdio.h>
#include <stdlib.h>

// Player position utilities
int left(int s) {
    return (s + 1) % 3;
}

int right(int s) {
    return (s + 2) % 3;
}

int iscomp(int s) {
    return s >= numsp;
}

// Generic utilities
void swap(int *i, int *j) {
    int h;
    h = *i;
    *i = *j;
    *j = h;
}

// Random number generation
void setrnd(long *s, long v) {
    *s = v << 1 ? v : -1;
}

int rndval(long *s, int m) {
    register long h = *s;
    int i;

    for (i = 0; i < 7; i++)
        h = (h << 16) | ((((h << 1) ^ (h << 4)) >> 16) & 0xffff);
    *s = h;
    return h & m;
}

int rnd(int m) {
    return rndval(&seed[1], m);
}

// Error handling
void synerr(FILE* f, char* s) {
    int c, l, n;

    fprintf(stderr, "Error in file %s", game_file);
    if (feof(f))
        fputs(": unexpected EOF\n", stderr);
    else {
        fprintf(stderr, " reading: '%s'\n", s);
        fputs("before:\n", stderr);
        l = 3;
        n = 200;
        while (l && n) {
            if ((c = fgetc(f)) == EOF)
                l = 0;
            else {
                if (c == '\n') l--;
                n--;
                fputc(c, stderr);
            }
        }
    }
    fclose(f);
    game_file = 0;
}

// exitus() is defined in ui/xio.c (handles IRC cleanup)