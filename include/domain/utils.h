/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2004  Gunter Gerhardt

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.
*/

#ifndef DOMAIN_UTILS_H
#define DOMAIN_UTILS_H

#include <stdio.h>

/*
 * Domain Layer - Core Utilities
 * 
 * Basic utility functions used across the domain layer
 */

// Player position utilities
extern int left(int s);
extern int right(int s);
extern int iscomp(int s);

// Generic utilities
extern void swap(int *i, int *j);

// Random number generation
extern void setrnd(long *s, long v);
extern int rndval(long *s, int m);
extern int rnd(int m);

// Error handling
extern void synerr(FILE* f, char* s);
// exitus() is declared in ui/xio.h (handles IRC cleanup)

#endif /* DOMAIN_UTILS_H */