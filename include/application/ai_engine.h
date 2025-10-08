/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2004  Gunter Gerhardt

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.
*/

#ifndef APPLICATION_AI_ENGINE_H
#define APPLICATION_AI_ENGINE_H

/*
 * Application Layer - AI Engine
 * 
 * Computer player logic and decision making
 */

// Main AI coordination
extern void computer(void);
extern void do_spielen(void);

// AI strategy functions
extern int ignorieren(void);
extern int genugdrin(void);
extern int gewinnstich(int f);
extern int uebernehmen(int p, int h, int n);
extern void schmieren(void);
extern int einstechen(void);
extern int niedrighoch(int f);
extern int ueberdoerfer(void);
extern int bubeausspielen(void);
extern int trumpfausspielen(void);
extern int hochausspielen(void);
extern void schenke(void);
extern int zehnblank(int ci);
extern int fabwerfen(void);
extern void abwerfen(void);
extern int buttern(void);
extern int hatas(void);
extern int schnippeln(int f);
extern void nichtspitze(void);
extern int spitzefangen(void);
extern int restbeimir(void);

// Move calculation
extern void m_bvsp(void);
extern void m_bmsp(void);
extern void m_bhsp(void);
extern void m_bvns(void);
extern void m_bmns(void);
extern void m_bhns(void);
extern void m_bsp(void);
extern void m_bns(void);
extern void make_best(int s);

// Support functions
extern void adjfb(int s, int v);
extern void calc_drueck(void);

#endif /* APPLICATION_AI_ENGINE_H */