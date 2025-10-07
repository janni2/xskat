/*
    XSkat Domain Layer - Null Game Logic Header
    Copyright (C) 2000  Gunter Gerhardt

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.
*/

#ifndef DOMAIN_NULL_H
#define DOMAIN_NULL_H

// Null game state variables
extern int wirftabfb[4];
extern int hattefb[4];
extern int aussplfb[4];
extern int nochinfb[4];
extern int naussplfb[3];

// Null game functions
void init_null(void);
void testnull(int sn);
int kleiner_w(int w1, int w2);
int kleiner(int i, int j);
int hat(int i);
int n_anwert(int fb);
int n_anspiel(void);
int n_abwert(int min_fb);
int n_bedienen(void);
int n_nicht_bed(void);
int n_abwerfen(void);
int minmax(int f);
int minmaxfb(int f, int fb);
int drunter(int f);
int drunterdrue(void);
void m_nsp(void);
void m_nns(int s);
void null_stich(void);
void null_sort(int *arr, int cnt);
int null_dicht(int sn, int handsp, int *skat, int *ufb, int *mfb, int *hfb);
void revolutiondist(void);

#endif /* DOMAIN_NULL_H */