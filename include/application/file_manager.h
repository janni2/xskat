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

#ifndef APPLICATION_FILE_MANAGER_H
#define APPLICATION_FILE_MANAGER_H

#include <stdio.h>

/*
 * Application Layer - File and Configuration Management
 * 
 * Handles file I/O, configuration persistence, and game state management
 */

// File operations and error handling
extern void synerr(FILE* f, char* s);

// Configuration management
extern void read_opt(void);
extern void save_opt(void);

// Game list and protocol management
extern void read_list(void);
extern void save_list(void);
extern void update_list(void);
extern void set_prot(void);

#endif /* APPLICATION_FILE_MANAGER_H */