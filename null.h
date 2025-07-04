
/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2000  Gunter Gerhardt

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

#ifndef NULL_H
#define NULL_H

#undef EXTERN
#ifdef NULL_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int wirftabfb[4], hattefb[4], aussplfb[4], nochinfb[4];
EXTERN int naussplfb[3];

extern void init_null();
extern void testnull();
extern int kleiner_w();
extern int kleiner();
extern int hat();
extern int n_anwert();
extern int n_anspiel();
extern int n_abwert();
extern int n_abwerfen();
extern int minmax();
extern int minmaxfb();
extern int drunter();
extern int drunterdrue();
extern void m_nsp();
extern void m_nns();
extern void null_stich();
extern void null_sort();
extern int null_dicht();
extern void revolutiondist();

#endif /* NULL_H */
