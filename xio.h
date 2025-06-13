
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

// #include <X11/Xlib.h>
// #include <X11/Xutil.h>
#include <SDL2/SDL.h> // Ensure SDL.h is included
#include <SDL2/SDL_image.h> // For IMG_LoadTexture_RW etc.
#include <SDL2/SDL_ttf.h> // For SDL_ttf

#include "text.h"

extern tx_typ tspnames[3][2];
extern int charw[3], charh[3];
extern int lost[3];
// extern Display* dpy[3];
// extern Colormap cmap[3]; // Already commented in xio.c, ensure consistency
// extern Window win[3];
extern SDL_Window* g_sdlWindow;
extern SDL_Renderer* g_sdlRenderer;

// SDL Color definitions
extern SDL_Color g_colorBlack, g_colorWhite, g_colorRed, g_colorGreen, g_colorBlue; // Basic colors
extern SDL_Color g_colorFg, g_colorBg, g_colorBt; // Game specific colors (foreground, background, button)

extern unsigned long bpix[3], wpix[3], fgpix[3], bgpix[3], btpix[3]; // These might be replaced by SDL_Color later
extern unsigned long b3dpix[3], w3dpix[3], mkpix[3]; // These might be replaced by SDL_Color later
extern int gfx3d[3]; // Game logic, keep
// extern GC gc[3], gcbck[3], gcxor[3]; // X11 Graphics Context
// extern XFontStruct* dfont[3]; // X11 Font structure - Replaced by g_font
extern TTF_Font* g_font; // Global font
extern int ggcards; // Game logic, keep
// extern Pixmap bck[3]; // X11 Pixmap - Background will be handled by renderer clear or specific texture
// extern Pixmap symbs[3]; // X11 Pixmap - Symbols will need new SDL_Texture handling
// extern Pixmap cardpx[3][33]; // X11 Pixmap - Replaced by g_cardTextures
extern SDL_Texture* g_cardTextures[33]; // Global array for card textures
// extern Cursor cursor[3][2]; // X11 Cursor
extern int actbtn[3]; // Game logic (related to button state), keep for now
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
extern int geom_f[3], geom_x[3], geom_y[3]; // Related to XParseGeometry, may remove later
extern int colerr; // X11 color error flag
// extern XSizeHints szhints[3]; // X11 window size hints
// extern XWMHints wmhints; // X11 window manager hints

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
extern struct DeskData desk[3]; // Game layout, keep

// extern XColor color[3][256]; // X11 Color structure array
extern int cnts[];
extern int bigs[];
extern int smls[];
extern int smlz[];
extern int smlc[];
extern int frm[2][9][2];
extern int ramp[4][6];

extern void change_gc();
extern void change_gcbg();
extern void change_gcxor();
extern int istrue();
extern void v_gtextnc();
extern void v_gtextc();
extern void v_gtext();
extern void clr_text();
extern void b_text();
extern void do_msaho();
extern void draw_skat();
extern void home_skat();
extern void nimm_stich();
extern void drop_card();
extern int query_err();
extern int closest_col();
extern unsigned long get_col();
extern void calc_desk();
extern void extractnam();
extern void extractnamln();
extern void usage();
extern void invopt();
extern void nomem();
extern void finish();
extern int ioerr();
extern void exitus();
extern void startirc();
extern int getdeffn();
extern void logit();
extern int getcode();
extern void decompgif();
extern void drawimg();
extern void create_card();
extern void xinitwin();
extern void xinitplayers();
extern void sdl_fill_rect(int x, int y, int w, int h, SDL_Color color);
extern void sdl_draw_rect(int x, int y, int w, int h, SDL_Color color);
extern int closecol();
extern void find_cardcol();
extern void card_colors();
extern void xinitres();
extern void xstoreres();
extern void read_cards();
extern void set_conames();
extern void xinit();
extern void waitt();
extern void stdwait();
extern void backgr();
extern void putdesk();
extern void drawcard();
extern void putcard();
extern void putback();
extern void hint_line();
extern void show_hint();
extern void putamark();
extern void putmark();
extern void remmark();
extern void movecard();
extern void homecard();
extern void givecard();
extern void initscr();
extern void spielendscr();
extern void revolutionsort();
extern void revolutionscr();
extern void clr_desk();
extern void draw_box();
extern void put_box();
extern void rem_box();
extern void inv_box();
extern void put_fbox();
extern void rem_fbox();
extern void inv_fbox();
extern int card_at();
extern int hndl_reizen();
extern int hndl_druecken();
extern int hndl_tauschen();
extern int hndl_spielen();
extern int hndl_nimmstich();
extern int hndl_button();
extern void setcurs();

#endif /* XIO_H */
