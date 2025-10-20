
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

#ifndef XIO_H
#define XIO_H

#ifdef __cplusplus
extern "C" {
#endif
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#ifdef __cplusplus
}
#endif

#include "text.h"

extern tx_typ tspnames[3][2];
extern int charw[3], charh[3];
extern int lost[3];
extern Display* dpy[3];
extern Colormap cmap[3];
extern Window win[3];
extern unsigned long bpix[3], wpix[3], fgpix[3], bgpix[3], btpix[3];
extern unsigned long b3dpix[3], w3dpix[3], mkpix[3];
extern int gfx3d[3];
extern GC gc[3], gcbck[3], gcxor[3];
extern XFontStruct* dfont[3];
extern int ggcards;
extern Pixmap bck[3];
extern Pixmap symbs[3];
extern Pixmap cardpx[3][33];
extern Cursor cursor[3][2];
extern int actbtn[3];
extern int skatopen, stichopen, spitzeopen, backopen[3];
extern int ktrply, sptzmrk, schenkply;
extern int revolsort, tauschcard, tauschdone, tauschply;
extern long ticker;
extern char* prog_name;
extern char* disp_name[3];
extern char* font_name;
extern char* title[3];
extern char* fg_col;
extern char* bg_col;
extern char* b3d_col;
extern char* w3d_col;
extern char* mk_col;
extern char* bt_col;
extern char* ccol[4];
extern int nopre;
extern int bwcol;
extern int downup;
extern int altseq;
extern int geom_f[3], geom_x[3], geom_y[3];
extern int colerr;
extern XSizeHints szhints[3];
extern XWMHints wmhints;

struct SelPosEntry {
  int x1, y1, x2, y2, f;
};
struct SelPosData {
  int num, act;
  struct SelPosEntry p[21];
};
extern struct SelPosData selpos[3];

struct DeskData {
  int large;
  int x, y, w, h;
  int col, plan;
  int com1x, com2x, com1y, com2y;
  int playx, playy;
  int skatx, skaty;
  int stichx, stichy;
  int cbox1x, cbox2x, cboxy;
  int pboxx, pboxy;
  int cardx, cardw, cardh;
  int f, q;
};
extern struct DeskData desk[3];

extern XColor color[3][256];
extern int cnts[];
extern int bigs[];
extern int smls[];
extern int smlz[];
extern int smlc[];
extern int frm[2][9][2];
extern int ramp[4][6];

extern void change_gc(int sn, unsigned long fg, GC* gcp);
extern void change_gcbg(int sn, unsigned long bg, GC* gcp);
extern void change_gcxor(int sn, unsigned long fg);
extern int istrue(char* s);
extern void v_gtextnc(int sn, int n, int c, int x, int y, int w, const char* t);
extern void v_gtextc(int sn, int c, int x, int y, int w, const char* t);
extern void v_gtext(int sn, int x, int y, int w, const char* t);
extern void clr_text(int sn, int x, int y);
extern void b_text(int s, tx_typ* str);
extern void do_msaho(int sn, const char* str);
extern void draw_skat(int sn);
extern void home_skat(void);
extern void nimm_stich(void);
extern void drop_card(int i, int s);
extern int query_err(Display* d, XErrorEvent* e);
extern int closest_col(int sn, XColor* xcol);
extern unsigned long get_col(int sn, char* ucol, char* prog, char* col, char* defcol, unsigned long defpix, XColor* xcol);
extern void calc_desk(int sn);
extern void extractnam(int sn, char* str);
extern void extractnamln(int sn, char* str, int ln);
extern void usage(void);
extern void invopt(char* opt);
extern void nomem(void);
extern void finish(int sn, int ex);
extern int ioerr(Display* d);
extern void exitus(int n);
extern void startirc(int f);
extern int getdeffn(char* prog_name, char** pfn, char* res, char* suf);
extern void logit(void);
extern int getcode(int* bpos, int csiz, int msk, unsigned char* thegif);
extern void decompgif(unsigned char* thedata, unsigned char* thepic, int* themap, int cmapsize);
extern void drawimg(int sn, int c, int f, int w, int x, int y);
extern void create_card(int sn, int c);
extern void xinitwin(int sn, int argc, char** argv);
extern void xinitplayers(void);
extern int closecol(int x, int* r);
extern void find_cardcol(unsigned char* bm, int* r, unsigned long* col);
extern void card_colors(int sn);
extern void xinitres(int sn);
extern void xstoreres(void);
extern void read_cards(void);
extern void set_conames(void);
extern void xinit(int argc, char** argv);
extern void waitt(int t, int f);
extern void stdwait(void);
extern void backgr(int sn, int x, int y, int w, int h);
extern void putdesk(int sn, int x, int y);
extern void drawcard(int sn, int c, int x, int y);
extern void putcard(int sn, int i, int x, int y);
extern void putback(int sn, int x, int y);
extern void hint_line(int sn, int c, GC* gcp);
extern void show_hint(int sn, int c, int d);
extern void putamark(int sn, int s);
extern void putmark(int s);
extern void remmark(int f);
extern void movecard(int nn, int sn[], int x1[], int y1[], int x2[], int y2[]);
extern void homecard(int s, int n, int m);
extern void givecard(int s, int n);
extern void initscr(int sn, int sor);
extern void spielendscr(void);
extern void revolutionsort(int sp);
extern void revolutionscr(void);
extern void clr_desk(int nsp);
extern void draw_box(int sn, int x, int y, int w);
extern void put_box(int s);
extern void rem_box(int s);
extern void inv_box(int s, int c, int rev);
extern void put_fbox(int sn, int t);
extern void rem_fbox(int sn);
extern void inv_fbox(int sn, int rev);
extern int card_at(int sn, int x, int y, int zw);
extern int hndl_reizen(int sn, int x, int y);
extern int hndl_druecken(int sn, int x, int y);
extern int hndl_tauschen(int sn, int x, int y);
extern int hndl_spielen(int sn, int x, int y);
extern int hndl_nimmstich(int sn);
extern int hndl_button(int sn, int x, int y, int opt, int send);
extern void setcurs(int f);

#endif /* XIO_H */
