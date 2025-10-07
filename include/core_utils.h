/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2004  Gunter Gerhardt

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.

    Redistribution of modified versions is permitted
    provided that the following conditions are met:
    1. All copyright & permission notices are preserved.
    2.a) Only changes required for packaging or porting are made.
      or
    2.b) It is clearly stated who last changed the program.
         The program is renamed or
         the version number is of the form x.y.z,
         where x.y is the version of the original program
         and z is an arbitrary suffix.
*/

#ifndef CORE_UTILS_H
#define CORE_UTILS_H

/*
 * Core Game Utilities
 * 
 * Basic utility functions used across all layers.
 * These are defined in skat.c as they coordinate global game state.
 */

// Player position utilities
extern int left(int s);    // Get left player
extern int right(int s);   // Get right player  
extern int iscomp(int s);  // Check if player is computer

// Generic utilities
extern void swap(int *i, int *j);  // Swap two integers

// Random number generation
extern void setrnd(long *s, long v);
extern int rndval(long *s, int m);
extern int rnd(int m);

// Error handling
extern void exitus(int code);

/*
 * Note: These functions remain in skat.c as they often need access
 * to global game state. A future refactoring could move some of these
 * to a dedicated utils module if global state is encapsulated.
 */

#endif /* CORE_UTILS_H */